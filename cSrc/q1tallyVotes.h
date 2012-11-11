#ifndef Q1TALLYVOTE_H
#define Q1TALLYVOTE_H
#include<uC++.h>
#include "AutomaticSignal.h"

class Printer;

#if defined( IMPLTYPE_LOCK )		// mutex/condition solution
// includes for this kind of vote-tallier
class TallyVotes {
 	// private declarations for this kind of vote-tallier

#elif defined( IMPLTYPE_EXT )		// external scheduling monitor solution
// includes for this kind of vote-tallier
_Monitor TallyVotes {
	// private declarations for this kind of vote-tallier

#elif defined( IMPLTYPE_INT )		// internal scheduling monitor solution
// includes for this kind of vote-tallier
_Monitor TallyVotes {
	// private declarations for this kind of vote-tallier
    uCondition round;

#elif defined( IMPLTYPE_AUTO )		// automatic-signal monitor solution
// includes for this kind of vote-tallier
_Monitor TallyVotes {
	// private declarations for this kind of vote-tallier
    AUTOMATIC_SIGNAL;
    unsigned int voted;

#elif defined( IMPLTYPE_TASK )		// internal/external scheduling task solution
_Task TallyVotes {
	// private declarations for this kind of vote-tallier
    uCondition round;
    bool finished;
    void main();
    void cast();

#else
#error unsupported voter type
#endif

	// common declarations
    unsigned int group_size, ballots, countOfTrue;
    Printer &prt;
    bool result;
  public:
	// common interface
	TallyVotes( unsigned int group, Printer &prt );
	~TallyVotes();
	bool vote( unsigned int id, bool ballot );
};

#endif
