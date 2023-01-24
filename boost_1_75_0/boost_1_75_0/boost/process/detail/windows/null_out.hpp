// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_WINDOWS_INITIALIZERS_NULL_OUT_HPP
#define BOOST_PROCESS_WINDOWS_INITIALIZERS_NULL_OUT_HPP

#include <boost/winapi/process.hpp>
#include <boost/winapi/handles.hpp>
#include <boost/winapi/handle_info.hpp>
#include <boost/process/detail/handler_base.hpp>
#include <boost/process/detail/used_handles.hpp>
#include <boost/process/detail/windows/file_descriptor.hpp>

namespace boost { namespace process { namespace detail { namespace windows {

template<int p1, int p2>
struct null_out : public ::boost::process::detail::handler_base, ::boost::process::detail::uses_handles
{
    file_descriptor sink {"NUL", file_descriptor::write}; //works because it gets destroyed AFTER launch.

    ::boost::winapi::HANDLE_ get_used_handles() const { return sink.handle(); }

    template <typename WindowsExecutor>
    void on_setup(WindowsExecutor &e) const;
};

template<>
template<typename WindowsExecutor>
void null_out<1,-1>::on_setup(WindowsExecutor &e) const
{
    boost::winapi::SetHandleInformation(sink.handle(),
              boost::winapi::HANDLE_FLAG_INHERIT_,
              boost::winapi::HANDLE_FLAG_INHERIT_);

    e.startup_info.hStdOutput = sink.handle();
    e.startup_info.dwFlags   |= ::boost::winapi::STARTF_USESTDHANDLES_;
    e.inherit_handles = true;

}

template<>
template<typename WindowsExecutor>
void null_out<2,-1>::on_setup(WindowsExecutor &e) const
{
    boost::winapi::SetHandleInformation(sink.handle(),
              boost::winapi::HANDLE_FLAG_INHERIT_,
              boost::winapi::HANDLE_FLAG_INHERIT_);

    e.startup_info.hStdError = sink.handle();
    e.startup_info.dwFlags  |= ::boost::winapi::STARTF_USESTDHANDLES_;
    e.inherit_handles = true;

}

template<>
template<typename WindowsExecutor>
void null_out<1,2>::on_setup(WindowsExecutor &e) const
{
    boost::winapi::SetHandleInformation(sink.handle(),
            boost::winapi::HANDLE_FLAG_INHERIT_,
            boost::winapi::HANDLE_FLAG_INHERIT_);

    e.startup_info.hStdOutput = sink.handle();
    e.startup_info.hStdError  = sink.handle();
    e.startup_info.dwFlags   |= ::boost::winapi::STARTF_USESTDHANDLES_;
    e.inherit_handles = true;

}

}}}}

#endif

/* null_out.hpp
77ktT6Tk5WU62bxxKpBSZIqgeJkUztP9Y2BUsskcOPXLXwRi8AUp1JhH23spK5J0/AXxh8Phec+W9z/ii6xHzXfaNqVk6JlZR9kvnx3+qSWYzZ9mDM2Q8bXTX9w7xY9+dRbh3XRYNwpORDNAXBaePWApISOSNRYN2rgkdmSva99EUm7rSqQpJkwMRdOF3lfvu1a84h6Idm2gm8s+MknF/6bGNeLWZMiVGuVp+Bi0b9t10C6h0aszyAcOUMuVQ30Pyf4S4GDqafqj7PdgUOH+kfSf3FKa21gKjG1SW/70yWtyV+SIye2Ge/iCipvEXnVPLWlYIXGtu7jMVenzNFDahqbIKKbjdcW5yOvpwPmI+ZD5GKaC0JaEUHU1d+O1JYLgaVyDLTYJTHEzgAS2jEKfokK/KAhTqN+22iBcsNXsgTUQKhezhmlnBlwj9OqnWMLAuGcikCagDzMTwYzrM+fB2+Z5wQR9gU18XfeQ71EVmPRBhJPC8xXAORH75r3UB+LwV6yv2KelvQhbOvOxWoIJgPWUDH95zLf/sFL3bnesc6tC2gL5SVrmQecLVmvfxzbSs2DcXqJf9bh9PNi4bzCGNwXYeHBIpzEdpglpNgnbKM/C1ZZeEr3/w+96AGH/H7K/8ztT8E3DL++OKnCENibrR6kusqDJyrS+ne+7vryHnvSylkACq87/2IWZJ2s7ZDQgDLa3N97BNKLZeb6S
*/