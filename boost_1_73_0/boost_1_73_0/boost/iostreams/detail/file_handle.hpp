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
6dfwhtpLTvh8/vSJoCvyjx/3YwiSe3+m6t8UfuB3jHUl+F/UDooxptNvRP8BzAn83ofZEUnQvk2fkf3QvpEDhTY13F7h83S6D8MJyon/HSH2ZIqP8MagRhR63N8ItlgG5KD3jDSPG01yCL+axzUyCuiakvfcXdEaeSXx03SJn94sebCymFu3+ep1vZTSbzXyb2tDRlbABAcKwtpI9fxmYy05z2BHRMZLJonk8+DWEpTAs8ts6knqEEsSh0pbsBl8YB4JlpTMmUtJb3D16fzyXY3cLpm9jAhteEjkkoeuQ5YWqCGoTdla0/EtEYDTAQlg4DAZANEwYNyrA39KAipWMqKDYliu5MRag8bWDBhaAVkGgS/bR0d2KNy6pEcOt+WRHRmgvgxW7rZmn0CgFZiD+wEJOAklGBUxamTFHTbH31Qs4KUfzlwml7VEMmDpOUdcEEldN6IHuIxKrQYlI2OyGoISHzRgAf6S3JPI7nbJVxlAsG1EaR4KDxiCbQDQ4WD+Ggk9hwqFoKwRsTG2Voa/d+sS+R3CPRCMVLojcj6qkJklmayRj+fj94PrMfnYHQ67l+NPZHBGupefIoL/Ob88rRHKgLEg9M4XVIIggrCV7zLqbPH/kaHj6ZP2jC6Y9/QJIUi8t6T2F3JLlTeI
*/