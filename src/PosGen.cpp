//
//  PosGen.cpp
//  Sketched Flash Fill
//
//  Created by Hadi on 3/2/13.
//  Copyright (c) 2013 Hadi. All rights reserved.
//

#include "PosGen.h"

PosGen::PosGen(string s){
    this->s = s;
    this->tokSeqGen = new TokSeqGen(s);
}

void PosGen::generatePos(int k, set<Position*>* result){
    //result->insert(new CPos(s, k));
    //cout << endl;
    set<TokSeq*> tokSeqLeft;
    set<TokSeq*> tokSeqRight;

    tokSeqGen->generate(k, &tokSeqLeft, &tokSeqRight);
    for (set<TokSeq*>::iterator itLeft=tokSeqLeft.begin(); itLeft!=tokSeqLeft.end(); ++itLeft){
        for (set<TokSeq*>::iterator itRight=tokSeqRight.begin(); itRight!=tokSeqRight.end(); ++itRight){
            
            try{
                if((*itLeft)->all != "" || (*itRight)->all != ""){
                    /*cout << (*itLeft)->first << ":" << (*itLeft)->all << "\t-\t" << (*itRight)->first << ":" << (*itRight)->all << endl;
                     */
                    string firstTok = (*itLeft)->first;
                    if(firstTok == "")
                        firstTok = (*itRight)->first;
                    RPos* rpos = new RPos(s, (*itLeft)->all, (*itRight)->all, firstTok, k);
                    /*
                     cout << rpos->valueIn("ab dadsfs ababa lf   ab asdfa", true) << "\t-\t";
                     cout << rpos->valueIn("ab dadsfs ababa lf   ab asdfa", false) << endl;
                     */
                    //rpos->print();
                    result->insert(rpos);
                }
                
            }catch(SFF_Error* error){
                cout << error->str() << endl;
                delete error;
            }
        }
    }
    for (set<TokSeq*>::iterator it=tokSeqLeft.begin(); it!=tokSeqLeft.end(); ++it){
        delete (*it);
    }
    for (set<TokSeq*>::iterator it=tokSeqRight.begin(); it!=tokSeqRight.end(); ++it){
        delete (*it);
    }
}



PosGen::~PosGen(){
    delete this->tokSeqGen;
}