// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_POSIX_PIPE_OUT_HPP
#define BOOST_PROCESS_DETAIL_POSIX_PIPE_OUT_HPP

#include <boost/process/pipe.hpp>
#include <boost/process/detail/posix/handler.hpp>
#include <unistd.h>

namespace boost { namespace process { namespace detail { namespace posix {

template<int p1, int p2>
struct pipe_out : handler_base_ext
{
    int sink;
    int source; //opposite end

    pipe_out(int sink, int source) : sink(sink), source(source) {}

    template<typename T>
    pipe_out(T & p) : sink(p.native_sink()), source(p.native_source())
    {
        p.assign_sink(-1);
    }

    template<typename Executor>
    void on_error(Executor &, const std::error_code &) const
    {
        ::close(sink);
    }

    template<typename Executor>
    void on_success(Executor &) const
    {
        ::close(sink);
    }

    template <typename Executor>
    void on_exec_setup(Executor &e) const;
};

template<>
template<typename Executor>
void pipe_out<1,-1>::on_exec_setup(Executor &e) const
{
    if (::dup2(sink, STDOUT_FILENO) == -1)
         e.set_error(::boost::process::detail::get_last_error(), "dup2() failed");

    if (sink != STDOUT_FILENO)
        ::close(sink);
    ::close(source);
}

template<>
template<typename Executor>
void pipe_out<2,-1>::on_exec_setup(Executor &e) const
{
    if (::dup2(sink, STDERR_FILENO) == -1)
         e.set_error(::boost::process::detail::get_last_error(), "dup2() failed");

    if (sink != STDOUT_FILENO)
        ::close(sink);
    ::close(source);
}

template<>
template<typename Executor>
void pipe_out<1,2>::on_exec_setup(Executor &e) const
{
    if (::dup2(sink, STDOUT_FILENO) == -1)
         e.set_error(::boost::process::detail::get_last_error(), "dup2() failed");
    if (::dup2(sink, STDERR_FILENO) == -1)
         e.set_error(::boost::process::detail::get_last_error(), "dup2() failed");
    if ((sink != STDOUT_FILENO) && (sink != STDERR_FILENO))
        ::close(sink);
}

class async_pipe;

template<int p1, int p2>
struct async_pipe_out : public pipe_out<p1, p2>
{
    async_pipe &pipe;
    template<typename AsyncPipe>
    async_pipe_out(AsyncPipe & p) : pipe_out<p1, p2>(p.native_sink(), p.native_source()), pipe(p)
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