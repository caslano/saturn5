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
Y90Rt9/unp3y1OOo+ntxE4Bjmk8hauaHXuh8UgXyqYy97I9flmTr1iOL1ynvMI9tcdJnS02dAID1mDbuhzqgSlNP/jqTFFz3b5M52SselDG1sJnhjATraDmugO+wsUTAiP4d8wAMgCVQ4P3vkREzfUivsR3CEew75+d/GPf+0HsNV4zRJvn988qBfpQmIdExk5fmeFCWORzMuOXaxZjlohVtA5+33KATS94XeWNbrKTBRObN
*/