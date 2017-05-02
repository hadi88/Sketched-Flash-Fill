//
//  TokSeqGen.cpp
//  Sketched Flash Fill
//
//  Created by Hadi on 3/2/13.
//  Copyright (c) 2013 Hadi. All rights reserved.
//

#include "TokSeqGen.h"
TokSeqGen::TokSeqGen(string s){
    this->s = s;
    start = new int*[s.length()+1];
    end = new int*[s.length()+1];
    for (int i = 0; i <= s.length(); i++) {
        start[i] = new int[Token::all.size()];
        end[i] = new int[Token::all.size()];
        for (int j = 0; j < Token::all.size(); j++) {
            start[i][j] = 0;
            end[i][j] = 0;
        }
    }
    int i = 0;
    for (vector<Token*>::iterator tokIt=Token::all.begin(); tokIt!=Token::all.end(); ++tokIt){
        regex e ((*tokIt)->getRE());
        regex_iterator<string::iterator> rit ( s.begin(), s.end(), e );
        regex_iterator<string::iterator> rend;
        while (rit!=rend) {
            start[rit->position()][i] = (int) rit->length();
            end[rit->position()+rit->length()][i] = (int) rit->length();
            ++rit;
        }
        i++;
    }
    //LOG: print dp table
    /*
     for (int j = 0; j < Token::all.size(); j++) {
     cout << "token " << Token::all[j]->getRE() << endl;
     for (int i = 0; i <= s.length(); i++) {
     cout << j << "," << i << " -> " << start[i][j] << " - " << end[i][j] << endl;
     }
     }
     */
     
}

void TokSeqGen::generateLeft(int pos, set<TokSeq*>* result){
    
    stack<int> posStack;        //position in s
    stack<string> tokSeqStack;  //tokens from bottom to top of stack
    stack<int> stack;           //token index stack
    //initalize the stack
    stack.push(0);
    posStack.push(pos);
    tokSeqStack.push("");
    TokSeq* ts = new TokSeq("", "");
    result->insert(ts);
    while (!stack.empty()) {
        int currIndex = stack.top();
        int currPos = posStack.top();
        string crrentTokSeq = tokSeqStack.top();
        
        stack.pop();
        while (currIndex < Token::all.size() && end[currPos][currIndex] == 0) {
            currIndex++;
        }
        if(currIndex >= Token::all.size()){
            posStack.pop();
            tokSeqStack.pop();
            continue;
        }
        stack.push(currIndex+1);
        tokSeqStack.push(Token::all[currIndex]->getRE() + crrentTokSeq);
        posStack.push(currPos - end[currPos][currIndex]);
        stack.push(0);
        //cout << tokSeqStack.top() << endl;
        ts = new TokSeq(tokSeqStack.top(), Token::all[currIndex]->getRE());
        result->insert(ts);
    }
}


void TokSeqGen::generateRight(int pos, set<TokSeq*>* result){
    
    stack<int> posStack;        //position in s
    stack<string> tokSeqStack;  //tokens from bottom to top of stack
    stack<int> stack;           //token index stack
    //initalize the stack
    stack.push(0);
    posStack.push(pos);
    tokSeqStack.push("");
    TokSeq* ts = new TokSeq("", "");
    result->insert(ts);
    string firstToken = "";
    while (!stack.empty()) {
        int currIndex = stack.top();
        int currPos = posStack.top();
        string crrentTokSeq = tokSeqStack.top();
        
        stack.pop();
        
        while (currIndex < Token::all.size() && start[currPos][currIndex] == 0) {
            currIndex++;
        }
        if(currIndex >= Token::all.size()){
            posStack.pop();
            tokSeqStack.pop();
            continue;
        }
        stack.push(currIndex+1);
        if(crrentTokSeq == ""){
            firstToken = Token::all[currIndex]->getRE();
        }
        tokSeqStack.push(crrentTokSeq + Token::all[currIndex]->getRE());
        posStack.push(currPos + start[currPos][currIndex]);
        stack.push(0);
        //cout << tokSeqStack.top() << endl;
        ts = new TokSeq(tokSeqStack.top(), firstToken);
        result->insert(ts);
    }
}

void TokSeqGen::generate(int pos, set<TokSeq*>* leftResult, set<TokSeq*>* rightResult){
    generateLeft(pos, leftResult);
    generateRight(pos, rightResult);
    
}

TokSeqGen::~TokSeqGen(){
    for (int i = 0; i <= s.length(); i++) {
        delete start[i];
        delete end[i];
    }
    delete start;
    delete end;
}