// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_VIEWS_DETAIL_RANGE_TYPE_HPP
#define BOOST_GEOMETRY_VIEWS_DETAIL_RANGE_TYPE_HPP


#include <boost/mpl/assert.hpp>
#include <boost/range/value_type.hpp>

#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/views/box_view.hpp>

namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename Geometry,
          typename Tag = typename tag<Geometry>::type>
struct range_type
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_OR_NOT_YET_IMPLEMENTED_FOR_THIS_GEOMETRY_TYPE
            , (types<Geometry>)
        );
};


template <typename Geometry>
struct range_type<Geometry, ring_tag>
{
    typedef Geometry type;
};


template <typename Geometry>
struct range_type<Geometry, linestring_tag>
{
    typedef Geometry type;
};


template <typename Geometry>
struct range_type<Geometry, polygon_tag>
{
    typedef typename ring_type<Geometry>::type type;
};


template <typename Geometry>
struct range_type<Geometry, box_tag>
{
    typedef box_view<Geometry> type;
};


// multi-point acts itself as a range
template <typename Geometry>
struct range_type<Geometry, multi_point_tag>
{
    typedef Geometry type;
};


template <typename Geometry>
struct range_type<Geometry, multi_linestring_tag>
{
    typedef typename boost::range_value<Geometry>::type type;
};


template <typename Geometry>
struct range_type<Geometry, multi_polygon_tag>
{
    // Call its single-version
    typedef typename dispatch::range_type
        <
            typename boost::range_value<Geometry>::type
        >::type type;
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

// Will probably be replaced by the more generic "view_as", therefore in detail
namespace detail
{


/*!
\brief Meta-function defining a type which is a boost-range.
\details
- For linestrings and rings, it defines the type itself.
- For polygons it defines the ring type.
- For multi-points, it defines the type itself
- For multi-polygons and multi-linestrings, it defines the single-version
    (so in the end the linestring and ring-type-of-multi-polygon)
\ingroup iterators
*/
template <typename Geometry>
struct range_type
{
    typedef typename dispatch::range_type
        <
            Geometry
        >::type type;
};

}

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_VIEWS_DETAIL_RANGE_TYPE_HPP

/* range_type.hpp
7iA2zOM3zBlHKe/rtG0HMRnkQjFUQSOUkqdj5YRQJ3k6+dzE51FISCPO4HMqaexOYn4o5jqbtIM60snTRh31tcRZ0AtFh2kjdpP39WBfqsR9ymYY2Ul7H0NOXCfwflF4z/hMYmN+h9gZ3kukzYN1jAXpAJ/zrsN2YKyYWI74Ngs6eN7G80Ku47ZTJu1u/gYy5zf6w6QDlF/Bs3qo4XnjVcHeZMVq4mCe15O2Qy+MQgJxbBrkQjFUQXIRcR4U+Xf5ojraDX0rKZe0hnISCpEH5ZeE9zRJW/i3jFq57gnv2YbfCe9ffhDZ7QrP7cRq5OneBeE2Q8LtjC2k30G/SbPIWwj57k1mHGDceZY+h3UUFEI51ELxXPoG6cimkbQTBmDGRbQbEpD98GWMzRn0kX/bu/ZcrmE5z0po54yj9ItxbISaBOYeKOGdVGSYA5Xka4BOGIKpF1MuFEA1tEAfxCbRP8iDCmi7nDJJk/gdUQN1lJP28nkYSulP0XR0iji5LrwfSpoDxckxoR4+ZyGjQsYunXYM0O5Y9CK+iPuky6EMaqAJUpBtN+ko9FJmeI82OzzGyC15hD7ACP0oIm2h7HZ+xzkAcfQ9FXKhDrK78TGk3YzbEAxyHVvM/AxZkA9lUAvN0A3DMHVtTCgNwvvUuaQlUAOt0A/x67A5WA4V0ADt0A/Nl1EOJDEei6EE+iCUQD9gMRRDImNbtS0cE1E2dEAf5KZhK5CEvIZIa8P6N5c80AI9MONyyoFiqIUBmMpv2DKhCGqhHYYhNx1ZhAnvZd8R7E+nJFMW93pgFGbMozwogzpogwGIn08/oQjqoQsGIe5K5AO5UAzV0ATdMEBcM0YdcVeRB3KhBHZAOwxA2euoB1qhZSblwiCE6HMOMu+qZ7yghutK7i3GrhpIO6AfYml/LlRDM/SFU2Q6AonoSxZUQRuMQMJ59APyIBe9LYIqmIovq0Uf+7HnMcjJxJahHOKLqRN97YByrvPxCaUQ140OQmm4fdAMBd3kp40VpCWk9dDEdTcMQ+IB3odG5D/4BM8ov596Q5SXCJkwlXLSIQ+GeT+BvMuh66O84989kiATFm8n7+0hfBl1QRsMQEoRbYFKiPfvMrnQwvvt/u0js5hyoQ36Ida/XZTAjHU8h0Talw610LaQsiH+TZQHead8R6gZumAQwt8JyoUdh/G34etn8K+k1X9kj4J7Kasp5wg2/wd88Qs8g2z+vYDBUZ79FR8Asc/zLnSOcD1pYigPsvmtcgekQMZx5oi/UQZ0Q4gy+rhXwvUOqOG6lnwh0kJogRF+SxvPvYSYiaG45/Bh/BsRabzXH06n8gzyoQE6f0d7IG6A+g/hv2hHD+8MPot/HKbMcyfyfXfKIo2bTn7SeqgIp+fQPtJi7o9wXfhH3uPzYj4nQyXvVZMWkGZBJwxC+O+mZeF9hHAerrP47V8NVNPGsb/gA8/nPvRDKxReQBvIn8JvrqdCF/dakGEXDMTQpwn0B6qgGXphDBKRQ3ks5dLPTK4r+FFPagxlcT1jCu3gupvrXK7buV7OdTN5criu4Lqf6xKuK3keO4G2H0aGtHEUmqETdryIzKELBmD4a4zzTuRYxTwAeeG/p4bZFvzgqOALzLfQDzO+yNwIrVsY308xruWMwy3oBdfDzNUVN1M2DEDBs9gHzzOhEKohaRNzewnzBcRuQI9gOVRBC1TewHs30lYYg8Wl6MIa6qTsRkjluhTiP0p7V3INOyCjkDKgfh79gsT53IMiqIMuiLsSXYZyaIYhSMmgPqiFThiDvAV8hh5IeCN2ANXQCbFX0SZohCFIy0SvoRkGIHEh70MNdMAoZLyJeROaYRCS30ydUAfdMDU=
*/