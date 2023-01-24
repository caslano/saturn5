// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_ADAPTED_C_ARRAY_HPP
#define BOOST_GEOMETRY_GEOMETRIES_ADAPTED_C_ARRAY_HPP

#include <cstddef>

#include <boost/type_traits/is_arithmetic.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/tags.hpp>

namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_TRAITS_SPECIALIZATIONS
namespace traits
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{


// Create class and specialization to indicate the tag
// for normal cases and the case that the type of the c-array is arithmetic
template <bool>
struct c_array_tag
{
    typedef geometry_not_recognized_tag type;
};


template <>
struct c_array_tag<true>
{
    typedef point_tag type;
};


} // namespace detail
#endif // DOXYGEN_NO_DETAIL


// Assign the point-tag, preventing arrays of points getting a point-tag
template <typename CoordinateType, std::size_t DimensionCount>
struct tag<CoordinateType[DimensionCount]>
    : detail::c_array_tag<boost::is_arithmetic<CoordinateType>::value> {};


template <typename CoordinateType, std::size_t DimensionCount>
struct coordinate_type<CoordinateType[DimensionCount]>
{
    typedef CoordinateType type;
};


template <typename CoordinateType, std::size_t DimensionCount>
struct dimension<CoordinateType[DimensionCount]>: boost::mpl::int_<DimensionCount> {};


template <typename CoordinateType, std::size_t DimensionCount, std::size_t Dimension>
struct access<CoordinateType[DimensionCount], Dimension>
{
    static inline CoordinateType get(CoordinateType const p[DimensionCount])
    {
        return p[Dimension];
    }

    static inline void set(CoordinateType p[DimensionCount],
        CoordinateType const& value)
    {
        p[Dimension] = value;
    }
};


} // namespace traits
#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS


}} // namespace boost::geometry


#define BOOST_GEOMETRY_REGISTER_C_ARRAY_CS(CoordinateSystem) \
    namespace boost { namespace geometry { namespace traits { \
    template <typename T, std::size_t N> \
    struct coordinate_system<T[N]> \
    { \
        typedef CoordinateSystem type; \
    }; \
    }}}


#endif // BOOST_GEOMETRY_GEOMETRIES_ADAPTED_C_ARRAY_HPP

/* c_array.hpp
f+dn1Ngy8NU8thT7sWW7s74G/J6Z0IHfN9ta2pqwH+pIFnTWa9aqzyMUx2xGE/RM7r+fvlfiqipljGbZRfUZ2PWg+bE/3rh5JX7j3JIPZ7j809/B+3a47342mzAXfWgLaNjLnW0cXYG1gigFEyEb96BPNt7/FokEb085cN+6vXGIWf/MMgAuUYXnv7W2ZZBZIIEIM4DEuttoOWzT8zdbawTKe0GfV462fMmHWR+2fDXstcLGmVKKa9P6gfKkaWJ/1QlW39P9T3yU637bp9MYsU+sFjFEf8ZHbX/F5PjtFeh/TwWhS1uC8fpYLLANeNw7nWN8asSOl8c5//gk+Mhf+6WQoXUTTm/kc+hnlgs6H2m8tUE7NgNrNVNS1sdDjdsGAwPhPlvzgI4zd4XGxiUuoilki/jX5Je0xCmy0saMvaG2+ADRLxRBdxcta4nLPQawJEUJ0c9xfmxfGdriuWfterBnU9BxD3qG8dxMWUc4W1ZTgD75uyX2M9Z3cXpkOpqqvZCZvXLZmeNreZ9/6HpmKlt4nEkT6y+/OK3sSaHIk2nibFr1TKyxNGWPOMkU3wJPTRV8qukXGc9ANNEyOML6W5BoubNAO/K0pMk4GpcNO9dX92lBE+u3B6lM2b69swS+KzSaEPjTM6FnHzsk8KvhDLC5Kchpl6fBH1h/p6CtCic2h0ORoHiuF3aRL7XDlifsItAis0H7WomgWSYJ
*/