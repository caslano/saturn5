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
6ah0eH0uoAeRR3cR5k73Vm33Z0doINildm6ovV63t329iib5TRPbjn/hTHe34fl4B0qBoVNbkLwYpvMiDzj30jsURbmXHUwuCFtI4vdJWOn0c36Se2eAiBUHUeGEvDBhzIucvdU5377GywrzKRUGxqPkP9ABcCoWg7Uq56T3qDMvAp22o3mKoqTjU2EWWOdHxUYqFAljR8ij1opWekAf/T9QSwMECgAAAAgALWdKUpNJ0eQZBAAA7QgAAB0ACQBjdXJsLW1hc3Rlci9tNC96ejUwLXhjLW92ci5tNFVUBQABtkgkYK1VXY/aOBR951dcdfZhRs0gpttRpdVqtSYYSDckbBKm06IKmcQBa0OMbAeG/vq9dmCgL51ZbXkgiX3vued+HPvq9uf9OledK/j27b53+5Tfyp3qbt67JV9uD0qs1gau8xt417u7g1t8vOt5MGC14BWkhtdLrlbwe+EW/lyzp6eu5n84/ylXG6G1kDUYCY3mHuQI6cFGFqLEJ6sLKIQ2Siwbw8GshQYtS7NnikMpFRocEGfbqK3UHPbCrAFX7VM2BkrOAT3WXPHlAVaK1YYXHmyV3ImCF4jHDP5xYEu54wiUPydUSyNy7gi4qNsz1dPWdsuZAlEDqyrrKbjuurSyMYU0HmafSEIh
*/