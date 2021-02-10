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
tl8is8JAwUOL8Wky8S0ROd3ki1Cw4UOyYKLf4OFPoFenTD3ePAgN0B7EoMSpUAwIbBKfPpqLsN1HSwG2Vpob7A/8VWhNSvAwqxVtOhQ6BK4OwZYO1Qzcqif+QX2IptCFfj0HBf8d/XmECITf3aKH8nNMbSNox+2/JWb7jj8d0QeaiKcS92AW8eABdHguDnuSDUEoF9ltF/kVGK8n2ysB4Bk+KGh5ksM6lIfcbIGLbOh4yfUSb33xpKcGFSKMweqyx9L2HXP13cc97NnANmylRdDrmYvbf8JUgME1pqAfWdI8HXTpCynQYq8nHgCKHsQsow8C/D/82SOMaErsE1VwYbJo3xyeFrGI0yJEcI47JqYNfSJ1yG2ilIqhPu6uNuQoes/bW2SG2ggkfrFXTOVy7mp4lFGSFSIxKRjeEyVYvB2inJnSBVLqo0mJYk2HS14iyLjUrkGN0pqvvqvY+4jWpLmcuuw9E3AS8Iiuwx8vB+PZaDI29bw0Zt+BtlmHeCD0E22Owxgw55og6xLdFMHvBRZbSHr3BFjK59Qmho6KEIB/Vuia/foS+4UyfHjU2BSUZR6G3UAyqHuebXKG54uQT9y22hQhWh1oLygFCz1vyhXSgCySA7XZzODcZZOJdlUkATbeJG+T9B2sYgMC
*/