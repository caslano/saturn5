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
mg/CFrfBDhJC55sUMAJP44P0SIUWJas9ZkK3A+9+ogXtfmaUTWm9Va74RwHc86r8yZUc+AaEp9ajuvLseFQ0HrCdYQz5kmYVU6jvljHTmUh8/R8/VD9sPg6N/vuI2QiwKmw+9x1scnu3oGpoI1sDw5cid2siipUAi8CsUR2HYeZXbDkT9PKTJRnzqb8dmvo64NuxYrgXAHxPazrHXp+y11OEyfVqkhUZmOCM+sdjvHAGCzfrYmwYDh6Po+a7EtiHscZq2ojRMpsJ+V8pBm+4g9q1ulHVdAIbGPGhz2vmRu+CqqaKoL21oCX89Z+RpiYrrw4db0dMErk1fORXckD8mJb17YVkcTYMxe6DjxoYH76/a0GpNPW4kZWX5d8lPr28sEGJcx8W/umvD/4IGFlZnSFp4qrHN3Xr1jGVxCckbjvaI+oMcyZv65jwEo69cZHlKiYuX8XTnrA8oJqigi2T4mqlmFtzDP/oqC/JkhkUAtdtzps10qURtMJlEMAbO+J4syWXfy/dcK/4Prx3UWhTOG6p7aA5v64iaDxs9zesMKCVgFZRKcoUyQkiFA==
*/