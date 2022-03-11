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