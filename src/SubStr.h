//
//  SubStr.h
//  Sketched Flash Fill
//
//  Created by Hadi on 4/16/13.
//  Copyright (c) 2013 Hadi. All rights reserved.
//

#ifndef __Sketched_Flash_Fill__SubStr__
#define __Sketched_Flash_Fill__SubStr__

#include "includes.h"
#include "Position.h"

class SubStr{
private:
    Position* ps;
    Position* pf;
public:
    SubStr(Position* ps, Position* pf);
    int compareTo(const SubStr* p) const;
    ~SubStr();
};

#endif /* defined(__Sketched_Flash_Fill__SubStr__) */
