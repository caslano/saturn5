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
8BKN+PyRDTQSkc5lUUBrUVYmrExo6a/FEp2EYVs2OKaw6BnunQv3j6SNTQpqTApbHNeCjnkwWSN1Qtrtmkhy2l/oZZefRp4IgvbVy3YVw9MtMUWmSqbM/L+35dgUUENtol3p/KPoIH7EUCfJTtxlpvmjs8av5KVqovOO/YIasBeWB4rpAQ6vA64rVFeUa4v7pOZmkF4sek9wDFqtO+M/24ZGsvD0kZf7EDIXjAW8ANUhexSw9tvUHRszMNgXz/AuJt776F5dPQ0G8jCp3ywEp4s3FY9YLhTvfSHQod4rxtS7SsNgO/GnXbv9KAC3n/Y21+pOj/KSUcJTk6vmGjG/GZYlyFVq8Eh4K+6vNgImuPoERcEFHCIu4h6iY1iKZeapnpncjpLjPv5q9teiEUrBG49niWb5lCZWWePTzR/OqNB4OxkYfQfRWMXG/CzOyev75nFxr3Q3SU4QYkEPMc2sYC/FWwi+Tp0NXaQKiEmg0kaN/lbOVbmh6xuxekh2VoRyqBGrhsVxDqp4VTVeNyPF22b7je4QZ+lWY9b7Iwfk6ftsHsZs2gtXHKEg/S6FIfcpAYMPh93lhvHYghh5Q/tD9kmZHLD0awkSJkoWyp39/aGGbW+SJ+YznoNLza4fqo88zaQLc8j7zosGVcQpAj6LEjJ9o/o/A5XjFKWO6vhdPHDwVmdVR1kEpmlBK1WVWBtcJ8tv7t6uTWo1LDpg
*/