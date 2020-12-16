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
VnY6XJUmj77/+zVTztxpch7xoXcdjxrhznW2sFRtcEituaPWO6TWzFHrElJr6qidH1Jr4qg1C6mdZ+meO6m79H58WW2lc7lLRtvq+VPGSL+tsFg/bkWxdeBrPGu5QvcrO3tMpJ8hahs8ayLmFJvz6bnPkr9+etea3E9fhfGRMcX7bpIXI/XdVG85d/zwBZE7+D7Se/l0LFnrEEd/Mvp1XkLkC32HrApWpLNf+rhmctw+XHQ+cvF7/1Tvg/Kug6ceE79LPZahfm4nevbKarHG1LsX8U0RWoPMeb8S3vC6b6uY6e6ehSCu5ofWF5fTb4ACUWtl1baSS23n05z79SRcr1t1CMtj2qccHwqfxEeWXceEzZP9IuZGWGXRo223mnlPbkNZh/oL8q3KmXX0z799gVrZ1HNXRGcGKifUTeiaUJulxbUDMQxRJgf8CXVhEmweXUeWG2cFo6mZc5zyuS7Zu161wI4c555tjZ9O4n4GOSGoaj5vXITN2c3HL+eyJizSt4yOp+v4ujPHIp4JG18/9IreZUNFVBt2gSlVkccWz9tjZnGLfZ45EcR7Gk1q6M7dUXkT82eG5jgdOxq59flqkbP8Je431nNQrhnPe7NivZR5zQnyvppbJhaOk/4o+4GSVY/agZzhmJd86vVxaN7lBvFPhj/D7aO7+kZoo+72IdaK3hr+0u41SvOMFz8tev2+ZOsd1EPj6feK+jW0PJeH3S+yVsKR5h1P13BUp7QHbb2qXne8jkfpXdrrxM5sfwerq9XU10n6D32orw7u17PhpjBV1DIu0MacxRV19jH242PD7+D4WeReWg59VpHIyf7W1l2+T3zlzzpm/p0dX2HzCb+IWrXQmLmEU8dkS4S9ghvG98TcEVZdT/C94gvaY9gvkb/2e+8JjudwiyR5l4h6Z55t8m6T7K13zthI1ffDeHTMdr07dq72HtivY+dX2kdcyCGRuq56DO82qN2cbrESy2PjeSfm9f0+niIxL8etBQPeszT0SdN0qnJA3eqDK+XjLTnbF/PWAfX/UIwmRzl+l3fpB2z7E+P7WK7f1b4DL5Pu9hkUo0n5xkmBJpLyZ0v3L8eFp/s3Iue66b7GyHgoip78HivmrOn+meitGpbuR0Utw5vumo8rqT5v3s6yMjTdXxVzJ61O6CtkDutdy077TMI/7GXn3pzrTdoHnbSPRb0jzzZ5tzY87fX9YB5J++Di6534c+zdx7udYnZqwhRNevNuJOrrePQOpIXedM/S98/yFKnZsZ6EL3HWraZVu1cct3Ilo81JmGJOL4llMsY+Rwb7EtGj8zSxiy9koiY2zemby/tWvC9y7OAMlYREdEbFyxkoCR53nf2c54fOPmDc+O/7hKZ/ZpdHq9aYqVPyrdBeGb27OVTvZ0Q+l2yGc9/vcNse66K08Dn+Kq/rHL/ev3wn7GnaoAnF26D8vNL36zr6K4jcH3mWyFf6bJmdHlfo2nVnnZn77RAaq50uZtb4zHjypTzar1G7U0NmQ98zobXxtlkrTftfx0Uu51tDDv6lZD9Mysctoqd66JwD8WMn9zv6CXk/WG5L62bFlWJ3UMd69Jtc1wC8KXoq+0QuFv7sZE8fxbOHLCB6juBSY6sXto7A5Rctv/rHcfeMVQ4dNRn3SwtrZ+3Dm2Z41tOsFf110Yfshqeb73Xahpr4zDVfSn9y+hV2+LNEDoU7Az/1I7eMhQU8VzKG0cPMjVIe9r5m9+PYFFa4hi5cIzpuF9Kly9YuXU1Pl66mp0sXoKYMBKPjErMus86lT2f7ibwofvwAX7SgFQ4Sb7HWYDjeGizl77+dl0nTPhz5zDuerOXOUdf8V2z/Was3bItn6fq0Ap4=
*/