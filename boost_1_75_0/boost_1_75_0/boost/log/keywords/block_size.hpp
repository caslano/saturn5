/*
 *             Copyright Andrey Semashev 2016.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/block_size.hpp
 * \author Andrey Semashev
 * \date   23.02.2016
 *
 * The header contains the \c block_size keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_BLOCK_SIZE_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_BLOCK_SIZE_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword allows to pass interprocess queue name to the queue constructor
BOOST_PARAMETER_KEYWORD(tag, block_size)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_BLOCK_SIZE_HPP_INCLUDED_

/* block_size.hpp
ZMWBvP24wFJFufd/vgn5gy7+ATVSrY/5vaLN8dXfOLzx6Nr5oBz65zd5J2vPgwlfp412ISdPaOdzNqoU4hJrLAAJ1Rbva/fpsn7xqJ05gXfp2/53F1XWdXptIs+IW6kUeGTOVitn4ulRb+JiO0UuWi6JGW6vYYhoCAD9Bh8a//BYgrQK5ZiFI243s3CDg5ZRiN+8G+DF3Q01kB6pJzOMnUoyEtc2GVo1IVjvAa4dklKvPQ314+l+gHHjO3AdBTNGmy0KX7yyDNgms0waKKObS+j/QMh/KTwT4Ut4fCfTRX+ynqtwj3uxCnXAmwBOPpbgEslLSkvyasKZ332tfrw4b4WuHgfQ/cUObjnVhbyNYQ33vQfhfHzBu3hMDnjmcP8ihQW3w+fQQUJUlgXB6nanbLjpszJZAz7dfLeHX9w7oTveS+779WweGDVcQDpjLJVqyB6n9l3HfyH8/2CuXHnReaK5M8H5hZU8RJ1jRvIklT4E3hHKeDPgOmsm8iw1AUDqlXl31beBIGWI9+WW0w2rpjJD7f0UooVehr8YeIn0kzhGt1JWN86ZVIawF+39JtpSSDW5GVavdohViAP6Kr7+uzV0mhBq9Ap0B/TzRKgqhxg+VP5IZim0mvLIHrmaNJcyaP485cGfA7nWGJMmUbhDlyYVJsnxjE/zJ9mfwj8u3/eqLwdgj+2i1iMoZ6UdlC8gqnK3NObC5DOvZpzf
*/