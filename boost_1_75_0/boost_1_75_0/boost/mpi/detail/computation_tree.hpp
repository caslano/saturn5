// Copyright (C) 2005 Douglas Gregor.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Compute parents, children, levels, etc. to effect a parallel
// computation tree.
#ifndef BOOST_MPI_COMPUTATION_TREE_HPP
#define BOOST_MPI_COMPUTATION_TREE_HPP

namespace boost { namespace mpi { namespace detail {

/**
 * @brief Aids tree-based parallel collective algorithms.
 *
 * Objects of this type
 */
class computation_tree
{
 public:
  computation_tree(int rank, int size, int root, int branching_factor = -1);

  /// Returns the branching factor of the tree.
  int branching_factor() const { return branching_factor_; }

  /// Returns the level in the tree on which this process resides.
  int level() const { return level_; }

  /**
   * Returns the index corresponding to the n^th level of the tree.
   *
   * @param n The level in the tree whose index will be returned.
   */
  int level_index(int n) const;

  /**
   *  @brief Returns the parent of this process.
   *
   *  @returns If this process is the root, returns itself. Otherwise,
   *  returns the process number that is the parent in the computation
   *  tree.
   */
  int parent() const;

  /// Returns the index for the first child of this process.
  int child_begin() const;

  /**
   * @brief The default branching factor within the computation tree.
   *
   * This is the default branching factor for the computation tree, to
   * be used by any computation tree that does not fix the branching
   * factor itself. The default is initialized to 3, but may be
   * changed by the application so long as all processes have the same
   * branching factor.
   */
  static int default_branching_factor;

 protected:
  /// The rank of this process in the computation tree.
  int rank;

  /// The number of processes participating in the computation tree.
  int size;

  /// The process number that is acting as the root in the computation
  /// tree.
  int root;

  /**
   * @brief The branching factor within the computation tree.
   *
   * This is the default number of children that each node in a
   * computation tree will have. This value will be used for
   * collective operations that use tree-based algorithms.
   */
  int branching_factor_;

  /// The level in the tree at which this process resides.
  int level_;
};

} } } // end namespace boost::mpi::detail

#endif // BOOST_MPI_COMPUTATION_TREE_HPP

/* computation_tree.hpp
TY4YplE+BTpCt1xUCdjfE/nYvgABmL9Eh53FkiD0N1dE5xKulJp+lnDkZoykQXwhgejU2qZodutuKpqCiKYIv1gFr4QIbt2qaHhjHXxsx9RmXhI9mrYG4RingitzfrgIbHsrxn8M3Is+l5jfvpDMBFOmnP41wNUl2Cbf1HDhSuuUWuV1vew4iDUneOm2AlpWS4vD+RKtt7rJCr5+R7bG0WNi3M1xhz2RsRfpmb6rvvvZyPK0qgr/5nXGEfeuxOCAU+4UDMz5VAVnN24dCa0xHa8RX1pv7QSipZfLo3UO5YCcXGcuac2OM3DfFaLeNsvMkb6HfrmbsPlOpsHJd2m1X0bBv8mDlFvDuH8KvOXzyBBw9v/Y8RVR4Tjw0khlhwS2OuugayhnC10xXDXC9V3Lv0f2vIAKt7KHtZg2wiOraRFKeCX94aRR+mnvpsQjNM+x/E7db6bcCdop01/+g1GI+HM0tYtuY5+qMLkf8lR49+Tte7vQwQ6JNqrf5AO3w582ajLPhlm7v6OzLlbBwY5KoDUHz47SMbMHyxjfI7+kR8VvG2tug8a/yiISMkegS2H3KPXDZpbCF4cfJ2iF5W0vPx7ZGOnIWi139/286JRCB6XgWYiTsCHMsLi5jcm/bYvuaVa2dMLAyQHldo97AUYLh13z05mVn9vx7iVGU4ekBVib7FmmFskRFOiQkHYX1dmKu+4H6LcV/p4svFbs
*/