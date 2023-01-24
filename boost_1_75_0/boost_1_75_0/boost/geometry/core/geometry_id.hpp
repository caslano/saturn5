// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_CORE_GEOMETRY_ID_HPP
#define BOOST_GEOMETRY_CORE_GEOMETRY_ID_HPP


#include <boost/mpl/assert.hpp>
#include <boost/mpl/int.hpp>

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DISPATCH
namespace core_dispatch
{

template <typename GeometryTag>
struct geometry_id
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_GEOMETRY_TYPE
            , (types<GeometryTag>)
        );
};


template <>
struct geometry_id<point_tag>            : boost::mpl::int_<1> {};


template <>
struct geometry_id<linestring_tag>       : boost::mpl::int_<2> {};


template <>
struct geometry_id<polygon_tag>          : boost::mpl::int_<3> {};


template <>
struct geometry_id<multi_point_tag>      : boost::mpl::int_<4> {};


template <>
struct geometry_id<multi_linestring_tag> : boost::mpl::int_<5> {};


template <>
struct geometry_id<multi_polygon_tag>    : boost::mpl::int_<6> {};


template <>
struct geometry_id<segment_tag>          : boost::mpl::int_<92> {};


template <>
struct geometry_id<ring_tag>             : boost::mpl::int_<93> {};


template <>
struct geometry_id<box_tag>              : boost::mpl::int_<94> {};


} // namespace core_dispatch
#endif



/*!
\brief Meta-function returning the id of a geometry type
\details The meta-function geometry_id defines a numerical ID (based on
    boost::mpl::int_<...> ) for each geometry concept. A numerical ID is
    sometimes useful, and within Boost.Geometry it is used for the
    reverse_dispatch metafuntion.
\note Used for e.g. reverse meta-function
\ingroup core
*/
template <typename Geometry>
struct geometry_id : core_dispatch::geometry_id<typename tag<Geometry>::type>
{};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_CORE_GEOMETRY_ID_HPP

/* geometry_id.hpp
Tau59l3HQpqRsbfjKd1ur7PYHNSPGoQzaDGImSdgat+V/DofL/nsjao6DWX6gmxBTDpz6GaYeId3l5TAiuPot5gkgoNjufB6xBlWgCd0h64dEINESwu9R7Y9mCmMOLpzfxTwqajuaafaFxKCDHVKdavM9T05F/DN9CWu/PQatH3V5rD3qSz3yv4rYQNAdvb0VIGGvlr4Q4iMUIvij1YVtj95FX0MtwMAB8cCFWrTl57Jz+t5RUlrq2CaC2WMw90Nq2EFbFPz8vKNZtVVpg/1trfi7v6X3XkpZXnZM9tvTs9353srLqIDwlLiqGMT9FRj9c+V+Ji4MsU/rShywOOss+U/8Y2+bbggooLM0HGxDQpMN7CMnE0Qra2+duyVbtHKWGpDMmfsabtxZpxV5U3v2gMtTqz5CYI/y4VnP3z5QWU5SzvfxtRUaMhfIabUrPnyFZA5k4YYDtu902+g1RlncC03ngR5dqhcizvSxvQeLI5di7shtYsWWvCp3KwJSVTEwlqEGdv3+PbhZ8RStoML07bjWQ+l26bL85zjpOMXlD9nR+7+2mLbC96/TWRfod7OVItwqWCcFIdgkqzrBpxkazrI6NUlqxZMHdlUz0a6cqDo55xZB8eazYCAwJHVUVdf6+9vEWj330ZEP8B6S1iuVpWO5tMkTR+QyLDdtsKJ7vqfOi8b3DZq+ZqM5WCqnsn2ZQ9emng1cPx2FIRO
*/