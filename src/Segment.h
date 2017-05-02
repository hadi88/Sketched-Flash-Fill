//
//  Segment.h
//  Sketched Flash Fill
//
//  Created by Hadi on 4/16/13.
//  Copyright (c) 2013 Hadi. All rights reserved.
//

#ifndef __Sketched_Flash_Fill__Segment__
#define __Sketched_Flash_Fill__Segment__

#include "includes.h"
#include "Pattern.h"

class Segment{
public:
    string name;
    vector<int>* numOfSegments;
    vector<int>* segmentPos;
    set<Pattern*>* startPattern;
    set<Pattern*>* endPattern;
    Segment();
    bool isMe(vector<int>* curPos);
    bool isMyLoop(vector<int>* curPos);
    void adjustValues(vector<int>* segmentStack, vector<int>* result);
    int getDepth();
};

#endif /* defined(__Sketched_Flash_Fill__Segment__) */
