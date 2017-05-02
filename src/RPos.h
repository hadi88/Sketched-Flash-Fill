//
//  RPos.h
//  Sketched Flash Fill
//
//  Created by Hadi on 3/2/13.
//  Copyright (c) 2013 Hadi. All rights reserved.
//

#ifndef __Sketched_Flash_Fill__RPos__
#define __Sketched_Flash_Fill__RPos__

#include "Position.h"

class RPos : public Position{
public:
    int cp;
    int cn;
    string rf;
    string rl;
    string rr;
public:
    RPos (string s, string rl, string rr, string rf, int k);
    bool isConstant() const;
    int valueIn(string s, bool isPositive);
    int totalNumOfMatches(string s);
    int indexOfMatchAt(int k, string s);
    string rest();
    string restTillMiddle();
    int compareTo(const Position* p) const;
    bool operator== (const Position& p);
    bool operator< (const Position& p);
    void print();
    ~RPos();
};

#endif /* defined(__Sketched_Flash_Fill__RPos__) */
