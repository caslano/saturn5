// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_WINDOWS_INITIALIZERS_PIPE_IN_HPP
#define BOOST_PROCESS_WINDOWS_INITIALIZERS_PIPE_IN_HPP

#include <boost/winapi/process.hpp>
#include <boost/winapi/handles.hpp>
#include <boost/process/detail/used_handles.hpp>
#include <boost/process/detail/handler_base.hpp>

namespace boost { namespace process { namespace detail { namespace windows {

struct pipe_in : public ::boost::process::detail::handler_base, ::boost::process::detail::uses_handles
{
    ::boost::winapi::HANDLE_ handle;

    ::boost::winapi::HANDLE_ get_used_handles() const { return handle; }

    pipe_in(::boost::winapi::HANDLE_ handle) : handle(handle) {}

    template<typename T> //async_pipe
    pipe_in(T & p) : handle(p.native_source())
    {
        p.assign_source(::boost::winapi::INVALID_HANDLE_VALUE_);
    }

    template <class WindowsExecutor>
    void on_setup(WindowsExecutor &e) const
    {
        boost::winapi::SetHandleInformation(handle,
                boost::winapi::HANDLE_FLAG_INHERIT_,
                boost::winapi::HANDLE_FLAG_INHERIT_);

        e.startup_info.hStdInput = handle;
        e.startup_info.dwFlags  |= boost::winapi::STARTF_USESTDHANDLES_;
        e.inherit_handles = true;
    }
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

class async_pipe;

struct async_pipe_in : public pipe_in
{
    async_pipe &pipe;

    template<typename AsyncPipe>
    async_pipe_in(AsyncPipe & p) : pipe_in(p.native_source()), pipe(p)
    {
    }

    template<typename Pipe, typename Executor>
    static void close(Pipe & pipe, Executor &)
    {
        boost::system::error_code ec;
        std::move(pipe).source().close(ec);
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

/* pipe_in.hpp
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
*/