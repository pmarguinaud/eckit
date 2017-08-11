/*
 * (C) Copyright 1996-2017 ECMWF.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 * In applying this licence, ECMWF does not waive the privileges and immunities
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */


#include <string>


#include "eckit/exception/Exceptions.h"
#include "eckit/filesystem/LocalPathName.h"
#include "eckit/filesystem/PathExpander.h"
#include "eckit/testing/Test.h"

using namespace std;
using namespace eckit;
using namespace eckit::testing;

namespace eckit {
namespace test {

//-----------------------------------------------------------------------------

CASE("test_expands")
{
    std::string s = "{CWD}/tmp/foo";
    std::string r = std::string(::getenv("CURRENT_TEST_DIR")) + std::string("/tmp/foo");

    LocalPathName ps = LocalPathName(PathExpander::expand("CWD", s)).realName();
    LocalPathName pr = LocalPathName(r).realName();

    EXPECT( ::strcmp(ps.c_str(), pr.c_str()) == 0 );
}

CASE("test_missing_keys")
{
    std::string s = "{FOO}/tmp/foo";

    EXPECT_THROWS_AS( PathExpander::expand("FOO", s), eckit::UserError );
}

//-----------------------------------------------------------------------------

}  // namespace test
}  // namespace eckit

int main(int argc, char **argv)
{
    return run_tests ( argc, argv );
}


