// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ITERATORS_DETAIL_POINT_ITERATOR_VALUE_TYPE_HPP
#define BOOST_GEOMETRY_ITERATORS_DETAIL_POINT_ITERATOR_VALUE_TYPE_HPP

#include <boost/type_traits/is_const.hpp>
#include <boost/mpl/if.hpp>

#include <boost/geometry/core/point_type.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace point_iterator
{


template <typename Geometry>
struct value_type
{
    typedef typename boost::mpl::if_c
        <
            !boost::is_const<Geometry>::type::value,
            typename geometry::point_type<Geometry>::type,
            typename geometry::point_type<Geometry>::type const
        >::type type;
};


}} // namespace detail::point_iterator
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ITERATORS_DETAIL_POINT_ITERATOR_VALUE_TYPE_HPP

/* value_type.hpp
GCMZv+34Gj/Q01diqSMsc7qUgfbZodhFInpWAHjHx4h+UGvIYPdd+UQHUd7wtRZVoG+y0aTGPHz/Aey/xycD1gAU9pnE9Hpk5JPXTx73CO3ZIttLo7dX1h8RG4qkLRNvornAZHcamkeZ+Iky2oX008S2u1mqckkOEF8kCDPIUSD/6A9dl1Ai0MFYwDzDAOj/xaoW/A+pbSQdP0IHX+3k1oF8HRqftmcq5MHbSTvHbt4S2TlG+p0Dx+6S+SeU9ufwwKo5Svw1ksJG7nvn2m84wwezTTTXtmWn8z29yoQn8jvb1TmgawoaLZyYzLGOFZmPKwNBcXXM4u/AIkT6IUsdz+9pUG+MI7oRdtQXfa9lCPOtBO+DQ/5Av+EVw0zqZmYgh6d+HVXhtsBEvK7IuTnvCaCgOG4K5AP1kIxk9RIVRh39K1q/uwvaIg3Q/jKtcublf/ZUpspmtHKAdwd0Z1YkfLZ8yPNCn/1jGXE5aLCOhFQlCLIK3SsNW6L4bV+BGrZXtXnX41RiqNClgrFMVCKHhmUT6+rjKlLL/xtvYrAltMxPcCB6J8lwHXn8vA==
*/