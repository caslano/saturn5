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
GsUY6RxPZsYJ3jwXd90hw/pNMB/9xtFgeL5R3J9Ti3lbe0Xs+U0PyJDFqHzaUX/Rq9QhTNKBjSMeX4oXQSDyKF+O1HI+DUn4NWIdygOilVj3+Km5vFpqdzwvkDMrMMdlrz78ySSBo61DQ9f4e0qZhkZKLwUjYy08jsKbfQauFxTU7ugY6yT2NI7RlqPLhwfDXhUH2Gc1w96Gu63lkZLM7Ld8REpBHq99t84yyyMyefaDx/HxZJog0nyJ6+uVJ8eqtqfKjnZzIAeVklIloULyFBb99HwuLh2dGQ+VQt1MQk9GZj3i4rjIg0Ooi0crEaqsFR9xO3zQbmuPU9r+Qsr+ItAPoqgdPnHaMOyVKCqR3uX8vFF6/ROF1JywxT6dEg10xvuGMmOZLyPTE4/Msy9iyy25hLvop0p6dnaFyrh+aW1i4vA03t54lqtH/p/vLlLXSLCwgDezRstNb1UhajNHXWNHwP9sK/75fl3PiPeHwuWIdjYnxpFTinfFy0boLa0PlEt+6uXZ/fpVt4bZLKVlnO1lAvlNTa+5SpVKBfevm/C/0mNerH68vQFgsp7dTAr2juo8L2uRsbeLF7zGXJSj1qY3CYgf3aTwW7cyyjpnAUoQ3/axJK8vvoDL6Jh4u7srBgRE9U3rmpoa6OqaGS6tTbpY2Qz+NbNGNHUve5cfiP3+PBdUSFdfFPL+Olfti0iBDCCy0/G5c633okbN
*/