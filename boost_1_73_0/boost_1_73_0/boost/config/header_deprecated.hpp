#ifndef BOOST_CONFIG_HEADER_DEPRECATED_HPP_INCLUDED
#define BOOST_CONFIG_HEADER_DEPRECATED_HPP_INCLUDED

//  Copyright 2017 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
//  BOOST_HEADER_DEPRECATED("<alternative>")
//
//  Expands to the equivalent of
//    BOOST_PRAGMA_MESSAGE("This header is deprecated. Use <alternative> instead.")
//
//  Note that this header is C compatible.

#include <boost/config/pragma_message.hpp>

#if defined(BOOST_ALLOW_DEPRECATED_HEADERS)
# define BOOST_HEADER_DEPRECATED(a)
#else
# define BOOST_HEADER_DEPRECATED(a) BOOST_PRAGMA_MESSAGE("This header is deprecated. Use " a " instead.")
#endif

#endif // BOOST_CONFIG_HEADER_DEPRECATED_HPP_INCLUDED

/* header_deprecated.hpp
/Q6Rtw0goZ2tvAPypRifW64ex6+k04tnIQxvzJDQ8MLc8kBttYx6pzhZe5PDw6d7ArUV0jRPVrV6MUhpYAhbE6wfJBuLnt14DC2P9LOPVDhWj1RR3rm840WJWWZjo6q5oFu3RGO9aLUFoirlVVjHK1tPk6HSDIE0TRUtEthW+F0GKXZMM3j9C/YuNBo73lTSatvmYp5dWo1qtnQWeuTHOaeM9HjHHaq+YqYn5U4J4ij0nty7cQSYnPVEX3R7cdU=
*/