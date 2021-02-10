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
 * Defines the function boost::iostreams::detail::absolute_path, used for 
 * debug output for mapped files.
 */

#ifndef BOOST_IOSTREAMS_DETAIL_ABSOLUTE_PATH_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_ABSOLUTE_PATH_HPP_INCLUDED

#include <string>
#include <boost/iostreams/detail/config/windows_posix.hpp>
#ifdef BOOST_IOSTREAMS_WINDOWS
# include <cctype>
#endif
#include <boost/iostreams/detail/current_directory.hpp>

namespace boost { namespace iostreams { namespace detail {

// Resolves the given path relative to the current working directory
inline std::string absolute_path(const std::string& path)
{
#ifdef BOOST_IOSTREAMS_WINDOWS
    return path.size() && (path[0] == '/' || path[0] == '\\') ||
           path.size() > 1 && std::isalpha(path[0]) && path[1] == ':' ?
               path :
               current_directory() + '\\' + path;
#else // #ifdef BOOST_IOSTREAMS_WINDOWS
    return path.size() && (path[0] == '/') ?
        path :
        current_directory() + '/' + path;
#endif // #ifdef BOOST_IOSTREAMS_WINDOWS
}

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_ABSOLUTE_PATH_HPP_INCLUDED

/* absolute_path.hpp
4YAh0xVjvO7Rd3+0lD4DWZf6DMPnhe0CPVB5Xqy+b3QM2o1to99vEIjjAMIcENAcOII5AHMA5oAg5oDYSn4KKV+TlIfPOYZ3v21yXkuFdy/4dOh4NR49xSmTc4GcezjgiVdtuODQ7CS44NBsaPa2aza8ZDH1dt5mpeL6yJjzlOz9PSL1bMa7Qyn6loXrW8b33NdPbXF8JDBbtHmqoDloDpqLQfMkjlSB6OleTfbO/qS1whzdS0JwG9heDtsww9MB7SQvFwPOgXPgfOqKzS41yQOxiEGLzAswecpyzvbiokeUeiMBkL0KkPECcAp6jYU2k06xU65US7L3Cv59M6PwRxpnR3EdLYphRZwdSTPii7worvM0hvLR72GJHX/KbaHduh5L88SzZkT2U7J/jux6dmTzE/GXq/Xen4jf2pVibInwIntXImx7hYKQ5fjKgcX1rhQ4uv3+FLSqcmwpYHEtToF36Df2K93sUkPHuxgcn+/farar6LLjqprJufl9939QSwMECgAAAAAALWdKUgAAAAAAAAAAAAAAACUACQBjdXJsLW1hc3Rlci9wcm9qZWN0cy9XaW5kb3dzL1ZDOS9zcmMvVVQFAAG2SCRgUEsDBAoAAAAIAC1nSlIOJI5LHQAAACAAAAAvAAkAY3Vy
*/