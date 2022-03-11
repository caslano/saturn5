// Boost.Geometry Index
//
// R-tree kmeans split algorithm implementation
//
// Copyright (c) 2011-2013 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_KMEANS_SPLIT_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_KMEANS_SPLIT_HPP

#include <boost/geometry/index/rtree/node/node.hpp>
#include <boost/geometry/index/rtree/visitors/insert.hpp>

namespace boost { namespace geometry { namespace index {

namespace detail { namespace rtree {

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

template <typename Value, typename Options, typename Translator, typename Box, typename Allocators>
class split<Value, Options, Translator, Box, Allocators, split_kmeans_tag>
{
protected:
    typedef typename rtree::node<Value, typename Options::parameters_type, Box, Allocators, typename Options::node_tag>::type node;
    typedef typename rtree::internal_node<Value, typename Options::parameters_type, Box, Allocators, typename Options::node_tag>::type internal_node;
    typedef typename rtree::leaf<Value, typename Options::parameters_type, Box, Allocators, typename Options::node_tag>::type leaf;

    typedef typename Options::parameters_type parameters_type;

public:
    template <typename Node>
    static inline void apply(node* & root_node,
                             size_t & leafs_level,
                             Node & n,
                             internal_node *parent_node,
                             size_t current_child_index,
                             Translator const& tr,
                             Allocators & allocators)
    {

    }
};

}} // namespace detail::rtree

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_KMEANS_SPLIT_HPP

/* split.hpp
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
*/