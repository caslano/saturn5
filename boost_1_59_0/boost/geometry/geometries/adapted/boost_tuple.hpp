// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2018-2020.
// Modifications copyright (c) 2018-2020, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_TUPLE_HPP
#define BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_TUPLE_HPP


#include <cstddef>
#include <type_traits>

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
    : std::integral_constant
        <
            std::size_t,
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