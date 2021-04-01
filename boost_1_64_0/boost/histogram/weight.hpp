// Copyright 2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_WEIGHT_HPP
#define BOOST_HISTOGRAM_WEIGHT_HPP

#include <utility>

namespace boost {
namespace histogram {

/** Weight holder and type envelope.

  You should not construct these directly, use the weight() helper function.

  @tparam Underlying arithmetic type.
*/
template <class T>
struct weight_type {
  /// Access underlying value.
  T value;

  /// Allow implicit conversions of types when the underlying value type allows them.
  template <class U>
  operator weight_type<U>() const {
    return weight_type<U>{static_cast<U>(value)};
  }
};

/** Helper function to mark argument as weight.

  @param t argument to be forward to the histogram.
*/
template <class T>
auto weight(T&& t) noexcept {
  return weight_type<T>{std::forward<T>(t)};
}

} // namespace histogram
} // namespace boost

#endif

/* weight.hpp
dQy9YxQT+Udyh/iQ+6jvNqFxTXH6cuiUkAorGUFaEPhnHa4AR/3MNdn2HprkFzQPUTS22GmpNNa7tiZ/3FEx8Vzpi9ILgvNKac1XHnK2yAWoLqNuVpLfb9EuO6BHvhszKW3TwDnFSjY8inIUealSyemAbb/jsVY4OiONSqhsXQFPZxNg22C2pkHTMBxiLNTHFpQ+FRfbVh/Kf59FgGSeFZkBN9ilrryVEZ7dXVIB9pYuQQxtN2ErDlaTOSDR5Yri72FXEISPNquuWYLTAwNeqGGBeQGBjss43uafNJjCg4p/z6zetopYmFwDLIGTXEhc9syL8s5cERHDUtH4siKSwP+wvdeLrk3hkUq9vk40WsHHi6nQPC7zfvWA3r3fBbhWmWaPjLHVNDIdSV1/5EyjKLhFBPjqxEe4xmD6X4s5ZOYPxhZze2NyGVBXZEv8NuYn+no6Jw4yi8yBqc9/IbshRili9aG4R74+avZE2Erh/G0RdeNGsPOe9B+diF1Na0Qzl5RFZKxn+KqJv9Nd9koB0PrSGus2NnteJ9u1A+UR2xu235jQVRVeG3M/VA==
*/