//
//  PatternGenerator.h
//  Sketched Flash Fill
//
//  Created by Hadi on 3/27/13.
//  Copyright (c) 2013 Hadi. All rights reserved.
//

#ifndef __Sketched_Flash_Fill__PatternGenerator__
#define __Sketched_Flash_Fill__PatternGenerator__

#include "includes.h"
#include "Pattern.h"
#include "PosGen.h"

class PatternGenerator{
private:
    string s;
    void findAll(string sub, string all, vector<int>* leftResult, int startPosition);
    bool generateRelativePos(int initPos, vector<int> poses, set<Position*> *result);
    void generatePatternForPoses(vector<int>* poses, set<Pattern*>* result, int depth);
    void generatePattern(int currentPosition, set<Pattern*>* leftResult, set<Pattern*>* rightResult, vector<string>* values, vector<int>* leftPoses, vector<int>* rightPoses, int pointer, int segmentDepth);
    
public:
    PatternGenerator(string s);
    //void generatePattern(set<Pattern*>* result1, set<Pattern*>* result2, string value);
    void generatePattern(set<Pattern*>* rightResult, set<Pattern*>* leftResult, vector<string> values, int segmentDepth);
    
    ~PatternGenerator();
};


#endif /* defined(__Sketched_Flash_Fill__PatternGenerator__) */
