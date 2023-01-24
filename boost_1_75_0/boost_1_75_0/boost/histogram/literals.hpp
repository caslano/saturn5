// Copyright 2015-2017 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_LITERALS_HPP
#define BOOST_HISTOGRAM_LITERALS_HPP

#include <type_traits>

namespace boost {
namespace histogram {
namespace detail {
constexpr unsigned parse_number(unsigned n) { return n; }

template <class... Rest>
constexpr unsigned parse_number(unsigned n, char f, Rest... rest) {
  return parse_number(10u * n + static_cast<unsigned>(f - '0'), rest...);
}
} // namespace detail

namespace literals {
/// Suffix operator to generate literal compile-time numbers, 0_c, 12_c, etc.
template <char... digits>
auto operator"" _c() {
  return std::integral_constant<unsigned, detail::parse_number(0, digits...)>();
}
} // namespace literals
} // namespace histogram
} // namespace boost

#endif

/* literals.hpp
rJL+PmGYRDyN+13C0FHZYB0DsQFTpjGfGDOvmmtzMNPjGdw3CVdMK8QBET5eaw2f6S64x+z6gb+7uC99LTR985BH8uDpXUl/pj6izB4HTbdOtSZjgRtGvFBKYzV+rfHuAK2O5FSsrbuNuo1Rcv6efc1h7XkGaR2WGoIWYhOWK24ZXl2SqzV28TS0uNcDoQyj7mUdyh4cny+LXEzoCrxx2OJXL+Ks1DYTPdQxdCtEd0filaqSYUvYYNL1HWQYA7aeUU+7hI2ZlOYjTHByTED0RrOz3RXYZyjeSOnrq/aKxGJ/x9SSZwp7bahF0rUtrCvQxhOG7pumlj6KBrru1jAol1yzEzAR5x8yLOeaJA+VGCo5pBA0oXpx4IQs8tCnmP/7hEH0zwlDye8ThuadMaG/TRgQf58wCIawbH+oBldTMOYeDu3wwZdnJJrP4gWLGiZiRrp1kWOaCGtCM204fgQl4vIsmItnrTUtkh+EQzyGl33NhkiF8nAE5HNbXNxAjdw4EVsjoh4Z3FSQq6dZCO9hUSl0YeWCXDhvF++XafCrkG3Wvz6XMCrgfxEqdLkP0RWAbQfp9tmhkqKAeii9Z76ccHvzEKF2bWhVCAvM4UWAINs+Y7W95JeHrwfUD8Ku6ZjFuGuszuu0VfmbtJO5a632C0tdplw4G4ibtMPJIitXynNXpmty2+vHf58wkPr8KWFoj39MGFr/mDBgLt/5
*/