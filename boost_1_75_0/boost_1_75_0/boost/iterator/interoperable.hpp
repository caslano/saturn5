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
TS6zDT0VkrdLYhzvBr46Z1lHwmWQGnFOwp5sKJ6YxbRHLF/+LsRhoIv09IweyKq/yE2lhwj8vY7luziRSveuqf3G8a/AQrP+UKmRZg2xWRClGOHzLWvIdzIGpo6+yDr5w8nt4V9b2XHk78ILmYxHR72wXx9kLe4rjosER5NWbnnn4B31Tr/+Ewws89P7XLfTONrniobJJGRx4Wzbw1tACN4JcXmR8SW5dbSoercSMwPz8nwTEDgXoSu6qOPjvoct1wtXf9yZEk7KC+IVfPp6GCOqIc3r9aQg1nq7j+QcdpmTJZkYtOpAE/3GW501xhmnuquoVk4RRJZ/E2xAjDrZfifs+D01PE0lasKG4oq4BhTdjnHtNZWbCk18LfdiveTzBRe9iHOyrX9Q/zfG7F8l1DUJx2Sa+69tRg+RcacevbsxpqpVmFRr2Hzxs6Kteb66c4q7I7Ob4limvhlikafScbONIOWn1naAUwMhGLVxWZtKanbrmIBTlyaO2HCgmJZ8R2zoVGYbxWL6kjx6ethtTQLBUWTuvZg7LXrbHOGZFw+J5EY6/sgDPs1boWegd6lmyln1aNy9BLiB5CGtcbUVnZpK0e7ce8cnJUI5MrkA35yFQ56lVjFuQ2k/dASttxUCrtK1eTqCT5gpadq3QN9XAOQufR3flzerM+RpOilIg5MTPpV73Nus8CqkVvDkqkcbCQPf2HZdfVjZWFAP
*/