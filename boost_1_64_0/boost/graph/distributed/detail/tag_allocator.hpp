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
S6ym3oC/4Kr7VqkDvhXqVNISVT65hXot+Qza4A3s0X2G+tDfSOUEVqk9gTOUlXKZc2H6t65eFZ6wzq0UsCZWvkF5OXvD7HhVW88lupe7CDvAeV+hV82z8uOOxM9Viz3pqglGICbgNuD0HuoUdVB3UEaqesbxruMC59lxQ707/RmuO9IT1NPpV2n7mKaNmP1cn5F2uVPqeUYGguC1XzB98sj8qeaa3DETHVYWLtJzkTpJWbXN9jC7qZ2jqjXR+QhrL99l3WI/UvmTyo/fo1p7PlY1E1qo/IQPrXMTK6tZuLWJtdR++CMux7deve77Qb2Z9KW1L/lM5fWvUPf466lD/rNU5cAa9mWpp04G5jqvTJ/t9pZv5ryoUktVp3JddUHll1W9bK/U6SDTVpzlP1UtyvXMcqkLs+ZL3g4prilpz6tyykTaV4/oaw6MsG11n4t/nPgnBvd2lWvmpqhrhptw0BZ08XRanT03Kk7a3CU53WjLYz2uLJm3YtJ1VMIn+XX48XmTjC1EPTemyvig3szETCudNtWYawS5CX9uevAaKIjr6djjqew45e3h1f2m3uPWbttvS9t+wpnAzvJtrXJWnqO/7IO6jWMTJY2ZOSXnd7XR+xF/J8cvq3IOIWY501nXl6jGu5NV+bgG1t1scLXOk6xmJySr8V6fugv3iXd+RlGVxJLz0Myeh/0uEnu92h/Oy6cyv6dcquibPqzLhcFjV5Xqw9DlnhM9h+wnSedop1/mdCHDd7W0X/dp55Rl6XDXn+a6z9B90dkoWqwMP0+9ql5yBHQfFbv8w3vCb5G0vFbFPu9otgifUTiR+FJ0/8T3d2kDNVVAy8LxDss6qoaXC8ZVTBq2SVx7pN9KCcWVN2uaxCP+pVImdVSG/v59XHHMrsvCSeNHhfaQ123yxXHos7qzkDbV11kLOwMnyVdku6xS5qh6KT6Up5esv/nqSFsJ2oyrLWk5PyfFzGcKWkGXTQnk3HWj9nDvH9wa2uzD/K1cb0ty7DLR+z3kFUvYdTqs3ie1acMWyuztf1DOexflaebTyZ4Qwa/0jXS/c0rivzins8OjLnF51N3sFzeWfYR7xR9Xt2MQan2CWz2TsDpzco47onzMFueqkb7Xzh4rfQa7IMfz/S2AHZoEbLykqwIWYK/DfYhb7HKzfraWqqHvxwnjpD2k+FQ1+rxXrSauoZ6NvsddtwXczG/ySD48DnpPyUd2xD2QHZK5A+Zy+eMRvTUW305Fzx15r8wfkzd9UnFuYZGKaLtjpO3e7yyLVb3mVkUr19FN6qoWcdwocRytcro9H8ZJuy60stW7Zu/TX2S8UM7K0O3zi1EyJ9NxsVUP22QB0ZsU7N+nBuUDHWF7xZskrkbMJKxpiV1w045Peeur7V6Jz8iWxx9VhVwzWVYNiS98TWf4PcxxPWGN8zzqHarKJ5Z3jUlOUguSr47a+yBH59s/Wa5LXzZWBuknrWnMPn3VeVHcWO8USdf4YBnKPe8+zjPVStF9z0xJexXHamu01F0g4przqXe9p7yVna3KxFnnJpez1vnLWW8FZnokPtK5TuKry3NIqtyDC0zay/l96iDTHjPj2npWWx28ldQV3gddIxn2XpPMvqN2m5Z2zjy/6D09dPvL0Pf1o9KOb8zJ457xhWdFOX1v1umsT1hjE7pABzVzjudIn9KaZ4Y0MzdmWQEy+q8U8bMTa6Hk1xqhvjb79reQttI9x04Xs8KCQ7MIm9Nji0LzHWvrvnmk5D3ReRlPTQ/hjuOaWM3VrbKveS3sU92jwuPXSydL3VvhfjxrUsj2e0bUePYWd3A863Jc4yRdMq9wmqTLH9FnMMjLHVVYNEvPm0LHPjaZC2Q=
*/