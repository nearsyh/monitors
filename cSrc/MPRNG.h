#ifndef MPRNG_H
#define MPRNG_H

_Monitor PRNG {
public:
    PRNG( unsigned int seed = 1009 ) { srand( seed ); } // set seed
    void seed( unsigned int seed ) { srand( seed ); } // set seed
    unsigned int operator()() { return rand(); } // [0,UINT MAX]
    unsigned int operator()( unsigned int u ) { return operator()() % (u + 1); } // [0,u]
    unsigned int operator()( unsigned int l, unsigned int u ) { return operator()( u - l ) + l; } // [l,u]
};

#endif
