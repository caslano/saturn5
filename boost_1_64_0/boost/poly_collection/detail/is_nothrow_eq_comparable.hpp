/* Copyright 2016-2017 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_DETAIL_IS_NOTHROW_EQ_COMPARABLE_HPP
#define BOOST_POLY_COLLECTION_DETAIL_IS_NOTHROW_EQ_COMPARABLE_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/poly_collection/detail/is_equality_comparable.hpp>
#include <type_traits>
#include <utility>

namespace boost{

namespace poly_collection{

namespace detail{

template<typename T,typename=void>
struct is_nothrow_equality_comparable:std::false_type{};

template<typename T>
struct is_nothrow_equality_comparable<
  T,
  typename std::enable_if<
    is_equality_comparable<T>::value
  >::type
>:std::integral_constant<
  bool,
  noexcept(std::declval<T>()==std::declval<T>())
>{};

} /* namespace poly_collection::detail */

} /* namespace poly_collection */

} /* namespace boost */

#endif

/* is_nothrow_eq_comparable.hpp
I62lcxlc998s7qJnAU4ElVxbZWdk0VtU1bdqcB0tHS99U80BxBqUixy1dHPojuITN6FDWWzQoyCzmI4d02hlM2IEicsJMAvQeOC/ao2jlMeJ/JfZ/ld0d1wzV94H2BUNSt5ABQWNTCkdYUe9USE0k+OcezbaFDus9pxz7EDNf/FQ0vzUietTCw/A3e5tqscz4UKuNaGtHRqwTQroWaBI5yozWyovim9phUYpSQhQFemQctsdpyI/BAvSrOatSFjtnWcFFktAQxlKAyq8gUJjcf/kZ/50B5HoRlCHmu5tn/ttR0PH0I0GRsWjpCd5B6/eKywkPeM4JF2nod77htCsB+i6xV3mQ9XZUflSj+D6tsqRHH6vQ1cBxQwV3jc7nS6QkwwxbgMhvgYzg5z+OqDWCdNoQAHZQhCpHqhTIGnsm5VlhH63I7eREyRBYhvD8G74FJ9bIfgEKiZJsTv1G39s1HYuMUqCba1LAdeKskoHgI3y7yTplzf0/iaxivxL0bEGfPthz4L2BrhEmgp1VjuryHu+iD9as+DUMILrVBbyCV3P2+6851kYZ+OTKQ==
*/