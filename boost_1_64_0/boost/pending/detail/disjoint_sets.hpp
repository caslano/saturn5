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
ccvdoT1/TXv6tfp8Vvj9tc9hvq39PuM84Pgt3WT/jL+uO2zcvkm7Pl/9uly/YrsP2O/F+vHZe2zXS/ov12mzNjve3rf19X4f+JD9Dr83PlP9LrSfP9Wvup6c4bg/ep/179S+ZyrX8a4rE5ynLGfmAe3MeWKLcfx16unTs/Q/+9STZsszvt45Xr/9MdsVoxz17zvujNLOnG/jlXuxdvhL7SjZ8fyJcnQefvY573+T9rzDeKXYetTTicZRF+knr/ykdlFu3He/47nN8dQvFOoXbt/geCiHjUX6WeXxtN8LbKzwecBO5eH8d5HjsLVWPUsP/y5BObxsO+Od1y7VnvRv8180/3z9Y4XP0Z2P5oe/Z7nFcfq484z9ufpp4wHlM/1r1uvz+7vz9UOuU877iXpXpD6rj0+nK4dV1qMePZ9k/AuvlP9d6+myv++2HuOMvb+O0r+4DnzK9p2pX+o1Lv+q9qNdH5qin5ppO+rC311Z7kb14suWH6Vf7tT/9OrfprguuUm7iXe83udzjG/rxxYql78an+/TT12iHWlnE7+hnB3vyecZz7Trx1J9fvMr3yc8qJ0ovxVbjcuHtJufq7/nqq/ax/oh/eYR51XXQRs+oN2oZxtusL+uDxf8TP054vrTuOTwIuO9v1iO8eumj9q/XfrxA47/OPXb9s1e5f0TfW70A+eTO13fPaYferPz2Nfsx4X6X/3y4njz279na71vvekK9blAPZvqOFjehnr1UT80L9rn6s4fDzxruae7PlynvUcppwb1cK7xcPi93oeV9y7vbzeudR65/mH1v9D5x3ZuPks9eL/12I/rf6F8WvT7+frZr+jH9nqcpvxdP165wPWx+vPsFufBWdpFnPrg/HR12D6T1UP14DrHZ2+0/ah0PJ1HcvVnR6JC6dIY48OfOg9sV48c7/wmx/M3js8PTL+sPcb63qjI/l6lPrpum6jejnd9vPhF/Yf93v2ScdN6/XuK84T1z/ux9/3WOPtK7Tj8fdkL2l2p/uU91l9mfGgcNLPbuOa3zgeNPi/RvmY2+b70W8YjHi99o3p8he261HHf4rzlOG6f4LyhnK981vfi8+zfz233fP3/auenOx3Hx5wPfT6yKUa5bdSeW83vfLnL8tdbb77tWfBRx1G7nPdN25usv73f66uNR1Ns/0H9afg9uvXN/qT9utX5+Suu96LVJ/s/XflMv0A/Gv7O+Hz7Mc71yRtcVyXpD6xn8eucRx5Xn5wnZ5yufbzFci92PnwkyvWu89d5yrXY9ech+3mJ88Eh/cTb9Td3qN/qwUVe3+F8uOI1lvOicviO89YN6v2TjvOfo/T/trNTv96h/Etch6vni39tP23vFp+T317v/frNDeH4VH3JTdBP65cnOs6bjc92Vjm/hN+rPOW65EH15HT9wFtdv21yPdqn3XYqv9nqaa/3dzu+39NPXKBcfms5c52/9ROzn3a+DH9/stm4yOc6uweNS34cZf+M55RH1Ke1h/B3Gf/Q39nuveabbzlXf8jz2dpHs+P61ijbZTtjbPdP7Z/93xKnPjzufQ9p52eoN78yrnmDz0/0m7P1Q4+O0c9a3wOF5v+xfuVM84flsSXK57363wb9+mT9f5pyiTH+t/6ZNzqPqW8Pas8bvmt/Gm3vHfqxifrDaWONq+3fadr9Wfr1fPVKecx1nbGpVv11fTtrjM/TwnJBv0L1aQeXO25TnEdNx9+sXzJdvMH6XYdtUu/G6Zd2Ghffk2i+R13P1zg/XOQ47NKuXLfNer16eLvz+0rn1xfs91/tx/32a4PrKv3Vuj6vP2Z/9ukH59l+4+Y9rc5/bfqvOV5XbzZFKddCU8f1Iu2zsMlxC38=
*/