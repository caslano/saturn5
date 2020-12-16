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
n+zJ/qvW13WhiecWTJne1m3OdO/crxPfY/tRwz+45/PX+yWmPLLwp3k37m26lXXuo6bzzN2z7mu3fF/Sp/V/23G2VZMIjsNqPl/xCSiaFhHxch+Ptj1mNRoYrL4LiOGLH3/o71+8Fh6+8LWxOSkrtpxWz4475KCrzjt5LgR/m+/JyXlfrj3yLnlPbq+8b/CUvLfzNIbhC/K8/n6MxndxvDwvFC/PBy3HN/ApfAuP49v4ueT/Gt/Bn1Ta2V8l53A5v+Zd0l81R94nypP3CRbJc/mLyz03Fy7l21o8NzfbUe49V8nnqfJV7FdZIv0jy9AD7yz/nJ+U87aY/h2SL9pFzlPq/GXma2lcu8vtaJAsRygGYRNsqT5f9SeT13yOp7XUc3ucjJ0wGcmj+tW64G3YFe/Gbrhe1aP5vEcPfBp7ynNY18rzV73wY+yN32Af/Fkdh83/G9wX/XCAPI8VhW1xOHbHERiNzJvq94rGGTjamB8cg+twLD6OMViI4/AAjse3MBbfw3g8hinGfGEafo0ZWIazdP3LOQkbWtR/A0e5/48n+QaqfBX74VdI/d8t/V73YWt5L6UDbsBu8j7JtfK+SaSkuX5T/U29Ii/ff7UmjbYM4hBxiqiTThsIEUMsJaRvSvqldJ8U/VEW/VC678mqv8m2n0n3Le0mjhGV+5Iq9CNV6EOq2E9UsX/Ivl9I9wld0hdUuQ+ojKjY71Oxz6dif491X89Rooyo2Jej+3GkD0f33+h+mzIifKRVH03FvpkCQvphKvXBZETrvhf6Xez7XCr2t1y5r6Vcv4ruUykl6EehD+Xf6z+p0HdSud9E+ksq9pVIP4nuIyklwq637gux7wex7gOJIKKJXGKN6ufQ/RvSt1G5X+MkcYEInFyx/yKBKE53qdRvcZy42F9Rsa+ikDhIHKXcGSI0g3ZnIpfYTRwlLmRcbTu8+nP15+rP1Z+rP1d/rv5c/bn6c/Xn6s/Vn6s//9sfd+LGv7D/n15Wo/v/P+r7N/ry7zH6rDsZbal0Vxudf9My+bj0NDob1fh7jfH9yo9Pmp0WT4+w9IknBdBWKX3iU+T2u7/0EfWRvs1Ys0984JgxZjcjU9Jdmv70E7mRL5l8KUb8ib6iNS72fUXWbet/vk/Iuk3fvm/Auu/Bvo9qbKCaz1qRCTtSnotbMfmpFa/MGHK/fV+Xdd+DfR+Mdd/Dn+9r+bN9V+a7B7LuZZsodlR89+AxeRdiCzaU//nQVv7nQw/5Lrs+uAMnuJr/rz+WsG2HtWiD1e2vFdteaXeVNtcK7a3SvlrFdlWfiu2oqv00htik2krt20lPERXaRi3bRSu2ieZcof0z0rrdU7d3ukvb5uKKbZn2bZgV2i+t2y51e6Vuq6zQTlmxfbJC26S0S1axHbKUiJC2R93uWIU2xwRieYV2xYptigeJvC+uthle/bn6c/Xn6s/Vn6s/V3+u/lz9+c9//urn/+PT05L+G8//G89v925gfgGPq8M55WnxNyVkqfv/yAaMStDjbuIh4ZtTsuOTE7PM+/9WAdzny/1/oVxKVzNR93pjKb9qt7r/N277+48aOWha/5gJ0+JZKtoSUuOmZ6ln4wepZ9zj47NzHPIMvLNcNTV+tnp2XvIzno+V8a5XfEbZeJ7dCwepZ9fVZ6hhRiGmyzA1XfNZZlmWCHle/Xt5bulDYhzl8y2WJYkHbbOSHXbLIWXCVHok6YMqvd9RQ94JMJ6i8pf3Ab5X4ybyfXFNZZiLo8keY9hUhrirMh5qDuPV+BGUOaLKtGD+fc1hukzqxTKqhjLkPQHaKVSZAOqONPnPqfQa2nnqO/qTayql0tT0RvjtI/8pV74Th8/18cl7wfk=
*/