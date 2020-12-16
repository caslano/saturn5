// Copyright 2015-2018 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_AT_HPP
#define BOOST_HISTOGRAM_DETAIL_AT_HPP

#include <boost/histogram/axis/option.hpp>
#include <boost/histogram/axis/traits.hpp>
#include <boost/histogram/detail/axes.hpp>
#include <boost/histogram/detail/linearize.hpp>
#include <boost/histogram/fwd.hpp>
#include <boost/mp11/algorithm.hpp>
#include <tuple>

namespace boost {
namespace histogram {
namespace detail {

template <class A, class... Us>
optional_index at(const A& axes, const std::tuple<Us...>& args) noexcept {
  optional_index idx{0}; // offset not used by linearize_index
  mp11::mp_for_each<mp11::mp_iota_c<sizeof...(Us)>>(
      [&, stride = static_cast<std::size_t>(1)](auto i) mutable {
        stride *= linearize_index(idx, stride, axis_get<i>(axes),
                                  static_cast<axis::index_type>(std::get<i>(args)));
      });
  return idx;
}

template <class A, class U>
optional_index at(const A& axes, const U& args) noexcept {
  optional_index idx{0};
  using std::begin;
  for_each_axis(axes, [&, it = begin(args),
                       stride = static_cast<std::size_t>(1)](const auto& a) mutable {
    stride *= linearize_index(idx, stride, a, static_cast<axis::index_type>(*it++));
  });
  return idx;
}

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* at.hpp
3qntX/yvfZbW8vnnc2P57TS6/YiQ72msVsckPKugWCH7TLiFwYYTvrToyOLl0GheFmXzsmgfrtNaY4lbFt2MPtzSK9613TT0msYrgNqmgcPddf01DDnFkTnFkx2kuMRIQWcPGw+DdBrDwTkOJmJw48HMjRfsKQA3ho9xzQ5eGJ5GjyOy8CaXSXm8uMFOMdeXbPy/ou02i65ttSMTJJFLoA7h+2n7Y+DfSFLwGPkEJRamsiPMQlSrGvKzu79ibReS/xcI9EsLTP+Nf9gTMZjT16uHi9ZCJaS+TZt6hn1Fd+PMzLcBKxVPl3Is9rVpjH6bJomiXSQjXTJIif9u3oh0x4jzhagnJWu9EA9gj66xhmRbJZ7IoTXTb5LwV7JUesKwLQeGserrwiOuFDwuaCXrEGIrYEczO3+ipNN32LeKNAysZonxV0WmxPgSIsng1DBvbTNl2ic4lbrDYkQVpebENdHE1DiUeRFxRj7LBJvenaybI052PTN7KW1vPaAyrr+KTy3TiqJaPFigsD+A7SkI/yX95I24fF8TdBUu9spAxXVDSvTDdQWqH9Ybh/PK6aYZWUAE8iyIP5wh1YEv7JDBW5wLyJc+rdKIOs85aDLXs73wjeyjEWB0NTwX5tLi7zty9RjuRddKwmwhK0YEflKK7fomKOcuEC+HqSf8A0kKUWos6WnhepOvesV7xpm0SG0fCObnyIrpzTHjZ19fOX70Q3HBW41gLSmqYuAx2LeH4T3roOAVdJbYiwd9EXt4NU/WIoefGDnceP+R/AzXDHyfxXcevh/m/5//nujDPifANftodbY4rnkL8P/LTFMlH5gDuTVb+6bN5JIMEYhCeKv9RHm/3q8or9ZN7w+r9yxW1jCzwuDQZzn0CvAsSBl+cQVoxVAFoyL3mmXUcBl9VBmwqJJnO7P57iq/eAL6TqZppHrATJXGqVrdsalq7H7xvYtI/W2JsOAFHWlf7YcJaf6MNH6DR2Sp8kQR3qGsY3cSk6UswDFawEw+nZPPcKvIU1YLnvSnJsK7OekipUh5s78TCh064TatUHl4tTZBfOu4ArDN0xyGNCxmd4/ug4zUJ0pbDtKPz4LZb2/EpUqOMRZMOp1YRiMPcQfuiy3xiYkftkU4ryrh6R41kXtJu8aUoabWzAVeJneLnhumO0zwV/ObMOUMc5mEOWVH1GSP4pPnr/RpWbi95wLUE/J7Kmc3Oc7F/xjw1cT05v0hez5VdGqYb85wAyt/12dk4We3T7zal+chFzHm0Jx3x/rEtDxGBlB9gs42879f5Z9Zl4wxMJmFiG99ykIEhyfP6IpwYLtzoMQOGMr2s+korv3paH9/2f6Ujtrf79j289W4fu3a63Aa4o4ssROtZLfwYnk7j5PgMFLl2XDNK/vLXJlnOoS+UflH0Xg2uXtvGwqmPN7IUwc1eviHw+Tf9I8yeYrhi3wybIBOspfj6pcuRpn1O0fVLz22fud2UL+Wc6h+2/Zw/ZBHcVz9Ps39XPVbOpHPP/SOlV/HK38AWjVrDoybGWb5SYEPte2fwBKNJfWfbNEldTMtjO5wiRvbTA56Nr371HsWtPBLojyn9UHjqDot84rEhRJM3wR6vQONn2+hDw9Qn/jeGdGR7lPrJIzyfj1YYZVjLOyu4NH8PGuI3+ilxvoEVu09zqEf9lChFfBxva3N3IR5UFtuiw772zGkb3IyDVaL+3qpg8gw+TJm7DCf253IZyGrxQ+VxVjtejYpm0EXguaQNmAge3QZI3eZecmOAL56e7a8cbsQarWHzldq7O/5xAxpmMwn+gWq1KrJE97ZAx3OBcVIjdPEDVBRBFrt08+4X08alFLnCiy3B1baEXLHx4E=
*/