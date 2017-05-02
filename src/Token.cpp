//
//  Token.cpp
//  Sketched Flash Fill
//
//  Created by Hadi on 3/2/13.
//  Copyright (c) 2013 Hadi. All rights reserved.
//

#include "Token.h"

vector<Token*> Token::all;

Token::Token(string re){
    this->re = re;
}
string Token::getRE(){
    return re;
}

void Token::init(){

    
    //Adding Special Tokens
    set<string> specialTok;
    
    string ws = "\\s"; //white space
    //specialTok.insert(ws);
    //specialTok.insert("\\[");
    //specialTok.insert("\\]");
    //specialTok.insert(",");
    specialTok.insert("\\.");
    specialTok.insert("\\\\");
    
    /*
    specialTok.insert(ws);
    specialTok.insert("\\.");
    specialTok.insert("\\;");
    specialTok.insert("\\,");
    specialTok.insert("\\:");
    specialTok.insert("\\-");
    specialTok.insert("_");
    specialTok.insert("\\\\");
    specialTok.insert("\\/");
    specialTok.insert("\\(");
    specialTok.insert("\\)");
    specialTok.insert("\\{");
    specialTok.insert("\\}");
    specialTok.insert("\\[");
    specialTok.insert("\\]");
    */
    
    for (set<string>::iterator it=specialTok.begin(); it!=specialTok.end(); ++it){
        Token::all.insert(Token::all.begin(), new Token("["+(*it)+"]"));
        Token::all.insert(Token::all.begin(), new Token("[^"+(*it)+"]+"));
    }
    
    //Adding Character Sequences
    set<string> charSeq;
    
    charSeq.insert("0-9");
    charSeq.insert("A-Z");
    charSeq.insert("a-z");
    
    //charSeq.insert("a-z");
    /*
    charSeq.insert("a-z");
    charSeq.insert("A-Z");
    charSeq.insert("0-9");
    charSeq.insert("0-9a-zA-Z");
    //TODO: add accent and alphanumeric alphabets
    
    charSeq.insert(ws+"a-zA-Z");
    charSeq.insert(ws+"a-z");
    charSeq.insert(ws+"A-Z");
    charSeq.insert(ws+"0-9");
    charSeq.insert(ws+"0-9a-zA-Z");
    //TODO: add accent and alphanumeric alphabets
    */
    
    for (set<string>::iterator it=charSeq.begin(); it!=charSeq.end(); ++it){
        Token::all.insert(Token::all.begin(), new Token("["+(*it)+"]+"));
        Token::all.insert(Token::all.begin(), new Token("[^"+(*it)+"]+"));
    }
}