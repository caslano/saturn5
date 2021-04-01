// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2010-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_REVERSED_HPP
#define BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_REVERSED_HPP


#include <boost/range/adaptor/reversed.hpp>

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>


namespace boost { namespace geometry
{

namespace traits
{

template<typename Geometry>
#if BOOST_VERSION > 104500
struct tag<boost::reversed_range<Geometry> >
#else
struct tag<boost::range_detail::reverse_range<Geometry> >
#endif
{
    typedef typename geometry::tag<Geometry>::type type;
};

}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_REVERSED_HPP


/* reversed.hpp
uKE9OzSey29J15RattDPYRZo9phE7C9tl7twVxil7gffMD4jPHAsMsPGWhlrXJPY4dKHev7j6/RSoehT40gPkU4DupnMKiTxV5fuw1BexPmnc+/r9Z/jvJo1spXHuOYThcuVqioGprt1wJkvoRHvwBwK+e2iEyw9xpmk8ZVTG1G0T+2Uo+yT3i0s+9OUSH2+IYXH4ceFwGXrxT7gXTA5+NuWf/89Qrk7cEex9uTxl4BbfFlArM801gadyeOm/IXgcdFmoPAyKexLKnGa4Rewr92T0k+KNiTalJ47JPKkfZIvosbWCeObhoALT14/B3Ns7Kf+dvuLXj2mb+ZCzxCdKyZaqoFIbMAodKIhec8tlhCQWKJXhQuB8oIfCIc/J8aSolGleb0DE+UMKIWvhkjEp7rsI36//PCwA4RPJqriI3dwtvAn1jtpkddvthXBeF71ArzDAJEqpx6iNFQieTttXa7rWHg9h9jV3eLp07ep0WkwawbnxX/FfiE4TMnwrqKRmlXZWkZdUeCtXjNUX4cARav7OXfmeFdQIeECDAFoYQlJJLBkrJmQ/nF/0g==
*/