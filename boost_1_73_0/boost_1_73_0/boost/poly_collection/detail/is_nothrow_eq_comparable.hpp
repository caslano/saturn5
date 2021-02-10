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
0G5Agn/2YD/Qak1NAg5B+lPD6UlkcKbiTyFNkRHlr/Bj06nhHHREPGUsNlHxCvsIsTf4pQH0VtMKX4NsD3orfkfDmAAquEh7jansPyAdaH0f1MDuKVYneh72TbA34PRj0bzqicRL+AuhD1YCimEBsdH2IfkJybg0lYNUIIC+2HwuEZviB+4Tjk2ARznJ/jnFN4mUE2MfnB+IP5gSNs9IS7KHej/DO0VYLkdEj3gJPPCevP+oYy3gIeZGh7iBNSIJRqm5D/wGDJyfcjwnDMIHxOjQWAPyHURZufZE/+pot79KhgSLQS4DO6Q8qTFDQj7p7KKipr2egUH5J7y+6Hydn3o0iuiIAmss07GnGNmc5GM1PKaJskDYIejr9w/pY5yytwktebRrQbOEPCMh+M6SFuQHtowaJRTSqmV1tIvby4bW27bDfZJskO8+hePH+Q36iONS2QiJi44VY9cA60G2JBYj9Mm/PIIRt8gmMPcJ8Q9PvIDh9VnyTbZ5Uu49K79HlPbbbVPZcc+yz0iu0JfIkvmHSNzZD7I9svWDvnB6CE/2PPV40BcbGKL7Q+JWaOiAbxV/X9fo9te++Ku2+ha0Q/argTVPNe5qJD+Ij2qbR5rCkXw4boM3jM2zxl1oozU07kHJPo7LtOMelPer
*/