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
P6n8NyW50dKjGPuTD4nRg9iYLSbe2jPNttuG3WPYRXeJi0tMiDP7qaUfIb8zPPJ7tPnmqenCbJxHfmdqfm+K1vaioVvqWsJMKnXmt4Ql6S8Kr2PqNqbZdaTIjnNoXDQSVrpaIwOQp7vg2xWXootq8ksjxUXddnWsxahwzj1Q+55alu5v09lBe/PteYN+0+/XjLIoCi8LnVcvcQgpC7mua8/m1br+p0sAcgZDJWHmudI/r7xySX5loS9im1f3XTzb9NlBe6mbm8nzsbGBupmQSNVsES31r7llGd7eI9e1lXpWQA87JCQf//Wu9M3nY9rQSGlTtz3Evsa0X01b0F7StoZ0dYoLpC061Wp2gbSlqd1o7B6y0u2j3bVowakAvm+c9hrT9txlu6VFeNkuxP/20LRrt+adfnWvZds/KTz9ah+xP9/uKPvVceRBC82f5GD+2HYzsHvEzp+4uG+cN8RX8ybyfeA0e99qPTegTPuCYqSEMPeH5Rd+57NzNduuzyupLSqMXHfUbzuzf2Z0WWD/zBTjvqpmrnjR/DR+yuw9dfkFruecu9tDwmkd0PlrpuhRjn3ztYz0HjO4LHjP3ZLCc6juBc3e+FJGMo9L3HTzpWJ2ju6nlSxmk5lZ01ndimO9Xgv51o8qZbuVslvWkvf1VtmOpPzaxofXCc2X48V/hup+OzwJ5xAXntNS68gp1JFErSNqV4vdI/Y1omPFTuqJxqEJ+wcs+45xcdHtEqosVzFW+rCvw26bhk3I0dYGvdH4sfzb9u8gD6n/xJi2iTFqb9fFTkeoi+khdTEVs37GTMtb3VqkPAJzY0PqY6PuEV+r9bFK62Nd2ZHqY2ak+qh+25n9YG8Uvehw9VH91EasjynweXGTadYpfKHlGak+/rgZ9fEhcdPPVR/vErNZvlEh9fELj/qY1YqyTND6OF7qY6CPxmxbgtavMx31S+32II+oH1f90jAnUy6P2vWrfUJ1Qklci8TYGKlfTfjtkmjqV8wA6ldM60D9OV7ts7BvNPUrKSE+LgrvCScCPt/8e+vaSLuutdZv43qF4XqfTF8UWtcWIRHrl7ofEfFeqfZSDlvIh4mttRz6SSYE2qHaFWLXKPeChPnYxrdJjGv9Te8Hke6VO9sEQsjSkCYhtfiv8Ez/sEjpV/fxpr+vFX2cuO8Znh/qPiuQH6R3RhvNj5OC+dFT7ZZh9yR2ibG+hPiEuQmDcdIiJTE20ffNxxA9Tb6453CO1RBPDQBz3pPif1dYvlDX2Ie+YGFRtefzkbb7n4m/k3yj+VfzTMOKPlwfpG5OjTjGUHvJx1fJp/VtNR+HOMYYarcHuyesehVN+yPhVn3bgNluZJNl3jJhSMLEuJjEloHxx9fNWzkHxLMteo9DTFtM1jP59Bm8BtlmPZOUO/O8rKissIZmHPEZSd33NXOSJ4leoOcQhdVFdd/DzJEeL/qFgTyPc+S5PoNOFPs8LQP1r2eh9Qq9T+jzcXG5nqtEno+z1klbczdhYsxEyWs98479sgN7sjf3mdTrOYg0hj+Txnnn+Tg9IKhVAPI99DnyfJcrzxfVlJbKy49I7V/dt2r2c6mzvjjjE6PrXez+vyMyH7dNrvhUFBUtZPAZuQ6o+6RI/bHad2p2fIua0afa71V8uud/hwBELbP+qQhNgz6ARE6H+ukQ8RlE7SP2D2r/jdLZnGcJu99sr4nO1LHbIOQi634alnbHi6XI6Vd/vSK+Q8oQ+07ceWI1T2w/SZHyRO37faN3Dc1572PXh32aJwM09BO0TueF5YkOMiLnh/pJj1Sv1T7epLU4kH/fqPwj1fPdus5hrIZ0EnIx/jd4p2vYYdKlfhJMvB8SfWik8YM=
*/