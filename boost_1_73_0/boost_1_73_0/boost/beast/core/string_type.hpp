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
KMyWlYfpBcXpod44ZtqEeqs7Lkh62qS5WcItEG6RcHcId7dwzwn3vHBbhdsu3F+F6xLukHDfCtffsdypjuUGCzdUuK+FOyxcKfWNtaqbVl5FUvRg69P88j91hiR5JI18AvsBiUjbJU68eXPttKmb/KU4Xoo+Tvts1V2efv2fuwzqFRFavM30ZgVxuorA+Pyg7VMHr3tb6RN8cxxZQuRvLoz+E/uJdpgY4//H2ZnAR1Hke7x6ZjIJIcdAEpJA0AE=
*/