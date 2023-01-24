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
lhUyJTJ9KGuwbJsIsTBtnO7mZfSGNa34sURTnevBhpb0Wo7p/VG3qZdyy94zO0y1gs36jgsGAyTNT4yV3U0TxY/t7U2EcEnFZJ/tGXB9Ty6UC6ZsDs2WpnChD04k2F8WevkdjbjZjpAe9c7OWq/8crFo7snmQ3UxBh5d0GyDsin5prJ29Y29MjdYFtecROSuB19VBoRIAUNn9+44gecqBrJh+yskUMk0eT+1gpHdCjbPMyY9lj80qxMW15Xn2NghFZp+ihqsT2WqOH+hlkZD/8eNbbOLHoHkptg5fqnbD74n4Xishzr9far64wcTaDKYm5kvC8eMvUQSBczFuk02vNfFJg0Um4y2hJCp4hvuzvm04u2UGqVsIHVHwbaD0p23x10sySNbhwYeTN95TH2zmkGjO8d7p4i32PxQFkIegzuHp0UWwKq+EP/nTpO+OUsrmwct9MekTUstqsaaBcG5DhfW+Sc2XPVpn0/Lu5yvBJQG4bR/HhbHsJ6N+k1+nepO+sqCatrWZdRbzurP16oxTd80k/4NbCwfEjDOJLcZGqfdTI3x6ZgpGTsNLXGx2emTjKu61qq8CTkP0m/pOruER5aCvKZPq3fqS5sZUfX22gZDjKE7PJWpnnX1mbLLNiETJJW0H319xme8z/Yq5iv6yVY/nBg/boGyOapmU6bUP57N7CZrWXN9ofYt3UOp4P3xF+1E7QEFtj9xFQ0z
*/