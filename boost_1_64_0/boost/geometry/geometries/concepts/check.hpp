// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_GEOMETRIES_CONCEPTS_CHECK_HPP
#define BOOST_GEOMETRY_GEOMETRIES_CONCEPTS_CHECK_HPP


#include <boost/concept_check.hpp>
#include <boost/concept/requires.hpp>
#include <boost/core/ignore_unused.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/concepts/box_concept.hpp>
#include <boost/geometry/geometries/concepts/linestring_concept.hpp>
#include <boost/geometry/geometries/concepts/multi_point_concept.hpp>
#include <boost/geometry/geometries/concepts/multi_linestring_concept.hpp>
#include <boost/geometry/geometries/concepts/multi_polygon_concept.hpp>
#include <boost/geometry/geometries/concepts/point_concept.hpp>
#include <boost/geometry/geometries/concepts/polygon_concept.hpp>
#include <boost/geometry/geometries/concepts/ring_concept.hpp>
#include <boost/geometry/geometries/concepts/segment_concept.hpp>

#include <boost/geometry/algorithms/not_implemented.hpp>

namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace concept_check
{

template <typename Concept>
class check
{
    BOOST_CONCEPT_ASSERT((Concept ));
};

}} // namespace detail::concept_check
#endif // DOXYGEN_NO_DETAIL



#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template
<
    typename Geometry,
    typename GeometryTag = typename geometry::tag<Geometry>::type,
    bool IsConst = boost::is_const<Geometry>::type::value
>
struct check : not_implemented<GeometryTag>
{};


template <typename Geometry>
struct check<Geometry, point_tag, true>
    : detail::concept_check::check<concepts::ConstPoint<Geometry> >
{};


template <typename Geometry>
struct check<Geometry, point_tag, false>
    : detail::concept_check::check<concepts::Point<Geometry> >
{};


template <typename Geometry>
struct check<Geometry, linestring_tag, true>
    : detail::concept_check::check<concepts::ConstLinestring<Geometry> >
{};


template <typename Geometry>
struct check<Geometry, linestring_tag, false>
    : detail::concept_check::check<concepts::Linestring<Geometry> >
{};


template <typename Geometry>
struct check<Geometry, ring_tag, true>
    : detail::concept_check::check<concepts::ConstRing<Geometry> >
{};


template <typename Geometry>
struct check<Geometry, ring_tag, false>
    : detail::concept_check::check<concepts::Ring<Geometry> >
{};

template <typename Geometry>
struct check<Geometry, polygon_tag, true>
    : detail::concept_check::check<concepts::ConstPolygon<Geometry> >
{};


template <typename Geometry>
struct check<Geometry, polygon_tag, false>
    : detail::concept_check::check<concepts::Polygon<Geometry> >
{};


template <typename Geometry>
struct check<Geometry, box_tag, true>
    : detail::concept_check::check<concepts::ConstBox<Geometry> >
{};


template <typename Geometry>
struct check<Geometry, box_tag, false>
    : detail::concept_check::check<concepts::Box<Geometry> >
{};


template <typename Geometry>
struct check<Geometry, segment_tag, true>
    : detail::concept_check::check<concepts::ConstSegment<Geometry> >
{};


template <typename Geometry>
struct check<Geometry, segment_tag, false>
    : detail::concept_check::check<concepts::Segment<Geometry> >
{};


template <typename Geometry>
struct check<Geometry, multi_point_tag, true>
    : detail::concept_check::check<concepts::ConstMultiPoint<Geometry> >
{};


template <typename Geometry>
struct check<Geometry, multi_point_tag, false>
    : detail::concept_check::check<concepts::MultiPoint<Geometry> >
{};


template <typename Geometry>
struct check<Geometry, multi_linestring_tag, true>
    : detail::concept_check::check<concepts::ConstMultiLinestring<Geometry> >
{};


template <typename Geometry>
struct check<Geometry, multi_linestring_tag, false>
    : detail::concept_check::check<concepts::MultiLinestring<Geometry> >
{};


template <typename Geometry>
struct check<Geometry, multi_polygon_tag, true>
    : detail::concept_check::check<concepts::ConstMultiPolygon<Geometry> >
{};


template <typename Geometry>
struct check<Geometry, multi_polygon_tag, false>
    : detail::concept_check::check<concepts::MultiPolygon<Geometry> >
{};


} // namespace dispatch
#endif




namespace concepts
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{


template <typename Geometry>
struct checker : dispatch::check<Geometry>
{};

template <BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct checker<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{};

template <BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct checker<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const>
{};


}
#endif // DOXYGEN_NO_DETAIL


/*!
    \brief Checks, in compile-time, the concept of any geometry
    \ingroup concepts
*/
template <typename Geometry>
inline void check()
{
    detail::checker<Geometry> c;
    boost::ignore_unused(c);
}


/*!
    \brief Checks, in compile-time, the concept of two geometries, and if they
        have equal dimensions
    \ingroup concepts
*/
template <typename Geometry1, typename Geometry2>
inline void check_concepts_and_equal_dimensions()
{
    check<Geometry1>();
    check<Geometry2>();
    assert_dimension_equal<Geometry1, Geometry2>();
}


} // namespace concepts


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_GEOMETRIES_CONCEPTS_CHECK_HPP

/* check.hpp
8ywqkuM1pEym4yZL3PQhJi6tg+JONoiP1XwdKm56Ed+Wki+pJ8iXjLp8kTR7xL+cg+JXt7J17cupSHMkC/kafxvtNOflc673Ut+TSQKlnbSqnyz7zBqnnmue9T3K0LevyIjQ/Qs1blcjX7RmzrwublLfpQVpnDz4NBzLNE6W22TVOTlqmtRXyeevE7z9nFUWY2WDOWuf/zCt/1YY0Vb9lDPck3WP+vSTKAfiRNqWSf2U/E0wda6rfeMITW9VpNfzg1r/7tWy2D6tLr3FnsJzrTsQHeXSRQsq8os8gcsDf/aZX5PQnxP9Jkcc/1+KmHlwP22Ams6BLA67Dg+bLn299reGo4PoQxztMOtOfOv8yS3Q7lv+JuF3JE0pQf3GkodOfLYjxQkIDn9Qfe4u4ZJXKf55OCtK97JF4pCten/ZON0nD8vKKj3WMTTkZSN1Wv0l23n4iOgbSAsnSSKx9r3GDkjvN+pX8yIefZfo1zk6Et+5SIP81zroyvXe+xNFx0D0UxwuzOL5v0H+q7+jEn48+RERzK/E90vphxZ6qorLinzPWDlF3DYTfSJ6lujxPn2SnoOkZ3icKvbJ2t5/WFnquUR6L7TzUMq4V27gMj7s9ga4CMs0pdlO1uTWL+NKTwVBNl7Glr++ko9noD8p+lCjp+EM2kZ+PcO/jcwU/U7HfMwudiQEbSP9xV2allFgv8l2fjeoo/Z5zo9LHIcZaUY0Zpb7opJK82qUqnUO+K/EXTvjIzNOYsbdX66X3Ghd2CRumkk4k9HvEX0q351lqZkV7xrHJInzpJg5UbLniCOEeuAc5SriLJFObSXPrTZSYI8bDki8ZqteFyc5s0TDWmeFVfOKK5eTRFoSYIq7Xnja1grE/wg9o9uK243U+JkS5veto9n1+ptbZ1h10f/cq546Go4OoT+DkXAnbuadYdfFBZ4qq7NZWLKIwcMyq0A1b1b610f1m2KfDbNC9M+NzjJKI+1yji1h+YSj9yr12178zkD/qeifGB2IdZ1fvziI2xzLLylZwxdWYkYZ15pm6C0caZygNUrOMgtYb7TPiJgp9xz8o9v+pxmtMKurp/7xLsXf8+JuLdex3BSX0WzEPhHtJbG/wAjW990l9mOkXYmZfe0iWnGu0YU6dcTNPbGltw64w2tucS13FYRHOpcjM1wTODKxhY5BdezyKCUcLM7xsJmktZURK7p1vZlGa8zMOry+BfejllqHV/a063CHuMB1+DIJb4XWYSu8GtIcZUi70DC3WmHW3EOYkc6WrjRCTY8JFGaohLk4QJhpEqaES3sYe4L2MA+u1PaQjF6MTl1C96uHYldeZ0c98+/Tj5+h7aje2PuA/E871m8WcuAOs5zPtNuRt7KZZ/GVVfi1mzTtW9uK2yzjclr9TuQgEma4HOmIti0Nr61dh416dXiC7aaLhDsRvYvoA4yLie8O5ABi0Bo6IQHqh/hLgsnib4xxPf8/jfwJiaVe9kfk7HquXxWjZdldijJaizJgn9lRwitVnVGI6AnSv+m4inor4VF3G31+Gm/3cz7lmqjPT1+KrvlSb4w6NM4bwCAdo/bTMeru2XY5Vdb1d8Uenh2sGhDweel18ddBy8cKp5V/vpp9ps+44wNxE4U+QsYO74ie1OD5Xd2rfaTq9KSih9e/hjwz6/OqHab9LHOS943GxjaaDjHP9jfn2v7PZaW62d1EvcAE5OLW3GfO8s1n+0mgoKx6kZSVjh3seu3T/LTeWGGk2/VotOitGhvLqp+J6NY9RC6pZ8Da9jo/FDSPsGd+yE57vThq3kQHGA/GYp5k9ytybb/8Opqg508iFi+i/yivyy8CK5m/nMfZ/IqF1jOjpCe23lw=
*/