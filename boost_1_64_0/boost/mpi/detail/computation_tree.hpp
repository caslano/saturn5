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
HrCkq3+2HeJIBbEC8lFn3hgQzNVMuxq/zmWziHmYT6uvEdfuQ8DX+LDl9VQ1vHushpdtqptlduJ2YCw6AWNOlTKC+Zm2xYf8hNuBpaibR/kp4zJSID9mwWzjtfgKZhkb4yuYYfwsvoKaMSW+gl6jX1wFmyghGE/z50neccgrRJFSfMkpO4AM2/Bdy8mthWVdbF/W2Rfxsn6lnmCWDvAvNTkDDpi/0FrMLFrMLFzMPayXgYLZSX2gYGJBLTcyILeWMEPLL5OnguFMZkWjvauOsjZ7Lw7OZOnAUqg2IK8mmKcRRI2Jyxj9OikP+dyrNrZeeahXHrxz/pi6pLG7eQFAoqROSvr50hhxAgh1WabclmT8j4w5NhnJf9LHvG89r9vpiXuxSU966l4b67MQ1uiUC+Wx6RWXRW7pOABk8+5432vz/lUKr1HpWsorsL2Fs6H7DFEON0ikIVh426gG9l8gDcyFHA5/pC5UnY07rKgGZCowEYqEBpBBMSTTmfMQFLEF6W9LcaD2seQrdBBPoLSf7+eXD/eS7vpxUc2fe4EicAktGF1t1Ojqiw1mQ2qp87U5efUg9u0f1dSn5zO664CkA9S+qRXvB8+Osm0WxOnxSuABQfbcIuxoSx5SvhzFg8uq6gE8Fc0YvhuQVY8dwTN5MlWWj2Dln/lvjO6W/P9ykUcJ6+LvKXzLIpjJjeeZzHQXF+Gw56ru/v7C/2CR1VYRFKZa/AuSCPDyNC7bPMX4XgW34jP62a9zk42uS0z+yj/UDryPBfx2GwdNxNunRWBNvYUzwq3CiiMGtEN3Oy/CGAlhwnCWj7S3sf1caSM0QiIos2fWnxKmoNiXhCJdgY4ROoXxdsgqiy6kyN+HyeneZuVfCx3kX/Ob1t8dOL95+djZU5qRf/kl38n+ZLB6N3iMNY/FmuM+/uofons+Uo8Gn5yphK7xxcdytK/1Wt9JmACOLJq2Xx0NfLe/B3SCTKIMPer9pRfnjNNLWHL59HQROg8GSgHoTGbMSWFAlg4d6+ntSkc/o1MgdAaw1mT4oQXz45IBO8y/8QgTCSUXTOXIJMF28sTZqPw1EeXbqvL5HquCVd7BtYdTPoXymSyzaOWzjdQMZwN5S/55sXr/vsOjDoewU8jH+pyCcNE0c2OVeaxIjxmmDx26B3zyE+I7OHqfR4wv8Ym1I+rc6JmvdGO7nAksww/d3qKJj8aP7hfb7IvTgfyxPYyydyE1H+OysaYOTKuN3egJQ9/2kXpUep6l8pyTB4Y0nny98iOxHeJMFeAt1yqkwduNFPqZFKLQPWoD+aUcFZmmbo8r8JzzfqyaHk8VvWSP05/uVzP6c1BG6Sc+OuvpUr493zAiujrwY9WLL2ZJL6zhR/Wi4hKrPvIZ26GhsVCfnoGepvoEi2Bk5pdOzgBukE5UX0SdqVJntdQhgVxhB337q924q3MoB1yh0T2zD4PMyvfzoNQT0thLGo9Hl/H0VbCFiv2Z3zEiZma5zEz4IirMl1pubGBUY2/z5B0Nsv0TPlb8y5lqP+6B249NOwAnMm1rfj8YDPw7KTtfHyH4981MDv/ag8SYz5/EKIQbjVfpvZnNP7hZ9g8XqvZXnmJrP+mqYYCfoE67vaaNVj4VWg5ll8/Cf3qVB/CfruVr8J8O5bfgP77yDfhPUvkm7CPqdK6DenfAz6Pwswl+7oOfm+Fnb5wfM/7PZc2fh+tny3nnIO88coFdX9xIBv0EFmbilW0LCTr1hAuOTzKhHQdqLdah4T4bvFtIEVE7PHIWJpKItBKeVVgFQNWxAkdjTSqQtFSt0AQ8utLLMDT4wpOoUlmuwWU2jZW4uSg4JQprJBdSGuVfx4odrDl7wUU=
*/