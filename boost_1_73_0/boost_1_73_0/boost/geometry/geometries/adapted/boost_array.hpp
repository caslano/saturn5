// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2010 Alfredo Correa
// Copyright (c) 2010-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_ARRAY_HPP
#define BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_ARRAY_HPP


#ifdef BOOST_GEOMETRY_ADAPTED_BOOST_ARRAY_TAG_DEFINED
#error Include either "boost_array_as_point" or \
    "boost_array_as_linestring" or "boost_array_as_ring" \
    or "boost_array_as_multi_point" to adapt a boost_array
#endif

#define BOOST_GEOMETRY_ADAPTED_BOOST_ARRAY_TAG_DEFINED


#include <cstddef>

#include <boost/type_traits/is_arithmetic.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/array.hpp>

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
struct boost_array_tag
{
    typedef geometry_not_recognized_tag type;
};


template <>
struct boost_array_tag<true>
{
    typedef point_tag type;
};


} // namespace detail
#endif // DOXYGEN_NO_DETAIL


// Assign the point-tag, preventing arrays of points getting a point-tag
template <typename CoordinateType, std::size_t DimensionCount>
struct tag<boost::array<CoordinateType, DimensionCount> >
    : detail::boost_array_tag<boost::is_arithmetic<CoordinateType>::value> {};


template <typename CoordinateType, std::size_t DimensionCount>
struct coordinate_type<boost::array<CoordinateType, DimensionCount> >
{
    typedef CoordinateType type;
};


template <typename CoordinateType, std::size_t DimensionCount>
struct dimension<boost::array<CoordinateType, DimensionCount> >: boost::mpl::int_<DimensionCount> {};


template <typename CoordinateType, std::size_t DimensionCount, std::size_t Dimension>
struct access<boost::array<CoordinateType, DimensionCount>, Dimension>
{
    static inline CoordinateType get(boost::array<CoordinateType, DimensionCount> const& a)
    {
        return a[Dimension];
    }

    static inline void set(boost::array<CoordinateType, DimensionCount>& a,
        CoordinateType const& value)
    {
        a[Dimension] = value;
    }
};


} // namespace traits
#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS


}} // namespace boost::geometry


#define BOOST_GEOMETRY_REGISTER_BOOST_ARRAY_CS(CoordinateSystem) \
    namespace boost { namespace geometry { namespace traits { \
    template <class T, std::size_t N> \
    struct coordinate_system<boost::array<T, N> > \
    { \
        typedef CoordinateSystem type; \
    }; \
    }}}


#endif // BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_ARRAY_HPP


/* boost_array.hpp
R5KYVR+ppEUfz5mqHFmjOYvA29NNEzSIAVpLbk4eogSwMPyxVFpkOEP2c8lg2phuVbKcBulak53Gfm6qXXUx1ubIzvEKt3SWg4wQL4qRz7cnRKLaQKlt94DtvEYdBU8Y8dCwoSeiO6/KgSARfNI8Awh9+9axCO0Bod1X30pJ3Yt9m/tWxTZ+s72lXvIW36oM9jwSiM7MaYv+Ss5byY+6kTjRz+df0Z0UY6uT7EAooFiB6uKjy9IHk3TZ3hwRSvzVV0h3/zGYrP0CQN3PO6DbLQIXCgjhJ9Z9cbC7d9DdB/y9+2odWJfOjQO80ltAF6JH8Vldl30LdMXNEX/AYm9DP+tBuoyZ30GuWFEcpQsaRU91Y0zwxb0ryOLBzK6tvzkr+iEfWyjoepcyMwX1Ddwek8BJMsFSqL6Ys4wXcUL3sWjgQYnlsfDiyP8GrrvfyHVpgg2MfwIcY21izRbn9OuU0Lh0vGUZsiOuLnFfTfouuDsPAkY8A/fFHyTp2BWo98cgerF33Y+XQFEk6gY/66u7fyio3zH0ql/MpA+t/M5SkJaP/JEc979AzqgCHQ5lNHYagNrjebTPH0L66Snk/vT7D+jyX3r+ovshdEdiZsr8fiv9Csf8nGwp/chdmhW5XrzsiKid0S/EEkhGOndB
*/