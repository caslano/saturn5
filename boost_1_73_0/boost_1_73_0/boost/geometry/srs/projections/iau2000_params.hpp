// Boost.Geometry

// Copyright (c) 2017, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_SRS_PROJECTIONS_IAU2000_PARAMS_HPP
#define BOOST_GEOMETRY_SRS_PROJECTIONS_IAU2000_PARAMS_HPP


#include <string>

#include <boost/geometry/srs/spheroid.hpp>


namespace boost { namespace geometry
{
    
namespace srs
{


struct iau2000
{
    explicit iau2000(int c)
        : code(c)
    {}

    int code;
};


template <int Code>
struct static_iau2000
{
    static const int code = Code;
};


} // namespace srs


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_SRS_PROJECTIONS_IAU2000_PARAMS_HPP

/* iau2000_params.hpp
kzw/O/VHWq/y5qn7ab2q0KP+t744OYP2R6nf+OoXJc/wpT3+GOpfIFGbDfZ7acbZS2tFhdl1J/2x7vCk70ONytJ4T9rDyYcg4x/qDp3p4h+w7VYmlj1o2lSueAQ94czN3FZob1PDhlj0MEJnOrvqaI+bJ+2hoxikLFmi3pC8n2IZ3nAE7mz1jbp9K/v6Br2pC7hdWyxN+9zrbAnuph1NKnHepl11+1Z9rkucP3c9ZLzhIsWtvuNuemPd2m5kypM=
*/