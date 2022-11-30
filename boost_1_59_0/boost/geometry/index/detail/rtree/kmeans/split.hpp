// Boost.Geometry Index
//
// R-tree kmeans split algorithm implementation
//
// Copyright (c) 2011-2013 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2021.
// Modifications copyright (c) 2021 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_KMEANS_SPLIT_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_KMEANS_SPLIT_HPP

#include <boost/geometry/index/detail/rtree/node/concept.hpp>
#include <boost/geometry/index/detail/rtree/visitors/insert.hpp>

namespace boost { namespace geometry { namespace index {

namespace detail { namespace rtree {

// TODO: This should be defined in options.hpp
// For now it's defined here to satisfy Boost header policy
struct split_kmeans_tag {};

namespace kmeans {

// some details

} // namespace kmeans

// split_kmeans_tag
// OR
// split_clusters_tag and redistribute_kmeans_tag - then redistribute will probably slightly different interface
// or some other than "redistribute"

// 1. for this algorithm one probably MUST USE NON-STATIC NODES with node_default_tag
//    or the algorithm must be changed somehow - to not store additional nodes in the current node
//    but return excessive element/elements container instead (possibly pushable_array<1> or std::vector)
//    this would also cause building of smaller trees since +1 element in nodes wouldn't be needed in different redistributing algorithms
// 2. it is probably possible to add e.g. 2 levels of tree in one insert

// Edge case is that every node split generates M + 1 children, in parent containing M nodes
// result is 2M + 1 nodes in parent on this level
// On next level the same, next the same and so on.
// We have Depth*M+1 nodes in the root
// The tree may then gain some > 1 levels in one insert
// split::apply() manages this but special attention is required

// which algorithm should be used to choose current node in traversing while inserting?
// some of the currently used ones or some using mean values as well?

// TODO
// 1. Zmienic troche algorytm zeby przekazywal nadmiarowe elementy do split
//    i pobieral ze split nadmiarowe elementy rodzica
//    W zaleznosci od algorytmu w rozny sposob - l/q/r* powinny zwracac np pushable_array<1>
//    wtedy tez is_overerflow (z R* insert?) bedzie nieportrzebne
//    Dla kmeans zapewne std::vector, jednak w wezlach nadal moglaby byc pushable_array
// 2. Fajnie byloby tez uproscic te wszystkie parametry root,parent,index itd. Mozliwe ze okazalyby sie zbedne
// 3. Sprawdzyc czasy wykonywania i zajetosc pamieci
// 4. Pamietac o parametryzacji kontenera z nadmiarowymi elementami
// PS. Z R* reinsertami moze byc masakra

template <typename MembersHolder>
class split<MembersHolder, split_kmeans_tag>
{
protected:
    typedef typename MembersHolder::parameters_type parameters_type;
    typedef typename MembersHolder::box_type box_type;
    typedef typename MembersHolder::translator_type translator_type;
    typedef typename MembersHolder::allocators_type allocators_type;
    typedef typename MembersHolder::size_type size_type;

    typedef typename MembersHolder::node node;
    typedef typename MembersHolder::internal_node internal_node;
    typedef typename MembersHolder::leaf leaf;

public:
    typedef index::detail::varray
        <
            typename rtree::elements_type<internal_node>::type::value_type,
            1
        > nodes_container_type;

    template <typename Node>
    static inline void apply(nodes_container_type & additional_nodes,
                             Node & n,
                             box_type & n_box,
                             parameters_type const& parameters,
                             translator_type const& translator,
                             allocators_type & allocators)
    {

    }
};

}} // namespace detail::rtree

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_KMEANS_SPLIT_HPP

/* split.hpp
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
*/