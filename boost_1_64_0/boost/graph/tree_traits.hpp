//  (C) Copyright Jeremy Siek 1999.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_STRUCTURE_HPP
#define BOOST_TREE_STRUCTURE_HPP

#include <boost/tuple/tuple.hpp> //For boost::tie()

namespace boost
{

template < class T > struct tree_traits
{
    typedef typename T::node_descriptor node_descriptor;
    typedef typename T::children_iterator children_iterator;
};

template < class Tree, class TreeVisitor >
void traverse_tree(typename tree_traits< Tree >::node_descriptor v, Tree& t,
    TreeVisitor visitor)
{
    visitor.preorder(v, t);
    typename tree_traits< Tree >::children_iterator i, end;
    boost::tie(i, end) = children(v, t);
    if (i != end)
    {
        traverse_tree(*i++, t, visitor);
        visitor.inorder(v, t);
        while (i != end)
            traverse_tree(*i++, t, visitor);
    }
    else
        visitor.inorder(v, t);
    visitor.postorder(v, t);
}

struct null_tree_visitor
{
    template < typename Node, typename Tree > void preorder(Node, Tree&) {}
    template < typename Node, typename Tree > void inorder(Node, Tree&) {}
    template < typename Node, typename Tree > void postorder(Node, Tree&) {}
};

} /* namespace boost */

#endif /* BOOST_TREE_STRUCTURE_HPP */

/* tree_traits.hpp
mi2OP77bc8fxLawPu2S+3G+Uv53RK3XI16Vrvpw1ezLrVGcpv+9E7M8r00Mv/P1qfvuvq26+rmlPS/7qARNjL3vMXPb0ioDCI8tn79e0hbK8XJakRVZ7+ubDIbdC/IK2DvuaawnKG5drzwYwn0zfU57OtmBTyU8g3832eaev8zOrsLbb9tndz/o8kfxYhvOV5txX5+Bc4m3b5wW2z/m2zwttn/fYxjslyPm5G5+nWp+lzdQYPj/M5+dtn3OCnO920I/d49XnDI3pU5/PErnqs+bKeg55mnoPCrKpSLcyOFbtBDdxcA/F97AabscW+AF2VumeKv047sCJuBvz8SPchwfwIB7Eo7gHP8NDeB1ba+o9GdhaTYc7RqvpyGZS/TEHQ3AChuNEbIHP4XW8oBnvm5BhSOjlT6vhvMD4IvFFrI4vYU2VX1+l43A6DsNXMAVnYRa+inn4Or6Mc/F1nIdv4gJ8Cxeq+V+Ey/BtfBfzcSW+g2vU8N7HpbgDl+FxXI4n8U38GufjaVyFV3G1qrcs4/0AeFnNszcmqfmNpVwYDsJGOBS7YhzGYDz2wwTMwGE4FRNxFibjOkzFf+BINd4VmmozH39T4/XHBWq8C0trecH4DtbAxdgMl+BjuBR74jLsi5twKL6L43AlvoircDGuxqWq3HpciztwHR7G9XgKN+APuBEvqfLXsbOr0Wa8tHEv0zuczy1d1b00L+oHj2M0nsbOeBZj8DsciucxBX/EifgTzsILuAUv4RH8GX/FK+jOuK5iGfwFI/EnjMZ/Yju8gX3xJo7E25iDf+AU/BMX4R3chH/hUbyL5/BvPI8a8/sLuuAf6IoBLuzPMBLdMRo9sBWWwt7oic+jF76lyq1Eb1yNPvgBlsMD6IvHMQxvYyV0oy7DsSJGYF2sgtEYiS2xGsZgdYzHGjgCa2GGSmep9AtYB+dhXVyI9XCN6n8LNsDD2BgdbuwH0QdbYBQ+gs2xJSZiK0zFNpiFbfEl7IAfYmc8hF3wBHZFfUfUHSMxAetiEj6KydgXh2MypuBEzMAZmImzcRQuxix8D0fjYRyDn2A2fok5eBYn4feYizdxMnp5cLzCWjgFm+FU7IHPYSI+j+PwBTyKM/AbfBm/xZl4EV9BrRT7NayCszEKX8MO+Dr2wzdwMM7DTHwTr8vx1mgLl21B7Wcra6xnqP+9SucKOBfr4jxsj29iF3wLe+ACjMdFOBzfxlxciq/jMiS0d3EdrsBDuAa/wbVYiOvwD9yPd/AA+jjY/rEafoDRuAO74C7sg7txBO7BTDyAT+NmnI1bcTnuxxWq+zb8CPfiPjwp+Wo/E2K0vSptxEq9dHRl/SNf/yvlquU1RS/sgN7YFX2wN5bBWCyHceiHieiPIzAAMzEQszEIx2Mw5mIY/og1UF8WnfASDsA/cSCWdeF4gH44BAMxDitgAobjMEzCkTgF03E6ZuBszMS5OArnYxYux9G4CbOxAHPwK5yAV3EiurqyXmN5fBofwmewA3ZCQpuMQ/BZHInTMBc3eLFe4CZciJtxJb6H23ELHsCteArfx19xO5Z2Y/ljBO7EZrgLe+BuHIAfYjLuwUzci+PxI5yC+3AR7sfteABP4kEsxEN4GQ/jXfwEXdh+j2A9fIH56IIzMQFfwxScg+NwPr6Ly3AVLseN+C7uwBW4B1fjPlyDH+NaPInr8CvciKdxE1b3oJ6wDm7B+rgVs/F9zMHtOAk/wL24Aw/iR/gp7sPP8AB+gQX4HR7Gn/AT/CcewVv4Kf6Nx7AM+43jGIGfYVM8gY/gSeyEn2N3/BJj8RQOwa8xCb/BNPwWx+EZnIiF+Dyew+l4HlfiD7gOf8L38SJux59xH14=
*/