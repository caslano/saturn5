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
X+otEFhlplOtAlXaYwS0etKsTGlRRjZYvguj+mYMkuUtIpwk4fhsw2FT6Sl7pa6b/q8ZJ6bM9iYInfmqLiKq1MPJvhy4/HJr8HiIfjZHWzb+aeFO3Xkh5u1mWDY+DNRnM/eEfMYEDuBT+3xRp8E7H9L/KZRUOanNGX7Br5dVe1Nktjp+Sy+QgiUbH+rWx17hTcO6sNjw9dTOK/8f1WnDnxfZHkkhwvXrSWyY1wToAwRHhhB5BDGwGOcblKBCveUid3k7GDAA/C6AqMkZhrCA8QexDtvrsNfrd6j79icZGnW4bPWkkbbiQX8OC1HIvuq+lMxhI7jrSZaENT6IxK8dZZ/ldnzRBNqSRd2wcThdzI+YrD3+rp66gWqLgVjNOIghl+ef7y8/BQKKOrzvtgbmL+sCdI//pHLfHEy9oCGXVuCyA4JXDbxcezB4ty9i77HZ+uuW8EGarsyaAnTI0Ss8q64c7pfQ1mVHUM/oGvKn7d7TlNys4W9gneji/fQeJIunZ+w6GOlCMQILw7FCS3P04I9tPKMRpVsVF3teIKPVFgIdQ7gfvlzOfZZF2Q==
*/