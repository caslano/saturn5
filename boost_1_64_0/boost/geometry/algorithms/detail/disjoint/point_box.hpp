// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2015 Adam Wulkiewicz, Lodz, Poland

// This file was modified by Oracle on 2013-2018.
// Modifications copyright (c) 2013-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_POINT_BOX_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_POINT_BOX_HPP

#include <cstddef>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/dispatch/disjoint.hpp>
#include <boost/geometry/strategies/disjoint.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace disjoint
{


/*!
    \brief Internal utility function to detect if point/box are disjoint
 */
template <typename Point, typename Box, typename Strategy>
inline bool disjoint_point_box(Point const& point, Box const& box, Strategy const& )
{
    // ! covered_by(point, box)
    return ! Strategy::apply(point, box);
}


}} // namespace detail::disjoint
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename Point, typename Box, std::size_t DimensionCount>
struct disjoint<Point, Box, DimensionCount, point_tag, box_tag, false>
{
    template <typename Strategy>
    static inline bool apply(Point const& point, Box const& box, Strategy const& )
    {
        // ! covered_by(point, box)
        return ! Strategy::apply(point, box);
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_POINT_BOX_HPP

/* point_box.hpp
7H1SDwGzc66REyvZfAu+348ONwrfxBveZ49bu9orNZemrQ68vkZft0Tc74an+sWx6vaDMK3VPD3gfr2duL1Yj3BDfvX3ycQ6MA2ykRhehJ+NgFu+89vL6lgpcXoPvH2NLf3dxKZrN9DyurAL/PloGK38TeO4Rt7i3zN+8FlF69N4Q4ES4o5fJp8jty9Tnxero2fj1+Z6pbF3sYckJM61VO3k0zNWiP/v9CG/0lbY+YNX4VIvvdWr9Ej9TZ6i6sFTYk3s5Iejn+qHs4u5o1Wt6al1Iwqx+zA8ZDg9LQeN+TAt+3y4q46Uqyp28JdC9IjnaondPHiCYw/oo7rnTnAv6ypZYE1M/KqhJWmGEaxcdhtsUVtmsklj2DDuCjrljzBf/icNVBtz4T60pfgX5jVaH91br+LcOXubH5s/XU3tfJHe089aYIKj4bpZrVfceS/d1LxXxGhh+smrXbtKX/rZ+fJzA41qKP/Jw5/olpXPoJPBvL3X0kh+EC9sc459D2sd23BilP5sqDGwspy606Kz9awJ6t2l8qeW/mcumyd6yaHy8DLngxH3ZTJOmJxf7zr4AfnTk4YMR0deCN+nwC+5vuFGHIINBl2MD8KEXE34n29qifsOrcXqGFxYzE8QM2MuUa+b46311KP6NIMs9tFVU+tW+fcO+FZFPPbUg8KoZWr5ZPZ/JAkWwN132lmbqa/3YqtJ5hP/TJ5dBXfU5qG79Bp91XJawfK2OMsQ/oeNSUej0CdNTg3R779iDCVhHF1pCDvnbyi2eob0Xv55nPChbrB6YuK5Kfb/rbC/7Us1Q50dYb6/DmP3h/WPm82hoRrc0/XMbfzF+irruDuejzl/CHWCfQbVYUVJY0ijJ46gC8CazfKj03Q9715zet1ftfHQ5WyDs8+4Ry07ym5qzmc5XLdzzB4Y428IF5fBPHp2b/Npot+px0b7C9Ng1b0HxXCXJrgPzPzxfNyumxxI7NnQO9ZVly49CJcqRenrEQ3ogb1gcfmN+oav1eff7Ds6Wx41jtJrzL030Z9b6Y3lURYcdfQJNb6qnLEHpiMM6aUevfyt/sQa3DQ1JTtcGEdvG/cWe1nLbMsGLXDDNh1oCuzQq5zakqQ+rWPT92Mhk5w/rK62Loi7b5G7cnzCveygZjR8W/094HryqtXtamdh6zT3yKtEv34Y3tYSPzB2qrHXmCjnv9IDF+U/uFHqep+NFitviDWfFSjv/COscRxwPO488Xm65t102WzwE77P6cwvxh5vRKOqoE59So+y9vGuvnjboBBupCUlPeY7eqP8heE1zK5fE49We1O+wvu+Ue9rqxeV6cMLcSDHX79dr4NDdWiEFzwkN/RiW98Vz2Nw17XsIteWq8/TntGz0qbHfEx3dNzESXJLXm+8SJ7bT/TTEPM5Fxe6GvekVZUrQPtfR0PsKjb0iF/r8zdmgn+1jUdORIVxMnU3pkY+ZZ9mbceM3HGyj8zzAe1tsf4VHvYcbIwTxEtP+NrGWkIeuI6DFVsutu7l4yV0BDrnm+rancbXQN9RsZFYfZRGeAhGZsZ5W+Ej/n6fJke38nkX9SY7XB1M5xHrt9Phct6v72sHR8dZh8PbEvc43qP/SlkHg4yhSn7cnX5yQebEmm8IJ8zz3iqwW/84X11ZVIme0JhGKc67nIuLwuypw+VIXvGRAi8m4l/w9ztj76Ff6oQn98U796y2NjpaPKv9m4vobVz3db1hu67WBrK47rVqUtCTs3HPLvY86McWp+CAr+E+l7OLerB+FMz+Ax42XS4/jBPMYe98cFVvX9acs6bpj+TdNp91g7XvOq7adLGJF37TQX+Fo9bPh6Mm7o9m426wOk+MXbKJT9w=
*/