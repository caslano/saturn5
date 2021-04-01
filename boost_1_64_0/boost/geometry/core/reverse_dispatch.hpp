// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_CORE_REVERSE_DISPATCH_HPP
#define BOOST_GEOMETRY_CORE_REVERSE_DISPATCH_HPP


#include <cstddef>

#include <boost/mpl/if.hpp>
#include <boost/type_traits/integral_constant.hpp>

#include <boost/geometry/core/geometry_id.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

// Different geometries: reverse_dispatch if second ID < first ID
template <std::size_t GeometryId1, std::size_t GeometryId2>
struct reverse_dispatch : boost::mpl::if_c
    <
        (GeometryId1 > GeometryId2),
        boost::true_type,
        boost::false_type
    >
{};


// Same geometry: never reverse_dispatch
template <std::size_t GeometryId>
struct reverse_dispatch<GeometryId, GeometryId> : boost::false_type {};


} // namespace detail
#endif // DOXYGEN_NO_DETAIL


template <typename Geometry1, typename Geometry2>
struct reverse_dispatch : detail::reverse_dispatch
    <
        geometry_id<Geometry1>::type::value,
        geometry_id<Geometry2>::type::value
    >
{};


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_CORE_REVERSE_DISPATCH_HPP

/* reverse_dispatch.hpp
Fn+0X3b//BhMN9Gu5y/GPoGnOOkDd6faveUmX6+qz2xFXiAwXZ+zxU9KtS2Tu2s1Ko33cy/ntH54ncsrP4jlcJ3Spu8/osMFmuQH62e8ZR0TRNRxbWJP4rOgKkMt9UUOx2/CfZtIUYZuhyKYsQA8E2pBN/yNO/yfsfcAlSC45+Uy7/JG3U9u5V66LxV/9L8RMvpWI8fN48PPysWu1FMRgYOFSb+xBx+71/IdjyPhpxftv2UUMOiIk5WtMsp3lSJWLYFhDWOfnNL4g83qv3VQu9j5fBkTgS8A5pz7kNgc+OcpJNx5iWSRGRpMKZU7Oy3NlJlB9/+GSpz6mbzyZfHVhFCJrtDAuP3/wW4mLJ2a5cTsC4RAL+D4ri44CCVl5w3NvKzkd6YEtGoYqwHj/j7Q+5+ELjbvgk/38p5h35DgRTdGfhF4aGwLifr1tetCCeYjm7qwiw3BqkFySxn/vHk9MYITepHu+hcQGNzpKQU2xi2NItzJ2GopBcBRr/od1dOaygboCjVMVgyUIMTnkBkGktZG3YgUq8AZaeOYsy40N+winAgxPyO+FDyvSw==
*/