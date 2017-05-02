//
//  Language Generator.cpp
//  Sketched Flash Fill
//
//  Created by Hadi on 4/3/13.
//  Copyright (c) 2013 Hadi. All rights reserved.
//

#include "LanguageGenerator.h"

int findNumOfSegments(string str, int pos, int depth){
    int result = 0;
    int currentDepth = depth;
    while (pos < str.length()) {
        while (pos < str.length() && str[pos] != '[' &&
               str[pos] != ']' && str[pos] != '{' &&
               str[pos] != '}' && str[pos] != '\\') pos++;
        if (str[pos] == '{'){
            currentDepth++;
        }else if (str[pos] == '}'){
            currentDepth--;
            if (depth == currentDepth) {
                return result;
            }
            if (depth == currentDepth - 1) {
                result++;
            }
        }else if (str[pos] == '[') {
            
        }else if (str[pos] == ']' && depth == currentDepth - 1) {
            result++;
        } else if (str[pos] == '\\'){
            pos++;
            if (str[pos] == '[' || str[pos] == ']' || str[pos] == '{' || str[pos] == '}' || str[pos] == '\\') {
            } else{
                cerr << "format error" << endl;
            }
        }
        pos++;
    }
    cerr << "format error" << endl;
    return result;
}

LanguageGenerator::LanguageGenerator(string format, string input, string output){
    this->format = format;
    this->segments = new vector<Segment*>();
    
    int startPos = -1;
    int pos = 0;
    
    vector<int> currentSegmentPos;
    vector<int> segmentsSize;
    
    currentSegmentPos.push_back(0);
    segmentsSize.push_back(findNumOfSegments("{"+format+"}", pos, 0));
    int depth = 0;
    do{
        while (pos < format.length() && format[pos] != '[' &&
               format[pos] != ']' && format[pos] != '{' &&
               format[pos] != '}' && format[pos] != '\\') pos++;
        if (format[pos] == '{'){
            currentSegmentPos.push_back(0);
            segmentsSize.push_back(findNumOfSegments(format, pos, depth));
        }else if (format[pos] == '}'){
            currentSegmentPos.pop_back();
            
            int segmentPos = currentSegmentPos.back() + 1;
            currentSegmentPos.pop_back();
            currentSegmentPos.push_back(segmentPos);
            
            segmentsSize.pop_back();
        }else if (format[pos] == '[') {
            startPos = pos + 1;
        } else if (format[pos] == ']'){
            
            Segment* seg = new Segment();
            seg->name = format.substr(startPos, pos-startPos);
            seg->segmentPos = new vector<int>(currentSegmentPos);
            seg->numOfSegments = new vector<int>(segmentsSize);
            segments->push_back(seg);
            
            int segmentPos = currentSegmentPos.back() + 1;
            currentSegmentPos.pop_back();
            currentSegmentPos.push_back(segmentPos);
            
        } else if (format[pos] == '\\'){
            pos++;
            if (format[pos] == '[' || format[pos] == ']' || format[pos] == '{' || format[pos] == '}' || format[pos] == '\\') {
            } else{
                cerr << "format error" << endl;
            }
        }
        pos++;
    }while (pos < format.length());
    addCompleteExample(input, output);
}




void LanguageGenerator::addCompleteExample(string input, string output){
    for (int i = 0; i < segments->size(); i++) {
        Segment* seg = (*segments)[i];
        
        vector<string> subStrs;
        int startPos = -1;
        int pos = 0;
        
        vector<int> currentSegmentPos;
        currentSegmentPos.push_back(0);
        
        do{
            while (pos < output.length() && output[pos] != '[' &&
                   output[pos] != ']' && output[pos] != '{' &&
                   output[pos] != '}' && output[pos] != '\\') pos++;
            if (output[pos] == '{'){
                if(seg->isMyLoop(&currentSegmentPos)){
                    subStrs.push_back("{");
                }
                currentSegmentPos.push_back(0);
            }else if (output[pos] == '}'){
                currentSegmentPos.pop_back();
                if(seg->isMyLoop(&currentSegmentPos)){
                    subStrs.push_back("}");
                }
                int segmentPos = currentSegmentPos.back() + 1;
                currentSegmentPos.pop_back();
                currentSegmentPos.push_back(segmentPos);
            }else if (output[pos] == '[') {
                startPos = pos + 1;
            } else if (output[pos] == ']'){
                if(seg->isMe(&currentSegmentPos)){
                    subStrs.push_back(output.substr(startPos, pos-startPos));
                }
                int segmentPos = currentSegmentPos.back() + 1;
                currentSegmentPos.pop_back();
                currentSegmentPos.push_back(segmentPos);
            } else if (output[pos] == '\\'){
                pos++;
                if (output[pos] == '[' || output[pos] == ']' || output[pos] == '{' || output[pos] == '}' || output[pos] == '\\') {
                } else{
                    cerr << "output error" << endl;
                }
            }
            pos++;
        }while (pos < output.length());
        PatternGenerator* pg = new PatternGenerator(input);
        pg->generatePattern(seg->startPattern, seg->endPattern, subStrs, seg->getDepth());
    }
    addExample(input, output);
}

int getDepthBySegmentPos(vector<int>* segmentStructure){
    int currentIndex = (int) segmentStructure->size() - 1;
    if ((*segmentStructure)[currentIndex] == 0) {
        while (currentIndex >= 0 && (*segmentStructure)[currentIndex] == 0) {
            currentIndex--;
        }
        if (currentIndex < 0) {
            currentIndex++;
        }
    }
    return currentIndex;
}

void LanguageGenerator::addExample(string input, string output){
    for (int i = 0; i < segments->size(); i++) {
        Segment* seg = (*segments)[i];
        for (int d = 0; d < seg->getDepth(); d++) {
            
            
            vector<int> segmentStructure;
            int startPos = -1;
            int pos = 0;
            
            vector<int> currentSegmentPos;
            currentSegmentPos.push_back(0);
            segmentStructure.push_back(0);
            do{
                while (pos < output.length() && output[pos] != '[' &&
                       output[pos] != ']' && output[pos] != '{' &&
                       output[pos] != '}' && output[pos] != '\\') pos++;
                if (output[pos] == '{'){
                    if(seg->isMyLoop(&currentSegmentPos)){
                        segmentStructure.push_back(0);
                    }
                    currentSegmentPos.push_back(0);
                }else if (output[pos] == '}'){
                    currentSegmentPos.pop_back();
                    if(seg->isMyLoop(&currentSegmentPos)){
                        int dep = getDepthBySegmentPos(&segmentStructure);
                        if (dep == d) {
                            removeOverApproximations(seg, &segmentStructure, input);
                        }
                        segmentStructure.pop_back();
                        int segmentPos = segmentStructure.back() + 1;
                        segmentStructure.pop_back();
                        segmentStructure.push_back(segmentPos);
                    }
                    int segmentPos = currentSegmentPos.back() + 1;
                    currentSegmentPos.pop_back();
                    currentSegmentPos.push_back(segmentPos);
                }else if (output[pos] == '[') {
                    startPos = pos + 1;
                } else if (output[pos] == ']'){
                    if(seg->isMe(&currentSegmentPos)){
                        int dep = getDepthBySegmentPos(&segmentStructure);
                        if (dep == d) {
                            
                            string substr = output.substr(startPos, pos-startPos);
                            removeIncompatibles(seg, &segmentStructure, substr, input);
                        }
                        int segmentPos = segmentStructure.back() + 1;
                        segmentStructure.pop_back();
                        segmentStructure.push_back(segmentPos);
                    }
                    int segmentPos = currentSegmentPos.back() + 1;
                    currentSegmentPos.pop_back();
                    currentSegmentPos.push_back(segmentPos);
                } else if (output[pos] == '\\'){
                    pos++;
                    if (output[pos] == '[' || output[pos] == ']' || output[pos] == '{' || output[pos] == '}' || output[pos] == '\\') {
                    } else{
                        cerr << "output error" << endl;
                    }
                }
                pos++;
            }while (pos < output.length());
        }
    }
}


std::string replaceAll(std::string subject, const std::string& search,
                       const std::string& replace) {
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != std::string::npos) {
        subject.replace(pos, search.length(), replace);
        pos += replace.length();
    }
    return subject;
}

Segment* LanguageGenerator::findSegmentByName(string name){
    for (Segment* seg : *(this->segments)) {
        if (seg->name == name) {
            return seg;
        }
    }
    return NULL;
}
string LanguageGenerator::expectOutput(string input){// TODO: support loops
    string result = "";
    int lastPos = 0;
    int pos = 0;
    
    
    //int startPos = -1;
    vector<int> currentSegmentPos;
    vector<int> loopStartPos;
    vector<string> loopResult;
    vector<bool> isLoopEnough;
    
    currentSegmentPos.push_back(0);
    
    do{
        while (pos < format.length() && format[pos] != '[' &&
               format[pos] != ']' && format[pos] != '{' &&
               format[pos] != '}' && format[pos] != '\\') pos++;
        if (format[pos] == '{'){
            result += format.substr(lastPos, pos-lastPos);
            lastPos = pos + 1;
            currentSegmentPos.push_back(0);
            loopResult.push_back(result);
            loopStartPos.push_back(pos);
            isLoopEnough.push_back(true);
        }else if (format[pos] == '}'){
            if (isLoopEnough.back()) {
                result = loopResult.back();
                loopResult.pop_back();
                isLoopEnough.pop_back();
                loopStartPos.pop_back();
                currentSegmentPos.pop_back();
                int segmentPos = currentSegmentPos.back() + 1;
                currentSegmentPos.pop_back();
                currentSegmentPos.push_back(segmentPos);
                lastPos = pos + 1;
            } else {
                result += format.substr(lastPos, pos-lastPos);
                loopResult.pop_back();
                loopResult.push_back(result);
                pos = loopStartPos.back();
                lastPos = pos + 1;
                isLoopEnough.pop_back();
                isLoopEnough.push_back(true);
            }
        }else if (format[pos] == '[') {
            result += format.substr(lastPos, pos-lastPos);
            lastPos = pos + 1;
            //startPos = pos + 1;
        } else if (format[pos] == ']'){
            Segment* seg = findSegmentByName(format.substr(lastPos, pos-lastPos));
            if (seg->startPattern->empty() || seg->endPattern->empty()) {
                return "no suggestion";
            }
            vector<int> currentSegmentPosAdjusted;
            seg->adjustValues(&currentSegmentPos, &currentSegmentPosAdjusted);
            int startPos = (*((seg->startPattern)->begin()))->posesIn(&currentSegmentPosAdjusted, input, 0, 0);
            int endPos = (*((seg->endPattern)->begin()))->posesIn(&currentSegmentPosAdjusted, input, 0, 0);
            
            if (startPos > -1 && endPos > -1 && startPos < endPos){
                if (!isLoopEnough.empty()) {
                    isLoopEnough.pop_back();
                    isLoopEnough.push_back(false);
                }
                result += input.substr(startPos, endPos - startPos);
            }
            
            lastPos = pos + 1;
            
            int segmentPos = currentSegmentPos.back() + 1;
            currentSegmentPos.pop_back();
            currentSegmentPos.push_back(segmentPos);
            
        } else if (format[pos] == '\\'){
            pos++;
            if (format[pos] == '[' || format[pos] == ']' || format[pos] == '{' || format[pos] == '}' || format[pos] == '\\') {
            } else{
                cerr << "format error" << endl;
            }
        }
        pos++;
    }while (pos < format.length());
    
    result += format.substr(lastPos, format.length()-lastPos);
    
    result = replaceAll(result, "\\{", "{");
    result = replaceAll(result, "\\}", "}");
    result = replaceAll(result, "\\[", "[");
    result = replaceAll(result, "\\]", "]");
    result = replaceAll(result, "\\\\", "\\");
    return result;
}

void LanguageGenerator::removeIncompatibles(Segment* seg, vector<int>* segmentStructure, string substr, string input){
    //cout << "segment " << seg->name << " :" << endl;
    set<Pattern*>* temp = new set<Pattern*>(*(seg->startPattern));
    for (Pattern* p: *temp) {
        p->removeIncompatibles(segmentStructure, substr, input, true);
        if (p->isEmpty()){
            seg->startPattern->erase(p);
        }
    }
    
    temp = new set<Pattern*>(*(seg->endPattern));
    for (Pattern* p: *temp) {
        p->removeIncompatibles(segmentStructure, substr, input, false);
        if (p->isEmpty()){
            seg->endPattern->erase(p);
        }
    }
}

void LanguageGenerator::removeOverApproximations(Segment* seg, vector<int>* segmentStructure, string input){
    //cout << "segment " << seg->name << " :" << endl;
    set<Pattern*>* temp = new set<Pattern*>(*(seg->startPattern));
    for (Pattern* p: *temp) {
        p->removeOverApproximations(segmentStructure, input, true);
        if (p->isEmpty()){
            seg->startPattern->erase(p);
        }
    }
    
    temp = new set<Pattern*>(*(seg->endPattern));
    for (Pattern* p: *temp) {
        p->removeOverApproximations(segmentStructure, input, false);
        if (p->isEmpty()){
            seg->endPattern->erase(p);
        }
    }
}