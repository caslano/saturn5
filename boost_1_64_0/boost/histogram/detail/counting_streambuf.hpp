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
we4/j+dnXI+/xxF+L+/SzP6Xjs1alioZ/ux8DeQEveL8ZMpMV9LEXRKzod8SjOmjMh61pCutTbCNlZHi/tvZDTi9z/NeCjbSp9ZgITR9SxLDeiVtPGKEHnWgfxz+1k3QipUcr/Y36ytQFcebv4Zaovu6XbFOkz8I38QXDSyfiOPGjeyK/JwIqTDnGD5Cmwg9CUjQZYz+tpc3JCIkg6mG/wV6O9Nvfy6wyiVTa7MmVDFhDg8wdaIo81QJKk/d5ae3X8JZCY+rpzPFJdTOHW9mhC+XaVhoLRyGgyF+EQyAbkRh/6ikkuQtyohFNBb8F9QEJv4r1qfAkmqaQ6kXN94iMNHlRPg36h0E625hYZ6VbHd6BQmEISJEMUKqXlrio/ZwA8cyzpDbSo4t/tN5XJksq1BA7Jn25dPwWa56kKPDxpLKOIy3+FvrpdQ/Ncu8WZ+ufloi1OAm0bnvsDerS9vVpAhFRPiKrIN6XezaJiAiAQPxge1/bnuKfi3ugP2HmAx0PRzbc3siL9ECj51xrMjFS6lu3sG/3mLVwFdz6+fCK82A6CPftdcCc9hcpg==
*/