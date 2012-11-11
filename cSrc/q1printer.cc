#include "q1printer.h"
#include<iostream>
using namespace std;

#define LOOP_PRINT(c, times) {\
    for(unsigned int i = 0; i < times; i ++)\
        cout << c;\
    cout << endl;\
}

Printer::Printer(unsigned int voters) 
    : voters(voters) {
    change = new bool[voters];
    param = new unsigned int[voters];
    states = new Voter::States[voters];
    memset(change, 0, voters*sizeof(bool));
    for(unsigned int i = 0; i < voters; i ++)
        cout << "Voter" << i << "\t";
    cout << endl;
    LOOP_PRINT("=======\t", voters);
}

Printer::~Printer( ){
    delete []change;
    delete []param;
    delete []states;
    LOOP_PRINT("=", 17);
    cout << "All tours started" << endl;
}

void Printer::printState() {
    for(unsigned int i = 0; i < voters; i ++) {
        if(change[i]) {
            cout << (char)states[i];
            if(states[i] != Voter::Start && states[i] != Voter::Complete)
                cout << " " << param[i];
        }
        cout << "\t";
        change[i] = false;
    } cout << endl;
    for(unsigned int i = 0; i < voters; i ++)
        assert(!change[i])
}

void Printer::print(unsigned int id, Voter::States state) {
    /* if the state of id has been updated before, then print the stored states */
    if(change[id]) printState();
    assert(!change[id]);
    /* store the new state */
    states[id] = state;
    change[id] = true;
}
void Printer::print(unsigned int id, Voter::States state, bool result) {
    /* if the state of id has been updated before, then print the stored states */
    if(change[id]) printState();
    assert(!change[id]);
    /* store the new state */
    states[id] = state;
    param[id] = (unsigned int)result;
    /* if the new state is finished */
    if(state == Voter::Finished) {
        for(unsigned int i = 0; i < voters; i ++)
            if(i == id) cout << "F " << param[id] << "\t";
            else cout << "..." << "\t";
        cout << endl;
    } else change[id] = true;
}
void Printer::print(unsigned int id, Voter::States state, unsigned int numBlock) {
    /* if the state of id has been updated before, then print the stored states */
    if(change[id]) printState();
    assert(!change[id]);
    /* store the new state */
    states[id] = state;
    param[id] = numBlock;
    change[id] = true;
}
