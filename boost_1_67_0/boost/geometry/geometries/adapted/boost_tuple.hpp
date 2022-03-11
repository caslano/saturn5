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
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
*/