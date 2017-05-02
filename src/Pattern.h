//
//  Parameterized Position.h
//  Sketched Flash Fill
//
//  Created by Hadi on 3/27/13.
//  Copyright (c) 2013 Hadi. All rights reserved.
//

#ifndef __Sketched_Flash_Fill__Parameterized_Position__
#define __Sketched_Flash_Fill__Parameterized_Position__

#include "includes.h"
#include "Position.h"


class Pattern{
private:
    vector<set<Position*>*>* data;
    //void posesIn(vector<int>* result, string input, vector<Position*>* innerPoses, int depth);
public:
    Pattern(vector<set<Position*>*>* data);
    static void intersectAssign(set<Position*>* s1, set<Position*>* s2);
    vector<set<Position*>*>* getData();
    void intersect(Pattern* p);
    bool isEmpty();
    void removeIncompatibles(vector<int>* segmentStructure, string substr, string input, bool isStartPos);
    void removeOverApproximations(vector<int>* segmentStructure, string input, bool isStartPos);
    Pattern* makeACopy();
    //void posesIn(vector<int>* result, string input);
    int posesIn(vector<int>* position, string input, int positionIndex, int positionIndexDepth);
    //int nextPosesIn(vector<int>* position, string input);
};

#endif /* defined(__Sketched_Flash_Fill__Parameterized_Position__) */
