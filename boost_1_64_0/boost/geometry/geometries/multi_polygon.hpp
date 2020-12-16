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
YolnmrQCtII+XyheQ+2wjgc79tCe6P6qA7a9rCUNWAN5pvO8wXPaF/C0XzNmFRTYcd2qlLK1udDY8xM71wpUDcXF9hnvUdZNsqdgjYW/RV+6z7v3xfmePi3vjlrrrKaqxjoVUdtrxaKaGrbGRdtUjZ97Rd9J9t7NcfcvLBe1y33h5iQs7rjCx6InxrcHNzEna9qHi9oyX2nt97fy/ndrqzGj9/aukbDWc/KjZx3RRPfckz1irrHvVyut1LXW0aInR74wQu7PFE+742qi53trPe6LmhtPL1pBVIt/izhzsm+KHxNV9lm3itzAkjvqqR86/mjWSsu6vNFUggks46kR9JyjFUjVvRiqfyT6U1ELLDHrgqLde4ucsjgnjUfb9PF/06YXFptHWuHWZ24eLjYWZ6djmprVb30nX4j6ujB10a/lNfysHdk3r+V1xS+2x475sENZ15y3tsQpr7q0peRlmiNYFTFpbuTyq+ZbumdAbxH5YV8PXH/Q50efs/4bm0LfqWqup/vt9oLIt/n+tC6x0sSMzuXKautQevdxzXK2ntYZm0Tei5tB3AzabqZhXteP67iXmmvg3gl5h8jP+gZYAUzLOJquW500NW/UpBH4WPqSPbV/Welq6TNJX9J79opf1If6TG8qVfTbBpotNeppbtkJW9c+O7R+51rxxyHfWP6/4sOEq2/WjHxWe+j6SXftxXbRv0xmg51xrlzxQwNfkvVL8bPUHQvce0avF/Ov+S63Yqzn+Hoofj+p8/03Qex8krqziaqF3MlhXK/4/Z2O/7qJnk+s1VbLCP771lOHTHfL8Cfy3ls35xt/h874kveVZd1rOm1Pu5OsjbXvqbsuIYlCmmSvjf72hGVV4V1obXds0JRd510r3hWpOa5ac9e/OvaO5/3cNN7HVw+kJ2RhPi2qeD1RTfW+Y/wg7nxo34MWHWOujhc/TuLdVh73nsMjcg+amM/S94fUL5gnAMF4oy9Orn0PRBX3V7NTjlvPJkzGnTjckXvQsCORd647r6kf9V0u74psc7gRiNfrIkuEe80pZ730JUafuf9bwtEK9QK1n5sN+2CeN/qto++v5dH7FzEesjtV7d7K+wP2uujuXvWPUd9t1KMX7zR27UB+37gl/tgZtibeSYMHz+Gs/jJmf9jS8H1gBcXmPua465Mp5bquodBVC6t3RP8K8076rZTdEncsh+qL0Lw/707bnhqjay1H6HzT4aVunSt9I+dgslL6SKqfsq7rlk+J3Mu60Ap65pvEKq1P1Qwut+O7qpT7KFRPOfdMsJ9F7mtdhL2hPK97jP6H9STZobWWxe4zE3+Er/E+Y1t4Q8Cy6sMpcLRZ473Mjasx+XnT5xbM1PqslHmlItH/tsadY76P25/YttzIXfwtrdd9objz1jWOmW7uWMNWkS8KaP/T0e+OoYx3zXR07/bYIPLFmBE3tC1z97dK/DwsetoFtH1SOy631B01E/593WWF9LVU5jR0kbO95xKoPT77HBDUQu1hgbHQPVdms+jrGXD6ujeJfNhfz9rod+zLLWZfttpXUVJtplyw4/Rz7xR9dQP/8jX1Of7bJ/6rZxXf01VN+4UHxMwBf9Ca6Jvl22xV96+3nmQHeZb2LffK+zKBZPJkIW17PXS+4veza905H9SJg/oiV1TZObOnte7BnuP53v5E7PzRb+J5ooTDJOeI8ZNH5UkYR2pb3UHMSpS5+StJ7L5aZXVLw6ff9+TTUJwsuEb2rPleIc2Kx0l8qB9uOfcdp4XdsX2lZnbJM9JHfED83jkQik/JIGF9jKckTOMl0M45/s+KuRyPucmTwu7tlnKRoXdElH52TLLoq6H9eqc8pfpjrT9986g=
*/