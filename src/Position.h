//
//  Position.h
//  Sketched Flash Fill
//
//  Created by Hadi on 3/2/13.
//  Copyright (c) 2013 Hadi. All rights reserved.
//

#ifndef __Sketched_Flash_Fill__Position__
#define __Sketched_Flash_Fill__Position__

#include "includes.h"


class Position{
public:
    virtual bool isConstant() const = 0;
    virtual int valueIn(string s, bool isPositiv) = 0;
    virtual int compareTo(const Position* p) const = 0;
    virtual void print() = 0;
    virtual bool operator== (const Position& p) = 0;
    virtual bool operator< (const Position& p) = 0;
    virtual ~Position(){};
};

#endif /* defined(__Sketched_Flash_Fill__Position__) */
