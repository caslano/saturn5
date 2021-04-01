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
iD4qMTMR2KJnb50MMY6CWkecb6u2W+bopzZA7S/u/HUpoKIgMIaviKj5JkI7TZDNO+S7UA9p3KjqbT6l+gCWjy7bWDYE2HReBT7ebGogmu31fpHPKF6RE4o8fAEuBUQ9SBZP3aQK/3ro9UcTRRK+a2EGJO+IRng9K24LmgTDmRkRifCmykwb8ewgmlIw2i6mRzzPemeMem7qjPRYj78uWju++9+nDg0EHGQydhRY178tLzz69TZHle5jRFtEigIDEa/wo0PLF2LyUa+83eyqxzI7spQB3OFSc1e6dAqwv77egQuzmjBJlpGXtqooiLfhunGzl6oavrwDhF2F8vUchWP5Iki5/Ax2wxiKaWuD3EAAgOwCF4zizcc+IX60TEFVvcgGI0h0919XfDDg/5CKzLrmJ56Nf8Vclx1FutTWNj3955uo8a67jGb/hlx8YnHnGv/wDmHNTsSWmqiMs4aCDF9nbst3ZJuNaK4CqejYxKInleRi68OeQyVwZCFvBs7IfMq+BghuSCLEWWrOB72m0tJ6OAW/ckNi+2v5xq4lA6cpK8+ihiiAWvPQJA==
*/