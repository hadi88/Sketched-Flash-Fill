//
//  Language Generator.h
//  Sketched Flash Fill
//
//  Created by Hadi on 4/3/13.
//  Copyright (c) 2013 Hadi. All rights reserved.
//

#ifndef __Sketched_Flash_Fill__Language_Generator__
#define __Sketched_Flash_Fill__Language_Generator__

#include "includes.h"
#include "Segment.h"
#include "PatternGenerator.h"

class LanguageGenerator{
private:
    string format;
    vector<Segment*>* segments;
    Segment* findSegmentByName(string name);
    void addCompleteExample(string input, string output);
    void removeIncompatibles(Segment* seg, vector<int>* segmentStructure, string subs, string output);
    void removeOverApproximations(Segment* seg, vector<int>* segmentStructure, string output);    
    
public:
    LanguageGenerator(string format, string input, string output);
    void addExample(string input, string output);
    string expectOutput(string input);
};

#endif /* defined(__Sketched_Flash_Fill__Language_Generator__) */
