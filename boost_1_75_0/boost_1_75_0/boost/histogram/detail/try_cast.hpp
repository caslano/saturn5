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
KQjFTVrQl+xPK8+C1z2RZeEkGCzkJk6/zbx56e5qZjKR9AVAHg6CD7RfwTM1Ex420ohMpIHPaB1ZlR6GQu+yiqSFHaffN1tHqkQnsuO4KA13KUl3fzScT0uw/PEj0aGP99vM7/Z74dcBc/INr5aEXzqvA+a0kit7pTuUHvvUh5zK8/gVD2DhFS44J/3ykc/YtT96eHEvHRC1PkW79FgWa/nlsqu5pm3FNLMTtnL0BbwT4egLpF71qLSpI+bj/vFGH8OpdPvLr7o71B9MxlXTQ5y604acKEZPDgq7g8awxC9EMlbZ12Ln6ha94Blh0+E3fxwnXx7RsGe9UclGALDg3ESgv252a9d5BCPd6sURn5eqw/dHoz4sM3ZV9LOkWEiPxNMjAhBWNFt+pr2IiTfm0Fq6EU2QZTZOjIUp7nur4DqRPNX98mEF8ZZmhNED+CxYJXUpOj3arSouBHxu1JtMhgXKKRxJyPj1lxQUlKWg7/asyrjqAxKDF4R/m3zQARhLkjcwLhnAFQa34UFagiMOTeAJWcB5lJd2yCy/aGOSrm0UCOgVUPYVkneTLIav98B7SBXt7x0KeNvtnUUUMPd5G3KkVQBbisufHbPPbbeoRbOPHYM9AP2/6onpJ4h12lMXZgRTNiMzxDTbg+K1qJtVK5GyDul0DixbpaeDsgPzmqaq+HN4Cx3eKuc3HsJiGnCLevOae2XEivkOrW7d
*/