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
WTcJgTrnTjg7QDRkSm7htt8G2FlNiwPGtKMvYcLJwbzyTAYeGMs+vEKwozXq3nskPzyP5CfKc4fiEw8crlllVZLvJYIuJAmi+B3a+QxZMOv2jHDcSPnAY6yYCZl0Met5ukw2fw0mThUzcz1z3npI3Lcjna+ULluVH9GAWI1i2uJl0+dWa8nbo7b9nbprhsNUYlls6PTJ81vGHQY/4KHqk7WzsVbvhowwBW5sHE8ZEhPQIQUY7GwksX8/349LVf6+0L5p4a20p/U4d7YshGzore070aZq7IH+o3vI0G6aAsLeYbYljjNpn37Er5PKw/OKVJSp1Wbb2IXbnUMhpTkaqEO+Zp1wR4Oma/9aNVVpxj4O5O2GaidIlNg8zx6AVKOI3iBJwH2vbuIIWeWSsE89+w0f2PWkj9s/sY1oPaxWGsg9U9W8JYnkAjQCTZFf0gyW52ZaSAP1mqPUV3Mzv/EhMTorlFpxyBqxpDCDNIR61J8UraV11B+yvlAzEFcfKPfkbVdckMMiJvBiwVjbXbm37RKB8UmdMpdnHWI4ASDEBBxaXLnQI1ODaa/fqQ==
*/