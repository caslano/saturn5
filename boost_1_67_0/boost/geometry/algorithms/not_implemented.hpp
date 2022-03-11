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
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
*/