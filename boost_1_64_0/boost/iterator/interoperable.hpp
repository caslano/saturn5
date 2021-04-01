// (C) Copyright David Abrahams 2002.
// (C) Copyright Jeremy Siek    2002.
// (C) Copyright Thomas Witt    2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_INTEROPERABLE_23022003THW_HPP
# define BOOST_INTEROPERABLE_23022003THW_HPP

# include <boost/mpl/bool.hpp>
# include <boost/mpl/or.hpp>

# include <boost/type_traits/is_convertible.hpp>

# include <boost/iterator/detail/config_def.hpp> // must appear last

namespace boost {
namespace iterators {

  //
  // Meta function that determines whether two
  // iterator types are considered interoperable.
  //
  // Two iterator types A,B are considered interoperable if either
  // A is convertible to B or vice versa.
  // This interoperability definition is in sync with the
  // standards requirements on constant/mutable container
  // iterators (23.1 [lib.container.requirements]).
  //
  // For compilers that don't support is_convertible
  // is_interoperable gives false positives. See comments
  // on operator implementation for consequences.
  //
  template <typename A, typename B>
  struct is_interoperable
# ifdef BOOST_NO_STRICT_ITERATOR_INTEROPERABILITY
    : mpl::true_
# else
    : mpl::or_<
          is_convertible< A, B >
        , is_convertible< B, A > >
# endif
  {
  };

} // namespace iterators

using iterators::is_interoperable;

} // namespace boost

# include <boost/iterator/detail/config_undef.hpp>

#endif // BOOST_INTEROPERABLE_23022003THW_HPP

/* interoperable.hpp
pQBlL9pCwkAJ+YQ6Fk7NE/ydD4hCfY2G95Pouoqzvezbh3txRwULPv6DPU9fSESQsU+l7vAX231LxuBraOQO7vWWzqSi/oZ1D30cFtsKkqk67hrgeE09iHt1ptZw4mejNHC82jM7YAvwbDZ7HLyGkfdDCjV6fbQYDbFcHFHB5DFKm26vZDdPn7XO97e0iz/gD8dzKopHn4CKTtdQDpj+bGwAcrkx73kWnrS3eXS9CcMT01hOo+KSyVDYfxYBgv6YthAEoie5J+xAbtbYgxbNmGKnm9QUJYj20+rYF9ssfh7CZN+8sNwQRsoZeI4N8HqwIBiSYErJdEqHj04LS67pG4tk+RFZbgfmJ+Ba++mBi4KYnRwhih6x9ST3dgw+hJ0JMq1upqLvqbxGAIcX4EfWBrOCj2p4z8z9Wa2/XUD78CvpKEIcQ1BFzMoIciDQg7esUHwzvYnzHllqCBKI9JvmsSu7bVNdZ6ChnUpDhmphuSQGqv4shS7dcM4hcKcZjkH9Fa/51VdbD3hf28mxqaSXJOHRoC5ShzNbUAIvBvBKFoeho6F7/fBdUCtXDw==
*/