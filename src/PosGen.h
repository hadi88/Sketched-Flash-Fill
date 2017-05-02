//
//  PosGen.h
//  Sketched Flash Fill
//
//  Created by Hadi on 3/2/13.
//  Copyright (c) 2013 Hadi. All rights reserved.
//

#ifndef __Sketched_Flash_Fill__PosGen__
#define __Sketched_Flash_Fill__PosGen__

#include "includes.h"
#include "TokSeqGen.h"
#include "RPos.h"
#include "CPos.h"

class PosGen{
private:
    string s;
    TokSeqGen* tokSeqGen;
public:
    PosGen(string s);
    void generatePos(int k, set<Position*>* result);
    ~PosGen();
};

#endif /* defined(__Sketched_Flash_Fill__PosGen__) */

