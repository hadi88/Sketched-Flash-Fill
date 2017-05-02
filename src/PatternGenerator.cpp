//
//  PatternGenerator.cpp
//  Sketched Flash Fill
//
//  Created by Hadi on 3/27/13.
//  Copyright (c) 2013 Hadi. All rights reserved.
//

#include "PatternGenerator.h"
PatternGenerator::PatternGenerator(string s){
    this->s = s;
}



void PatternGenerator::generatePattern(set<Pattern*> *leftResult, set<Pattern*> *rightResult, vector<string> values, int segmentDepth){
    vector<int> leftPoses;
    vector<int> rightPoses;
    generatePattern(-1, leftResult, rightResult, &values, &leftPoses, &rightPoses, 0, segmentDepth);
}


void PatternGenerator::generatePattern(int currentPosition, set<Pattern*> *leftResult, set<Pattern*>* rightResult, vector<string>* values, vector<int>* leftPoses, vector<int>* rightPoses, int pointer, int segmentDepth){
    if (pointer >= values->size()) {
        /*for (int p : *leftPoses) {
            cout << p << " ";
        }
        cout << endl;
        for (int p : *rightPoses) {
            cout << p << " ";
        }
        cout << endl;
        */
        generatePatternForPoses(leftPoses, leftResult, segmentDepth);
        generatePatternForPoses(rightPoses, rightResult, segmentDepth);
        return;
    }
    
    string val = (*values)[pointer];
    if (val == "{"){
        leftPoses->push_back(-1);
        rightPoses->push_back(-1);
        generatePattern(currentPosition, leftResult, rightResult, values, leftPoses, rightPoses, pointer + 1, segmentDepth);
        leftPoses->pop_back();
        rightPoses->pop_back();
        return;
    }
    if (val == "}") {
        if (leftPoses->back() == -1 || rightPoses->back() == -1) {
            cerr << "empty loop in complete example" << endl;
        }else{
            leftPoses->push_back(-2);
            rightPoses->push_back(-2);
            generatePattern(currentPosition, leftResult, rightResult, values, leftPoses, rightPoses, pointer + 1, segmentDepth);
            leftPoses->pop_back();
            rightPoses->pop_back();
        }
        return;
    }
    vector<int>* allLeftPoses = new vector<int>();
    findAll(val, s, allLeftPoses, currentPosition);
    if(allLeftPoses->empty())
        return;
    for (int leftPos : *allLeftPoses) {
        
        leftPoses->push_back(leftPos);
        rightPoses->push_back(leftPos + (int) val.length());
        generatePattern(leftPos, leftResult, rightResult, values, leftPoses, rightPoses, pointer + 1, segmentDepth);
        leftPoses->pop_back();
        rightPoses->pop_back();
    }
}

void PatternGenerator::findAll(string sub, string all, vector<int> *leftResult, int startLeftPosition){
    int startPosition = startLeftPosition + 1;
    string temp = all.substr(startPosition, all.length()-startPosition);
    int pos = (int) temp.find(sub);
    while (pos <= all.length() && pos >= 0) {
        leftResult->push_back(startPosition+pos);
        temp = all.substr(startPosition+pos+1, all.length()-(startPosition+pos+1));
        int newPos = (int) temp.find(sub);
        if(newPos > temp.length() - (int) sub.length() || newPos < 0)
            break;
        pos += 1 + (newPos);
    }
}


void PatternGenerator::generatePatternForPoses(vector<int>* poses, set<Pattern*>* result, int depth){
    vector<int> depths; // poses where each element replaced with its importance in position generation
    int firstPos = -1;
    vector<int> depthStack;
    for (int i = 0; i < poses->size(); i++) {
        int pos = (*poses)[i];
        if (pos == -1) {
            depths.push_back(pos);
        } else if(pos == -2){
            depths.push_back(pos);
        }else{
            if (firstPos == -1){
                firstPos = pos;
            }
            int ptr = i - 1;
            while ((*poses)[ptr] == -1) {
                ptr --;
            }
            int num = (int) i - 1 - ptr;
            depths.push_back(num);
        }
    }
    
    set<Position*>* firstPositionSet = new set<Position*>();
    PosGen* posGen = new PosGen(s);
    posGen->generatePos(firstPos, firstPositionSet);
    delete posGen;
    
    vector<set<Position*>*>* patternData = new vector<set<Position*>*>();
    patternData->push_back(firstPositionSet);
    if (depth > 1) {
        
        for (int d = depth - 1; d > 0; d--) {
            //cout << "depth " << d << ":" << endl;
            bool isExampleBig = false;
            set<Position*>* positionSet = new set<Position*>();
            for (int i = 0; i < depths.size(); i++){
                int dep = depths[i];
                if (dep < d)
                    continue;
                int initPos = (*poses)[i];
                vector<int> positions;
                for (int j = i+1; j < depths.size(); j++){
                    int innerDep = depths[j];
                    if (innerDep == d-1) {
                        positions.push_back((*poses)[j]);
                        //cout << (*poses)[j] << endl;
                    }
                    if (innerDep > d-1){
                        break;
                    }
                }
                /*for (int pos : positions) {
                    cout << pos << " ";
                }
                cout << endl;
                 */
                if (isExampleBig) {
                    generateRelativePos(initPos, positions, positionSet);
                }else{
                    isExampleBig = generateRelativePos(initPos, positions, positionSet);
                }
            }
            if(isExampleBig == false){
                cerr << "The first example is not complete" << endl;
                exit(-1);
            }
            patternData->push_back(positionSet);
        }
    }
    Pattern* pattern = new Pattern(patternData);
    result->insert(pattern);
}

bool PatternGenerator::generateRelativePos(int initPos, vector<int> poses, set<Position*> *result){
    if (poses.size() < 1) {
        //cerr << "complete example must have size > 1" << endl;
        return false;
    }
    string rest = s;
    //unsigned prevPos = 0;
    
    rest = rest.substr(initPos, rest.length()-initPos);
    
    unsigned pos = 0;
    int i = 0;

    while (i < poses.size()){
        //prevPos = pos;
        pos = poses[i] - initPos;
        i++;
        
        set<Position*>* toAdd = new set<Position*>();
        PosGen* posGen = new PosGen(rest);
        posGen->generatePos(pos, toAdd);
        Pattern::intersectAssign(result, toAdd);
        delete posGen;
        rest = rest.substr(pos, rest.length()-pos);
        initPos += pos;
    }
    return true;
}


PatternGenerator::~PatternGenerator(){
}