// Copyright 2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_SAMPLE_HPP
#define BOOST_HISTOGRAM_SAMPLE_HPP

#include <tuple>
#include <utility>

namespace boost {
namespace histogram {

template <class T>
struct sample_type {
  T value;
};

/** Helper function to mark arguments as sample.

  @param ts arguments to be forwarded to the accumulator.
*/
template <class... Ts>
auto sample(Ts&&... ts) noexcept {
  return sample_type<std::tuple<Ts...>>{std::forward_as_tuple(std::forward<Ts>(ts)...)};
}

} // namespace histogram
} // namespace boost

#endif

/* sample.hpp
xMRWNOWy/Ryt28gic02RPJ66K8VhawhRMNzPmcvLO49H/4Ty3zqap/JWVFXT658sVagt1/P+XL1/C5vt0slbIR1IrgWxq0wOKq5o4jN7XOuQZe2hulKrNokhzoSoYwpi8jskfAmolPnmQk7Dankyj2qL1Q1CubaUuvWrcfMcL5pxxqQnTIo6X+sv19OhKoZcvho2mPcHKX269P2cmVRn/tPjE488Bq3rzUGaAm3S5mNVtXIK1HCJFwkKvVG+pHE=
*/