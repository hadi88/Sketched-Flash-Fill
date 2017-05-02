//
//  SubStr.cpp
//  Sketched Flash Fill
//
//  Created by Hadi on 4/16/13.
//  Copyright (c) 2013 Hadi. All rights reserved.
//

#include "SubStr.h"

SubStr::SubStr(Position* ps, Position* pf){
    this->ps = ps;
    this->pf = pf;
}

int SubStr::compareTo(const SubStr* ss) const{
    int res = this->ps->compareTo(ss->ps);
    if (res != 0)
        return res;
    return this->pf->compareTo(ss->pf);
}

SubStr::~SubStr(){
}