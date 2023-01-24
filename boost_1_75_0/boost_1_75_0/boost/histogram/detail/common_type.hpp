// Copyright 2015-2018 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_COMMON_TYPE_HPP
#define BOOST_HISTOGRAM_DETAIL_COMMON_TYPE_HPP

#include <boost/histogram/detail/detect.hpp>
#include <boost/histogram/fwd.hpp>
#include <boost/mp11/list.hpp>
#include <boost/mp11/utility.hpp>
#include <tuple>
#include <type_traits>

namespace boost {
namespace histogram {
namespace detail {
// clang-format off
template <class T, class U>
using common_axes = mp11::mp_cond<
  is_tuple<T>, T,
  is_tuple<U>, U,
  is_sequence_of_axis<T>, T,
  is_sequence_of_axis<U>, U,
  std::true_type, T
>;
// clang-format on

// Non-PODs rank highest, then floats, than integers; types with more capacity are higher
template <class Storage>
static constexpr std::size_t type_rank() {
  using T = typename Storage::value_type;
  return !std::is_pod<T>::value * 10000 + std::is_floating_point<T>::value * 100 +
         10 * sizeof(T) + 2 * is_array_like<Storage>::value +
         is_vector_like<Storage>::value;
  ;
}

template <class T, class U>
using common_storage = mp11::mp_if_c<(type_rank<T>() >= type_rank<U>()), T, U>;
} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* common_type.hpp
XoV9O4l8EXqvozB4W3iEnaHNYmLU4nVF7paUiJFULiSQJSIFiY2J6fICN01DSA9r3DoNFpSXjUciOP0gPjgZXrQ1tTfZbFtuiz2tdpsAlmSfBCtnkZlsbs3jB4k2DJ/ISdZku4DW99w1Qtdfri8bVEuL3uIWJ1Y2lHTfz06lnLSpQas67Jnf1jmkszIFF6t+u9TcWkWtEC93La2vAzz+4sbhWQvoIo36skG1Wf/yjnX2xKPKxiT+fLSgKpqhpFjJQndRtFwD2WFcKib0xy1jHVRh765bJtltCu5eilSvXnUW61Bmitr0wjdqI8okIso4mcYXWlNZz+I0z2sYauhTySBYGb8wi3Dv5vexdJ+h4KxcJA0e+bUN1wZEUxerv6zpS/bZ5tEIuyJM4VpVC3HtK6DREDTvXdaW0BEtBEwu0aO8J7rYSe5oFd78gaSjJeejAccUa9e/Ll/g1kxQjlgrnnspz91A0FOtgIjGQ8r4hTpRDN8559tGnHO2CP3WxvXFhuQFHtYvzgpceWEHrVIeUB0gXdNRU/u6Uq6c0SiARpe1PVNLu18/cnXv6Gg0PGjlTcZaOMT0alYvF41ku+Akd+eGvp5aZEUZTSUAj7tNu2sjcsmSw7SQ2h1zvewIKNWsSrCulFGC7qA7/N3zDCxC/Iv58pr1cLcdLPwgAkW4vlK/8A6us4ZYjGWJV5vdru1SQGKJiqE7N3/8hSzF
*/