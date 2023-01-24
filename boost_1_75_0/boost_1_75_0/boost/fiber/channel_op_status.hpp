//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_CHANNEL_OP_STATUS_H
#define BOOST_FIBERS_CHANNEL_OP_STATUS_H

#include <boost/config.hpp>

#include <boost/fiber/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {

enum class channel_op_status {
    success = 0,
    empty,
    full,
    closed,
    timeout
};

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_CHANNEL_OP_STATUS_H

/* channel_op_status.hpp
yVmlIZPNUz3RiUGDeBhjylRmlprBs1s0IC9BHGfv4cqwLbxlk9qWTtMmQ9DPNso2DyOZB0bi4zLSgI0yBIvThVzFj18JrqJR/XXkK2S2Fn5PbEb1V/TcRcmV9HgbU/crr8LrfuV5XuhJyl3PX1O+x9er6XEZ1KicehXvipreTcG4EuQHd7dwhRthK841irGiM9w25wSGzsONN6jMXq5dxOzwmpt26eSF/9lG8sIsYGTMGJQ7svEaZGT6JSOFmXytCHmdv4PkhVle8zO74kS46wdeIHmh5gWxfre/iogl9VniWb4R3Pa/BDv5raTJunnM8lp+0jCVfSZhl94YiF06PxC7ZIKeQUcUz/fR0nCDaygr0jsZi6RfgkUS1SJ3YxFTyRoJWKO0ZyuxG0QNeYd77uasqL/IHFlRf4eAyIrmAgQVr/Rx8VWgO8m896WAldfUX5u+pCXP/FcMt/SZnHjOW+6Qu4s45ee8sMU95qtuhduEWos3Wm5gH/RhxeyeSY1UbMOlcDtbwxYteeXFyIUm9UiUpGJHYoLXmrIvU96j7MzvAdD0bf9z3q3h0PRlX8a0ieciGGHP3MRNEIibuOHPhglHwjkQfJsBRz7Er3BDNDi3M8lrrvggDlRwGQRZWfF3KgGCrNCXhKEEQM8NwKXYjJBj7nU1euStUZLgbkZ21njN0z9A8GFpw/8WS5zr6r4QCdRVyVCWw2OtZN9d
*/