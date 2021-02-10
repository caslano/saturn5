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
TQoEQbeLemCUh1dVFcKwtkIY6grS79/tk5O7d/n2eU66IHruuJ6XCPznREbvGW/tl9Kxb24BzGlyUnhnGgzsN/LHTZxmuI+XCvvrwWjs9NsX3Uau2quiGPQE+nIwvdPO7CdYZ9QdO4NLss+dv22fX3UbxZJa39esUGUdx9HGnVnoZ35T7c5hMzhHLxeGjcShD+TNhDtzA0To2keTtIwImccJxnq4kYgxGFQGFKoZkGIXDWuk3NSXJv1WObSDChrxMlQIt5TwC7Z16DssUQawHrzhRnYqyHagGqrbVlVthODrxyPt+CxLJXYTkliSu1mqoXwq640iuFFSdqj7IvaMycQTkuM8kEb0Sty4iBfNSYxUJOqRgxh5wKWQOcXuRDLTJmtG2qk6Zsxc44n2wOFTHUMxQce0NomNrjqd7mhUST2jIWyBgBcNTBWWqnuQtT4cUFI6n0ENd5ndkLVHUxpKt6/Gr7GGwt8yQF6lOAtw4UNbwjL1E5zP2vhYgK/eN5WpzSQ2Rh/mRC7FJzbM9SSneyFmURJm7SBUD0MdCoURsVa2+tEpzvAroMOZc9G9GAzfWXbAIhXQ9FJBgLo+r/VMmZ+6EXkIkIWbprdx4jUfTv1C178K4V+2T52zq36HFon28NXVRbevnbj4n4q3
*/