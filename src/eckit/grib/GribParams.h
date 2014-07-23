/*
 * (C) Copyright 1996-2013 ECMWF.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 * In applying this licence, ECMWF does not waive the privileges and immunities
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

#ifndef eckit_grib_GribParams_H
#define eckit_grib_GribParams_H

#include "eckit/grib/GribHandle.h"
#include "eckit/memory/Builder.h"
#include "eckit/value/Params.h"

namespace eckit {

//------------------------------------------------------------------------------------------------------

class GribParams : public eckit::ValueParams {
public:

	typedef BuilderT1<GribParams> builder_t;
	typedef GribHandle::Ptr ARG1;

	static std::string className() { return "eckit.grib.GribParams"; }

	GribParams( GribHandle::Ptr );

	virtual ~GribParams();

	static GribParams* create( GribHandle::Ptr );

protected: // members

	GribHandle::Ptr g_;

	long   edition_;                  ///< Grib 1 or Grib 2
	double north_;                   ///< In degrees
	double south_;                   ///< In degrees
	double west_;                    ///< In degrees
	double east_;                    ///< In degrees
	double epsilon_;                 ///< Grib 1 or Grib 2
	long   numberOfDataPoints_;      ///< Must match the grib iterator data points

	std::string hash_;               ///< may be used to persist grids
};

//------------------------------------------------------------------------------------------------------

}

#endif