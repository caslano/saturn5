// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2005-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_NEWLINE_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_NEWLINE_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

namespace boost { namespace iostreams { namespace detail {

template<typename Ch>
struct newline;

template<>
struct newline<char> {
    BOOST_STATIC_CONSTANT(char, value = '\n');
};

template<>
struct newline<wchar_t> {
    BOOST_STATIC_CONSTANT(wchar_t, value = L'\n');
};

} } } // End namespaces detaill, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_NEWLINE_HPP_INCLUDED

/* newline.hpp
pp1iLdd/tuUXC5wL2S8WiRljRh8aCTUWK5t1I6+O0WqazMuPCPldoI7AnSGSXFtaWWiScCsDZ5HzbPIcyqwDlgUem8aR6mP7raebIUFreNfk2miWCGUae1xoaThQyFP8hfQtzJD7sdG0jjaGZrVlVGFmi12qYGhb0r+LSMdbZNYYiqhu6Wul8+IQOoaElmqh+QubqBQYw4r1TLraja6rMQWV/fj6wU6lyErU+pTTFIg0rGnTkKaS+Lq9lHT1VlY=
*/