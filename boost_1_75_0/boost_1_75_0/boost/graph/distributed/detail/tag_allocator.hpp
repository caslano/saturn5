// -*- C++ -*-

// Copyright (C) 2007  Douglas Gregor  <doug.gregor@gmail.com>

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_GRAPH_DISTRIBUTED_TAG_ALLOCATOR_HPP
#define BOOST_GRAPH_DISTRIBUTED_TAG_ALLOCATOR_HPP

#ifndef BOOST_GRAPH_USE_MPI
#error "Parallel BGL files should not be included unless <boost/graph/use_mpi.hpp> has been included"
#endif

#include <vector>

namespace boost { namespace graph { namespace distributed { namespace detail {

/**
 * \brief The tag allocator allows clients to request unique tags that
 * can be used for one-time communications.
 *
 * The tag allocator hands out tag values from a predefined maximum
 * (given in the constructor) moving downward. Tags are provided one
 * at a time via a @c token. When the @c token goes out of scope, the
 * tag is returned and may be reallocated. These tags should be used,
 * for example, for one-time communication of values.
 */
class tag_allocator {
public:
  class token;
  friend class token;

  /**
   * Construct a new tag allocator that provides unique tags starting
   * with the value @p top_tag and moving lower, as necessary.
   */
  explicit tag_allocator(int top_tag) : bottom(top_tag) { }

  /**
   * Retrieve a new tag. The token itself holds onto the tag, which
   * will be released when the token is destroyed.
   */
  token get_tag();

private:
  int bottom;
  std::vector<int> freed;
};

/**
 * A token used to represent an allocated tag. 
 */
class tag_allocator::token {
public:
  /// Transfer ownership of the tag from @p other.
  token(const token& other);

  /// De-allocate the tag, if this token still owns it.
  ~token();

  /// Retrieve the tag allocated for this task.
  operator int() const { return tag_; }

private:
  /// Create a token with a specific tag from the given tag_allocator
  token(tag_allocator* allocator, int tag) 
    : allocator(allocator), tag_(tag) { }

  /// Undefined: tokens are not copy-assignable
  token& operator=(const token&);

  /// The allocator from which this tag was allocated.
  tag_allocator* allocator;

  /// The stored tag flag. If -1, this token does not own the tag.
  mutable int tag_;

  friend class tag_allocator;
};

} } } } // end namespace boost::graph::distributed::detail

#endif // BOOST_GRAPH_DISTRIBUTED_TAG_ALLOCATOR_HPP

/* tag_allocator.hpp
6dNESd6TpNpl/5IBaF2ZQ1gPLa7D9xMyNySEBCyHBHhEu6hSlRcENIQZ5DpJuefQUPBb8xWN0USkB12CUfvgbUKHBpRvXff2VSCTmAFSH607iE2WQyyt+jnCQHgt7WOlQcNgfqzVD2WrJVbExO0+I2v180VV3PF1bNJ0+rzGE0F3daYVbD3Rd62A6UKnWwZGdIMXD6rlie+I9c/YzXIgTADV0qR2xN7wexPb83pTEOyQ3NXG/jX4ZiohNqxgUnd4LBfuPLze1Y/mLBdS5Tmpek/bkyZWZUeGFbWLrDwnf8q79FUw+X1h+TivL/HK5Yb6qib9eC2pIgJifr2E0ZQt9DmePVXtZBHfbCejFDu5laoAamRiyZmvdsnxIcXPHHRDFP2u4A1b7AaFoQM4zO31K22j7eTxX/NjD/rEpbTZY1/eoFUvBz0j6ttjb8ePqULgtvgRK9ZsYRsGoDK5NvJZImru2OJYW5jjCPvBAw0dcWjSK0laW1hbOJn0eKqMy/3c+4fqPIX0wFvoNAn/oYzPD6kwhK65IMfPA1HSgu0mPUZw5ICU5WMpHQrPoV/GtJBnOuWI0j+pS2HoiG9876QmSc1GT24jX/qjvTQZwclqn2e9lUDG9idgm5BMDZoA6cdxlrBc4c9WdlSHH33CTYovpjn0W7kayLKtxjRmHH+u5XPJSPjX5wIDw7zTcs5eHmVgAbFXya/g0cE/HC3o
*/