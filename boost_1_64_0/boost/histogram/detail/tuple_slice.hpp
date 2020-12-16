// Copyright 2015-2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_TUPLE_SLICE_HPP
#define BOOST_HISTOGRAM_DETAIL_TUPLE_SLICE_HPP

#include <boost/mp11/integer_sequence.hpp>
#include <tuple>
#include <type_traits>

namespace boost {
namespace histogram {
namespace detail {

template <std::size_t I, class T, std::size_t... K>
decltype(auto) tuple_slice_impl(T&& t, mp11::index_sequence<K...>) {
  return std::forward_as_tuple(std::get<(I + K)>(std::forward<T>(t))...);
}

template <std::size_t I, std::size_t N, class Tuple>
decltype(auto) tuple_slice(Tuple&& t) {
  constexpr auto S = std::tuple_size<std::decay_t<Tuple>>::value;
  static_assert(I + N <= S, "I, N must be a valid subset");
  return tuple_slice_impl<I>(std::forward<Tuple>(t), mp11::make_index_sequence<N>{});
}

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* tuple_slice.hpp
g84gl+npxSEv8TWhorYYnEVOphOVz8hCQHVUHcTUuDAzBcueCSRtXQ8CUTzTSjUwocwiw47Esc06nk5QCTOuop7jl001E3cDjXVta5BrimhDahYokhBblE0snyls26hW9uKRk0vurpPNUv8AhSTKWhtGdqqMvXiUr0s0K64PLpA7hzSYcxOdGwVaGKbW1UuqXr3sbCqtLco0hslGVnElqAL4ZvzPUdfjv4dBTJQgWOJMrQ/je439xMYwUotm5JyT2u7e7G5JbQOt1DBF7sHkwjfwRH2dIvAuiOrZjv8u/DJS0W9oa3RvDCOUITEDW9wAnNqmZ92MjKVI7MBvIn6Z1HEDmT6g0IiMQAF0soXZDAipKFS0ugHH3W7AYCZMoU6KYXfSRZdKHVbghV9WWz11X8VGZHa6NwPWVKKq2Q2gNU0EIbVNaadNgqjrKWEa0gwQJCAIpPDLZkilTAZ1j9pS2wHJvREcAf/AdhSttOK/D78cBVWLGitlfVu96AojLk5JTzIAI05DOigwUKDydTpc+HlQOqpAmLGS1DARoIlhxGkIAHcdhoFWKdMxEb8MpsEu2pHfAdkAB+RlqTjAh830sakgQZwPTQZHJTczdUzwn+kABUQTYEiCAMOgxROH0WDwUvIxK45HhqSDZOLeLJoBhQhKkEdGT3nYdeZmE96Ejehqq5dCDOPtRFIpYlm0ymKh6aiKPaSSReiDyuP1C5TopSMVmU/EGax0ERIGGYyOg6jcCBiJgiFK4jCymSbCKT0ujhwigmHkgEKiSkqGBQL5sGTjUskxuGFoksFVtKWMFGs7oR/GmyEfQEiQikvCALZx7fAa6LCG4ymhrjiOqysCz7CXUbIAEyO/ZYT26Nj4xAFdT3LiepJPbSvTIZgkKWF6Vo4Cii4ir45/hrLYk99WrxwLE16HRBvhICVKKLUQJQqiIj/ggreRXqCicV/El7qZu4Fvkr1FcgfbXF+4Ctq1j2EgJ2amwD3dOhdJ/Ln/tIc7RZvboqkbkXeqOCBbfTdpJdBvQB5qO/X0pUYbzx8PoAGdqDe4h7GJWwgFIFQy9jDZCoKpTv5lU/RL68JksY8QTjzPA4y7e7rAl1t92VPgboqCALQSke9SXmWr0dqLjT3be73vRY0DqONsgcivOU+H0XgyjyYmtPSt3PYxputropSYtAIx79HCT+nRk5E5qCVADLpvbdTWM4+aKOL4Vp7o6u5Bkahbqf2ON1m+3q076DZ6MUZ5/ImLSChB73Z9Sryd9HBPZ73RE9mTSJuH+eEg7sn+axy/bO6dQTBZ3N3Bx6gIAnAzKJQAFKSR1Tex8pLtkhWY+wbU8UJXHEqj5woDiAIslSNGuw6ZJ8rORVkIUwDiWjrVKA6N+hp+ItyNuppQU6GFKBcWT+g9p3Z8MhOUdVwdqfVsU4PUdqtBIEvdDFAHDjJnUGmpN7kYqtwa5y2C0GiBr4tR0mJguRjcaYSxbCK+QXZGXXNGMQ+gk0jAWhl1hzqDmmH8B1b4T9zBDLbRy2xrUEjjiKP1TNgU6r2A5V4glo6OSFF4Bn9RzUCuLuqYyOE1QbpEOQlIPGspuBKmlDPAV5TdtkbdhXu20oLOQwNbjlLKKfNNRA5MptJUpcQapKUrzfiPz038zxFIY2gc0xknDsSDHcpR7o+gvyJFCTFSNZCyJNbydyMVRCUHSKlZDUiupGRh7ukAwgzcD5im2msamZA3KBeCN5nmmrla9mIRwLSYAlaIlgRksigLLbVVnrkmYaeuQHihJZgiDnWYOmMxuU/UlDMZYT13nbvOXeeucxfPNwV5b+nfJs4Xz8XhKMt4VziaDVzs/5vlqyOwU7ntqsM0HUzTrfXvKEk=
*/