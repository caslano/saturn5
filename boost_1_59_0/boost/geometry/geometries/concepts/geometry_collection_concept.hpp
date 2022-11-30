// Boost.Geometry

// Copyright (c) 2021, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_GEOMETRIES_CONCEPTS_GEOMETRY_COLLECTION_CONCEPT_HPP
#define BOOST_GEOMETRY_GEOMETRIES_CONCEPTS_GEOMETRY_COLLECTION_CONCEPT_HPP


#include <utility>

#include <boost/concept_check.hpp>
#include <boost/range/concepts.hpp>

#include <boost/geometry/core/geometry_types.hpp>
#include <boost/geometry/core/mutable_range.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/visit.hpp>

#include <boost/geometry/geometries/concepts/box_concept.hpp>
#include <boost/geometry/geometries/concepts/concept_type.hpp>
#include <boost/geometry/geometries/concepts/linestring_concept.hpp>
#include <boost/geometry/geometries/concepts/multi_point_concept.hpp>
#include <boost/geometry/geometries/concepts/multi_linestring_concept.hpp>
#include <boost/geometry/geometries/concepts/multi_polygon_concept.hpp>
#include <boost/geometry/geometries/concepts/point_concept.hpp>
#include <boost/geometry/geometries/concepts/polygon_concept.hpp>
#include <boost/geometry/geometries/concepts/ring_concept.hpp>
#include <boost/geometry/geometries/concepts/segment_concept.hpp>

#include <boost/geometry/util/sequence.hpp>
#include <boost/geometry/util/type_traits.hpp>


namespace boost { namespace geometry { namespace concepts
{

namespace detail
{

template
<
    typename Geometry,
    typename SubGeometry,
    typename Tag = typename tag<Geometry>::type,
    bool IsSubDynamicOrCollection = util::is_dynamic_geometry<SubGeometry>::value
                                 || util::is_geometry_collection<SubGeometry>::value
>
struct GeometryType;

// Prevent recursive concept checking
template <typename Geometry, typename SubGeometry, typename Tag>
struct GeometryType<Geometry, SubGeometry, Tag, true> {};

template <typename Geometry, typename SubGeometry, typename Tag>
struct GeometryType<Geometry const, SubGeometry, Tag, true> {};


template <typename Geometry, typename SubGeometry>
struct GeometryType<Geometry, SubGeometry, geometry_collection_tag, false>
    : concepts::concept_type<SubGeometry>::type
{
#ifndef DOXYGEN_NO_CONCEPT_MEMBERS
    BOOST_CONCEPT_USAGE(GeometryType)
    {
        Geometry* gc = nullptr;
        SubGeometry* sg = nullptr;
        traits::emplace_back<Geometry>::apply(*gc, std::move(*sg));
    }
#endif // DOXYGEN_NO_CONCEPT_MEMBERS
};

template <typename Geometry, typename SubGeometry>
struct GeometryType<Geometry const, SubGeometry, geometry_collection_tag, false>
    : concepts::concept_type<SubGeometry const>::type
{};


template <typename Geometry, typename ...SubGeometries>
struct GeometryTypesPack {};

template <typename Geometry, typename SubGeometry, typename ...SubGeometries>
struct GeometryTypesPack<Geometry, SubGeometry, SubGeometries...>
    : GeometryTypesPack<Geometry, SubGeometries...>
    , GeometryType<Geometry, SubGeometry>
{};


template <typename Geometry, typename SubGeometriesSequence>
struct GeometryTypes;

template <typename Geometry, typename ...SubGeometries>
struct GeometryTypes<Geometry, util::type_sequence<SubGeometries...>>
    : GeometryTypesPack<Geometry, SubGeometries...>
{};


} // namespace detail


template <typename Geometry>
struct GeometryCollection
    : boost::ForwardRangeConcept<Geometry>
{
#ifndef DOXYGEN_NO_CONCEPT_MEMBERS
    using sequence_t = typename traits::geometry_types<Geometry>::type;
    BOOST_CONCEPT_ASSERT( (detail::GeometryTypes<Geometry, sequence_t>) );

    BOOST_CONCEPT_USAGE(GeometryCollection)
    {
        Geometry* gc = nullptr;        
        traits::clear<Geometry>::apply(*gc);        
        traits::iter_visit<Geometry>::apply([](auto &&) {}, boost::begin(*gc));
    }
#endif // DOXYGEN_NO_CONCEPT_MEMBERS
};


template <typename Geometry>
struct ConstGeometryCollection
    : boost::ForwardRangeConcept<Geometry>
{
#ifndef DOXYGEN_NO_CONCEPT_MEMBERS
    using sequence_t = typename traits::geometry_types<Geometry>::type;
    BOOST_CONCEPT_ASSERT( (detail::GeometryTypes<Geometry const, sequence_t>) );

    BOOST_CONCEPT_USAGE(ConstGeometryCollection)
    {
        Geometry const* gc = nullptr;
        traits::iter_visit<Geometry>::apply([](auto &&) {}, boost::begin(*gc));
    }
#endif // DOXYGEN_NO_CONCEPT_MEMBERS
};


template <typename Geometry>
struct concept_type<Geometry, geometry_collection_tag>
{
    using type = GeometryCollection<Geometry>;
};

template <typename Geometry>
struct concept_type<Geometry const, geometry_collection_tag>
{
    using type = ConstGeometryCollection<Geometry>;
};


}}} // namespace boost::geometry::concepts


#endif // BOOST_GEOMETRY_GEOMETRIES_CONCEPTS_GEOMETRY_COLLECTION_CONCEPT_HPP

/* geometry_collection_concept.hpp
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
*/