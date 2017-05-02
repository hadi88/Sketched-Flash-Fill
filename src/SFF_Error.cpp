//
//  SFF_Error.cpp
//  Sketched Flash Fill
//
//  Created by Hadi on 3/2/13.
//  Copyright (c) 2013 Hadi. All rights reserved.
//

#include "SFF_Error.h"

SFF_Error::SFF_Error(string error){
    this->error = error;
}

string SFF_Error::str(){
    return error;
}