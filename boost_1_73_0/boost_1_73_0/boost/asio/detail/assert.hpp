//
// detail/assert.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_ASSERT_HPP
#define BOOST_ASIO_DETAIL_ASSERT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_BOOST_ASSERT)
# include <boost/assert.hpp>
#else // defined(BOOST_ASIO_HAS_BOOST_ASSERT)
# include <cassert>
#endif // defined(BOOST_ASIO_HAS_BOOST_ASSERT)

#if defined(BOOST_ASIO_HAS_BOOST_ASSERT)
# define BOOST_ASIO_ASSERT(expr) BOOST_ASSERT(expr)
#else // defined(BOOST_ASIO_HAS_BOOST_ASSERT)
# define BOOST_ASIO_ASSERT(expr) assert(expr)
#endif // defined(BOOST_ASIO_HAS_BOOST_ASSERT)

#endif // BOOST_ASIO_DETAIL_ASSERT_HPP

/* assert.hpp
ZaPoVGi93qkgBjefbRyTscrLnTY6atwMg0umEzslBmk7ozqhrYiDalo6Gid+V23cNs2PaWd0GLTdi0+2d36UUTvbXD/5r2neGiMO1s1WwKqY6OVWsEnnhdE7/umVkREnPvRJeoVnAt3CEd/gTX51Vrugo1oBIvfqXy+HGKfw55sbemYb1A0gCDf1me0QR/MKAfz8HAKvXxcMrIuvXxMSgE/5BYkKwlWocezSvoletgflYfiXlb2T+EgoAqVnkbmFxXiadCtNTagAnhl+glcKq55J2Ekgw5KeN8bNAYd/dvBySccqm6PsVPVX7lyKsHtpKtmojdARNhu2YMwJ2bIu2RbBy8jBK6TP9fiJk4u7W3E74O6opA0b9l3dy3EyiIuuywb4iIIPYelPYkwhis9fbsmz1ivOenT5IT5Gh5CQWI2js5VZg0GjPKjmfLuGA5fg9jlrZLXToU0hMGXwxCk7/Th5zSg1w0wEQyhvTXAIJQRQibANrtXs3qzjwIZaN446hvV55Bfda7zqwRR22vFxS9qsjAk0Ll5kG0L3qE9LTmmgVl4pflXkqXiR2GtBRJmUD4iHgnNH5cnvBY4N//Rqch503ZRfga9eZhpFJMS3WiYDJwZubOEVF825hB7fe7UVn+g0kE6TOsC6VzCH
*/