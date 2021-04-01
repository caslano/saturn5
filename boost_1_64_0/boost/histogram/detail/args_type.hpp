// Copyright 2015-2018 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_ARGS_TYPE_HPP
#define BOOST_HISTOGRAM_DETAIL_ARGS_TYPE_HPP

#include <tuple>

namespace boost {
namespace histogram {
namespace detail {

template <class T>
struct args_type_impl {
  using T::ERROR_this_should_never_be_instantiated_please_write_an_issue;
};

template <class R, class T, class... Ts>
struct args_type_impl<R (T::*)(Ts...)> {
  using type = std::tuple<Ts...>;
};

template <class R, class T, class... Ts>
struct args_type_impl<R (T ::*)(Ts...) const> {
  using type = std::tuple<Ts...>;
};

template <class R, class... Ts>
struct args_type_impl<R (*)(Ts...)> {
  using type = std::tuple<Ts...>;
};

#if __cpp_noexcept_function_type >= 201510
template <class R, class T, class... Ts>
struct args_type_impl<R (T::*)(Ts...) noexcept> {
  using type = std::tuple<Ts...>;
};

template <class R, class T, class... Ts>
struct args_type_impl<R (T ::*)(Ts...) const noexcept> {
  using type = std::tuple<Ts...>;
};

template <class R, class... Ts>
struct args_type_impl<R (*)(Ts...) noexcept> {
  using type = std::tuple<Ts...>;
};
#endif

template <class FunctionPointer>
using args_type = typename args_type_impl<FunctionPointer>::type;

template <class T, std::size_t N = 0>
using arg_type = std::tuple_element_t<N, args_type<T>>;

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* args_type.hpp
cZqWlWPH2Z8sf23NcudxB5GdLyYXz8wrRHnfpjY4ulvY54BmjD6WQ54MoqdAi8ciTa8P57arrBWc5jRnBm16qYLRJiq0krFYgM9bWJxMz3f0HkcSfGCKxXl3M2U5HWoPJLmVvZG7YoecLz2t1Lcip2BoFmEvXL1NFh6IHXMNmnxwbQJj4hk/JgrTMubcIpPUiuSia/5ZviBYz+PGP29a48WYCfhjLBWdK0UJkZGOEIv0Ps70ACU81T6R18MNJpkYEKyQIh32++ekAvKlVIjlRev/7vNUDi7mTDD316UvBiMj0LCnEdiDxaR2Re7uOd+LVsoPEV5KPakXioQe8qacpiTwSQDqS0TKqY8W2NkviMgpWezl1nUy4C6JcYRrthcU/p+o0xLhhcxIW/wS4JKkbw1xnjTHi/rPGFA6fDMs8CdAXiHZaYfLmPe/d3MIMxVnFrYDnjXobx3V82g2gIvC8RT9Rn/wCRRZLeolXtIPy2GkIf40xDir0kFmSLicMOplwMPBcxaulQQyaboqu7VEUFAXpik/JfrANSatHlGLohFG0oCQ50ZES67ZQQ==
*/