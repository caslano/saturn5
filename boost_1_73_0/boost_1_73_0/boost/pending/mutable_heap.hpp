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
tovBs7MY3YmcKYhvXEXl9dmLTh9RTK4svHMVpzuWF8JlN9vVcdeJIr6b2S7Jr5CvWtYnZhJ3knGN5CMvPXi0hrIC8iq+wyvA6xjIX0rMypZtZe3yu/xIepxiTuwVvXw+8M8bK2eu3JC/wbIL9T2bb7c0k5BjO8c/6Ymg/dzl0/Lo5k2VvrxOme8QIcickY10MYtllEv1md2Msw3mL0+zyn8O/wNnrQQBQMtDUkrHhF109S3mxWQlT4oJFHWOt64kdOWKLSB4KMIoSUQmK7YTeSEv5ZvrVCJOb6Rup9HNfgqFaoKL/cuO0he2tfNaOdnNF0vfKic+i4xvSXq51jL9ss8fF4lS5wOlDPcKN7b8QtpmfEmaXVbfTNJ4jsJp8vLqyWJVBLO87u2K6jQ0jVrN5D14nyn3KIsm+WR55h4jelukEy01ulTyrQLSCl4u80LmZLeIQ+m1FZvIAMPb2dx4mQSd31nv+vzKojf/vU8aOwYDC5W7nkbWkJLgZGRBlYPrYE9EXh9mQru17eGB4qjz0rZJIZ9v/o1JOg0Gtmir8kZjPKQka4w9wLcpZbuTMG8cNF5dqwv8/2wUw4IZ4kqWj0kXa5LEVrBgJcNZ56d0k5i9wzrjmpKSjANVvmAHKltr6mIeFNucoabrrKK6
*/