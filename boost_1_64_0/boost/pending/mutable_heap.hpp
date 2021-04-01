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
QaAuQyzEE4tqz8HpvZdCYHSJBtZjT26Umjt/WpN7Cal/qNZCRzXTi55K3A4WiDQMS6zZTMGhbdRLNg2yJJ6pfj/N5Jn1iTDCE5HqNilCT8H1zK1QbSTQtWrvZmngpIKSdftqq+jT6+Q93fb6oWFHRgrqBZM/BIfD6miUGsQnaBY6mvNvxyuYv5gEg8hpNxEgm8x7n8dAvBJWOGtpXJTUHw8aXvSQXlpnFYk79xwvYN9d50ujOzk1lWPhfLF5ntXsMs6/WRTOjp0kQgnIwnYXGBVD9AsHnJ+o1kXgg7cn2M1Sx5xj7ViDmyQKyzcQ7+FrWniIN4wiwmp4J6s5Xk3hVDPya98J4YE4WjcKBlVVS83c9HfCoOgtFR8TeOJCQUc71KANa/tN52Ce+7C0ampgyW+H8U2jPMsrU6Xb3CE1saqhm9gktyLzCEbl/zibxunl1ccnRrSzN2uNSVGdnVehXjyWl02s4ag8fF3wMR5doAihXAijbT7BHzdPDmVOSxjN8I4senNsf7hK2PyftZxwl883+tS1q9Mv4EXLhaqZ24/ANU/rEaHziLG0OA==
*/