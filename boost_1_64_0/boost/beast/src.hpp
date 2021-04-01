//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_SRC_HPP
#define BOOST_BEAST_SRC_HPP

/*

This file is meant to be included once, in a translation unit of
the program, with the macro BOOST_BEAST_SEPARATE_COMPILATION defined.

*/

#define BOOST_BEAST_SOURCE

#include <boost/beast/core/detail/config.hpp>

#if defined(BOOST_BEAST_HEADER_ONLY)
# error Do not compile Beast library source with BOOST_BEAST_HEADER_ONLY defined
#endif

#include <boost/beast/_experimental/test/impl/error.ipp>
#include <boost/beast/_experimental/test/impl/fail_count.ipp>
#include <boost/beast/_experimental/test/impl/stream.ipp>

#include <boost/beast/core/detail/base64.ipp>
#include <boost/beast/core/detail/sha1.ipp>
#include <boost/beast/core/detail/impl/temporary_buffer.ipp>
#include <boost/beast/core/impl/error.ipp>
#include <boost/beast/core/impl/file_posix.ipp>
#include <boost/beast/core/impl/file_stdio.ipp>
#include <boost/beast/core/impl/file_win32.ipp>
#include <boost/beast/core/impl/flat_static_buffer.ipp>
#include <boost/beast/core/impl/saved_handler.ipp>
#include <boost/beast/core/impl/static_buffer.ipp>
#include <boost/beast/core/impl/string.ipp>

#include <boost/beast/http/detail/basic_parser.ipp>
#include <boost/beast/http/detail/rfc7230.ipp>
#include <boost/beast/http/impl/basic_parser.ipp>
#include <boost/beast/http/impl/error.ipp>
#include <boost/beast/http/impl/field.ipp>
#include <boost/beast/http/impl/fields.ipp>
#include <boost/beast/http/impl/rfc7230.ipp>
#include <boost/beast/http/impl/status.ipp>
#include <boost/beast/http/impl/verb.ipp>

#include <boost/beast/websocket/detail/hybi13.ipp>
#include <boost/beast/websocket/detail/mask.ipp>
#include <boost/beast/websocket/detail/pmd_extension.ipp>
#include <boost/beast/websocket/detail/prng.ipp>
#include <boost/beast/websocket/detail/service.ipp>
#include <boost/beast/websocket/detail/utf8_checker.ipp>
#include <boost/beast/websocket/impl/error.ipp>

#include <boost/beast/zlib/detail/deflate_stream.ipp>
#include <boost/beast/zlib/detail/inflate_stream.ipp>
#include <boost/beast/zlib/impl/error.ipp>

#endif

/* src.hpp
rvjrLGAbNcDUWGknJkJnzxfmgusacWyGE9rhMYcy5vU9coo1qpfbd+IpVS7njypjZwu3+F67XvpZLiyoL9RHfhznyBEhgNBMw5OVOkQfhtexU8jV9vj7trNDdQD0Gh2idCqYVjvoyJFDyDmOU6JiA3bavLdmZDQamL9m8wxGeY4+fbMCN3FGBYt2+y3z15buefH47GKJjkEz0qHERsCGgv2eBlNeZXo7RLUZlRsCHxxCCPSZ0X8lNjrwMmqRk+MkXZrH+kZ3ndTIx3wHuLhgy8i/D2doPSz9jBN34r/sdnE1xqfWRQD1MvSu4afPhKm7wGhDPkCLrZSlnyjPUe8KUgSuu/aYTslmr51UW8nzylw26zAbn5r4UxlqIEdrNVxqX3PiNIJU5UcTNhas7LVGeKVtghY8mA9LeyCo8RNonbYNG6/DcXJgwp1bDsGvniwd6wixmtnbYRI403g9ASzmmeQ9nkbVmu42IE3TSg5TJmf8seIu+LGAcxd2uaQqgA9DrCtwe8vj0wFwnkbZwd5Lv1S1XPQ0UIyCfrhyP4wWy83QFFTYZddzDihQXg==
*/