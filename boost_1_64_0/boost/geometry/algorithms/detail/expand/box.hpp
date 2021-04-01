// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2014-2015 Samuel Debionne, Grenoble, France.

// This file was modified by Oracle on 2015, 2016, 2017, 2018.
// Modifications copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXPAND_BOX_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXPAND_BOX_HPP


#include <boost/geometry/algorithms/dispatch/expand.hpp>

#include <boost/geometry/core/tags.hpp>

// For backward compatibility
#include <boost/geometry/strategies/cartesian/expand_box.hpp>
#include <boost/geometry/strategies/spherical/expand_box.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


// Box + box -> new box containing two input boxes
template
<
    typename BoxOut, typename BoxIn
>
struct expand
    <
        BoxOut, BoxIn,
        box_tag, box_tag
    >
{
    template <typename Strategy>
    static inline void apply(BoxOut& box_out,
                             BoxIn const& box_in,
                             Strategy const& )
    {
        Strategy::apply(box_out, box_in);
    }
};



} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXPAND_INDEXED_HPP

/* box.hpp
t3Jr2JHhzgF61L0DWNMfUv1G5yW3yzbVCoof2z+GhoH0qQUzeaBDKQhSq52FG/7qN/5PiG1YV97XoChJ35e3jvNA0AWeBjJpY37mKmyb+DCog0DepCkX7auTZx+2b/rMstDL7paw9EuHYPJ1LMIq2xyZKc2X6cnUe5FnOhDCP79k6Uo50m6oqeOYgizf9k2L+yaLf+cGIYDtNiIkV2Lz9/CfJ3/JjmqJt/WRQur/A2pBqIqRT5YsshqDsIJCNARTAyoPT/AIb6s64HA7eGZk67Y7XKl9UHkYrrRwUT5YlsXnZ3ibIGjNMv4s43bhnmfEmLHIwzMRtInR8gBpjv8sVAp5vx5iR5OMKZCp+28QbKw9ZMNnqdB8QMQvJWhN4pXYtxxHW24ksXn5BEMVbo2IHF7ZLx/omYIkmKP6D077uFyH8LWy5Zmc8BtbyghZSw6wR50nQxGZIEPRNFSTyPJcge88Dx00QV8c21QEsweh92zhm6CQrbHZ9T+/RurPQYUD4n4l0ptCmKqmyhbd6+OvHOzva0B19pYuF+x/qv/QR98RbIfPcwx00Pgumg==
*/