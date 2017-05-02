//
//  PositionSet.h
//  Sketched Flash Fill
//
//  Created by Hadi on 3/27/13.
//  Copyright (c) 2013 Hadi. All rights reserved.
//

#ifndef __Sketched_Flash_Fill__PositionSet__
#define __Sketched_Flash_Fill__PositionSet__

#include "includes.h"
#include "Position.h"

class PositionSet{
private:
    set<Position*>* poses;
    bool isOK;
public:
    PositionSet(set<Position*>* poses, bool isOK);
};

#endif /* defined(__Sketched_Flash_Fill__PositionSet__) */

