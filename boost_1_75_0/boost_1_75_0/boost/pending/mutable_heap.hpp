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
qNTqlGZXtDLLsx9XL/2Cl8QPYCkCQw7B4wNW9iMiZlWbJS2UblfpBxLhzZ0Vnpqmt++8VoU6G8ONQWgSmt5CyBGWo3puMWyTk6P+3Zp7F7T2FX3g5R+z7EEZ5YWaXr9dVu+kLJjVYJOfDVWW7/QCvMZyaP3eLrKN3rANM+d7Ls0ccKhBHHbfNLLOhm0r/9bl+vi8O3iRxBhZbddVEGksBKknydl2gZB6WtSQqN1I/jIlCZiJzoRy72IplJ7HCP9uvC/8JIdhdqqKb59AKCW3nPOQNqotBUB8TunyE3Vv+ANsMaldbtAL1AMg7x+5k2T+bNThznb4natDVcbMX/j6U8X89wO05Iw7mj0A+YP4Pu+PhV4ErHLuUAx+zTMQBY8d+8Ng1ReCaJqu4tQPh8qWbSLGzj7z1UJlbJY4G1j9nuQOPqC9/eM+1hjfnsDMWIX+m2Y3CQnI5AHpUTUEYvpgvISQagh7X8uleEYR9bY/cf9lu6UZUMr1EFIplw8C4mTgAbB3sGCEHlTQN5MEshNfaf8AJ/agqwUVrD8DkHgQQAOt6DYNRu9rS5Yd9y9lGr++BzeD6V4PrJn7dSbDvkSsD0FNFXi/pPDtrQx89xWGyk/OqGUfXXdElWCIni6AFR080+Th4UNJs+5kbbQWa2Yf15ytDzQumpOHDslYO31HXZnXMdJhKyPU3hgOyK66QxOjTKfqub0OV7jytJLU
*/