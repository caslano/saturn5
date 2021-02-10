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
6jAQfc+vyOD45GAovSg4pTMUgSpYsK3WMnfGKUlKC/3AJLSU8cffAFfxwTwk2c3Zs5vsiSYoFzjgVAdanIW5XNa0KnNGuA6coTsD6ywvs/co54IDDZ0PNXTCgwtwAftJTDNR5zGhQMNHQyI4ZQVlOuCh2Ej8l6ltGMURxWsdpGsSM1jfwMuZd4+SfIkO9Sh/Wp1reYCuOY9k4BmvhTQQW0b5N+nZAbUsSOmpaljGIoI4Z2y7EZTAn5eAGjoBoYbzNA0yooP6Ft7BA+MdQpfm1HEfZneXjmPOpraLYD2Rib6xWhgnFB4ourVfK0Y/stV08Kl8flTNjq/s0BUaqp3enoxaLaXlO055hbufsdH03lor9qLOXQ9fzcNRsL01zUFh4C6UdHXGA9iTw1CtfdBXKtwcHM2HUs4Pg16V3VttfP+o7qy9vXIta4Rjx3R2m+1iF81v/Gw9IRvFXbOR187+ArujDqrWqzCosUh8106Gb4b3uBwPsTs27Ec0/fNhzMvFy1IojZ65UpX4JmpbNApdpSPsdjlCfj9dqWPhT8y0JPvUUygZTDqjpkXemuN47Be3aL9NKvW5SGeN517Dirx1b98YE8966h56Jh/wKA9Bs0IH/Rd78m5OnwbdX1VwVM4JKbvwX1tSc6+UxWEF
*/