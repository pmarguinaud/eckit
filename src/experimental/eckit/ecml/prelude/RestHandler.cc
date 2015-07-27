/*
 * (C) Copyright 1996-2013 ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

#include "RestHandler.h"

#include "experimental/eckit/ecml/parser/Request.h"
#include "experimental/eckit/ecml/core/ExecutionContext.h"
#include "experimental/eckit/ecml/core/Environment.h"

namespace eckit {

RestHandler::RestHandler(const std::string& name) : RequestHandler(name) {}

Values RestHandler::handle(ExecutionContext& context)
{
    Values vs (context.environment().lookup("of"));
    if (vs == 0)
        return 0; // TODO
    return new Cell("_list", "", Cell::clone(vs->rest()), 0);
}

} // namespace eckit
