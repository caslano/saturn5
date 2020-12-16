//
//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
//
#ifndef BOOST_GRAPH_DETAIL_MUTABLE_HEAP_H
#define BOOST_GRAPH_DETAIL_MUTABLE_HEAP_H

/*
  There are a few things wrong with this set of functions.

  ExternalData should be removed, it is not part of the core
  algorithm. It can be handled inside the tree nodes.

  The swap() should be replaced by assignment since its use is causing
  the number of memory references to double.

  The min_element should be replaced by a fixed length loop
  (fixed at d for d-heaps).

  The member functions of TreeNode should be changed to global
  functions.

  These functions will be replaced by those in heap_tree.h

 */

namespace boost
{

template < class TreeNode, class Compare, class ExternalData >
inline TreeNode up_heap(TreeNode x, const Compare& comp, ExternalData& edata)
{
    while (x.has_parent() && comp(x, x.parent()))
        x.swap(x.parent(), edata);
    return x;
}

template < class TreeNode, class Compare, class ExternalData >
inline TreeNode down_heap(TreeNode x, const Compare& comp, ExternalData& edata)
{
    while (x.children().size() > 0)
    {
        typename TreeNode::children_type::iterator child_iter
            = std::min_element(x.children().begin(), x.children().end(), comp);
        if (comp(*child_iter, x))
            x.swap(*child_iter, edata);
        else
            break;
    }
    return x;
}

template < class TreeNode, class Compare, class ExternalData >
inline void update_heap(TreeNode x, const Compare& comp, ExternalData& edata)
{
    x = down_heap(x, comp, edata);
    (void)up_heap(x, comp, edata);
}

}
#endif

/* mutable_heap.hpp
Ma7743cyHvP1c+XvOk9x3YPvsBeEd5gwh+ujQ2ONXW64n/b2MueTlazHtRxP7P89bSyP5xBHua7YzfGwsD/HB+19x27aXyb9M7+3D3mI96LoDwLL6Vdot9HHWP9M6nkm11Gf0B/G815PIMch79Uc6cJzOvqbMNe91jH8/sz+8hjNc7ZZ/K6dwXUn7a3PVKSV+q+kHfXj/DyW+yD6NQ+Gp69jfkG8d+n6+yba68SHue903T8MY72pn+gHaG+u9don9IcT+J3qfd4P4T5qSW/GK6dfoP4X3M19nuvvO3necOIO5s/5PdZ1/4/rgJ6sfzTtO74n+5H1iT7O8ZbLct5lOvaPH+MNSTD9voh/p3D0Np5L8L5cdKHr/ITjhP7mBOzUV35Tb0e5flvfnfdu3+Tfn3JencJ5KyOQ7effN2XRLxzl95Ihr/LvT1jell7sL85nW55k+dzXT+G4X8/948Ex/P7G+SliJ/Xo+ntgxo/lunYB369m/CzqZ0Y/tnuyiRc/hecGy+gn6G9nrOH+l98f8+q5X3X9vS/spiN8jfXIpX1Sr1lreO9kHPN/mOuTT9hP40y/dOd8umghy0N9IhDu4TzQcyjzpR4ODeM+NJf6ZnmF93Pe6kk7YbopzH85++kUwyyGgf2Z/+X8vsH4SzmPLuD6Nov9HjGA88J36ZcmudrBeX4uxzHHd04J/QXn57Pc5+5PRboOe2W/8RzjF30ONIytilnca+kvOk3ZFpDRt/MP61Z08knYd7Xvjt5Xzo17LrmXT6nHbO+oLm91eymudLP/yJ7vDXreJ2PjmtIA/6Dq+mcDFr8f5X1lyXs+D3630+C02G+k7/D4hRPwlve1BYl1nfvfFLxkRcmvBpX84Net95T0viot4PrSIM9ZHjGPFkYdTOjtlXJkfKcVjnfMuUSPQTlX/cwvaeir9UHnYpKHO71qYuKOjY6f+/PWgCtKYiflzGh8eeOsJQ0lh+q6DAwqGFoSOrjcNyLcWfSn2cXeg2PLPLuO9/GI6eof8FBk/Mq7VuycVe73xhVBfV6r6FUdndWlx/LeZe+1Lff4UWvd6E4hTTMTcN0/NKb0jQGPOLd6lKTFOYu800JyN41wfPevHJBd9ZsfDAlqvtEz0vnRxNfvfrzulbIMj/ZxizdcX9J2xdhxPwzdmNxY0VS3YmOwT0pVacWemPLug53YkoHdwgOO/XD5mqm90W0Bg72coE3Ooi+bI7wry/yqqoJCJo9Yusnj24NLH+2R0Rgc9JsoP98nZpWkR11dENkUlZxQtemZHpeXnntq+7BTi0d32fujD/uOmXXTds+ma7qF7PtxXNCkpYW/DfWLTexc0X//bYPnNYyaPrpl2ejOQQXTpk9+PzSvdP9zXQOS9gT1rv/tGI/YJwb3PPy74UHfzLwqvXVM/ZKqgMev6uUc3zSqb8Ccktiuw7ouHvaw7/ywutF+HscXH3f4BIORIAGkgHSQC4pAKagA60ANOACagCRuB74wqB4gCISCOJAM0kA2KAAloBxsBNWgFuwDjaAFnAMB0FwIiAQxIAmkggbQDFpBghfqB9JBESgFFWAd2AxqQB04AJrABdDDG3UDUSAOJIM0kA02glrQCFpAGzgHvDGp9gchIBLEgCSQCfJBMSgDq0AV2Ap2gnrQAJpBKzgDnE6O0xX0BsEgHIwECSAFpIMisA5sBjWgDjSB46AdXAC+ndEOEAqiQBxIBtmgAJSAclAJNoJG0ALagLcv9Av6gxAQA5JAKsgHZaAKbAU7QT1oBq3gDHD8UHcQDkaCBJAC0kEuKAKlYB3YDGpAHTgAmsBxcAH4dkF/gCAQCqJACagEG0E1qAX7QCNoAW3gHPC+DPU=
*/