//
//  PositionSet.cpp
//  Sketched Flash Fill
//
//  Created by Hadi on 3/27/13.
//  Copyright (c) 2013 Hadi. All rights reserved.
//

#include "PositionSet.h"

PositionSet::PositionSet(set<Position*>* poses, bool isOK){
    this->poses = poses;
    this->isOK = isOK;
}