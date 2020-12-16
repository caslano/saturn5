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
vJaz1QxSTgpQ/IzFSJKHZiDGzU3JwSRdNiVdNiUj0pRM2RRBXL28zF9azgrLus0tJ9RFdjxKy97sZtnbug5Js4z8j2EAw77kdeQ3VovF2n0T+401u8PLXKHpjUfDtTQ0wfJJHQC/cMXCznwn6W5VbHKzTxzxiHNHfgibggodh6N35KvN+xlXDNzsFybXbkUOVMKVuUO/BXuwC2P/dBf5nZXWbguTXAzHUtfM0LSDcTH4fqXWasF/5Sz/H47mvzKAVKU9L5dVtR62EF6HTeGDZr5SR+r1tWKeW+kjUYeBcnQ7PhNnpgJRdwHAD0+ZYa+bI1p6QnVX5ffAeT621X6A2SW7QYUKkqGvVIYO3/x9wlt5c2AtUbEbTsIDa330JkrdLgRtotTOp6X4l012qVJ7Z5gkh2yKoZt9uUF17S0mUq3J3aOu1fAWxfP1oy7G8OMSoxkeHAWGf5AqJZ5/kNQiiO3XkpyTnL+WhJ3D4xacaqpYS2kAmxwCUowhwMmqdhgCOD2NAg9SGSThDDu6lCQHbTODfWSVW1Auuk6WOdWw2iRLtvsTYNdJcCmCC8X3Inx3waSTH6DFZgFtBKU5a+23DbgflnBnrX1UDiW0vWkgi0xN3b8bekrLCV1revAm6ngoSeeh5CtyKAkwbGR6JR2mVzCYSGzQeMJgkL4oisBQMDO8KfiqmXQcac5HPu+g68gnBTR0hDKtIH1KjcGphkcfd+i78N6JQce9yvtcBg8Z3AbKozcCOWUreIjkZgg5i5zlv8ftL62KDCUgoC8+zAQ0bIr/z/pJ/nvw28PmP/tg/kseLv+lWS/Of3d87835z6LznxP/MiX/VVzAf3kR/ps8HP77esLbwX86ixjMl0kTffBchP8izJdNwncYrEL6jUTUeJKsHsqhxJZ61cSluviP4lDiywEuBYYkk17Afi9E2G/z28R+xHrEIeC5dGJBdyWrIkMqxV/IfhNDbyf7Xf2d/2b20/Vv1YcG6d9G69x6/87dtQA2WV3hpPlJQxtIkAIFClSoUihgpQiFgpRCHwiDlNIEx6PMIf5GVISEh8MCS6sNP1E3dc65h0z3fqhzczidtnS2iE4QJ7LhA6birZWHglAekn3n3P9Pk7TF+tor2pD7vvfcc88995xzz+VjTIARYUa29thDFNye8xjP1F0PUOguHc/s2tQxsOgkGOY8yTvESltOI7OFM3KJQ8zZoU2dmNNA4nOdOUwBskmDKJdmYac/M2mX02asCZXN06auk2jnzEFOiWjaBoloqVqgSiJaWnDGYo12hKlLQlNwcdqxejAUsANLy+eIP95vqLIMg98lHJNRz1aU28P6HM66//Mb7uofgpqNWSKvqVz86R2rSf2ZSeeavK7GwhQWJBSmdiGw72PFB464+SBLCQupV1gt0r97mdtTCqvBkD9do7Vd6CQUdLuD5SZ46gKvFN7teNwauiXbUyvwBlSt1+y+du9tVGkSRBbZFQ64f9D8+W4j1aOnvm9BKgT1X4HhuTl0kzOSoVTP8LyeoTA/VOIMLU9HtjZ5fhaVJz20PLu9PAGZB/clOFt2aDm1KHPJLG5kFguMbHbARkGsvrbmf65X7M6nv/q2MR08S8JzX6v+KpdMA+L/3CJ3I08TmFSF9FnqvUYNbmFezxhGdtrn298evid2f4O9W+Se3Dy+7t/dcZtP3sDXsdhx2xKEy9x0eKk9oMzJaqiBHBNkDNLGAfysAxRT8OCxFOGLTCBoGUNNYtpbVhPoIspkZTVssJkdTqwPvvRCMgoSQNRCZ5JRC/csZZF3C5jUQ0kEL1SP+zJyoqQfZvyoQ5h+J+iSkNEcstSgzk3bEEAO/C7Ucymb6kZvo5w=
*/