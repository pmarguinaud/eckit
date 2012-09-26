/*
 * (C) Copyright 1996-2012 ECMWF.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 * In applying this licence, ECMWF does not waive the privileges and immunities
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

#include "eclib/Application.h"
#include "eclib/Log.h"
#include "eclib/Types.h"

#include "eclib/config/Script.h"
#include "eclib/config/Compiler.h"

class TestConfig : public Application {
public:

    TestConfig(int argc,char **argv): Application(argc,argv) {}

    ~TestConfig() {}

    virtual void run();

    void test();
};

//-----------------------------------------------------------------------------

class Statement : private NonCopyable
{
    
};

//-----------------------------------------------------------------------------

void TestConfig::test()
{
    ostringstream code;
     
    code << " a = 1; "                          // assign digit
            " b = lolo; "                       // assign string
            " [ class = od, stream = oper;"     // condition with multiple statement
            "   c1 = \"4 x 4\"; "               // double quote
            "   [ date = today; "               // nested branch
            "      d = 4; ]"                    // close after semi-colon
            "   c2 = '5 x 5'; "                 // single quote
            "   e = '6'; "
            "   e = '66'; "                     // override
            "  ]"
            " [ xxx = yyy; f = ignored; ]"      // branch not visited
            " [ xxx = yyy; ]"                   // empty branch
//            " [; g = go ] "
            ;
     
    istringstream in(code.str());
    
    config::Compiler c(in);
    
    config::Script s(c);
    
    s.print( std::cout );
    
    StringDict din;
    
    din["class"]    = "od";
    din["stream"]   = "oper";
    din["date"]     = "today";

    StringDict dout;
    
    s.execute(din,dout);
    
    std::cout << dout << std::endl;
}

void TestConfig::run()
{
    test();
}

//-----------------------------------------------------------------------------

int main(int argc,char **argv)
{
    TestConfig mytest(argc,argv);
    mytest.start();
    return 0;
}

