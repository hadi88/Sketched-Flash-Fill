//
//  TokSeqGen.h
//  Sketched Flash Fill
//
//  Created by Hadi on 3/2/13.
//  Copyright (c) 2013 Hadi. All rights reserved.
//

#ifndef __Sketched_Flash_Fill__TokSeqGen__
#define __Sketched_Flash_Fill__TokSeqGen__

#include "includes.h"
#include "Token.h"
#include "TokSeq.h"

class TokSeqGen{
private:
    string s;
    int** start;
    int** end;
public:
    TokSeqGen(string s);
    void generate(int pos, set<TokSeq*>* leftResult, set<TokSeq*>* rightResult);
    void generateRight(int pos, set<TokSeq*>* result);
    void generateLeft(int pos, set<TokSeq*>* result);
    
    ~TokSeqGen();
};

#endif /* defined(__Sketched_Flash_Fill__TokSeqGen__) */
