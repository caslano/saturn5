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
X+RCxe/H3JQ2/GSJOouyls4o7ftdt60qp/1A2ZQR4xqsv++RRwf+u/rRkYxluhr+Xdrv7ZDY/N9zKzwQc9vHua0ZfDre3aTtyzPRy+3dLUbe1W6BPQnLgH3hGDgI3gqHiDuM+9A9k3cB9AYZyFzE1CWczyzQJyzPLqINSwzQAtAVBGTxLoPU5G/zfWwl7p3IWzH4s6/BuVV27QTu7sTJQEydwyX8gu6zK93DOSQIPUKUISiB4pEUJAH3crgRGcbf+6DxXhdLulm4T+FeQlkMfURwtuPd7ih/X0Ca4u6OZCBLkLA2hMNzSAv+HoT0o3wXSDMJTsUdkeN4L1zI3+1zCOc8WwjrJ/qMw20g/ieQS8g+6uIMfgEJnD+Xd0BD+DsBXiJNEnTWc+ThDuPdaCF/b0F24j4I30KOcZ6dxLuEXy7nfYu/T5F/8HjSIwnIT8RLgk3JI6It6fk7HvZDjvH3eWQSf4dNoI6QfkjghwHqXXQ5fy800iAbcZ+AMYQdjOWcbQnnnGHtOA8yDP9jxD+LhE106FFmIbETSQuPIOeQNNyzkKAbqWvKlM/fB4348j57lr9jCDtK3gkwBbmA/1RYszFhkyh3Im2E8IxJ5IXE47+c8C3IVtyDcJ+BR3Bfgudg9GSHDqYpYupgzpOPqYc5hVwQ/csg4kbDXkgWshzZjUzFv2ZSgOhiyBdJknflI4SZupgz/B202q7lUSdht1E+JAb/frAznAQz4E7CFxpEjiJhTble6iSBtOdwd8edxN8aOpp1pDlN/Pac/yB/R+AX+BH3ifCzuFvgDppC+ZAk0et05u91MAM663h247cTv0v8fQSewn0OBk/Fj79jYWckCynfmeuHUynXPhiP+xQcBnORoGmEw51Ie/5eSbzd/nd5/+E//If/8B/+47/+CEBSf/fx/28f+1fhO9tOTIoHDzDstlE1MpxneJ8+Ijs5O31UjgrvTHjCIOfw1PFjR+bmcGkqvAvhWYOdw7MpcuZYI0Io4SEwb68RTpGZJkjPVemUfnyl5Z+bRqoUZhb4dp5wSTfLDJdpBkluhCt92jr3cNKPlvBulGuuCreUp4lpyTlpGkdtwnNh1FCncLnuyYl8NzSCypF8upPPTpVP38F93a6vnuSzRIWnZKpsrBkRypqYyQ0lQW6iVl3iLrfKTHzXOGou5uWq6D9ER3nBJutfIhWFA4z7lWrphvv2a9uvg/oiWOwO+hGOnlJ0lGbcqtZeB9cp93QJ17Xtyq1b3/8nByOF0AWb335yPkPv6KLTzreLHgKJUvVEPJQ0pwvKnZySIjdFqdfFRsH1+3vagKQhB/n+0dKNvlL1ynM+Xr4HcylnkOiAK5JhmHAQ1xN1i5dyTlAF9VVOSVPd+uaznXJ/i85Gd/oGNTn7lhxLPyxpKlt7NrRW7k4F68crd10zPQeNy+m77SEq/F3snUt6fL8Vyl+ZKvwINu2VvK5ZPkGFH2LNsGCn8BwVnkn+bf7D3nmAR1FEcXwvCTEkEUKA0EmkRogaFTX2oIARUCM1xGi6Bg0Qk6CoqFFR0c8SFTV27NhRsTfsXWNHRcXeNXbs/nbu7dzu3S53l0Tk87vle/wzN+3Nm7I7b97MKP+1rD91wd/ioU7fqf2q8i83uMFP1rR9xmr1W49AeNsd/Ccpv1vhMEefFX+8+u0UI4Ff+2NvstS0C+1i2ZvMSxmeMtq0NUn2WoNfouJvKW4r/1RP+4GzlP9Ah+1JKelunI48CPBCZmTtX9uSBO3tL9D7FFVdO+45aZH2tlzW5s+AluHTVKPbWyUDfr2/xcGzvz/zMBjzWH34BhX+GN1nX4yQZzsvjRvJ2qvYnWwOlZBX2WzNi+JCxjM=
*/