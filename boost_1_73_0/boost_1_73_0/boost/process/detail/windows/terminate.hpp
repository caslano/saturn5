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
0USQxstA44dAo7dRtcGrOg3LUOXP6fTqxjHw6CuUcNhC3xdpbAcaN8zDvqtoTulUNNdrH3GZTj+sefo6fYGW6SKdPr3R9P+7Oug1lWx/qbLBq7DYS7cArLulNd3em61gyM7Aeev4NgPvq/Urz43G+dsNrOz76zG2Wla/2hLRv8fBCUCIeczmHzZwGRtHgtncdm9C+fms/JPx8vN3VX4BG49d+ZoZzJGtmevFpbuAyXSfA+vbWLXibD9m01XgnWY=
*/