// Boost.Geometry

// Copyright (c) 2017, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_SRS_PROJECTIONS_ESRI_PARAMS_HPP
#define BOOST_GEOMETRY_SRS_PROJECTIONS_ESRI_PARAMS_HPP


#include <string>

#include <boost/geometry/srs/spheroid.hpp>


namespace boost { namespace geometry
{
    
namespace srs
{


struct esri
{
    explicit esri(int c)
        : code(c)
    {}

    int code;
};


template <int Code>
struct static_esri
{
    static const int code = Code;
};


} // namespace srs


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_SRS_PROJECTIONS_ESRI_PARAMS_HPP

/* esri_params.hpp
XUMXQHP/C0JwWGiBQ/jJp85gR4q/fArB6N/4G15j62kB9mhDyoOH+jF36JxReNAEUHPnumkxhWEfTj+aopVhgTDWwU1mR/YWJccHx2afHll3/rj5AwPhey2XuUzfnyXuWQk8sAafRkPkzW6bXn7x2uZxIOytpByo0DhGmFkJ8Pq7mk0j0exnzUuMy6GXmZl7MmWdkB2ATNhYcfYllnxZzanha/YrDjLTG2nzBQMYuCySJKrXbqK3HDYq1kRGWxdoa+Q9kyzXs9KWg5g4LUrNYnZFmEzLaN6mveHVpMa+IzKaPnuVR7IXy8iUmblcq7ASxpZWi/JnZZ8ETWbzOK5TEcTmyY0uJ7971ELpPklVv2TO4o+dL53z+GMaThaY0DjQSi9fFE0o2GK8yaDqt55xY32KI/EwZvVgsxpjLu/L12Fw4M9K9tieHo77/RMRbuTxIQ5b9lm3giOclAt7iNBtjY9EfiPkoDQ4q3WJrhMonqiXlCXFACJeuHWmzHIFGDhROuTcvrD3zHb+2rOx5/lcGmV22tDO+zmDmCh2HdulaoykuZ2CyC8mgz/re2lIZl7gq71xcxtUplnYlmYBrDr91t1mqewmfJJ+JUGT31G/fO7gkEPN5z9BNBwL/IGumJuEaq1GA5RHp2dPbjX3jJRX+jLm971CVd0WZQgpq7XCg26mGCBY8uNzT/kGaP0C1R3hXX+j6/nxHRYCBm9d
*/