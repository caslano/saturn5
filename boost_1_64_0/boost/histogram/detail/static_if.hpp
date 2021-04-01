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
FXS40Y0+ArARtv9e2DF9sxpvNil4v5QJf1ZdcSiD+TmtWCiS7nvr3sAG3kOdKwnSS2zM2q1J+//RincMbz5z86hj9Moj9mSnZ3XdA224GiAwS+WnmqtpBxGJXooZqiSig/wq3QzbB2cYD6bHh04RgttJO/KdsSFJ0iKdrdRYVTaGiTs47BrNMpnr63KQiTE4XJQMJIhMUpJ7/iTZUSxvXzABjtwCiTOVr8rIAZ4X5UJn2xMNIDDpVI3fT1iQ9FluuXfQAhup7WeWwHrtPr/I7wYowAVAAxZdRKkIoiRpHfLI/GHLkOH0dsQypKw+j0qgtVd+9sWF5llAsSp+Z3yl482c1qAM+sWoBDEfCX/EvBku8QpuxT2pOG3ZQFEbv/ooRzKAmxEC2loYLvKPT79RaanjDxX3AfiJKLr0II1JMX5I+DvM1E8T9sqXMqGvppCMyTJNmtAbU75FEwRDqnOlUWJRbJv0O+lIo5BYw1PA5RlSZuGmsaW3zDRgnpzgHAHnG1QbTftAXZYsfXmsFFGvK6TsaA1+6yxoEwvvf0IikCxGaZgRbwskZ1/bhA==
*/