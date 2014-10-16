/*
 * (C) Copyright 1996-2013 ECMWF.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 * In applying this licence, ECMWF does not waive the privileges and immunities
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

#include "eckit/xpr/Take.h"
#include "eckit/xpr/Scalar.h"

namespace eckit {
namespace xpr {

//--------------------------------------------------------------------------------------------
Take::Take(ExpPtr e, ExpPtr l) : Function()
{
    push_back(e);
    push_back(l);
}

Take::Take( args_t& a ) : Function(a)
{
    ASSERT( a.size() == 2 );
}

std::string Take::returnSignature() const
{
    return Undef::sig();
}

ExpPtr Take::evaluate( Scope &ctx ) const
{
    ExpPtr idx  = args(0, ctx, true);
    ExpPtr list = args(1, ctx, true);

    size_t i = (size_t) Scalar::extract( ctx, idx );

    if( i >= list->arity() )
        throw UserError("Take supplied index larger than size of list" );

    return list->args(i);
}


void Take::asCode(std::ostream&o) const
{
    o << "xpr::take("; printArgs(o); o << ")";
}

ExpPtr Take::cloneWith(args_t& a) const
{
    return ExpPtr( new Take(a) );
}

//--------------------------------------------------------------------------------------------

ExpPtr take( ExpPtr e, ExpPtr l )
{
    return ExpPtr( new Take(e,l) );
}

//--------------------------------------------------------------------------------------------

} // namespace xpr
} // namespace eckit