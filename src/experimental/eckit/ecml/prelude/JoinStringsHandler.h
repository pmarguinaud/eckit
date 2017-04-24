/*
 * (C) Copyright 1996-2016 ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */
/// @author Piotr Kuchta, August 2015

#ifndef eckit_ecml_JoinStringsHandler_H
#define eckit_ecml_JoinStringsHandler_H

#include <sstream>

#include "eckit/ecml/parser/Request.h"
#include "eckit/ecml/core/RequestHandler.h"

namespace eckit {

class JoinStringsHandler : public eckit::RequestHandler {
public:
    JoinStringsHandler(const std::string&);
    virtual eckit::Values handle(eckit::ExecutionContext&);
};

} // namespace eckit

#endif