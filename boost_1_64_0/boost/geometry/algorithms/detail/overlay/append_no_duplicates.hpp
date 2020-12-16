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
rUaPjw7tyIfG8n3z/TX5jNBr9FLbXtaqeOoA+pLDTBTjDhrXWL6VfLfB2S3GJIdtxt5rsuXieWGevluCrTyollN8Bh/tKk7R72pzumw+l/hCrlN8yxhn/YBb+/+x/Y53bI3b6eaXZH1eLg/PTtJh7st8A44e5ltVpuLwo/Ct0fYDWufFm/hDBTGRXXcv4jm6RXAiRd2zEt1v+evdD33URN75GraIue/pf5RwThq+/JR7nBDz5veHtaPYP5u+awp/nyS28cdy/T3nH4txL+Lcp3DpaTiyWs3vMLekWP69vQQjfF6znz2g7Poj9607jG38g++pNVU4KKbjS9d7HmmwmmIHelm9lu7xt/YNxQd6X5wir2gvdvDZW17/671IJxuR7jg+/6qvd1AtmSM3wGlXq+/x55rVcBZxvMLG5PMq6srylL7Jd/zBsfAGuxls/BPZiXt+MVu8tG+6vXy590y8XN0+ZaV7LeZ3pdjI72yDfn9j+wvYzS3lxWnrPExvIH265PNabB+Wb8Z3q/RSJ1YTSE36AM790D/Zu/M4nas9gOO/mWes2fctJsbOWJNsWWbs+74Mk2Uw9jVLiUo7IRVZCtkqulRuRBeVSkoqdZNIEYoWZVfc93ONpXL3e1+v+wev+7nPzG8953u+57ud80z6+6Qx7TieTIrpwwn5BP9Qht953vg3/NQ862cODTZH+Z285vGX5km5UWRRnUy2sZXekZEsZ/NT8WfZXHHkQjn4yDjxHNt3m/xol/nY4l520Dy6mf9NNLe7iMWmthJjyQ93trO+wK+v40eWs83fdpU35zeXrK0+4b399/H3VbxPTv2ImP6NCPb0Ou/k32rT8WLGp5C4uPJX9Ep/Y8zh9YXtU/J7hx4h8TrdJRN/38p+C/U9Nvbcbeoad4mFjefHw8mDXRrLZs0opq9i/06nAvsf2ETx5km+ZiP5nE4XksuJhWvwaebGlGSxfEW63VWfFgbWTdQ42YTh+rhbDH+qAL8uhy/+iWvu9A56v5W8S+RmX5aJ4bSp5sPiznvt59slDjjAr7IF9X9Rx88rt8jBpqgVl69jDiyhx9bRFsqlxIS+26duc0isIxc/K4efRLdGNhb7tSNr7a3+Hf9dUQ6xVp9rme97zTVjP6WVnP9B43iKr6EzEcXVBh5iq82fivLnU3S2MR+2/aA4iZ/ObN6t+oRNNleeWGl+amvzJsZvgJiALt6hHa2Oe0Y7cUMzdr8nfTrK73zqWfTuhkrG81XzhF1cmF18iK34AE1eo8dVxUiP+RRj5uggt3+BTR1KV+7kI8WJde+yJ3K3PL0UP/aK+nUH8enPbINxKjZafX2wGND1yxbTRW1JFeiL2meVcXwqH3Fre3NbXWKRuL3oEn5crSHbs9Y23zMmU8yv2d591LvkOxM28l838WmPGw8y7kCPv/5WfULO9tZx48XWbv7UOBu/H4eKg4Z45iA52+vqampzhchsZF7zo5Z5+AL/W0beTiZrt9DVN/gtMceBDmKWRDbXWsYAz/pI7PFtGjml+OoUu5VjjD1JYpxJ7GHItTHDzHv2tEhv8a+6ao4sYm42LKP1hZ1Fw/VfdeYnxAls6/FuYkJrIQ+HxKRpwn/b0LteJbdNbLPxP9LM8zKa/64vUpTN72PMZ6oV3mcOa+MIc6PNTHrbSMzant/ty97xrW96x7qCbGw7sphLL9V9c7Whw3fwD2XljbeIJ9qrW/C9m8n3hLre6JnWBTx3b3+5Ef2sU4sfMhZZD8tD6eSx6daXvHOG9cm26/i9fPxMtsD+RjmGtcjsQ/hj49c1YG/Zi9695edNyWW+8RwfoUZLDuxE6DY2xlr5tmbyD7K83lw7ZF1rGj8=
*/