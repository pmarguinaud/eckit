/*
 * (C) Copyright 1996-2012 ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

#ifndef eclib_config_Block_H
#define eclib_config_Block_H

#include "eclib/machine.h"

#include "eclib/config/Compiler.h"
#include "eclib/config/Statement.h"

namespace config {

//-----------------------------------------------------------------------------

class Block : public Statement {
    
public: // methods

    Block( Compiler& c, bool skipBraces = false );

    virtual ~Block();
    
    virtual void execute( const StringDict& in, StringDict& out );
    
    virtual void print( std::ostream& out );
    
private: // members
    
    std::deque<Statement*> statements_;

};

//-----------------------------------------------------------------------------

} // namespace config

#endif
