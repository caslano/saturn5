//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_STRING_TYPE_HPP
#define BOOST_BEAST_STRING_TYPE_HPP

#include <boost/beast/core/detail/config.hpp>

#if defined(BOOST_BEAST_USE_STD_STRING_VIEW)
#include <string_view>
#else
#include <boost/utility/string_view.hpp>
#endif

namespace boost {
namespace beast {

#if BOOST_BEAST_DOXYGEN || ! defined(BOOST_BEAST_USE_STD_STRING_VIEW)
/// The type of string view used by the library
using string_view = boost::string_view;

/// The type of `basic_string_view` used by the library
template<class CharT, class Traits>
using basic_string_view =
    boost::basic_string_view<CharT, Traits>;

#else
using string_view = std::string_view;

template<class CharT, class Traits>
using basic_string_view =
    std::basic_string_view<CharT, Traits>;

#endif

} // beast
} // boost

#endif

/* string_type.hpp
HieQe0Iia320H3vwFdpwX+pdx2rGYoygMILF4gujTpLbsFH1UcFuYy7okaBDBLyj4figM/Q6wyE6hNKhk/oNG4CUGyxU1C1BHlnHEn3iU/FcgNHrHKq0/SYXaNhchAeU/JgzmSW56BKdOPY9LF5vfOh96n8aTy7p/X1Bycogl2UNlbWT06lYaG6wATo5vGvNjk+n3sVg2Ot2Jr1PnWn32IVtCkKxZ0XMqcHQM/aWGQ8VdpwyBykAvpI+Mi0mACZdSk3oddjd4/PRiXdwNPIOz0fd6WA8ch8V4CYyLMRekedCmBZ91pKwk2bGOU6mlEkd8jT9Tkr9UW8Npar0lrTs7Fpywz2I80qjsOCgNZqST1kL+rUbMhlM+xV4WbhLSGxbS79y7y1ESeK1MLmjvc6048LPRTW/lt1DrarCN2r+2Z8cjM/6eYoRyVxP06FDAnUCihm2EsrdJxPBUTK+Kw8bMdPGHh8aRYGHDrUe2NuD942qrDaxwZtL/ermr+2/rec81vw7VOuhSfD0wW8Zjkm+hdnaMlybVrO+jAgdCWw9LLfrTU636kUWBs8LWFXzAidXr96WTWH5dkPPWOlX9//XsWYnQpLiUujU3/4SwNtf2xrebrfj7ADqbilHVYds3u0TPcnmfAXAyaQW1xJr
*/