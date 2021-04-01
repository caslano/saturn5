// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2018.
// Modifications copyright (c) 2018, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_TUPLE_HPP
#define BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_TUPLE_HPP


#include <cstddef>

#include <boost/tuple/tuple.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/tags.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_TRAITS_SPECIALIZATIONS
namespace traits
{


template <typename T1, typename T2, typename T3, typename T4, typename T5,
          typename T6, typename T7, typename T8, typename T9, typename T10>
struct tag<boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> >
{
    typedef point_tag type;
};


template <typename T1, typename T2, typename T3, typename T4, typename T5,
          typename T6, typename T7, typename T8, typename T9, typename T10>
struct coordinate_type<boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> >
{
    typedef T1 type;
};


template <typename T1, typename T2, typename T3, typename T4, typename T5,
          typename T6, typename T7, typename T8, typename T9, typename T10>
struct dimension<boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> >
    : boost::mpl::int_
          <
              boost::tuples::length
                  <
                      boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>
                  >::value
          >
{};


template <typename T1, typename T2, typename T3, typename T4, typename T5,
          typename T6, typename T7, typename T8, typename T9, typename T10,
          std::size_t Dimension>
struct access
    <
        boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>,
        Dimension
    >
{
    static inline T1 get(
        boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> const& point)
    {
        return point.template get<Dimension>();
    }

    static inline void set(
        boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>& point,
        T1 const& value)
    {
        point.template get<Dimension>() = value;
    }
};


} // namespace traits
#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS


}} // namespace boost::geometry


// Convenience registration macro to bind boost::tuple to a CS
#define BOOST_GEOMETRY_REGISTER_BOOST_TUPLE_CS(CoordinateSystem) \
    namespace boost { namespace geometry { namespace traits { \
    template <typename T1, typename T2, typename T3, typename T4, typename T5, \
              typename T6, typename T7, typename T8, typename T9, typename T10> \
    struct coordinate_system<boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> > \
    { \
        typedef CoordinateSystem type; \
    }; \
    }}}


#endif // BOOST_GEOMETRY_GEOMETRIES_ADAPTED_TUPLE_HPP

/* boost_tuple.hpp
OZSdYLeu5qkT7a9oQIz3K1GPYmle9H4srpgqVWbnqP9GhJMbD0rYu9E36r1nzNPyUejClTkdF2Myw6nOkhZ0lH2XuhT1/4pFOv0BFzZfjN1SiFGfhcM1pKGtVaE2KjlOaK4J9WFA8Kdc4MlFP3nxFlZFeNZvCqAJZVpEN9Q109XPCzsd6bus3amRun/SaNxxJ6KAtWCX8syF1jW/JMYMFfGyZfbsgMEOTkkZMlZVTAgUtNuIPpJCyK+jeX98esn5+U0ipPhOZEKP+DhhgBQrVudIJBYCxZHuV409F2VX4+AVIyJOs77NKLWTAuVdU+8w+pefGtv2bjgJ5uXca4g8fXFY3oNhug96O1lLz+/nYw0VgEp0k0xd0oy8aHWDQbAIVZV2DIxhgTqBC+03upYmLFw5wHS7BK90/cbg/M2sI+LNu8vWBtMDnWYPIlou3E/JrmUHK7oLaykwrhqDRDgRzOXKpU34fobk5u4EjyE4DUhQIl+8kbIRsYciI94WEIcLAP0pCC7PoYvwn7EoYWMK06szdn6z31dFG3NCiN/OIFRb2nw5qsHu4eCq5A==
*/