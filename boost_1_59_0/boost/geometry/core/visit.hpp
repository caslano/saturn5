// Boost.Geometry

// Copyright (c) 2021, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_CORE_VISIT_HPP
#define BOOST_GEOMETRY_CORE_VISIT_HPP

#include <utility>

#include <boost/range/value_type.hpp>

#include <boost/geometry/core/static_assert.hpp>
#include <boost/geometry/util/type_traits_std.hpp>


namespace boost { namespace geometry { namespace traits
{

// TODO: Alternatives:
// - free function
//    template <typename Visitor, typename ...Variants>
//    auto visit(Visitor &&, Variants && ...) {}
//
// - additional Enable tparam
//    template <bool Enable, typename ...DynamicGeometries>
//    struct visit {};

template <typename ...DynamicGeometries>
struct visit
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not implemented for these DynamicGeometries types.",
        DynamicGeometries...);
};

// By default call 1-parameter visit for each geometry
template <typename DynamicGeometry1, typename DynamicGeometry2>
struct visit<DynamicGeometry1, DynamicGeometry2>
{
    template <typename Function, typename Variant1, typename Variant2>
    static void apply(Function && function, Variant1 && variant1, Variant2 && variant2)
    {
        visit<util::remove_cref_t<Variant1>>::apply([&](auto && g1)
        {
            using ref1_t = decltype(g1);
            visit<util::remove_cref_t<Variant2>>::apply([&](auto && g2)
            {
                function(std::forward<ref1_t>(g1),
                         std::forward<decltype(g2)>(g2));
            }, std::forward<Variant2>(variant2));
        }, std::forward<Variant1>(variant1));
    }
};

// By default treat GeometryCollection as a range of DynamicGeometries
template <typename GeometryCollection>
struct iter_visit
{
    template <typename Function, typename Iterator>
    static void apply(Function && function, Iterator iterator)
    {
        using value_t = typename boost::range_value<GeometryCollection>::type;
        using reference_t = typename std::iterator_traits<Iterator>::reference;
        visit<value_t>::apply(std::forward<Function>(function),
                              std::forward<reference_t>(*iterator));
    }
};

}}} // namespace boost::geometry::traits

#endif // BOOST_GEOMETRY_CORE_VISIT_HPP

/* visit.hpp
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
*/