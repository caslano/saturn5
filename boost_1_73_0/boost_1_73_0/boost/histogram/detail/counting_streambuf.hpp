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
npkMTfp5JjTV7+eZEXX3Z1sbqP3PNpexU/zxOVXcUIYUTDE1/FUAAdlShrVNcR8qbDe1Kyez6dKq7GzYDPT5tDlZl/5tO5MW2qnc3P9AxXStCDcPAtO1bm7DweyNN5tPKcZrepGhSQ2p5p7pdCNTWlPlQS7u5Dp2j+quJry5yVXA36GLXrOX/xSK2fN9VpLNXg6mw/8LNFtv4jJy0ezin0Iye7rPSrKLq/P56H8fyShLlXC3wEM9KlIdyTMdi6pW7OG/2s10Bm0xlwEtsjS/xeA4JR5R82VE1j0lPHOCAZqL2F1Zifxx/7kavYosStLLT6atBivnTslm7aVLgqywLDZ3XNKeCaw8O0xZmbw2RGagstmwx0FLxKTaOYy9RWZ7W6EQrO3TMR1PBzRIXxwcHDBKf/U9ctj6+Q2OjNQRe5mfw/EbP+vdCajKCSlEoRM1I/uxlcX/w2A6Ho1fHIF8xZSTUgcM0zXJP8OHAJ2GwqljeJsBf7TLgm95gDl/HRIqHhoJK7j5VgF0A6AeTXvMaytKH7jbzynsI7HHq4POUA81XMsLV35WJXQKbPaMM+q4uxZyas2+m6E3eaUYqqlhzJD83iKTBwuHL32viB2VlTwsomy5o76UjFy8i8rFSuVPYe0DzQne/M3l8GIw
*/