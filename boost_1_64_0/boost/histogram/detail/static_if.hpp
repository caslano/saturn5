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
DBL1sxA1MzRNCRUMDk22fTS/mc9d566PyiXHK1o7TzJeMep0hivM/6/DFZaTDVdYP0LDFfZTd0sdH2qHqO+kOHt2iFwfcIfoTL4u008tBc+HLIW+VSzjOycuhcyP0HBF1qmlkP0BSuFMFCqnpxTyP+C6cCZS8J5suKLoIzVcUdpTChM/dCn0fbjCd+q6MOUDrAtnYpGm9pTCjI/QcMWcU38oX/ehSqHvwxWBnlKo+tDrQt+lMPfUUgh+NIYrZi88frxi8bnxinPjFeeuc9d/4SX9UUZt75LnGdDhXys/ZVtZYLKtnIfP8smW6D8tqVr0VQvCkuXzy/Ss8DMe+qXux//+SMEPKcbDgNQNYifuxghHQapt5SIrv0RfIwiDUg/DvrvwNLimvuTOtV9EsNKeehgBNjyKdamHyc7Vj9kF21DTSSn6YPRhroxPPdEQHiia+9yN0XOFx5vFGt6kbj1S1NRHrPc1RF9yqmuje8ELp7pXdCmbxA7djI/ZBRg1DfPfvCW/D+a8J3LjLaK57w3LDiMjrUQYbxWt0d2WyHeGD7vwLuQGduAYYmBO1SZxZMyWMF6UzTUNr766Y+FpdcN64WgHjtxy9J2DojE8Hj7eiJV8e90SfdWpHhAdcBxH01LTmX1x0eDI/fRf2XwmuDlPQ7pip5GxKTzexfJdBw4y76CU0X1O9SgdfRe5/4brQq4xu5S2mk56er/4hcdzawn29Q0/A7s14fEe1jxD54CUQ+pdEDjvGLOrprNlrT038h36r7S9X/yIfxmnIVvWP0O6maIV+hbd61QPkeriOKIxO8HMms6H7ht9q7qW+fgAPSttp9Vj64Vf1mnIN0G62Ym6J/n3mlN9l04SxvnnO2saWl98ekTk/rHuwlfOjH85p8O/XQkSzhfrYSajr0OqxL8g+LcD/NM5950vFd+5FvrX8IM/L7r0TPDzvg/+QbpFkK7Bv33MP6q/h2hfPtTgHTUN+TB3kQeevdt635nxr/Q0+Jcg34miBdmYX6i2xDK0RZDvTjrtmepHaNiwCyP303+l7bS6273w870P/kG6U8R6si/cetjUi4uYk6jCij5yj0oNmIyWuhdAqFKHgbosAk0dZeorjlNPH8fw+Bm8HeA+efY0qV9N/QXXXxcCS8VOgELdVltJOzVi7pitSrvOxZqGfzz08AJC/hgAo1aBlNPk6ZzTl3l4/HXAF5giXj1M3FwfhskRW4mdaFFga8Y9vxZ8o/9K+5lYnIBo7vMHd4LEqyIPzH/wvtHM1S5wERM1vCnsLjKR+4mTHcomo8ewg3oMnZT+9DVy7un0GLDwIiFrUGymWv2yU90Q/Yezpv6fWe5CVG9lk7orjhmg1nRSxOlxLjx+YY+2bvasE+M2sxu56fGsi8+Wp/C569z1n79qsRdvUnAQrbo9oCbZO4b/tCtGLys/h5clWJ7QK30AqYy90E/400b/qOska6D5TGaksxq/4ADtgj9SDmuD1v6kfDhBea4T/bQ7nuC1AwkZVl3H338tXQn74czBl8Tc5asrntl/ywi77ar9WNRppmnsuT6t/UFje8QhqOUTPXOwdUb6Bgq7rgElBJHU6vdptt93GXsZ7m/hR1flHJ/2EEjF7hu0EhlY0ClPyP5SK2fvow3g9YsV/sjXXWL+DJx0tKy49ljObaNXeWlzlUbsTnI59qDALstmrET0l6kHte3JSXwKUk6PBGORwLaycESoJAe34aGSXNyGhUrG4eYMleThNjRUko/bx0Ill+F2fqUpVHI5HrA7TajkCq0OYCu9/qbCGbzY+m8/BGWpEKNsU2lUK5lu9tCVJm64Qlcmh8YrYoJZRl5p1mP76bH9Q+NTxASLHms=
*/