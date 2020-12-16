//
// detail/global.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_GLOBAL_HPP
#define BOOST_ASIO_DETAIL_GLOBAL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_HAS_THREADS)
# include <boost/asio/detail/null_global.hpp>
#elif defined(BOOST_ASIO_WINDOWS)
# include <boost/asio/detail/win_global.hpp>
#elif defined(BOOST_ASIO_HAS_PTHREADS)
# include <boost/asio/detail/posix_global.hpp>
#elif defined(BOOST_ASIO_HAS_STD_CALL_ONCE)
# include <boost/asio/detail/std_global.hpp>
#else
# error Only Windows, POSIX and std::call_once are supported!
#endif

namespace boost {
namespace asio {
namespace detail {

template <typename T>
inline T& global()
{
#if !defined(BOOST_ASIO_HAS_THREADS)
  return null_global<T>();
#elif defined(BOOST_ASIO_WINDOWS)
  return win_global<T>();
#elif defined(BOOST_ASIO_HAS_PTHREADS)
  return posix_global<T>();
#elif defined(BOOST_ASIO_HAS_STD_CALL_ONCE)
  return std_global<T>();
#endif
}

} // namespace detail
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_GLOBAL_HPP

/* global.hpp
3uXHZ3CuUbv8IkQedR35DsQA+reQN74S5wvrW8gTX5Xw+lG7/LNjMCeoXR46FttHXXl1wlt3XMKbsHWy10Ce9xpsy61HXtCNaxjra8jZ12KcWB8g34sYxPrU6xLeSxA11BnkdyLqqH3kMxADqEvIVyKG3HaQRxAno06+PuEdhjgJdRp5EFFG3ULefyquK9cH+XDEItcH+XhECXUOeTmiF3WA/H1EP2rv+IR3MKLqxob8EkTDjQ357YiKeyzyMSckvLuuxmORf4m4A3XmDQnvS4jdqFvIl2dxLq7BuUAO3ohjx/oa8mPflPCSWJ9GXoE4GrXLdcSxqF2+C3Ey6tSJCe+5JyW8Q1EHyC3EMMbg8rQ349pC7fLvEROxfZdf/hbMudsX8sffimNB7fJ+PZhn1C4fhBhE7SN/5m14LqBOvj3hrXwH6q0YM/IBJ+O55uYB+YuIXvRx+eB3Yq5Qu/w0xEa3HeRvIXpQ596F6wGxCGOuIP/+PeiP2uX178N9CbXLdcR2d7zTE96vEWM+ijHMwLWJmIA6h7wNMRF1A3kPYvga9JmZ8B6Tx3lBnUM+ahbmBbU/C/1nYV819Ef+0SzMGx7r8ltn47mP2uU+xLGoK8gjiEmoM3Mwnjnoj8ci428PYx5Qu9yHyKMO/IS3E7EGtcvPWIDrDTUyvuvA3KJ2eTFiELXLH0E0Ubs8tQ/XAGqXpyGSH5sc5gv6MDbULt+IyKLOLUx4By7C3LqxIa9GXIba5e8gtqN2+V7EEGqXZy7GtYfa5VMQ7W4ekP+0GMeD9S7PXoJjQe3yUkTg5gH5M4hJ7tiRb0f0YgxN5HsR01B7SxPeExCLUKcKeM4h+lG7vBuxEbXL+y/DPKDOIl+H2IHa5euXY+5Qu3wn4i7UmRUJ73H9uM4/jv7Ix52K+xdq91tyZyH2oI/LJ6zG/RzrXb4ckUbt8hGn4Tyi9tYkvKcjJnwCzynkExF7sD6HPIwYg/XJ0xPe6xD5T2A9coCYiNrlyxGHonb5FsTRqF2+B3ES6uxa3DMQZWzT5b734z6A2uUliB2oXV6OGEbdQG4/A/3x2IrLZ+IcoW4iv/0s7Bt1Hbl3A86j64O8/9m4HrZh/GejHdGJ2uWXl3CMqF2unotzgdrlOqIftcvfQZRQN87DuM7HcwHbTG3C2BE+ah/504gC6gbyzAswvk/iWJC/hJiEuom8sIxjxnZqyAsuxD3NbR858QGcO9Q55HWII9C/gvwpxA7XB/l2xFbUTeR7EdtRe5txzSC2oU4hH4W4zG0HeQPiULcd5G8jpqB2+fUXY/5Ru7wScRJqly9C9KL2PojrCrETdQv56ZdgzlGnkV9Swf0FdYB8MWIr6jrynYjLXH/kIz+EefsUzilyL2KH64886VJc22498gZEC+td/jnCw3qXD9yC6xC1yycg0qhdno+YitrlfkQOtXcZrjXEGtQl5KsR29x4kO9EbHfjQW6/HH1QJ5EXI2roX0P+CWIAtctPvwL3E9Qu+4gm6gry+A/jeFGnkf+A2OzqKt4jIUZQB8jPvRLX1afRH/lzCA91A/m6q3Bdofa2Yp+IHtQuX3M15gW1y7cj1qPOXoN1iHbUwTXunopjdzXyZYgKapfHfBzXKGqXJyF2oc4MJLy7ET0Dk8Oc+BzmGbXLT0asR91Efvl2nEf0d/nTCPznZ2H+8rWYc9Qu34JIo3b554hjUQfX4V6C6PgMjuX6hLcKkULdqCe8HyBq6OPyWZ/HuUbt8lcQTdTJG3CNfQFz5caAfMwO3Hvx2BzyFkQV69NfxPlEVFD7yEfdiGsVffyb8J4QUUSdGkx4H0WUUDeR70UU3Hi+hOsfkXd9kI9C9KDOIL8=
*/