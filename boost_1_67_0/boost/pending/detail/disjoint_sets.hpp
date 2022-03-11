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