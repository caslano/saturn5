// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2017.
// Modifications copyright (c) 2017 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_MULTI_MODIFY_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_MULTI_MODIFY_HPP


#include <boost/range.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{


template <typename MultiGeometry, typename Policy>
struct multi_modify
{
    static inline void apply(MultiGeometry& multi)
    {
        typedef typename boost::range_iterator<MultiGeometry>::type iterator_type;
        for (iterator_type it = boost::begin(multi);
            it != boost::end(multi);
            ++it)
        {
            Policy::apply(*it);
        }
    }

    template <typename Strategy>
    static inline void apply(MultiGeometry& multi, Strategy const& strategy)
    {
        typedef typename boost::range_iterator<MultiGeometry>::type iterator_type;
        for (iterator_type it = boost::begin(multi);
            it != boost::end(multi);
            ++it)
        {
            Policy::apply(*it, strategy);
        }
    }
};


} // namespace detail
#endif


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_MULTI_MODIFY_HPP

/* multi_modify.hpp
NpVuXmLmog9acEz79pQIkkcZHuV4jE8gGzLzOgOuAyjHLc7DysZWo7UDDMqZLsKZnTm2U8ODzHvHv9mAMOZDx4wUQSGZdb65+1ZDP+FifW6SLSMnwRaOKqEVPaCRELcUWtLN7/p9yGLhIzrorR3w8aF8AjmyoV4o0+wlkEz9hoLBwsVBF4yZ/loKDuHc0geDWXDM/X4Tj+YcowWZNDPGFdDdHLq5oRtnFqFpA+ccfZnLORqq+/7Zgvyk4ZOcCPXvF5HPg6qeWTdtKX2WXAN40bb0oo1OcaXDVH1glWVWNArLPAUF/Ku+VE+MuowP1Wk0puA836msX1T/unP4O2QGCSsvWcc1bofd8tthi5Ytxh+zHElLwrGBgSFmUrPwyPZKEURkDw0SLc1UIeYD+gDyw7n4OovMB/XrZkRXtVt8bgxQh7CzFShcSanJmU3csijici1lc4WPU6CaZWs2p9nlV1OcknfXadi1pHEJgcbnp9ngczJfOq0+CZtN12rDmjKCJQQiYMl+ylEuu1sWHy14ZMFRw1eIhAnjv4xm6MFycwyOYD2IfgXb3kKQhteI/gdCtLTf3pxQOGXrj7a8VtSctf8Fp0iP4EpLcdcBBTT5QQPwfbU0GlGOOGEJ9Ea/WeR83wiy3Yd3k2NiJYdz
*/