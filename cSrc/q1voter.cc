#include "q1voter.h"
#include "q1printer.h"
#include "q1tallyVotes.h"
#include "MPRNG.h"

PRNG generator;

Voter::Voter( unsigned int id, TallyVotes &voteTallier, Printer &prt )
    : id(id), voteTallier(voteTallier), prt(prt) {}

void Voter::main() {
    prt.print(id, Start);
    yield(generator(19));
    bool ballot = generator(1) == 1;
    bool result = voteTallier.vote(id, ballot);
    prt.print(id, Finished, result);
}
