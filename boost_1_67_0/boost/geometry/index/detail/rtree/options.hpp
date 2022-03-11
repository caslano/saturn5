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