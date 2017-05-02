//
//  Parameterized Position.cpp
//  Sketched Flash Fill
//
//  Created by Hadi on 3/27/13.
//  Copyright (c) 2013 Hadi. All rights reserved.
//

#include "Pattern.h"
#include "RPos.h"
vector<set<Position*>*>* Pattern::getData(){
    return this->data;
}

Pattern::Pattern(vector<set<Position*>*>* data){
    this->data = data;
}

void Pattern::intersect(Pattern* p){
    if (this->data->size() != p->getData()->size()) {
        cerr << "logical error: size of patters don't match" << endl;
    }
    for (int i = 0 ; i < this->data->size(); i++) {
        /*
         cout << " --- prev" << endl;
         for (Position* p : *((*(this->data))[i])) {
         p->print();
         }
         cout << " --- new" << endl;
         for (Position* p : *((*p->getData())[i])) {
         p->print();
         }
         */
        Pattern::intersectAssign((*this->data)[i], (*p->getData())[i]);
        /*
         cout << " --- now" << endl;
         for (Position* p : *((*(this->data))[i])) {
         p->print();
         }
         */
    }
}

void Pattern::intersectAssign (set<Position*>* s1, set<Position*>* s2)
{
    if(s1->empty()){
        for (Position* p: *s2) {
            s1->insert(p);
        }
        return;
    }
    set<Position*>* temp = new set<Position*>(s1->begin(), s1->end());
    for (Position* p1 : *temp) {
        //TODO:use set for search
        bool isInS2 = false;
        for (Position* p2 : *s2) {
            if(p1->compareTo(p2) == 0){
                isInS2 = true;
                //cout << "equal" << endl;
                break;
            }
        }
        if (!isInS2){
            s1->erase(p1);
            //delete p1;
        }
    }
    //for (Position* p2 : *s2) {
    //delete p2;
    //}
    delete temp;
}

Pattern* Pattern::makeACopy(){
    vector<set<Position*>*>* newData = new vector<set<Position*>*>();
    for (set<Position*>* s : *data) {
        set<Position*>* newS = new set<Position*>(s->begin(), s->end());
        newData->push_back(newS);
    }
    return new Pattern(newData);
}

bool Pattern::isEmpty(){
    for (set<Position*>* s: *data) {
        if (s->empty()) {
            return true;
        }
    }
    return false;
}

/*
 void Pattern::posesIn(vector<int>* result, string input){
 set<Position*>* firstPosSet = *(data->begin());
 if (firstPosSet->empty()) {
 result->clear();
 return;
 }
 
 Position* fp = *(firstPosSet->begin());
 result->push_back(fp->valueIn(input, true));
 if (data->size() == 1) {
 return;
 }
 input = input.substr(result->back(), input.length()-result->back());
 vector<Position*>* innerPoses = new vector<Position*>();
 
 bool firstTime = true;
 for (set<Position*>* poses: *data) {
 if (firstTime) {
 firstTime = false;
 continue;
 }
 if (poses->empty()) {
 result->clear();
 return;
 }
 innerPoses->push_back(*(poses->begin()));
 }
 
 posesIn(result, input, innerPoses, 0);
 }
 
 void Pattern::posesIn(vector<int>* result, string input, vector<Position*>* innerPoses, int depth){
 if (depth == innerPoses->size()) {
 return;
 }
 string rest0 = input;
 while (true) {
 int firstPos = (*innerPoses)[depth]->valueIn(rest0, true);
 if (firstPos <= rest0.length() && firstPos >= 0) {
 result->push_back(-1);
 string rest1 = rest0.substr(firstPos, rest0.length() - firstPos);
 int nextPos = (*innerPoses)[depth]->valueIn(rest1, true);
 if (nextPos > rest1.length() || nextPos < 0) {
 nextPos = (int) rest0.length();
 }
 posesIn(result, rest0.substr(0, firstPos), innerPoses, depth + 1);
 result->push_back(-2);
 rest0 = rest1;
 } else {
 break;
 }
 }
 }
 */


Position* getIthElementOfASet(set<Position*>* s, int index){
    set<Position*>::iterator posSetIt = s->begin();
    for (int i = 0; i < index; i++)
        ++posSetIt;
    return *(posSetIt);
}

int Pattern::posesIn(vector<int>* segmentPos, string input, int positionIndex, int positionIndexDepth){
    set<Position*>* firstPosSet = *(data->begin());
    if (firstPosSet->empty()) {
        return -1;
    }
    Position* fp = *(firstPosSet->begin());
    
    int firstPos = fp->valueIn(input, true);
    if (firstPos == -1) {
        return -1;
    }
    int endPos = -1;
    string rest = input.substr(firstPos, input.length()-firstPos);
    int result = firstPos;
    for (int depth = 1; depth < segmentPos->size(); depth++) {
        
        if (((*data)[depth])->empty()) {
            return -1;
        }
        Position* position = * ((((*data)[depth]))->begin());
        if (depth == positionIndexDepth) {
            if (((*data)[depth])->size() < positionIndex + 1) {
                return -1;
            }
            position = getIthElementOfASet((((*data)[depth])), positionIndex);
        }
        
        for (int segNumInDepth = 0; segNumInDepth < (*segmentPos)[depth]; segNumInDepth++) {
            int nextPos = (int) rest.length();
            nextPos = (position)->valueIn(rest, true);
            if (nextPos > rest.length() || nextPos < 0) {
                return -1;
            }
            if (endPos != -1) {
                if (nextPos >= rest.length() - endPos) {
                    return -2;
                }
            }
            result += nextPos;
            rest = rest.substr(nextPos, rest.length() - nextPos);
        }
        endPos = (int) rest.length() - position->valueIn(rest, true);
        //rest = rest.substr(0, nextPos);
    }
    return result;
}

void Pattern::removeIncompatibles(vector<int> *segmentStructure, string substr, string input, bool isStartPos){
    
    int currentIndex = (int) segmentStructure->size() - 1;
    if ((*segmentStructure)[currentIndex] == 0) {
        while (currentIndex >= 0 && (*segmentStructure)[currentIndex] == 0) {
            currentIndex--;
        }
        if (currentIndex < 0) {
            currentIndex++;
        }

    }
    set<Position*>* currentSet = ((*(this->data))[currentIndex]);
    if (currentSet->empty()) {
        return;
    }
    for (int i = 0; i < currentSet->size(); i++) {
        //Position* p = getIthElementOfASet(currentSet, i);
        //if (p->isConstant()) {
        //    p->print();
        //}
        int pos = posesIn(segmentStructure, input, i, currentIndex);
        int startPos = pos - (isStartPos?0:(int)substr.length());
        string expected = "";
        if (startPos >= 0 && startPos + substr.length() <= input.length())
            expected = input.substr(startPos , substr.length());
        if (pos < 0 || substr != expected){
            Position* toDelete = getIthElementOfASet(currentSet, i);
            /*if (toDelete->isConstant() == false) {
                RPos* p = (RPos*) toDelete;
                if (p->rf == "[A-Z][\\.]" ) {
                    cout << "position given = " << pos << endl;
                    toDelete->print();
                }
            }*/
            currentSet->erase(toDelete);
            i--;
        }
    }
    return;
}


void Pattern::removeOverApproximations(vector<int> *segmentStructure, string input, bool isStartPos){
    
    int currentIndex = (int) segmentStructure->size() - 1;
    if ((*segmentStructure)[currentIndex] == 0) {
        while (currentIndex >= 0 && (*segmentStructure)[currentIndex] == 0) {
            currentIndex--;
        }
        if (currentIndex < 0) {
            currentIndex++;
        }
        
    }
    set<Position*>* currentSet = ((*(this->data))[currentIndex]);
    if (currentSet->empty()) {
        return;
    }
    for (int i = 0; i < currentSet->size(); i++) {
        //Position* p = getIthElementOfASet(currentSet, i);
        //if (p->isConstant()) {
        //    p->print();
        //}
        //p->print();
        int pos = posesIn(segmentStructure, input, i, currentIndex);
        if (pos >= 0){
            Position* toDelete = getIthElementOfASet(currentSet, i);
            /*if (toDelete->isConstant() == false) {
                RPos* p = (RPos*) toDelete;
                if (p->rf == "[A-Z][\\.]" ) {
                    cout << "position given = " << pos << endl;
                    toDelete->print();
                }
            }*/
            currentSet->erase(toDelete);
            i--;
        }
    }
    return;
}
/*
 int Pattern::nextPosesIn(vector<int>* segmentPos, string input){
 set<Position*>* firstPosSet = *(data->begin());
 if (firstPosSet->empty()) {
 return -1;
 }
 Position* fp = *(firstPosSet->begin());
 
 int firstPos = fp->valueIn(input, true);
 if (firstPos == -1) {
 return -1;
 }
 
 string rest = input;
 int result = firstPos;
 for (int depth = 1; depth < segmentPos->size(); depth++) {
 int nextPos = (int) rest.length();
 for (int segNumInDepth = 0; segNumInDepth < (*segmentPos)[depth] - 1; segNumInDepth++) {
 if (((*data)[depth])->empty()) {
 return -1;
 }
 nextPos = (*(((*data)[depth])->begin()))->valueIn(rest, true);
 if (nextPos > rest.length() || nextPos < 0) {
 return -1;
 }
 result += nextPos;
 rest = rest.substr(nextPos, rest.length() - nextPos);
 }
 rest = rest.substr(0, nextPos);
 }
 result = (*(((*data)[segmentPos->size()])->begin()))->valueIn(rest, true);
 if (result > rest.length() || result < 0) {
 return -1;
 }
 return result;
 }
 */