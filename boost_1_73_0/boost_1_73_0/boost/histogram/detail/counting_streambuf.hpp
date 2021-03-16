// Copyright 2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_COUNTING_STREAMBUF_HPP
#define BOOST_HISTOGRAM_DETAIL_COUNTING_STREAMBUF_HPP

#include <streambuf>

namespace boost {
namespace histogram {
namespace detail {

// detect how many characters will be printed by formatted output
template <class CharT, class Traits = std::char_traits<CharT>>
struct counting_streambuf : std::basic_streambuf<CharT, Traits> {
  using base_t = std::basic_streambuf<CharT, Traits>;
  using typename base_t::char_type;
  using typename base_t::int_type;

  std::streamsize count = 0;

  std::streamsize xsputn(const char_type* /* s */, std::streamsize n) override {
    count += n;
    return n;
  }

  int_type overflow(int_type ch) override {
    ++count;
    return ch;
  }
};

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* counting_streambuf.hpp
twq4FyT43pHkex+4QxJ8pyT5zgLX55XyfONfkeOrBe4HEnw3SPIlgctI8D0kybcSuDUSfNsl+XYBt1eC7xtJvtPAnftqeb7Rr8rxTQBuugRfQpLvJuDSEnxLJfmWA7dKgm+rJN8O4N6X4DsuyXcSuLMSfMPWy/GNAa52fXm+sCRfM3BJCb67JfkeAG6lBN9GSb5twO2S4DsqyfcX4E6X4SPcwNfk+EYDd8Vr5fmCknxzgUuV4aP53iPJtwy4JyQ=
*/