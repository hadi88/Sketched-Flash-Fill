//
//  SubStrGen.h
//  Sketched Flash Fill
//
//  Created by Hadi on 4/16/13.
//  Copyright (c) 2013 Hadi. All rights reserved.
//

#ifndef __Sketched_Flash_Fill__SubStrGen__
#define __Sketched_Flash_Fill__SubStrGen__

#include "includes.h"
#include "SubStr.h"
#include "PosGen.h"

class SubStrGen{
private:
    string s;
    PosGen* posGen;
public:
    SubStrGen(string s);
    void generateSubStr(int ks, int kf, set<SubStr*>* result);
    ~SubStrGen();
};

#endif /* defined(__Sketched_Flash_Fill__SubStrGen__) */
