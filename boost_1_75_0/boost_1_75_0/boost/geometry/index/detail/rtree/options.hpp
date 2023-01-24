// Boost.Geometry Index
//
// R-tree options, algorithms, parameters
//
// Copyright (c) 2011-2014 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2019.
// Modifications copyright (c) 2019 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_OPTIONS_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_OPTIONS_HPP

#include <boost/geometry/index/parameters.hpp>

namespace boost { namespace geometry { namespace index {

namespace detail { namespace rtree {

// InsertTag
struct insert_default_tag {};
struct insert_reinsert_tag {};

// ChooseNextNodeTag
struct choose_by_content_diff_tag {};
struct choose_by_overlap_diff_tag {};

// SplitTag
struct split_default_tag {};
//struct split_kmeans_tag {};

// RedistributeTag
struct linear_tag {};
struct quadratic_tag {};
struct rstar_tag {};

// NodeTag
struct node_variant_dynamic_tag {};
struct node_variant_static_tag {};
//struct node_weak_dynamic_tag {};
//struct node_weak_static_tag {};

template <typename Parameters, typename InsertTag, typename ChooseNextNodeTag, typename SplitTag, typename RedistributeTag, typename NodeTag>
struct options
{
    typedef Parameters parameters_type;
    typedef InsertTag insert_tag;
    typedef ChooseNextNodeTag choose_next_node_tag;
    typedef SplitTag split_tag;
    typedef RedistributeTag redistribute_tag;
    typedef NodeTag node_tag;
};

template <typename Parameters>
struct options_type
{
    // TODO: awulkiew - use static assert
};

template <size_t MaxElements, size_t MinElements>
struct options_type< index::linear<MaxElements, MinElements> >
{
    typedef options<
        index::linear<MaxElements, MinElements>,
        insert_default_tag,
        choose_by_content_diff_tag,
        split_default_tag,
        linear_tag,
        node_variant_static_tag
    > type;
};

template <size_t MaxElements, size_t MinElements>
struct options_type< index::quadratic<MaxElements, MinElements> >
{
    typedef options<
        index::quadratic<MaxElements, MinElements>,
        insert_default_tag,
        choose_by_content_diff_tag,
        split_default_tag,
        quadratic_tag,
        node_variant_static_tag
    > type;
};

template <size_t MaxElements, size_t MinElements, size_t OverlapCostThreshold, size_t ReinsertedElements>
struct options_type< index::rstar<MaxElements, MinElements, OverlapCostThreshold, ReinsertedElements> >
{
    typedef options<
        index::rstar<MaxElements, MinElements, OverlapCostThreshold, ReinsertedElements>,
        insert_reinsert_tag,
        choose_by_overlap_diff_tag,
        split_default_tag,
        rstar_tag,
        node_variant_static_tag
    > type;
};

//template <size_t MaxElements, size_t MinElements>
//struct options_type< kmeans<MaxElements, MinElements> >
//{
//    typedef options<
//        kmeans<MaxElements, MinElements>,
//        insert_default_tag,
//        choose_by_content_diff_tag, // change it?
//        split_kmeans_tag,
//        int, // dummy tag - not used for now
//        node_variant_static_tag
//    > type;
//};

template <>
struct options_type< index::dynamic_linear >
{
    typedef options<
        index::dynamic_linear,
        insert_default_tag,
        choose_by_content_diff_tag,
        split_default_tag,
        linear_tag,
        node_variant_dynamic_tag
    > type;
};

template <>
struct options_type< index::dynamic_quadratic >
{
    typedef options<
        index::dynamic_quadratic,
        insert_default_tag,
        choose_by_content_diff_tag,
        split_default_tag,
        quadratic_tag,
        node_variant_dynamic_tag
    > type;
};

template <>
struct options_type< index::dynamic_rstar >
{
    typedef options<
        index::dynamic_rstar,
        insert_reinsert_tag,
        choose_by_overlap_diff_tag,
        split_default_tag,
        rstar_tag,
        node_variant_dynamic_tag
    > type;
};

template <typename Parameters, typename Strategy>
struct options_type< index::parameters<Parameters, Strategy> >
    : options_type<Parameters>
{
    typedef typename options_type<Parameters>::type opt;
    typedef options<
        index::parameters<Parameters, Strategy>,
        typename opt::insert_tag,
        typename opt::choose_next_node_tag,
        typename opt::split_tag,
        typename opt::redistribute_tag,
        typename opt::node_tag
    > type;
};

}} // namespace detail::rtree

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_OPTIONS_HPP

/* options.hpp
LMoS/WRX/Zi5Z02bCWtYZGqqFPK57TYF2lxy0Y68o7y+fRtkL1GoW7Idb6PINBW5/b1sOM2CScSYGuWEjgI4+3DPczgwUk7N1CijD5X4ptScPqP0xxSa0pbld8CzAoELd8x71Oyy3NwFKV0VXL+7ak9OEP+tMNhOjJ4poMr9OFQZ1Fw7Az//VdPfsBY+b3CphSPx8ZiA1VFiaHvx10G/7u/+rpXWe1GX8VHbFlXGrUZi7ew17iWCCxIcRKCUj9dHUedtYzbPw7zNpj/xqqE/1lgdgj/00TJ6+xyKeo10LgX4IZi2D3+mv2R0catAK/D51nXH8mlvb3KLfdNVo/oT0oe86vvlWVOZNqF2w5g/n1UXwy8PJb5GvscHrbYHNq2ixFlj3nOzDUwMjHvet2xdIzQu9Uw9zWYacdi50KfeIxoDi3tTTcOmtOlDjQPfSxeEG1XVntFRrLWrX/K95LGyc7ncqku56vJZf0j2Gj8Inp8++P29rKeH3C/fofLwsEXMdZFj3syfyGW2lgKBTTUauiRf/PnKRNEHGFVr0JWub93Da7VDVP0onGXAM1Xca9xa+HgDOPlISbGDC579mjnonpMRtrgB6tgEKo2PKYA4qjtuV56nIAZ5TQ/cqn/ty0EnURnVjLnpc342PtzEtGbNrlnkUkddL1lJNKdYxjtXDeSSPuYQZvsd91xRWFNqZHv0b7+H2iX3dnG1iz9f
*/