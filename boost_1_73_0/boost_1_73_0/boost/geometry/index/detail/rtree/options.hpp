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
xQq+3vEX0ViP1OqBdPKM4+jRCJCyotSbsQfeFR5NKdZPeZJXZKPJjf442mndyc3tQYuGwujRdVMVgdht3vBlncJj6vuaMjG5psxSCmqsDNY0BxuEo3X9Ep2PrXrzbAqn9gmYDzVPMX4GyktpZtC0QDb7DC474DC67dydiX5y/vC98/xzNum7jH8yFBUz0w3mvBma2Y/7CiyEUU4N8oV1iOMuTEY7CKFl+ll4Hza6wamt5+YH/thtUdPW43dohQ92kk1j1+ljcfkk/4yCeb46vZ55V+eGH7V128Wt3Gh03hV1wIzlCHY/yyfNZD1L/F2tC63xmPWZdFudaTFmJy8m1reVLWji+kpwGy40cFA13Xk/VXKnFC/UyH3HeuWu4YEKEFZsvoStQCjBHXH4puk6aqYSe5A27/eX+ODTySQ++N0JJsT05y1Xuek177wh6ZV3SiUijJuCvcEX6raaTm/S2yrwPBaPcFK0wCNxNm/6fm80ZtsBSU2uouGYTatqaXh/GIx8rluh03+JGMh6Deb/BTSWfXK/AqY3nHtz0IYXVf0KS/qoTuDOf9afMYUViS+KuM6GbrO0Z857lv5kEze3IlDFfWPz27QqqZAleYKlZKBGhpetgIXKSTZRk1mLyt6FEUXpsnK42HxOccYz
*/