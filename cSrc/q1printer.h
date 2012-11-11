#ifndef PRINTER_H
#define PRINTER_H
#include "q1voter.h"

_Monitor Printer { // chose one of the two kinds of type constructor
    unsigned int voters;
    bool *change;
    unsigned int *param;
    void printState();
    Voter::States *states;
public:
    Printer( unsigned int voters );
    ~Printer( );
	void print( unsigned int id, Voter::States state );
	void print( unsigned int id, Voter::States state, bool vote );
	void print( unsigned int id, Voter::States state, unsigned int numBlocked );
};

#endif
