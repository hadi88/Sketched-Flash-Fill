//
//  Segment.cpp
//  Sketched Flash Fill
//
//  Created by Hadi on 4/16/13.
//  Copyright (c) 2013 Hadi. All rights reserved.
//

#include "Segment.h"

Segment::Segment(){
    this->startPattern = new set<Pattern*>();
    this->endPattern = new set<Pattern*>();
}

bool Segment::isMe(vector<int>* curPos){
    if (segmentPos->size() != curPos->size()) {
        return false;
    }
    //cout << segmentPos->size() << endl;
    for (int i = 0; i < segmentPos->size(); i++) {
        int sPos = (*segmentPos)[i];
        int cPos = (*curPos)[i];
        if (sPos != cPos % ((*numOfSegments)[i])) {
            return false;
        }
    }
    return true;
}

bool Segment::isMyLoop(vector<int>* curPos){
    if (segmentPos->size() <= curPos->size()) {
        return false;
    }
    //cout << segmentPos->size() << endl;
    for (int i = 0; i < curPos->size(); i++) {
        int sPos = (*segmentPos)[i];
        int cPos = (*curPos)[i];
        if (sPos != cPos % ((*numOfSegments)[i])) {
            return false;
        }
    }
    return true;
}

void Segment::adjustValues(vector<int> *segmentStack, vector<int> *result){
    result->clear();
    if (this->numOfSegments->size() != segmentStack->size()) {
        cerr << "logical error: depth of segment is not correct" << endl;
        return;
    }
    for (int i = 0; i < segmentStack->size(); i++) {
        int current = (*segmentStack)[i];
        int size = (*numOfSegments)[i];
        int index = (*segmentPos)[i];
        result->push_back(((current - index)/size));
    }
}

int Segment::getDepth(){
    return (int) segmentPos->size();
}