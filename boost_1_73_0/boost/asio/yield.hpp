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
N4Okv6sHtvOne1S+wobU8NjH4ftkVu7lDNMIlceoQcPls+0Y2Qp1wtHS3cPxJ3OPyrrTXqTZ2wN+pFUfy4+0sK0KsB5ZQrpCQ18bzAFwv6TWFRQYuE4p9HymnlTTDHQIZiNc2YpdRwRey4GZehYVU/VtlLWIhspGgZ6d9va1UTQTI+fGg5N3bgKIlnNX+sy9LXbKopfbPSS+nU9bpzW8nQOZaY6N4xhSesfjPC1EdjamnAwT
*/