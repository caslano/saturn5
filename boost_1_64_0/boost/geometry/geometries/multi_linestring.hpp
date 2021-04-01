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

#ifndef BOOST_GEOMETRY_GEOMETRIES_MULTI_LINESTRING_HPP
#define BOOST_GEOMETRY_GEOMETRIES_MULTI_LINESTRING_HPP

#include <memory>
#include <vector>

#include <boost/concept/requires.hpp>

#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/geometries/concepts/linestring_concept.hpp>

#include <boost/config.hpp>
#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
#include <initializer_list>
#endif

namespace boost { namespace geometry
{


namespace model
{

/*!
\brief multi_line, a collection of linestring
\details Multi-linestring can be used to group lines belonging to each other,
        e.g. a highway (with interruptions)
\ingroup geometries

\qbk{[include reference/geometries/multi_linestring.qbk]}
\qbk{before.synopsis,
[heading Model of]
[link geometry.reference.concepts.concept_multi_linestring MultiLineString Concept]
}
*/
template
<
    typename LineString,
    template<typename, typename> class Container = std::vector,
    template<typename> class Allocator = std::allocator
>
class multi_linestring : public Container<LineString, Allocator<LineString> >
{
    BOOST_CONCEPT_ASSERT( (concepts::Linestring<LineString>) );

#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST

    // default constructor and base_type definitions are required only
    // if the constructor taking std::initializer_list is defined

    typedef Container<LineString, Allocator<LineString> > base_type;

public:
    /// \constructor_default{multi_linestring}
    multi_linestring()
        : base_type()
    {}

    /// \constructor_initializer_list{multi_linestring}
    inline multi_linestring(std::initializer_list<LineString> l)
        : base_type(l.begin(), l.end())
    {}

// Commented out for now in order to support Boost.Assign
// Without this assignment operator first the object should be created
//   from initializer list, then it shoudl be moved.
//// Without this workaround in MSVC the assignment operator is ambiguous
//#ifndef BOOST_MSVC
//    /// \assignment_initializer_list{multi_linestring}
//    inline multi_linestring & operator=(std::initializer_list<LineString> l)
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
    typename LineString,
    template<typename, typename> class Container,
    template<typename> class Allocator
>
struct tag< model::multi_linestring<LineString, Container, Allocator> >
{
    typedef multi_linestring_tag type;
};

} // namespace traits
#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_GEOMETRIES_MULTI_LINESTRING_HPP

/* multi_linestring.hpp
/hwDk5sgDWvUQ8651iP0UVOzxUb+FcfWHGyB0/iYY0dfkItCtLMNc0McA6g8Z+yQ1iMD7xK4FpcIHHaRUUwu/vq/THU56jOe9KpQvsRDOQXTuvq6M8XnwDOQ5fI25jl96XlYs2/CAlHjEM3fPO/IX9diNX9NuXHUXLmb2U1OpyZqXIpSXdkUbROjaitRYSVaAHl/7365843PVF4WbnY2ZVijx0bMO6NiVAUgn/+s4Pb+BtMRWO4Kz1XxkRC0j6AeF964cwC2IrQN205i6WPNbS99LreOohQwaP9BVM5VgeDOZ3L/OuC9srVmpxtG1G+Ipxcr7/hsgdOYITNj7KH2zDHaDD3KOVNOgW5zmTutGnnD8TICDdGAJFoJi5xjcEFFsHU4f1AuM9iEklJ8v4qhqCYiTszrMYG2DaGeycmJVSoLi4bd+ezjDA0QLNNUd0XVnGfpVZHGKIXAgoKq0gdx61rdRVzBeLuvIOFs9qr5/VngW0dWkYf5vpvgbXS7V4ITyPmJkcaCBqXSyk6VqznqtpyyHJUEl/VRkvjYy2JIsFKtNlrtt/FpLC5DNw==
*/