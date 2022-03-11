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
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
*/