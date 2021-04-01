// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2018.
// Modifications copyright (c) 2018 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_APPEND_NO_DUPLICATES_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_APPEND_NO_DUPLICATES_HPP


#include <boost/geometry/algorithms/append.hpp>
#include <boost/geometry/algorithms/detail/equals/point_point.hpp>

#include <boost/geometry/util/range.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{

template <typename Range, typename Point>
inline void append_with_duplicates(Range& range, Point const& point)
{
#ifdef BOOST_GEOMETRY_DEBUG_INTERSECTION
    std::cout << "  add: ("
        << geometry::get<0>(point) << ", " << geometry::get<1>(point) << ")"
        << std::endl;
#endif
    geometry::append(range, point);
}

template <typename Range, typename Point, typename EqPPStrategy>
inline void append_no_duplicates(Range& range, Point const& point,
                                 EqPPStrategy const& strategy)
{
    if ( boost::empty(range)
      || ! geometry::detail::equals::equals_point_point(geometry::range::back(range),
                                                        point,
                                                        strategy) )
    {
#ifdef BOOST_GEOMETRY_DEBUG_INTERSECTION
        std::cout << "  add: ("
            << geometry::get<0>(point) << ", " << geometry::get<1>(point) << ")"
            << std::endl;
#endif
        geometry::append(range, point);
    }
}


}} // namespace detail::overlay
#endif // DOXYGEN_NO_DETAIL



}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_APPEND_NO_DUPLICATES_HPP

/* append_no_duplicates.hpp
/WvOdkTHSH5Um8xYvmrpX1KdAadzV2IxP3PHzlnt2gHGtcCCFPnGh4GO0bM3irGnJCc96bfh6jN1ZbFxJw7aH1ugZavwyf8uHndj/QotfI7zeCEVNBaBUSjnb5HpcfndhflPVIId9uTflYF6syA6YI22Bu1xEw47VFly5cb/ZCM9QvfdELVqUt/7OjVUBPOyf0jQxwN/8Wyc5X9GGNG6yNHrf7IJDdqreh9BXRWc7+Zmiy3o0Q1CcN1gpufTFPTbAD+3gqBCI+/san3j1lJyr2GPjh/fow09Tm1F4k0sNM40xteZeF53uOqc8nvd83BXLBLIqBtMLbP3GPLMv81wmIs/PtxlOAQPlaTmRXK4oEyIdakphwjvvWB7qvtLfpk4tFykMgBxWT+3/Oy20wqV8d/Y3uwLct1B4AtNRBLPSIGNguFOS1POcBEInzTfcwmUoyYkjXRM7az+Ho89XwutyIoEB/hGYpOYXRLGeW0RAqYFbJi1lWsbjmwQuPaGHzcpN80/vIGQF/zRaZHNXc4VIt+S4BtuVy7Q53PNna8ffMOUEaakJ5J2PNh/Hw==
*/