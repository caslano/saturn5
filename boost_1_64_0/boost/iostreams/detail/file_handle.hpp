/*
 * Distributed under the Boost Software License, Version 1.0.(See accompanying 
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)
 * 
 * See http://www.boost.org/libs/iostreams for documentation.
 *
 * File:        boost/iostreams/detail/file_handle.hpp
 * Date:        Sun Jun 22 14:23:12 MDT 2008
 * Copyright:   2008 CodeRage, LLC
 * Author:      Jonathan Turkanis
 * Contact:     turkanis at coderage dot com
 *
 * Defines the type boost::iostreams::detail::file_handle, representing an
 * operating system file handle.
 */

#ifndef BOOST_IOSTREAMS_DETAIL_FILE_HANDLE_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_FILE_HANDLE_HPP_INCLUDED

#include <boost/iostreams/detail/config/windows_posix.hpp>

namespace boost { namespace iostreams { namespace detail {

#ifdef BOOST_IOSTREAMS_WINDOWS
    typedef void*  file_handle;  // A.k.a. HANDLE
#else
    typedef int    file_handle;
#endif

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_FILE_HANDLE_HPP_INCLUDED

/* file_handle.hpp
o+5bQoOlmWiOI3N0shn9/K5X94lhH8vebvihrmG5Uv7iaGyoILYum8xCXf3R2lUq3uRAklLUZ9orUsRiOc6LK3ZO9jR9iIw5izZeF+MuHldZgzX3bPwywWr1jOqbPeegKm5rwlZBem7/NWwnd6wZbVtvRjxAaCu1bK4pCklhdBgBGE6E+junOez4udR375aG0oSjxcuIEd1IsFNyDyfcbmIEjyCm7O2QVUuVvTg5xo+AgSRovzIgp6GhFJTCHLDgESnZXkc+wh5mWsrkVzSn7DZNCrKHSw/j/eMJSOpbUcnwUSGN4WToN9k9LPqlnLRlpNhV+/+Jz5Kc5OpDmLBvLgOCGtPqQEQDvMtL8MQbWvzUl2AFjJA6BK/Fs4ESyB2fjD8OlTKu7HfsofQPO9qq5KvBZjjPYqtd0zAIZAHKN/GGq/8ChN4aAiSBpfNLlOMshwA+pHssoXoT9LFxa3BmY/J8gAp4t8kjQesEfTZgMNv10thhusWhiwRTcpl/XpkhMl2uSqjJW1IXoIoDK3Y4/KKWG21NaAwv2ieKxFrhZzcLui1u3zDqGhUoVg==
*/