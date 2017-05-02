//
//  SFF_Error.h
//  Sketched Flash Fill
//
//  Created by Hadi on 3/2/13.
//  Copyright (c) 2013 Hadi. All rights reserved.
//

#ifndef __Sketched_Flash_Fill__SFF_Error__
#define __Sketched_Flash_Fill__SFF_Error__


#include <cstring>
#include <iostream>
using namespace std;

class SFF_Error{
private:
    string error;
public:
    SFF_Error(string error);
    string str();
};

#endif /* defined(__Sketched_Flash_Fill__SFF_Error__) */
