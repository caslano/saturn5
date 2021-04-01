// Copyright 2015-2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_RELAXED_EQUAL_HPP
#define BOOST_HISTOGRAM_DETAIL_RELAXED_EQUAL_HPP

#include <boost/histogram/detail/detect.hpp>
#include <boost/histogram/detail/static_if.hpp>

namespace boost {
namespace histogram {
namespace detail {

template <class T>
constexpr bool relaxed_equal(const T& a, const T& b) noexcept {
  return static_if<has_operator_equal<T>>(
      [](const auto& a, const auto& b) { return a == b; },
      [](const auto&, const auto&) { return true; }, a, b);
}

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* relaxed_equal.hpp
OtLfyBttePnHQmPJv2lAWS3eBU7gRS6pRsKh5Vt1MJypZJk68zZ/fUcNVYbyNE1uPzMMIt8d8/vON632nEMwMBjclXsTA4zOVDGr/fDX2T87h1t6jr0uQvQRCVQ4liT2NcI0QbI+CE1ykK3nv0Z7Dsf9KKu9eXniwjxNVXGbKN/AxvBSEZ9oA/13RahuTYP4crHKyc6SJJO+SE/yf048kJlNwF7XiVqphLOfeOTOAzEz2RRYuBo8PnsTgz15uAPuunZfllR5TEHWCI6ADvyh/FkSLTfiBZ2/G2hhbTxunkN4P8TyFVk90AcNOU4130DItW3sPgtPL3FSEEzimFEbIID6lKAO70tsl5MXmT5OCyRvsnFqf29UqvwhRzeRsD7eDjzNtDbDCs/k//9/5wSCL9OCd8LoFlK4JvMCqoV7InfGJkxJb3uJFU/L8XYY1Ds17PRn/jtXx8OvVOek/p0rsOR3JXumrxEdX4pxumTi+OhAaz2XiOom9Zw/OPi8E64+EirbyKYNiMpDjzTzW7Phk3bw3iiUjlklKNC0cfoyJCJFO8KxkShTShE/Ng==
*/