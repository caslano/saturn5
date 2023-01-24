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

#ifndef BOOST_GEOMETRY_GEOMETRIES_MULTI_POLYGON_HPP
#define BOOST_GEOMETRY_GEOMETRIES_MULTI_POLYGON_HPP

#include <memory>
#include <vector>

#include <boost/concept/requires.hpp>

#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/geometries/concepts/polygon_concept.hpp>

#include <boost/config.hpp>
#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
#include <initializer_list>
#endif

namespace boost { namespace geometry
{

namespace model
{

/*!
\brief multi_polygon, a collection of polygons
\details Multi-polygon can be used to group polygons belonging to each other,
        e.g. Hawaii
\ingroup geometries

\qbk{[include reference/geometries/multi_polygon.qbk]}
\qbk{before.synopsis,
[heading Model of]
[link geometry.reference.concepts.concept_multi_polygon MultiPolygon Concept]
}
*/
template
<
    typename Polygon,
    template<typename, typename> class Container = std::vector,
    template<typename> class Allocator = std::allocator
>
class multi_polygon : public Container<Polygon, Allocator<Polygon> >
{
    BOOST_CONCEPT_ASSERT( (concepts::Polygon<Polygon>) );

#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST

    // default constructor and base_type definitions are required only
    // if the constructor taking std::initializer_list is defined

    typedef Container<Polygon, Allocator<Polygon> > base_type;

public:
    /// \constructor_default{multi_polygon}
    multi_polygon()
        : base_type()
    {}

    /// \constructor_initializer_list{multi_polygon}
    inline multi_polygon(std::initializer_list<Polygon> l)
        : base_type(l.begin(), l.end())
    {}

// Commented out for now in order to support Boost.Assign
// Without this assignment operator first the object should be created
//   from initializer list, then it shoudl be moved.
//// Without this workaround in MSVC the assignment operator is ambiguous
//#ifndef BOOST_MSVC
//    /// \assignment_initializer_list{multi_polygon}
//    inline multi_polygon & operator=(std::initializer_list<Polygon> l)
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
    typename Polygon,
    template<typename, typename> class Container,
    template<typename> class Allocator
>
struct tag< model::multi_polygon<Polygon, Container, Allocator> >
{
    typedef multi_polygon_tag type;
};

} // namespace traits
#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_GEOMETRIES_MULTI_POLYGON_HPP

/* multi_polygon.hpp
6NxKWrRpYZlhrnwg3Tp51pYK4EHu8QpkUrzd97yEozjSa8Kg+exN5V3E+bGQkHC1nYtlYKaycKbI3JHJAfckBbrqd+ZA4I9Kt8K5AIdU7tQrVevvqsavvXHsxwd1gdaNckuN11lDTdFVsQ3z6QGjELeCFyse+1Cn418XCzUVIgy3eXL6IKMsg31HmuSlUwK+vwt8fLZ6OlDFg5SMm5R1rzZ6bURIHL0Mj5OTw9FxPG5DYoxm4pDnXt61E5DCHcpAWCzTtXjovKlv3FRN2a9GbsyBdc2RiCPf2zof+KNJMLoBRyvTw2ONQ3kYjdedOda8oT8aLGGcNQgzahmVdsqMf/Y2tybQvWB0V2pSSmnmCclyKBOoIWH86lfT5cpTc3gA23bmgqlxatVV4ZzD0a+9J5lJET1pvQcFmqJqPGuvTuI/Zd9topQ0DRi0iewxrfwXAC0s0tOThvexR+4c3H9Oje59wrdNeVPZt2M+2k5D8arar8e1Xllueo/w1vee9J9n4Yz21PAeyICFk7a++XJR76CfuzVMuPBUiTbWUMbe70HvGetnB/Txj2rQoZ7nuipodw3v+I+OKi9LHVCxz+FdR+0ndPEORVtsKNe8MuD5iOtXX3T3uzurwumaN16jfTa8jxx2O3X/vZDMHqEJj69WKhfmgzbb8I6L78DMBNN9HXouP7FmYc9mNmfRjhvKyp5t47g+cPVPLgE/fue/
*/