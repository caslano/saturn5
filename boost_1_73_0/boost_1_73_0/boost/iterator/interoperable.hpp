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
CPv6gGgymSLQKRrcaZh3SDHCSqu80sVNSqELVaGRU+rDzwq3afgeXreVk/nG7YyhDywiy9ZSvT5Kh8qNytsFKt1H/XFP1MG05a5tJmJ/NmJvNmJvNuIH2Tzk99mIH2cj9mQjumzSLbC+S7N10eePyKsslwpvTp4g3yUxKPKszJc7RJRmhzRmdw7UuEMs37W8Ni4hi6WXZIK0QsLJrFIaIZNJpbaoRkw4sxu8omLkNeVkmtxCmxrNbxO45A6M1Q/YthcDErxqdp+xNQnCKwzRJqhd8t2V2DqpFjpGNUvzqbljeJHeJMwuE28a7pnju0ikzhqmNjd8kyJk+2AaqoL9SJjRS8PTKkAEEH9CuMMHOiEV58kUdPey0nmCnKzi51WduFkb6bhu3T6Wfcd3Oh64Zc6ZQdOppLcqEA9VEKOgggj0KkiJV0FKvApS4lWQEq+ClHgVxKRXQYx6FUSoV0FMOhVEZFBBhLYqiNlWBRHcqmCXbd9h9yrYefYqiFGvghgNKojYoIIIBRXEz4MKYuZVED0PKthBInU2qCBBvQpS1qkgZoMKImZLXlQp6VSQkjYx3skiBp2WIjIIJUZeKNFz/zlIUJ2EstXOHtZpJxrotDN8Qc62n5BwODeFP3KEj9NwLPGH2IaH44I/O6ND
*/