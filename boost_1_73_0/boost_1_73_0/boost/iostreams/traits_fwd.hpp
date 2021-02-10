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
6wNiyHJVKIsWw5ECzo8VZiZPXP0ZE+f0z6QtwbZ1Fpy3hJUnz9YbpRptXOjpEHcibc96GzjDgcuZY5gZ+k+UN35Ca0hwskwHyorDmyF1dRrHAd15TcOiGQzXxmgkiOOfwUQQ0EQQZsYSTASYCDARpkwEjuMpE0FsdcdsrHXJO+9yRS/A1kk81vNsygSYN2N5tu6jozjNEr/BTgCO9xi7AeCqJ0zL4axDyZPgrEPJoeRQ8lBffULJ4VGLq8LjHeb8C5wZWW5U4FRvgRRjaD3epQJMTO8qNal+J3dYI/IuyMXrQq1WQme5wJ3lIZo7JsvRVRafjoRrLaqow7uGpCfBu4akQ9LTJ+liqzF87HXJ8WRPN7zsLZNkDF1v6HtaUXUavdzJl2SBnGw4wklUXrjC0N0kuMLQXehu6nQX3qq4mjljCRU/o+Uly9d5OK1bIJ4YGo48C2v6Rxretp/yw7giZfRSK65oENYOA3U9uy7cBlc717zQ0BktjgKvMr8rw+uTuuE+6yXmbXtVIawZYLU3TJUPM1Xg5cNQSYKXD0MFhgoMlc0sIV9oqGDNOYyMsDEE9Ihsq6GBYXxBDJGoy9oiWR8Yk0iuoSHW6ref17Ev0yOCpe8wKdBzAYMicT0XMChgUMCg2Mxy+mV6LrAC
*/