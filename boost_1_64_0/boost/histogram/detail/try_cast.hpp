// Copyright 2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_TRY_CAST_HPP
#define BOOST_HISTOGRAM_DETAIL_TRY_CAST_HPP

#include <boost/config.hpp>
#include <boost/core/demangle.hpp>
#include <boost/histogram/detail/type_name.hpp>
#include <boost/mp11/integral.hpp>
#include <boost/throw_exception.hpp>
#include <stdexcept>
#include <string>
#include <type_traits>

namespace boost {
namespace histogram {
namespace detail {
template <class T, class E, class U>
BOOST_NORETURN T try_cast_impl(mp11::mp_int<0>, U&&) {
  BOOST_THROW_EXCEPTION(E("cannot cast " + type_name<T>() + " to " + type_name<U>()));
}

template <class T, class E, class U>
T try_cast_impl(mp11::mp_int<1>, U&& u) noexcept {
  return static_cast<T>(u);
}

template <class T, class E, class U>
decltype(auto) try_cast_impl(mp11::mp_int<2>, U&& u) noexcept {
  return std::forward<U>(u);
}

// cast fails at runtime with exception E instead of compile-time, T must be a value
template <class T, class E, class U>
decltype(auto) try_cast(U&& u) noexcept(std::is_convertible<U, T>::value) {
  return try_cast_impl<T, E>(mp11::mp_int<(std::is_convertible<U, T>::value +
                                           std::is_same<T, std::decay_t<U>>::value)>{},
                             std::forward<U>(u));
}

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* try_cast.hpp
0WMH6LEDQ+NTxQSrHmvVYwfpsYND421igl2PteuxQ0R0NkefJzeSC41P68N6uNO9eL+6yjmVSRXaDicvSWvqb3JfdQPWeYYfbdmnb1BsOfbiXx5sKrbeNuViOw4q2f/SCw3vsS6t0mQoujYaeY8b/6M1LVZSRsfymFzhRBphF4WOiPVw3tr5SqzQiU7iBIeYMCOqXWAqdFbQcphImas25p3vjphzsahx/gh/xDyw3Kd5JMqMpenrM2ZNnz2z4RlSJUSP6apAimQnaVKk0OUr03gDUC+edalDkZS9Y45prwwlKB5xKLq3P3bsPK+ivEyjahV9tT+AUxLsuzHEj4zhr88AzN9yeitK44JnnolUVk0h9Zv9HK9qn0o+J3Yx1+LHyEqA9xMCp6qi9f1sK0fZVk4yRV9C4/tVMzoAqVvRI0VQMjmVbMWDwv/7IYWyMbUDfhhZeO1PsR22lbMteElJ7UBGUWpV19NgtrvUrJZaxVy7sq6m8aFFd3xB6RKl5mh0pNiEjpkPGQYAGMqh0icNVNqNklJTt9Y2WUWpRUUynKwTUEstyrowEBULrag/VTVNDO4IkMgRFkC0rbwojHS2leOJAiBOOI0n1PlBwfJxPofJF0ZusRklqkgOJLPd65WNVIyyTky11DQQ3GjjSGUrElfZVg4pCOMefRmMYFzbKJjDOMCSEBAr4kCErCfY7lYUVURPYiOKA3FNI6GZKKdmDSPfcUYlEHSvu1m0EynrFRSlrIs2jBSQak09w+d8JGWGQ19Bzp6g7QOMIMCgUAUgZaEU07tYDmtVm90t0TUj1VZlXeQ7PcqZASiAADrGSpJeNUjq6k1SV2/YCGlWW8K0J1AQrFuvNkMGKOGBHiVMta3MlaBfM0Af6QW6Z0DqEYIPvfFByWeIFnU9cHS3SgYB13y1BVxr0qUNZQqckTwmQlWnio1cCqD7QMD9OgFViEAOcA7p7IiPC8XB4BTk7iEYR69iOeh4iThAVKu7OfIDKod4R4KR5ICD4eD7pgi8AqaloMge+RMDR+1TW6KYaRspFRpuVso628qhSheDnmRi2IbBaGOD0VbbZBZUfwEG4Ka4m7lCbJL5S2WdjvyVK10DVY8qrtMzbCvL0fh+nkACOAH7vAH18wR1DUG18+Rfs9gcRj7kJb1BqIQ9pbuegRFEIJgx9X0yo5mZgSot2qGZDD+d2hSUwQaDVQikZJ5JlSbFgCxbuhUoAIHOUNZBaQzzCUpniHao2+ZotJ9CB9FtBN/UzeDZHK4m6WTK8MvBL6stiiI8EGUzhDfVvV5aTVVnSEA5ikQTxWb8z8YvA8l5GtQoPtPdquwBabApHpVUyi4rDtI6lD34XwR2oCiZekZbVNmGpBm0eZ5ew7YBXxdUxjWSaojY6O7gtOgT7gW4Ugbi5eIJT5TYFpU5w8Be2SNauQCXm3iutoJS5Q2iVExBLNmQKXGEnMobhJAkg5sXjPFRXimvo+ChcgT5solHNfU/7tx6C2LzmQVeZkEmk5+DXJJ8ZN3KXNqms9RJLAWIHJmdyA2jABbJRp0ucFbdq+4D04A9ycMeL2siU5vPFGVzWU5iis48tdkw306Zg6XpSJCmB3koPxmaOUwVjNcmtFowY0YWssLEWCqOiTekinE+6NIcKmwzWe8WsofqeqDLALwJZU5RZbnOOE8csPotXCpzZiOoQy4pB4eRk3VPFp0f170iai+QE0XJJrCBchLD0F4l5AyoslxvnDellJPLbKGcm4A0Y1qakMuucpmMbQ5yoZwwQoTkDdGLhnEzsi2mAg2xg2ajTNYXV5y3AZI9l9l6HJ2BnuUync44e+3cALAYj6PT3otD+cRXKtOonfES1WY=
*/