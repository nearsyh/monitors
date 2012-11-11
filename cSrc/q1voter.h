#ifndef Q1VOTER_H
#define Q1VOTER_H
#include<uC++.h>
#include "q1tallyVotes.h"

class Printer;

_Task Voter {
    unsigned int id;
    TallyVotes &voteTallier;
    Printer &prt;
    void main();
  public:
	enum States { Start = 'S', Vote = 'V', Block = 'B', Unblock = 'U', Complete = 'C', Finished = 'F' };
	Voter( unsigned int id, TallyVotes &voteTallier, Printer &prt );
};

#endif
