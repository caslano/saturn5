// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2015.
// Modifications copyright (c) 2015, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_ALGORITHMS_NOT_IMPLEMENTED_HPP
#define BOOST_GEOMETRY_ALGORITHMS_NOT_IMPLEMENTED_HPP


#include <boost/mpl/assert.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/geometry/core/tags.hpp>


namespace boost { namespace geometry
{


namespace info
{
    struct UNRECOGNIZED_GEOMETRY_TYPE {};
    struct POINT {};
    struct LINESTRING {};
    struct POLYGON {};
    struct RING {};
    struct BOX {};
    struct SEGMENT {};
    struct MULTI_POINT {};
    struct MULTI_LINESTRING {};
    struct MULTI_POLYGON {};
    struct GEOMETRY_COLLECTION {};
    template <size_t D> struct DIMENSION {};
}


namespace nyi
{


struct not_implemented_tag {};

template
<
    typename Term1,
    typename Term2,
    typename Term3
>
struct not_implemented_error
{

#ifndef BOOST_GEOMETRY_IMPLEMENTATION_STATUS_BUILD
# define BOOST_GEOMETRY_IMPLEMENTATION_STATUS_BUILD false
#endif

    BOOST_MPL_ASSERT_MSG
        (
            BOOST_GEOMETRY_IMPLEMENTATION_STATUS_BUILD,
            THIS_OPERATION_IS_NOT_OR_NOT_YET_IMPLEMENTED,
            (
                types<Term1, Term2, Term3>
            )
        );
};

template <typename Tag>
struct tag_to_term
{
    typedef Tag type;
};

template <> struct tag_to_term<geometry_not_recognized_tag> { typedef info::UNRECOGNIZED_GEOMETRY_TYPE type; };
template <> struct tag_to_term<point_tag>                   { typedef info::POINT type; };
template <> struct tag_to_term<linestring_tag>              { typedef info::LINESTRING type; };
template <> struct tag_to_term<polygon_tag>                 { typedef info::POLYGON type; };
template <> struct tag_to_term<ring_tag>                    { typedef info::RING type; };
template <> struct tag_to_term<box_tag>                     { typedef info::BOX type; };
template <> struct tag_to_term<segment_tag>                 { typedef info::SEGMENT type; };
template <> struct tag_to_term<multi_point_tag>             { typedef info::MULTI_POINT type; };
template <> struct tag_to_term<multi_linestring_tag>        { typedef info::MULTI_LINESTRING type; };
template <> struct tag_to_term<multi_polygon_tag>           { typedef info::MULTI_POLYGON type; };
template <> struct tag_to_term<geometry_collection_tag>     { typedef info::GEOMETRY_COLLECTION type; };
template <int D> struct tag_to_term<boost::mpl::int_<D> >   { typedef info::DIMENSION<D> type; };


}


template
<
    typename Term1 = void,
    typename Term2 = void,
    typename Term3 = void
>
struct not_implemented
    : nyi::not_implemented_tag,
      nyi::not_implemented_error
      <
          typename boost::mpl::identity
              <
                  typename nyi::tag_to_term<Term1>::type
              >::type,
          typename boost::mpl::identity
              <
                  typename nyi::tag_to_term<Term2>::type
              >::type,
          typename boost::mpl::identity
              <
                  typename nyi::tag_to_term<Term3>::type
              >::type
      >
{};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_NOT_IMPLEMENTED_HPP

/* not_implemented.hpp
Z6/UcN8dDbkPHk20TB09gSXR5nFRA9jhQPPyAIoUia1X94bvN14gOWPEtZOzl+cUsNS9RP9Sh3nRBWo5ZTOvRaOsMT0iIKzYwNJO/JDJMWu2TUA3pcK3FHVFUOQgCf4RmsT327x/RZaV6VNo/ceH/UOzevWNXn5bg9B50zYYlhuUtJpZBJQ7+YEbR7NbXaObk2Vn5Ng+jHJSHifI/ivzCklExLe7FHXK3VybW4TvkahcrZ+OlnmsKPj9d9fWEupLdCi4NylHsUYQV3fj0X4OE2BtFjzV8dAU2KMDwv20dSg9zmFkTdT4J44zRTQcZjN8e8cPFvhWVvJrE+ECBcr77jlNb2d5Ly6u6P064pnk2OqGahnFCzKc3r1A/s7XTRmZ6P4uG9vsAkMDfa3A1XzdQw78BmHWFnKH+Oa7kgN0n3MsCks9/FgXwnpppuVWQpTRp3sYm4FwQncwkp0IgYikRRTiUiRUamxCOdGJ8SdZyi9JoNUx3mnjT1jOAlyvtAS4iMLOMawRxTMJOHJXwK/RmZWe6qoyLdgzSVW5nFFN+4pmsKwSrFeoBdWZsnUdRI55Xs1uJZmKxpKO1t06UKhVKbKalj7RZKnlKu73g0MQHJqsWG+FduVsXzQb5W81T+GoiavbJfpvqwcQd4lx
*/