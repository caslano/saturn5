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
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
*/