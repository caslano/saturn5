//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_ZLIB_HPP
#define BOOST_BEAST_ZLIB_HPP

#include <boost/beast/core/detail/config.hpp>

#include <boost/beast/zlib/deflate_stream.hpp>
#include <boost/beast/zlib/error.hpp>
#include <boost/beast/zlib/inflate_stream.hpp>
#include <boost/beast/zlib/zlib.hpp>

#endif

/* zlib.hpp
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
*/