/*
 * (C) Copyright 1996-2015 ECMWF.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 * In applying this licence, ECMWF does not waive the privileges and immunities
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

/// @author Tiago Quintino
/// @author Simon Smart
/// @date Dec 2015

#include <iosfwd>
#include <fstream>

#include "sandbox/multiplexer/DummySink.h"
#include "sandbox/multiplexer/DataSink.h"

#include "eckit/exception/Exceptions.h"
#include "eckit/io/Length.h"
#include "eckit/thread/AutoLock.h"
#include "eckit/thread/Mutex.h"

namespace eckit {
namespace multiplexer {

//
// Create the global (singleton) object so it can be found by the DataSinkFactory
DataSinkBuilder<DummySink> DummySinkFactorySingleton(std::string("foo"));

//----------------------------------------------------------------------------------------------------------------------


DummySink::DummySink() {}


DummySink::~DummySink() {
    close();
}

void DummySink::open(const std::string& key) {
    key_ = key;
    eckit::Log::info() << "[" << *this << "]: open" << std::endl;

    file_.open(key_.c_str(), std::ios_base::trunc | std::ios_base::out);
}

void DummySink::write(const void* buffer, const Length& length) {
    eckit::Log::info() << "[" << *this << "]: write (" << length << ")" << std::endl;

    if (!file_.is_open())
        throw eckit::SeriousBug(std::string("DummySink: Cannot write without opening"));

    file_.write(reinterpret_cast<const char*>(buffer), length);
}

void DummySink::close() {
    eckit::Log::info() << "[" << *this << "]: close" << std::endl;

    file_.close();
    key_ = "";
}

void DummySink::print(std::ostream& os) const {
    os << "DataSink (DummySink): " << key_;
}



//----------------------------------------------------------------------------------------------------------------------

}  // namespace multiplexer
}  // namespace eckit

