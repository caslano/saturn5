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
k77BZ458sq24KRf0S85Ipf/gq6nMfYpZ9MYfLfhzgWp6zkzFn0V8cnc1gqfIv0Dw84BqtvbCPw1Iyc2gUCDbBbL+rFTIQ6+kNoN9r6R0id71ca0QskDDXJeXSujrr6QW+XMkpPjFmxjnVacL30uFyCeEyB7gm8vPTiVyE4mw3NcRP6W8IcFbd7Yo4A+k4p3TK/PTiNxHf4gKiQCwze5eJA52pAritx0n5f8VQZ48Csjto1KR
*/