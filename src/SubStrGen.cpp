//
//  SubStrGen.cpp
//  Sketched Flash Fill
//
//  Created by Hadi on 4/16/13.
//  Copyright (c) 2013 Hadi. All rights reserved.
//

#include "SubStrGen.h"

SubStrGen::SubStrGen(string s){
    this->s = s;
    this->posGen = new PosGen(s);
}

void SubStrGen::generateSubStr(int ks, int kf, set<SubStr*>* result){
    
}

SubStrGen::~SubStrGen(){
    delete this->posGen;
}