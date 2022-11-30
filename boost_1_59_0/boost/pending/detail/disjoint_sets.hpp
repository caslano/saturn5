//  (C) Copyright Jeremy Siek 2004
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_DISJOINT_SETS_HPP
#define BOOST_DETAIL_DISJOINT_SETS_HPP

namespace boost
{

namespace detail
{

    template < class ParentPA, class Vertex >
    Vertex find_representative_with_path_halving(ParentPA p, Vertex v)
    {
        Vertex parent = get(p, v);
        Vertex grandparent = get(p, parent);
        while (parent != grandparent)
        {
            put(p, v, grandparent);
            v = grandparent;
            parent = get(p, v);
            grandparent = get(p, parent);
        }
        return parent;
    }

    template < class ParentPA, class Vertex >
    Vertex find_representative_with_full_compression(ParentPA parent, Vertex v)
    {
        Vertex old = v;
        Vertex ancestor = get(parent, v);
        while (ancestor != v)
        {
            v = ancestor;
            ancestor = get(parent, v);
        }
        v = get(parent, old);
        while (ancestor != v)
        {
            put(parent, old, ancestor);
            old = v;
            v = get(parent, old);
        }
        return ancestor;
    }

    /* the postcondition of link sets is:
     component_representative(i) == component_representative(j)
     */
    template < class ParentPA, class RankPA, class Vertex,
        class ComponentRepresentative >
    inline void link_sets(ParentPA p, RankPA rank, Vertex i, Vertex j,
        ComponentRepresentative comp_rep)
    {
        i = comp_rep(p, i);
        j = comp_rep(p, j);
        if (i == j)
            return;
        if (get(rank, i) > get(rank, j))
            put(p, j, i);
        else
        {
            put(p, i, j);
            if (get(rank, i) == get(rank, j))
                put(rank, j, get(rank, j) + 1);
        }
    }

    // normalize components has the following postcondidition:
    // i >= p[i]
    // that is, the representative is the node with the smallest index in its
    // class as its precondition it it assumes that the node container is
    // compressed

    template < class ParentPA, class Vertex >
    inline void normalize_node(ParentPA p, Vertex i)
    {
        if (i > get(p, i) || get(p, get(p, i)) != get(p, i))
            put(p, i, get(p, get(p, i)));
        else
        {
            put(p, get(p, i), i);
            put(p, i, i);
        }
    }

} // namespace detail
} // namespace boost

#endif // BOOST_DETAIL_DISJOINT_SETS_HPP

/* disjoint_sets.hpp
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
*/