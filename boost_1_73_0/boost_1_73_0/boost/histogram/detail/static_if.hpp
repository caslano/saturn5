// Copyright 2018-2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_STATIC_IF_HPP
#define BOOST_HISTOGRAM_DETAIL_STATIC_IF_HPP

#include <type_traits>
#include <utility>

namespace boost {
namespace histogram {
namespace detail {

template <class T, class F, class... Args>
constexpr decltype(auto) static_if_impl(
    std::true_type, T&& t, F&&,
    Args&&... args) noexcept(noexcept(std::declval<T>()(std::declval<Args>()...))) {
  return std::forward<T>(t)(std::forward<Args>(args)...);
}

template <class T, class F, class... Args>
constexpr decltype(auto) static_if_impl(
    std::false_type, T&&, F&& f,
    Args&&... args) noexcept(noexcept(std::declval<F>()(std::declval<Args>()...))) {
  return std::forward<F>(f)(std::forward<Args>(args)...);
}

template <bool B, class... Ts>
constexpr decltype(auto) static_if_c(Ts&&... ts) noexcept(
    noexcept(static_if_impl(std::integral_constant<bool, B>{}, std::declval<Ts>()...))) {
  return static_if_impl(std::integral_constant<bool, B>{}, std::forward<Ts>(ts)...);
}

template <class Bool, class... Ts>
constexpr decltype(auto) static_if(Ts&&... ts) noexcept(
    noexcept(static_if_impl(Bool{}, std::declval<Ts>()...))) {
  return static_if_impl(Bool{}, std::forward<Ts>(ts)...);
}

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* static_if.hpp
EVj9HU6q17sym1pMgFg2dU7GQGhN5HMBeWxApMcLLGpWkLCOMA5YHjNAnNuA2RQN5e5MggkkotKyxLDFgwOadg3AcxHQGI/ZBPfLxHSJQVQxq3kSXE5Mz6s13rpksf0HTsH7X57D1z/wCcerg2g9+xRuAzhYHxVoaJ0stBM4RRzOv/s//HnebuK/fI8irR8eguR8fhFJV0CCYZyt52H67eE0CSw0Vy9P2fADqplsr7Q9C1vy8sROZg+zD4mxvtNzyHZHAgkrGkOzbEs5SCcSx4/wDQeOy9ZL6iY+wbIdSEe0hoSNd0eAYsbksG9DnmccBqMkFJ/uwSQkMpyVQLLdm81281S/cIJ2a1pun+1K3RvTZVSOlfNzzkUx8cfNg4Kfxmf73F4PJsi+aVvKTq0LhE7AG/uJZCuHs0s7DkkwpG63JJ3bEUk7QNwSda9A5Q2NSlEHd5i6/j4gqXVLVEbAhIRT7kImaE1L1ER+pKP0bVHJePOJonlwfFvdA9ESVW1suL5lDANCDnkL07Ld3OK7JFBRJZwum6RM39RVgze6qAu/TEBdeXqMKpSoAjzuzLo4cW22+pAgRR2IT7uToETRz1immnuhiwI/GQ8do0+bi3RR2CERmtZBURHYlBM4g2DEJmBlO1cXNcAZm26c
*/