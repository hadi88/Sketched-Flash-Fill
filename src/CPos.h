//
//  CPos.h
//  Sketched Flash Fill
//
//  Created by Hadi on 3/2/13.
//  Copyright (c) 2013 Hadi. All rights reserved.
//

#ifndef __Sketched_Flash_Fill__CPos__
#define __Sketched_Flash_Fill__CPos__

#include "Position.h"

class CPos : public Position{
private:
    int kp;
    int kn;
public:
    CPos(string s, int k);
    bool isConstant() const;
    int valueIn(string s, bool isPositive);
    int compareTo(const Position* p) const;
    bool operator== (const Position& p);
    bool operator< (const Position& p);
    void print();
    ~CPos();
};

#endif /* defined(__Sketched_Flash_Fill__CPos__) */
