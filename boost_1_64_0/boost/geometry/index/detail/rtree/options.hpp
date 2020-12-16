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
hlFWyt3hqPz81jDpTxsp1w1j0JifsRiJ47A/Xo/RxjLieJyMsTgFk3AqZmEs6uNUY/v9tprUo5fst9VlvyWty/uG2u8P3rI/+Mj+UFP2B9LSf0pI+QCL/tNfpH3uV2mfO4/eeAH98TfU7+FcZj4cch/oIv36rhgoab1dhdrvXxtlvT0m7X2b0Pm8aL6znEvl50VXS3vk/Rgi6SbG9KUfZyOq71vDeFyLWfiQ7G/rcQ1uwHW4BbfhI1iE+bL8DNf7e2kTc36etdjfh8pz6WOwAY6V74OKke+Duh474QS5f58qz6tPwzk4HXMxDhdJeqmkl2MC7sZEfFLG6/b5pq627zltl/1vF7bDJ6RdsFD2wyext5nWyxnZTK5XLK5fG8n22hgbYVMcjs0wDcMwAzvgfGyBD2FLzMdW+DK2xqPYBt+X/J9iO/wJ22OZDNfbUZjMl8V21Fa2o3boapQv364u5WpalLtbju+r0AdXo25XD7M/3vwkn3dGjjdn0dnuUSzlglwqt3t08JTvkZD2nHDZHjpKe85gafeIkHaPrngndsMVMn4D9pTtoC8+g/3xGxn/Kw5E9huVroekLz6n0+Jiu07JJdsL5xK1XB+iK36ENfEfWB+PYzB+jPo5DZneOIvjTKGLeTx52sUs/wx2xn3y/tCz6HwOsFim4+FS+TnAJbXN/XwVRhnDcQrej3G4BlNxLc7C9bgYN+BKfATvw424BTdhMW7Bg5L/A9yGn+B2/Ap34A+4F3U7QStzPmdZ3Demy3N3mdgIs+W5uzkYgzkYj/MxEXPReR2dL9OdY3Ed/ZxMtwib44vYBvfjdfgSXo+vYBIewmR8HdMknSHpH+V/RkW2Nj/vA/k8f1wvnzeSfM1wFHbAMdgZx+K1GIPq/IixOF2WZxLOxslS/zdIvTNc3c/G4hpJb8Z4fByT8SVMxNcwCd+V6er2/jbm/Hpa7I+fynXsZ+iBn5er11gpt96iXr8iXyCewnD8FiPwNPbB7+R5yR9wmIwfjT/Kcv6EN+OZcs8hhrc1P2+ARXsL60KtR8qqz52DDdX/7jLrOwf741ychvPxJlyEeeoaxjyeLkNjmnfiXhlfhPdgiUzvS3W+NNtdFqAv83ILdsNbsQ+STx8XjrQz5zvG4jxyv8Pcj1mHavtbi/1wHQ7Fh3CkWce63iPbm9NLsKj3AvLVw63YAndgR9xmzJ+ke+ETOETVq9n/uwdH416ciIXyeYeIYvm8eKl3Y/pF5Y5rTeQ41laOY8PwY5mui4t5PKHu1Pr8Ajcidai2z6/wCTyFe/A0vonf4bv4PZ7BH/AXPCP1fRbr4DkMxV8wDC/gNfg7RiIzzvcSgouch12NDObyfCH9VMbxcrGrvG9MvrpYF9tiPRyG9XEk7sHp6hxkXk80xmUYijuxCRZiGD6HzfEEtsAvsDV+g23wd9WWZbY3dURf7IQR2BmvxXY4DdtjGnbB+dgVN2A33IQ98RBSRn0vYi/8O/bDX7C/8Xk4AD2NfiWshYMwAKOwCQ7B5jgc2+EI7IgjsQeOwj44GqNxDt6Ot+HduAjX4Bp8DNfiblyHL+J6fBUfNuYX8/Ed3Ijv4Sb8Tsr9hFtdzO8h2ob+uB0jcBaOxj04FW/HVMzBbJyLt+E8XIJjcT9OxHdwEn6Ik/FTnIJf4jQ8i7HoyvYRh9UwFSMwDcdjOsZjBs5EY34ycBzm4Hhcj9fjY7gLt+BufA6D8QSGoPN7aPO7qO1S7V/dK3wPrfp+Xp2vuIr5SqqYz9G1avlCdT71UyEf9+A6X2S5fK1cK+brUS5fbBXz5VUxX34V8xVXMV9JuXxll9QLeS7WXzf7fFFu5eqvivkiq5gvtor58qo=
*/