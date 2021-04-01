/*
 * Distributed under the Boost Software License, Version 1.0.(See accompanying 
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)
 * 
 * See http://www.boost.org/libs/iostreams for documentation.

 * File:        boost/iostreams/detail/execute.hpp
 * Date:        Thu Dec 06 13:21:54 MST 2007
 * Copyright:   2007-2008 CodeRage, LLC
 * Author:      Jonathan Turkanis
 * Contact:     turkanis at coderage dot com
 *
 * Defines the function boost::iostreams::detail::current_directory, used by 
 * boost::iostreams::detail::absolute_path.
 */

#ifndef BOOST_IOSTREAMS_DETAIL_CURRENT_DIRECTORY_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_CURRENT_DIRECTORY_HPP_INCLUDED

#include <boost/config.hpp>  // make sure size_t is in std.
#include <cstddef>           // size_t
#include <string>
#include <boost/iostreams/detail/buffer.hpp>
#include <boost/iostreams/detail/config/windows_posix.hpp>
#include <boost/iostreams/detail/system_failure.hpp>
#ifdef BOOST_IOSTREAMS_WINDOWS
# define WIN32_LEAN_AND_MEAN  // Exclude rarely-used stuff from Windows headers
# include <windows.h>
#else
# include <unistd.h>        // sysconf.
#endif

// Must come last.
#include <boost/iostreams/detail/config/disable_warnings.hpp>

namespace boost { namespace iostreams { namespace detail {

// Returns the current working directory
inline std::string current_directory()
{
#ifdef BOOST_IOSTREAMS_WINDOWS
    DWORD               length;
    basic_buffer<char>  buf(MAX_PATH);
    while (true) {
        length = ::GetCurrentDirectoryA(buf.size(), buf.data());
        if (!length)
            throw_system_failure("failed determining current directory");
        if (length < static_cast<DWORD>(buf.size()))
            break;
        buf.resize(buf.size() * 2);
    }
    return std::string(buf.data(), length);
#else // #ifdef BOOST_IOSTREAMS_WINDOWS
    basic_buffer<char> buf(pathconf(".", _PC_PATH_MAX));
    if (!getcwd(buf.data(), static_cast<size_t>(buf.size())))
        throw_system_failure("failed determining current directory");
    return std::string(buf.data());
#endif // #ifdef BOOST_IOSTREAMS_WINDOWS
}

} } } // End namespaces detail, iostreams, boost.

#include <boost/iostreams/detail/config/enable_warnings.hpp>

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_CURRENT_DIRECTORY_HPP_INCLUDED

/* current_directory.hpp
FjcPLEzWjvr9wbbi066QPYTmgf8G9i3kzvYJxJpyUd8rrHzy0pjYvGUQkYlLGsjhOHWrqFOeNrS+a0H7ax1aDtAYQavKCSFIf+jYCXtetfS+3cIfkP30tjReRuWylW05TC3uiPr8KM95WxyiKSYdHuyqZuInMcF8H2fi9Gg/ptQhJr5leOIn/XxUaXHpeYz5ouUBuTJ1IMUnGeuDNnb3DcgriIz47uk/MKg7gNhnavDQOIxFZOVNm7m82PQHImX3Y7Pa5edi//FDP8TR7rZtykRCcj+xIciamWS5RqbJU1iVnQnuP+43CC1+qe9WhxWCaUwDM7f8ym1m3AJUTyn/DzzlS/dNJBXgVY7r2PGqzwoSVP6ZooXYqT8b0+VVRqD4IjHPSWRUe75nXWEleZiP/kMyPNNU9GQKxaPWSqEiBmE30h7qO5Zybcw5v2PBY5AVUAMT1p0qQnINY6jp9fQYdiaZR1xUC8Kj8/j7OpuG6OD8xiqx9JlIRoTIERVJAkgGDu0cE+YUp8SbnXLHljOG6ZaMztoNKTqJkfBIBCL70f8k4aVEgnK3dgUPBQ==
*/