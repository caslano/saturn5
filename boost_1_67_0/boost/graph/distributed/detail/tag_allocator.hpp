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
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
*/