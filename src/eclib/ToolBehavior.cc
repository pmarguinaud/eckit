/*
 * (C) Copyright 1996-2012 ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

#include <stdlib.h>

#include "eclib/ToolBehavior.h"

using namespace std;

ToolBehavior::ToolBehavior()
{
}

ToolBehavior::~ToolBehavior()
{
}

string ToolBehavior::home() const
{
    return string( getenv( "HOME" ) );
}

void ToolBehavior::setup(int argc, char** argv)
{
}
