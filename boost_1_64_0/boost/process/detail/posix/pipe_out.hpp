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
hIJbBAKx1IcZJ5ahVmLPENVSkd8oPQAPXT7GHrBEF4QpMRCXxVb1Go5p7tVzjpampf+kwU0SO3ivyyBm1sUDm033jTjSAv1KJyQDK9H+Z/BVqy1Am/lN31Bnw8+oG3AhcrT4SC/Veng8qkEv+Kkxipwj/oUt2A8hTTXlN3PGBTVZ9rUxzfnbaHeZUvmSutTm7oK7lyjy9JEL4ATGDlB+iekUmx6B40U7AypFUf69oSppt6uCxJxjIfw44zxfy7dCCAJSlqTaC6Rcu2kVLFuLmXiMmo4IUmYj3q/kYQ6huJcvNBPl7istskEAGkimKtFQK/WgV7Lx46AWgPwTbtPUYm7jn+yOwmtfGZVh8ZDi69HAlHoH2YdS7B9+Sw8o6D/DzrPv16fecnlV1XXTaZeHgM6YpU4FXfWTfYEuAQ1IrsLT0V6yVr/a2kvUytiy6gRqxLp5akz4/0LttAgqP+WCEE1F/QMUprJEO79/z6TL54HjgFDSZ2f7Tcc7oEtGyKH+QhH4eqV6XMwnBLeIMCo8zJcJkPbgCdpnDcZxVuUU8pU+6GUzIP79gp0++g==
*/