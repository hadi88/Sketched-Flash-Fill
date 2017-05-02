//
//  CPos.cpp
//  Sketched Flash Fill
//
//  Created by Hadi on 3/2/13.
//  Copyright (c) 2013 Hadi. All rights reserved.
//

#include "CPos.h"
CPos::CPos(string s, int k){
    this->kp = k;
    this->kn = k - (int) s.length();
}
bool CPos::isConstant() const{
    return true;
}
int CPos::valueIn(string s, bool isPositive){
    return (isPositive)?this->kp:this->kn;
}

int CPos::compareTo(const Position* p) const{
    if ( p->isConstant()){
        return this->kp - ((CPos*)(p))->kp;
    }
    return -1;
}
void CPos::print(){
    cout << "position : " << this->kp << endl;
}
bool CPos::operator== (const Position& p){
    return compareTo(&p) == 0;
}
bool CPos::operator< (const Position& p){
    return compareTo(&p) < 0;
}
CPos::~CPos(){}