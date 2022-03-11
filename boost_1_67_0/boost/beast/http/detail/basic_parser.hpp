//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_DETAIL_BASIC_PARSER_HPP
#define BOOST_BEAST_HTTP_DETAIL_BASIC_PARSER_HPP

#include <boost/beast/core/string.hpp>
#include <boost/beast/core/detail/char_buffer.hpp>
#include <boost/beast/http/error.hpp>
#include <boost/beast/http/detail/rfc7230.hpp>
#include <boost/config.hpp>
#include <boost/version.hpp>
#include <cstddef>
#include <utility>

namespace boost {
namespace beast {
namespace http {
namespace detail {

struct basic_parser_base
{
    // limit on the size of the obs-fold buffer
    //
    // https://stackoverflow.com/questions/686217/maximum-on-http-header-values
    //
    static std::size_t constexpr max_obs_fold = 4096;

    enum class state
    {
        nothing_yet = 0,
        start_line,
        fields,
        body0,
        body,
        body_to_eof0,
        body_to_eof,
        chunk_header0,
        chunk_header,
        chunk_body,
        complete
    };

    static
    bool
    is_digit(char c)
    {
        return static_cast<unsigned char>(c-'0') < 10;
    }

    static
    bool
    is_print(char c)
    {
        return static_cast<unsigned char>(c-32) < 95;
    }

    BOOST_BEAST_DECL
    static
    char const*
    trim_front(char const* it, char const* end);

    BOOST_BEAST_DECL
    static
    char const*
    trim_back(
        char const* it, char const* first);

    static
    string_view
    make_string(char const* first, char const* last)
    {
        return {first, static_cast<
            std::size_t>(last - first)};
    }

    //--------------------------------------------------------------------------

    BOOST_BEAST_DECL
    static
    bool
    is_pathchar(char c);

    BOOST_BEAST_DECL
    static
    bool
    unhex(unsigned char& d, char c);

    BOOST_BEAST_DECL
    static
    std::pair<char const*, bool>
    find_fast(
        char const* buf,
        char const* buf_end,
        char const* ranges,
        size_t ranges_size);

    BOOST_BEAST_DECL
    static
    char const*
    find_eol(
        char const* it, char const* last,
            error_code& ec);

    BOOST_BEAST_DECL
    static
    char const*
    find_eom(char const* p, char const* last);

    //--------------------------------------------------------------------------

    BOOST_BEAST_DECL
    static
    char const*
    parse_token_to_eol(
        char const* p,
        char const* last,
        char const*& token_last,
        error_code& ec);

    BOOST_BEAST_DECL
    static
    bool
    parse_dec(string_view s, std::uint64_t& v);

    BOOST_BEAST_DECL
    static
    bool
    parse_hex(char const*& it, std::uint64_t& v);

    BOOST_BEAST_DECL
    static
    bool
    parse_crlf(char const*& it);

    BOOST_BEAST_DECL
    static
    void
    parse_method(
        char const*& it, char const* last,
        string_view& result, error_code& ec);

    BOOST_BEAST_DECL
    static
    void
    parse_target(
        char const*& it, char const* last,
        string_view& result, error_code& ec);

    BOOST_BEAST_DECL
    static
    void
    parse_version(
        char const*& it, char const* last,
        int& result, error_code& ec);

    BOOST_BEAST_DECL
    static
    void
    parse_status(
        char const*& it, char const* last,
        unsigned short& result, error_code& ec);

    BOOST_BEAST_DECL
    static
    void
    parse_reason(
        char const*& it, char const* last,
        string_view& result, error_code& ec);

    BOOST_BEAST_DECL
    static
    void
    parse_field(
        char const*& p,
        char const* last,
        string_view& name,
        string_view& value,
        beast::detail::char_buffer<max_obs_fold>& buf,
        error_code& ec);

    BOOST_BEAST_DECL
    static
    void
    parse_chunk_extensions(
        char const*& it,
        char const* last,
        error_code& ec);
};

} // detail
} // http
} // beast
} // boost

#ifdef BOOST_BEAST_HEADER_ONLY
#include <boost/beast/http/detail/basic_parser.ipp>
#endif

#endif

/* basic_parser.hpp
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
*/