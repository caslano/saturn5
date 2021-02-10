// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.
// Copyright (c) 2014 Adam Wulkiewicz, Lodz, Poland.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_LINESTRING_HPP
#define BOOST_GEOMETRY_GEOMETRIES_LINESTRING_HPP

#include <memory>
#include <vector>

#include <boost/concept/assert.hpp>
#include <boost/range.hpp>

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/concepts/point_concept.hpp>

#include <boost/config.hpp>
#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
#include <initializer_list>
#endif

namespace boost { namespace geometry
{

namespace model
{

/*!
\brief A linestring (named so by OGC) is a collection (default a vector) of points.
\ingroup geometries
\tparam Point \tparam_point
\tparam Container \tparam_container
\tparam Allocator \tparam_allocator

\qbk{[include reference/geometries/linestring.qbk]}
\qbk{before.synopsis,
[heading Model of]
[link geometry.reference.concepts.concept_linestring Linestring Concept]
}

*/
template
<
    typename Point,
    template<typename,typename> class Container = std::vector,
    template<typename> class Allocator = std::allocator
>
class linestring : public Container<Point, Allocator<Point> >
{
    BOOST_CONCEPT_ASSERT( (concepts::Point<Point>) );

    typedef Container<Point, Allocator<Point> > base_type;

public :
    /// \constructor_default{linestring}
    inline linestring()
        : base_type()
    {}

    /// \constructor_begin_end{linestring}
    template <typename Iterator>
    inline linestring(Iterator begin, Iterator end)
        : base_type(begin, end)
    {}

#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST

    /// \constructor_initializer_list{linestring}
    inline linestring(std::initializer_list<Point> l)
        : base_type(l.begin(), l.end())
    {}

// Commented out for now in order to support Boost.Assign
// Without this assignment operator first the object should be created
//   from initializer list, then it should be moved.
//// Without this workaround in MSVC the assignment operator is ambiguous
//#ifndef BOOST_MSVC
//    /// \assignment_initializer_list{linestring}
//    inline linestring & operator=(std::initializer_list<Point> l)
//    {
//        base_type::assign(l.begin(), l.end());
//        return *this;
//    }
//#endif

#endif
};

} // namespace model

#ifndef DOXYGEN_NO_TRAITS_SPECIALIZATIONS
namespace traits
{

template
<
    typename Point,
    template<typename,typename> class Container,
    template<typename> class Allocator
>
struct tag<model::linestring<Point, Container, Allocator> >
{
    typedef linestring_tag type;
};
} // namespace traits

#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_GEOMETRIES_LINESTRING_HPP

/* linestring.hpp
CyDHWqKEHlQOa1zZ5Sy3wp1PGB9oDbufKlif5GCNnBLO6H1fFMb+8qlCuM5cP4n5A4OfFwb/LAdPwdQ/MPRpYegzOdSxb8pG6uvdKwz96ZMFMdIuLnkGPsS0bLyxt2PkR60Q7ZOFb5TdcDvMyxKdQT080FmyKkmbJCzyLRTM/OJhx0IfZU+fPCnugNQHhw5zOl4pDbOSwgJgIzM91yvbKdXUO+skdiUDJlYgXtiQU5UMVddMeZPuzN7YAadsPCXNIMu34t8DsHVvLqdlW91mr4d69PT1v9qtfvr7lN756rzptJr9dqpNV9yPXWlBiBj5hxAqiSm6zdftLuyvNy/YwMBq2MDIAEoiq3oYwrqnerD/wFQfmt2LdtEuaZMpx+hAJVPLdfs6nZ7T5Q/p8FLdvU5nZ6ix2sGKms7ShoLWD/IObSdZzDpFzbLWrvIAfrDAyFEqc1EiQ0HBFAkeCZjhi6RT6LTg6Xtk8p02+b7X99FuMyNGJnDCkJt/NKu/Dz89sQbRE1gANdJtn3DXHudcGXneIXdMYrdyb7HOYnlVoTZ6dozaB8coADv2X+7kD2emBzJTZQBRnN4B2ndVUxflExr29Iy38MqKGO+VY6yqXH8dX1EG+0ewzWsl4UDcU7faWy4rWim7qKlIPymm
*/