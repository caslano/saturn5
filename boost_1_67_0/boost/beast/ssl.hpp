//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_SSL_HPP
#define BOOST_BEAST_SSL_HPP

#include <boost/beast/core/detail/config.hpp>

#include <boost/beast/ssl/ssl_stream.hpp>

#endif

/* ssl.hpp
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
*/