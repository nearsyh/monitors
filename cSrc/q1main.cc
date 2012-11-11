#include "q1tallyVotes.h"
#include "q1voter.h"
#include "q1printer.h"
#include "MPRNG.h"
#include<iostream>

void uMain::main() {
    int totalSize, groupSize, seed;
    totalSize = argc >= 2 ? atoi(argv[1]) : 6;
    groupSize = argc >= 3 ? atoi(argv[2]) : 3;
    seed = argc >= 4 ? atoi(argv[3]) : getpid();
    if(totalSize <= 0 || groupSize <= 0 || seed <= 0 || argc > 4 || totalSize % groupSize != 0 || groupSize % 2 == 0) {
        std::cerr << "Usage: " << argv[0] << "Voters (> 0 & V mod G = 0, default 6)  Group (> 0 & odd, default 3)  Seed (> 0)" << std::endl;
        return;
    }

    Printer prt(totalSize);
    TallyVotes tallyVotes(groupSize, prt);
    Voter *voters[totalSize];
    for(int i = 0; i < totalSize; i ++)
        voters[i] = new Voter(i, tallyVotes, prt);

    for(int i = 0; i < totalSize; i ++)
        delete voters[i];
}
