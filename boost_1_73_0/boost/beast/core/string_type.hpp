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
o9VLA9I9mOmO3fGBKlkBHlzfiyRQk/J9ZKag7rr9e1VhfDasavFYEKhzVU0+hRCyw2XxrXx9t3rNXwhtfRvOOE4vJdT00qD8huV3q/zukN+n4PdLdSyv6gNV6Dac6uVMuBmWbh8gWwhXKwbwiX7YlUxewtnjK+x846V4XPUJvgQD0I30ffL+VYy+ejmjn4CB80nGXXg99vU+/DeQc1bpcTyhfcU5mvx+oOrYYzh/nfabrroY
*/