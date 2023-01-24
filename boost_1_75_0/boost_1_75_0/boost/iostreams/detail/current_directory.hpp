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
yBB7DXXxDUPF0AEWnZdmFvnC8X4+E7PXHO2l0njnaLD2t1RoA3d+Ba3lXOeB5WAJwoslhDE/Mr6+xef8CyHpU9SpQpetVIHO87yx+YN31kzpA4Iq8rOYgXlG+/r7GU1s6DAO7mDXbY1pyRtnU0Z+75hu5vt9Z8taAjgHDeHaP+bvORlT+qaOqcWVuxsiVH8izs2D6uvkj5/tdOhjBi6S2eSICsIqeYceoGDThcp8fgdX4sRaZu+Vkj4PWlix6vEYTOQTJnkSg2ZZ6YuMLBVkCxDjPWSpv3rjn0lqTBfsho29sKPO8lCx0WZrRFfPNSF8hAIM1S9d0JhCT483T1ssxtuTaToQF/sfG3/7jufHTivC3dG+/8Y/8yUk7RzAudOLE/cCPGvAHm6ZomT6AYf+CDpHujZFUT/CSalaqLnfNGHXDPfLCz++puWVGhnkipad7l525YRzlRlCFnGQ8VHybrkO9FmSkUHmWnN781Akx3aSKS7AOGX3yhM/GCdle+3vPLVmw+7e+252f9MNpNLr/wEpY1eO8AhuBmkhq06RtciyV5wpamLUGpj4tKaF32iEYozPkzY/lmJ2GbTOMXVz/Dmg4Rx63mleJTEbafLY6CZ6AJ6FHQPbas0uSnzSN8QEij9+fxrWW8qrmG6V8MTSUW604b11NeUaS0UZ87MxJIh9XRyw3ifR8/Q2M+O9ta2ieI9DVkEJp70C0ujV
*/