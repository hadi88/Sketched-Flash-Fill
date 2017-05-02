//
//  Token.h
//  Sketched Flash Fill
//
//  Created by Hadi on 3/2/13.
//  Copyright (c) 2013 Hadi. All rights reserved.
//

#ifndef __Sketched_Flash_Fill__Token__
#define __Sketched_Flash_Fill__Token__

#include "includes.h"

class Token{
private:
    string re;
public:
    
    static vector<Token*> all;
    static void init();
    Token(string re);
    string getRE();
};

#endif /* defined(__Sketched_Flash_Fill__Token__) */
