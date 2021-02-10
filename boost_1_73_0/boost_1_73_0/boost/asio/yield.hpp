//
// yield.hpp
// ~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "coroutine.hpp"

#ifndef reenter
# define reenter(c) BOOST_ASIO_CORO_REENTER(c)
#endif

#ifndef yield
# define yield BOOST_ASIO_CORO_YIELD
#endif

#ifndef fork
# define fork BOOST_ASIO_CORO_FORK
#endif

/* yield.hpp
4oV3kkbWGA6HI50eBuykfExt4J0sjfQl76lp7RgGTSKORh/yb0glyssldVzBTTaqe45nY/AKxKFTJQUO6eLZjV+g6zzJoyaZZs0K3TNkU/8C7BJg3qEXjrnNuwUVRXt8q0kJkGZn2eUqbWqlU7Yc2tYv0VE/SXAqB3FcjkXyHal4HtqpFCgT45xMvZM8RJofSQaj99ikmLQKXdDvhE+XJqds4VjTg2YkPH6U4haxaQd5KAMIhm6DcEc2NfLjjOCnqXsJG5XH9VFgcIhJyBrpKpmOnvNG0IMMhqlmwCwstbMiJpLRgegA9KKhztbCTvVwJv5P/Tc1Cw7XaUXXioYkx47SvJ2BrKLmbn87Wu0s4UnxJtpOk52P9LVYjo4aU0dHM2j0+AReMugf2hJK0QRyLNE4R30NTHhP5AsKDrH5VgrFNY1BEei6Qzi0PICPvdaDQN4gjbNdTCceSbDmmJAm1U7NIrbDQD4p+DAbTpZpOk4XiUaVJeyFs6lnYmsbC60E7oUADOUlyRP0qT/RTWQ6reEGbnckYt6hjOD4kyRLL7PPfEGOwfgm0yTBdNyVKXTBxePwQNWgnZNAcvYwOohIz3gJdwdFKHYSW5A5ltC9ib8XidJ0is+Oe8TP3O+7fimH2yZNS14gjyWrJY0Q
*/