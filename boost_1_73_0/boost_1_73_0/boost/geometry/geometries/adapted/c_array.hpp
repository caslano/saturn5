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
AhCC5obZ0R/BiqMobHaPzg5g8aXeJWkzMHa06hWJWV1RYfD++PSwe7S7MxiISRslON3W7XfPWw7YcrCzK4iR0fdTt79z/FF21eUvfngFZeV9To53Ch0kK0p7fDo4evF88GmnVwHwIxiGT9CiYsBvYLNjiNXHkwExAdoOep/7PaDw8dFZjvaotCTZR27qsvRuCqoRlQmTi3GIGmToTlEblcu8zWMx/mSKcjVxbwdpiZzoRplqlQHTL4EEheZS7Eog59ZSOTzeSEz8qWj6/nxvD9c+e/H8FQOdAhppDFRAI4Xtm2nUBB1P2nIcRG4qC4ZuMATdy3XNSpW/NwYTEnqXbgpuE9t9T5xi9Rft71ngpWgcHFJRklfAxpPuafdjr987PSMzAhgFoLVZkgKMIXhx6KMYxB8Muh8P9rvgeT4VS27v+PRjt4/8NpjMDqOZFzeHbgJq3r/002STIRgBdgiLLGXDKxcnDQ0HvM0vX9g2W221n794+d2r73947V4MYYTLK/+362ASRtPf4yTNbma3d3+sdmiU8+l0uVEybFgxSvf9zm5vb//DwX/+ePjx6Pjkb6dn/fOfPn3++b9wFEkr8Id2PnRP67fOXIdbOd7AInDVvi7VON8R9W8dmO65k3pdiRNOxIHxG6y+d3DY
*/