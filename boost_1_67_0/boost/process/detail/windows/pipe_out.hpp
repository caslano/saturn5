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
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
*/