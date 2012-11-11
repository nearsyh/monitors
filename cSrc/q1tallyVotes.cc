#include "q1tallyVotes.h"
#include "q1printer.h"
#include "q1voter.h"
#include<iostream>
using namespace std;

TallyVotes::TallyVotes(unsigned int group, Printer &prt)
    : group_size(group), prt(prt) {
        assert(group%2 == 1);
        ballots = countOfTrue = 0;
#if defined( IMPLTYPE_AUTO )
        voted = 0;
#endif
    }

TallyVotes::~TallyVotes() {
    assert(ballots == 0);
}

bool TallyVotes::vote(unsigned int id, bool ballot) {
    prt.print(id, Voter::Vote, ballot);
    countOfTrue += (int)ballot;
    // ++ ballots may be moved here
#if defined( IMPLTYPE_LOCK )		// mutex/condition solution
#elif defined( IMPLTYPE_EXT )		// external scheduling monitor solution
    if(++ ballots < group_size) {
        prt.print(id, Voter::Block, ballots);
        _Accept(vote);              // forming an acceptor stack
        prt.print(id, Voter::Unblock, ballots - 1);
    } else {
        result = countOfTrue * 2 > group_size;
        countOfTrue = 0;
    }
#elif defined( IMPLTYPE_INT )		// internal scheduling monitor solution
    if(++ ballots % group_size != 0) {
        prt.print(id, Voter::Block, ballots);
        round.wait();
        prt.print(id, Voter::Unblock, ballots - 1);
        if(ballots > 1) round.signal();
    } else {
        round.signal();
        result = countOfTrue * 2 > group_size;
        countOfTrue = 0;            // duplicated
    }
#elif defined( IMPLTYPE_AUTO )		// automatic-signal monitor solution
    ++ ballots, ++ voted;
    WAITUNTIL(voted % group_size == 0, prt.print(id, Voter::Block, ballots), prt.print(id, Voter::Unblock, ballots - 1));
    if(ballots % group_size == 0) { result = countOfTrue * 2 > group_size; countOfTrue = 0; }
    ballots --;
    assert(countOfTrue == 0);
    prt.print(id, Voter::Complete);
    RETURN(result);
#elif defined( IMPLTYPE_TASK )		// internal/external scheduling task solution
    prt.print(id, Voter::Block, ++ ballots);
    round.wait();
    prt.print(id, Voter::Unblock, ballots - 1);
    if(ballots == 1) round.signal();
#else
#error unsupported voter type
#endif
    ballots --;
    assert(countOfTrue == 0);
    prt.print(id, Voter::Complete);
    return result;
}

#if defined( IMPLTYPE_TASK )
void TallyVotes::main() {
    while(true) {
        _Accept(~TallyVotes) {
            break;
        } or _When(ballots < group_size) _Accept(vote) {
            if(ballots == group_size)
                cast();
        }
    }
}

void TallyVotes::cast() {
    result = countOfTrue * 2 > group_size;  // violate dry
    countOfTrue = 0;
    for(unsigned int i = 0; i < group_size; i ++)
        round.signal();
    round.wait();
}
#endif
