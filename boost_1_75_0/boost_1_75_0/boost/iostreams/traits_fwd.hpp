// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Forward declarations of templates defined in traits.hpp.

#ifndef BOOST_IOSTREAMS_IO_TRAITS_FWD_HPP_INCLUDED
#define BOOST_IOSTREAMS_IO_TRAITS_FWD_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <iosfwd> // stream types, char_traits.

namespace boost { namespace iostreams {      

template<typename T>
struct is_istream;

template<typename T>
struct is_ostream;

template<typename T>
struct is_iostream;

template<typename T>
struct is_streambuf;

template<typename T>
struct is_istringstream;

template<typename T>
struct is_ostringstream;

template<typename T>
struct is_stringstream;

template<typename T>
struct is_stringbuf;

template<typename T>
struct is_ifstream;

template<typename T>
struct is_ofstream;

template<typename T>
struct is_fstream;

template<typename T>
struct is_filebuf;

template<typename T>
struct is_std_io;

template<typename T>
struct is_std_file_device;

template<typename T>
struct is_std_string_device;

template<typename T>
struct char_type_of;

template<typename T>
struct category_of;

template<typename T>
struct int_type_of;

template<typename T>
struct mode_of;

template<typename T>
struct is_device;

template<typename T>
struct is_filter;

template<typename T>
struct is_direct;

namespace detail {

template<typename T>
struct is_boost_stream;

template<typename T>
struct is_boost_stream_buffer;

template<typename T>
struct is_filtering_stream;

template<typename T>
struct is_filtering_streambuf;

template<typename T>
struct is_linked;

template<typename T>
struct is_boost;

} // End namespace detail.

} } // End namespaces iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_IO_TRAITS_FWD_HPP_INCLUDED

/* traits_fwd.hpp
g4KeGwNRZlUSVSFV6IRA3NWRZBGYmXbeGUSfaRSIPWZW6IY9ftYnsuhuAvywo20Y8xCUb00EVucD19X+KVFsbUSAHtxmMtJQkhqk9kt1cAgbcaAYL9RUdx0bYiIbChMVPDX7bXVhTmubaHzv50psV3YeeFVqSBgpPEUshRLVoGhYgU+N0Geby88l0zBwFOH4oshUJfoIu6O8OwxiFm+WomKpNMvwD90+l+SCiHFBcPw7f3zOIYsVx1bq4Qvv+awgRsUlgWQdAmcgIAhLUoOW9VlEchueOIyCF+lo51N/7tDOxYFag3cnkUG60C7aUdSXxg4SigTWHLPGnUSwTTPURbfOJXMB7LrUuvzQ4JHUxMyqQbWq/PXbpq5O1iJ0o35FQNIIjLr5DfmqV8raM6ZuKOOlizvGyNjnH3gam361pLVkLb0NMp2RF1UpOuFM2Lg4TKy6jEy7J11a8Va6enSXnfeHP2G+VO974iFFVRHVM+hpJnmjlBBwJ2Z5mVehDunEdFT1do7NgKL2J/XHdBm3OwOvb0JCbpBSYay9JJbjszQ+OpwC5d5w3ILSm8uZcB0RVVlHzcf43OCKO8qmpe16s7ut4PGYunl2vtT3nF4yeKPg63MzqXVvAh/PcUeajkLeWKlMDFBB0sJntHLq11ye9cPcP9w2KrL6Oq4WAOsx9tVjDQcyiB5QQTGaf6BecbKPKrczXv98IRWZGW49
*/