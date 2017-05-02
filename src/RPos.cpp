//
//  RPos.cpp
//  Sketched Flash Fill
//
//  Created by Hadi on 3/2/13.
//  Copyright (c) 2013 Hadi. All rights reserved.
//

#include "RPos.h"
RPos::RPos(string s, string rl, string rr, string rf, int k){
    this->rl = rl;
    this->rr = rr;
    this->rf = rf;
    int total = totalNumOfMatches(s);
    this->cp = indexOfMatchAt(k, s);
    this->cn = cp - total - 1;
    if(this->cp == -1){
        //Since tokens can have intersection, this can happen. However, since intersection happens in case of subset, the procedure is correct and we over approximate all possible combination of tokens. (Matching can happen only from left to right. Matching from right to left don't provide any new answer)
        throw new SFF_Error("Logical Error: RPos with no match");
        this->cn = 1;
    }
}
string RPos::rest(){
    string result = rl+rr;
    result = result.substr(rf.length(), result.length()-rf.length());
    return result;
}
string RPos::restTillMiddle(){
    if(rl == "")
        return "";
    string result = rl;
    result = result.substr(rf.length(), result.length()-rf.length());
    return result;
}
bool RPos::isConstant() const{
    return false;
}

int RPos::valueIn(string s, bool isPositive){
    int c = cp;
    if(!isPositive){
        int total = totalNumOfMatches(s);
        c = cn + total + 1;
    }
    regex ef (rf);
    string r = rest();
    regex er (r);
    string rtm = restTillMiddle();
    regex ertm (rtm);
    regex_iterator<string::iterator> rend;
    regex_iterator<string::iterator> rit ( s.begin(), s.end(), ef );
    int i = 0;
    int pos = 0;
    while (i < abs(c) && rit!=rend) {
        if(r == ""){
            i++;
            if(rl == ""){
                pos = (int) rit->position();
            }else{
                pos = (int) (rit->position() + rit->length());
            }
        }else{
            smatch m;
            regex_search(rit->suffix().str(),m, er);
            if(!m.empty() && m.position() == 0 ){
                i++;
                if(rl == ""){
                    pos = (int) rit->position();
                }else{
                    if(rtm == ""){
                        pos = (int) (rit->position() + rit->length());
                    }else{
                        regex_search(rit->suffix().str(),m, ertm);
                        if(!m.empty() && m.position() == 0){
                            pos = (int) (rit->position() + rit->length() + m.length());
                        }else{
                            throw new SFF_Error("Logical Error: RPos::valueIn: rest matched, while rest till middle, did not");
                        }
                    }
                }
            }
        }
        
        ++rit;
    }
    if(i != abs(c))
        return -1;
    return (int) (pos);
}

int RPos::totalNumOfMatches(string s){
    regex ef (rf);
    string r = rest();
    regex er (r);
    regex_iterator<string::iterator> rit ( s.begin(), s.end(), ef );
    regex_iterator<string::iterator> rend;
    int result = 0;
    while (rit!=rend) {
        if(r == ""){
            result++;
        }else{
            smatch m;
            regex_search(rit->suffix().str(),m, er);
            if(!m.empty() && m.position() == 0 )
                result++;
        }
        ++rit;
    }
    return result;
}

int RPos::indexOfMatchAt(int k, string s){
    if(k < 0 || k > s.length()){
        throw new SFF_Error("k is out of string bound");
    }
    regex ef (rf);
    string r = rest();
    regex er (r);
    string rtm = restTillMiddle();
    regex ertm (rtm);
    regex_iterator<string::iterator> rit ( s.begin(), s.end(), ef );
    regex_iterator<string::iterator> rend;
    int result = 0;
    while (rit!=rend) {
        if(rit->position() > k)
            return 0;
        if(r == ""){
            result++;
            if(rl == ""){
                if(rit->position() == k){
                    return result;
                }
            }else{
                if(rit->position() + rit->length() == k)
                    return result;
            }
        }else{
            smatch m;
            regex_search(rit->suffix().str(),m, er);
            if(!m.empty() && m.position() == 0){
                result++;
                if(rl == ""){
                    if(rit->position() == k)
                        return result;
                }else{
                    if(rtm == ""){
                        if(rit->position() + rit->length() == k)
                            return result;
                    }else{
                        regex_search(rit->suffix().str(),m, ertm);
                        if(!m.empty() && m.position() == 0){
                            if(rit->position() + rit->length() + m.length() == k)
                                return result;
                        }else{
                            throw new SFF_Error("Logical Error: RPos::indexOfMatchAt: rest matched, while rest till middle, did not");
                        }
                    }
                }
            }
        }
        ++rit;
    }
    return 0;
}

int RPos::compareTo(const Position* p) const{
    
    if ( !p->isConstant()){
        RPos* pos = ((RPos*)(p));
        if(((this->rl) == (pos->rl)) && ((this->rr) == (pos->rr) && (this->cp) == (pos->cp) ) ){
        return 0;
        }else{
            if (this->rl > pos->rl) {
                return 1;
            }else if(this->rl < pos->rl){
                return -1;
            }else if(this->rr > pos->rr){
                return 1;
            }else if(this->rr < pos->rr){
                return -1;
            }else
                return this->cp - pos->cp;
        }
    }
    return 1;
}
bool RPos::operator== (const Position& p){
    return compareTo(&p) == 0;
}
bool RPos::operator< (const Position& p){
    return compareTo(&p) < 0;
}
void RPos::print(){
    cout << "position : " << this->rl << " : " << this->cp << " : " << this->rr << endl;
}
RPos::~RPos(){}