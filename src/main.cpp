//
//  main.cpp
//  Sketched Flash Fill
//
//  Created by Hadi on 3/2/13.
//  Copyright (c) 2013 Hadi. All rights reserved.
//

#include "Token.h"
#include "LanguageGenerator.h"
#define MAX_SIZE 10000
int main(int argc, const char * argv[])
{
    Token::init();
    
    //PosGen* pg = new PosGen("P. C. , Hdaaf, V. B. ");
    //set<Position*> res;
    //pg->generatePos(15, &res);
    //for (Position* p : res) {
    //    p->print();
    //}
    char format[MAX_SIZE];
    char input[MAX_SIZE];
    char output[MAX_SIZE];
    cin.getline(format, MAX_SIZE);
    cin.getline(input, MAX_SIZE);
    cin.getline(output, MAX_SIZE);
    
    LanguageGenerator* lg = new LanguageGenerator(format, input, output);
    
    char commandType[MAX_SIZE];
    while (true) {
        cin.getline(commandType, MAX_SIZE);
        if (string(commandType) == "example") {
            cin.getline(input, MAX_SIZE);
            cin.getline(output, MAX_SIZE);
            lg->addExample(input, output);
        } else if(string(commandType) == "input") {
            cin.getline(input, MAX_SIZE);
            cout << lg->expectOutput(input) << endl;
        } else
            break;
    }
    
    /*
    string format = "[number] - [lastname] - {[init], }";
    LanguageGenerator* lg = new LanguageGenerator(format, "[1] Cerny, P. C.", "[1][Cerny]{[P][C]}");
    lg->addExample("[12] Sankaranarayanan, S.", "[12][Sankaranarayanan]{[S]}");
    cout << lg->expectOutput("[323] Ravanbakhsh, H. Z. F.") << endl;
    */

    /*
    string format = "{[lastname] - {[init]# } |}";
    LanguageGenerator* lg = new LanguageGenerator(format, "Cerny, P. C. , Hdaaf, V. B. ", "{[Cerny]{[P][C]}[Hdaaf]{[V][B]}}");
    lg->addExample("Sankaranarayanan, S. D. , Zack, B. V. ", "{[Sankaranarayanan]{[S][D]}[Zack]{[B][V]}}");
    cout << lg->expectOutput("Ravanbakhsh, H. Z. , Deck, V. B.") << endl;
     
    */
    
    /*
    string format = "[digits1] ([digits2]) [digits3]";
    LanguageGenerator* lg = new LanguageGenerator(format, "324-235-5483", "[324][235][5483]");
    lg->addExample("(236)-123(2141)", "[236][123][2141]");
    cout << lg->expectOutput(" (324 512 ) 6532") << endl;
     
     */
    
    /*
    string format = "[value] [unit]";
    LanguageGenerator* lg = new LanguageGenerator(format, "BTR KRNL WK CORN 15Z", "[15][Z]");
    lg->addExample("CAMP DRY DBL NDL 6 OZ", "[6][OZ]");
    cout << lg->expectOutput("CHORE BOY HD SPNG 1 PK") << endl;
    */
    
    /*
    string format = "{[name]\\\\}";
    LanguageGenerator* lg = new LanguageGenerator(format, "Company\\Code\\index.html", "{[Company][Code]}");
    lg->addExample("Company\\Docs\\Spec\\specs.doc", "{[Company][Docs][Spec]}");
    cout << lg->expectOutput("Company\\System\\Bug\\test.html") << endl;
    */
    
    /*
    string format = "{[name]\\\\}";
    LanguageGenerator* lg = new LanguageGenerator(format, " adf Company\\Code\\index.html", "{[Company][Code]}");
    lg->addExample("Company\\Docs\\Spec\\specs.doc", "{[Company][Docs][Spec]}");
    cout << lg->expectOutput("Company\\System\\Bug\\test.html") << endl;
    */
    
    /*
    string format = "{[value] #}";
    LanguageGenerator* lg = new LanguageGenerator(format, "(6/7)(4/5)(14/1)", "{[6/7][4/5][14/1]}");
    lg->addExample("49(28/11)(14/1)", "{[28/11][14/1]}");
    cout << lg->expectOutput("() (28/11)(14/1)") << endl;
    */
    
    /*
    string format = "{[Init]}";
    LanguageGenerator* lg = new LanguageGenerator(format, "International Business Machines", "{[I][B][M]}");
    lg->addExample("Principles Of Programming Languages", "{[P][O][P][L]}");
    cout << lg->expectOutput("International Conference Software Engineering") << endl;
    */
    
    /*
    string format = "{[value] }";
    LanguageGenerator* lg = new LanguageGenerator(format, "   Oege   de    Moor", "{[Oege][de][Moor]}");
    lg->addExample("Kathleen     Fisher     ATT      Labs", "{[Kathleen][Fisher][ATT][Labs]}");
    cout << lg->expectOutput("International    Conference    Software     Engineering") << endl;
    */
}

