// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_WINDOWS_PIPE_OUT_HPP
#define BOOST_PROCESS_WINDOWS_PIPE_OUT_HPP

#include <boost/winapi/process.hpp>
#include <boost/winapi/handles.hpp>
#include <boost/process/detail/used_handles.hpp>
#include <boost/process/detail/handler_base.hpp>

namespace boost { namespace process { namespace detail { namespace windows {



template<int p1, int p2>
struct pipe_out : public ::boost::process::detail::handler_base, ::boost::process::detail::uses_handles
{
    ::boost::winapi::HANDLE_ handle;

    ::boost::winapi::HANDLE_ get_used_handles() const { return handle; }

    pipe_out(::boost::winapi::HANDLE_ handle) : handle(handle) {}
    template<typename T>
    pipe_out(T & p) : handle(p.native_sink())
    {
        p.assign_sink(::boost::winapi::INVALID_HANDLE_VALUE_);
    }

    template<typename WindowsExecutor>
    void on_setup(WindowsExecutor &e) const;

    template<typename WindowsExecutor>
    void on_error(WindowsExecutor &, const std::error_code &) const
    {
        ::boost::winapi::CloseHandle(handle);
    }

    template<typename WindowsExecutor>
    void on_success(WindowsExecutor &) const
    {
        ::boost::winapi::CloseHandle(handle);
    }
};

template<>
template<typename WindowsExecutor>
void pipe_out<1,-1>::on_setup(WindowsExecutor &e) const
{
    boost::winapi::SetHandleInformation(handle,
            boost::winapi::HANDLE_FLAG_INHERIT_,
            boost::winapi::HANDLE_FLAG_INHERIT_);

    e.startup_info.hStdOutput = handle;
    e.startup_info.dwFlags   |= ::boost::winapi::STARTF_USESTDHANDLES_;
    e.inherit_handles = true;
}

template<>
template<typename WindowsExecutor>
void pipe_out<2,-1>::on_setup(WindowsExecutor &e) const
{
    boost::winapi::SetHandleInformation(handle,
            boost::winapi::HANDLE_FLAG_INHERIT_,
            boost::winapi::HANDLE_FLAG_INHERIT_);


    e.startup_info.hStdError = handle;
    e.startup_info.dwFlags  |= ::boost::winapi::STARTF_USESTDHANDLES_;
    e.inherit_handles = true;
}

template<>
template<typename WindowsExecutor>
void pipe_out<1,2>::on_setup(WindowsExecutor &e) const
{
    boost::winapi::SetHandleInformation(handle,
            boost::winapi::HANDLE_FLAG_INHERIT_,
            boost::winapi::HANDLE_FLAG_INHERIT_);

    e.startup_info.hStdOutput = handle;
    e.startup_info.hStdError  = handle;
    e.startup_info.dwFlags   |= ::boost::winapi::STARTF_USESTDHANDLES_;
    e.inherit_handles = true;
}

template<int p1, int p2>
struct async_pipe_out : public pipe_out<p1, p2>
{
    async_pipe &pipe;
    template<typename AsyncPipe>
    async_pipe_out(AsyncPipe & p) : pipe_out<p1, p2>(p.native_sink()), pipe(p)
    {
    }

    template<typename Pipe, typename Executor>
    static void close(Pipe & pipe, Executor &)
    {
        boost::system::error_code ec;
        std::move(pipe).sink().close(ec);
    }

    template<typename Executor>
    void on_error(Executor & exec, const std::error_code &)
    {
        close(pipe, exec);
    }

    template<typename Executor>
    void on_success(Executor &exec)
    {
        close(pipe, exec);
    }
};

}}}}

#endif

/* pipe_out.hpp
x3YZnGk+d3yhLjF0G21p4nTwi9wvWH4/rwe/plJGCtgqTof0CgkAINMOwgUDvCzDDXRM0cMKD0/9f/fBC8X7qhP+z+139v80ZQsK/iML9+82O9DnYQ8pt+b3RNgUb3icuDCVhz6+7/xDPCf9rK3uOxmJwpQGowlWrlk5Q7vmqrVu/BFsq5T0YsfuFJfYrCZ7mI1qJouOubhHVkvDcbFikpBDkmS2gOqsCLviCotN/TFU1fZPt8JxnfoUiqnzKE2wyZ7f/tRau9Ve156LpSfkcvd5nd/98u5GwfempKgD/ZaYvZ0F3lAGbRK2nadme6FjHStw7rrO4R81gjco2KUoGPcluTFSMccDd3vbe/E2JTb95AzSK1kq0N6P6CwxdhxnhbI3cgmrAp/byFQyUjVcHKeueC81LELLwYoBjtCyBa/1VUTS/fhEsOv4Vz1dFTOl6We9r7rupKO240coBAn12OTLNsEcNrAa0bmEDPyF/FFX5QNgp4+B8ENrWGmdW0Dlm1iX2AeJDC40jzNzO8JLELK4SAYSErFD8S9u4NqPHULsYBWmTM7oqX3MLEuzYKUDKCwm49xkEjD4HJHFjQuD/kDH3OzbgCPH0ZHSDk8saHOUFZYBokofAvM8jin+gol8eByBDRxebsglr+oaoThWz4gMCXMJp2LENRfeXRPtXew/CQPw/Lj3r1w7jtGqTO+f6T8zVHBFbx5L5S0q
*/