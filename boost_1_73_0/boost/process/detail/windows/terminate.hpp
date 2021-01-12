// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_WINDOWS_TERMINATE_HPP
#define BOOST_PROCESS_WINDOWS_TERMINATE_HPP

#include <boost/process/detail/config.hpp>
#include <system_error>
#include <cstdlib>
#include <boost/winapi/process.hpp>
#include <boost/winapi/get_last_error.hpp>

namespace boost { namespace process { namespace detail { namespace windows {

struct child_handle;

inline void terminate(child_handle &p, std::error_code &ec) noexcept
{
    if (!::boost::winapi::TerminateProcess(p.process_handle(), EXIT_FAILURE))
        ec = boost::process::detail::get_last_error();
    else
    {
        ec.clear();
        ::boost::winapi::CloseHandle(p.proc_info.hProcess);
        p.proc_info.hProcess = ::boost::winapi::INVALID_HANDLE_VALUE_;
    }
}

inline void terminate(child_handle &p)
{
    std::error_code ec;
    terminate(p, ec);
    boost::process::detail::throw_error(ec, "TerminateProcess() failed in terminate");
}

}}}}

#endif

/* terminate.hpp
+Sz1TvwrfOQYEq52s68THVpRsz9+6AB7OfrQRdaPwMF8cVwGLWkFXR85yY8vCYGFmdtnNwp8i/YcO7t5ZyoTSiz5JFH43cTkxmO4JkouoEFnescmlaiHw4p13vaYsfVPQI4ysTEYM4+LJRZtZX2fVg8RkzBmEf/YP4mOtWwLSq5mtcszE3RstWDLCYkesbijexu3yRTdZ3GPNZ5s2j5v8NtPIxyvK/AEIQmR+IA+gU/z9ZN4
*/