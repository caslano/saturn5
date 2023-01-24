// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_WINDOWS_SHELL_PATH_HPP
#define BOOST_PROCESS_WINDOWS_SHELL_PATH_HPP

#include <boost/process/detail/config.hpp>
#include <system_error>
#include <boost/filesystem/path.hpp>
#include <boost/winapi/basic_types.hpp>
#include <boost/winapi/get_system_directory.hpp>

namespace boost { namespace process { namespace detail { namespace windows {

inline boost::filesystem::path shell_path()
{
    ::boost::winapi::WCHAR_ sysdir[260];
    unsigned int size = ::boost::winapi::get_system_directory(sysdir, sizeof(sysdir));
    if (!size)
        throw_last_error("GetSystemDirectory() failed");

    boost::filesystem::path p = sysdir;
    return p / "cmd.exe";
}

inline boost::filesystem::path shell_path(std::error_code &ec) noexcept
{

    ::boost::winapi::WCHAR_ sysdir[260];
    unsigned int size = ::boost::winapi::get_system_directory(sysdir, sizeof(sysdir));
    boost::filesystem::path p;
    if (!size)
        ec = std::error_code(
                ::boost::winapi::GetLastError(),
                std::system_category());
    else
    {
        ec.clear();
        p = sysdir;
        p /= "cmd.exe";
    }
    return p;
}

}}}}

#endif

/* shell_path.hpp
uNcOhNxzvlqSkKDnacI/vM+34y60s/+jwDpdGDjOVxgm7I41dRZtUJDuAHxWE6sQTi5odK22UPkx83YqOPL+RQWpxPwGRTTHy26jmpzOYKMgYI7Z3CHfieTcVtEiMx4RdVnhbPanzTdDh58RnhDNq8CteRhM+ZJwO50qIyqg0/gnDXmAuOcfHf9YFD75h734E+lJGi8UffvFqsFSjF1/qKebI++GzKqEzSCJy6hzJX0POa+dvfJGxVD4cUVkpr0cKXdmk/HM3VBhZNCHoLxOUd13by5OxauqiNRvL0YCrpI/2/NF0S0sOBPl+f6JDax2GHCm0C349UNdHysuyVTQdheO4ymvFwhf9DyoTuSg5gnr8eZ61ctHXHXiwppnRbwhxNG3dnOAbi2/ZbXY+ZN760cGr8EGgdNyx9OD8lu6oata53p+v29/9Bj04ft286XDZbLNtRl20HodcBZtLCtludzhIgfvFyP1GPptLtYSY6cxfMD7eLyfAuW4Y70O4NXzUZWpZjPqwCgyaQ0wlbuxjXmxWknf6L7/R2oR3aIbn06zO/naKMvGON5uKeKgZbeaEGnZsHUrs5lF9Uw2HXgAllvJ4xFIytXvInQOcEyX6WpI+JV8iXLxgdXILzPZczaB2uukYOrLxKHAk9hXII5njZrbG89Z+9b6Pvlt01d/urQbGwNqVv167AkfNqL+zfXyQruBLSniT67CnKSl
*/