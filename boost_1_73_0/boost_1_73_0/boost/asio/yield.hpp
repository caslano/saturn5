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
zgZxLXWNrK8yD67f46x1cNbhqk237dHZxDGG2+FGNtFNhqic4XacuHQ2gQebQTELNMkauvGnuFA1PAkdwhfEU6N0z1ae4rRkES99WuIqDE5LRDABlpelYXmI4MTGMrI0LIPLTMalZraSIbYVp2UUhBkSmyQtr8kQokk8BUJMmwNhW5G+Bh0zUyG8RuI4DV0mfRq6+BDcQtithM0nbBFhqwhbQxj0jMQsmo7hbw+QdHHVpdsGH3LWtebA4APOFfU=
*/