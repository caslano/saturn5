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
jphP0/ltQadRXlQHeNT+q98PeYLHYfybHhyRT8QFBsg/s/Xfyut9rGa+fsBeFwSCz1cfhdtBVSW5rGU8bTcvXQhuq3YFF0goB2kPFyGVWUPEWi2GsJDhXyC1ErAUORDwKtcuyMKQJpR8zA4j6LZvlZRRN6pkAPphFTi5J37dSNo2V1379Yr1Sr/aNbGVp8bhfqs+7+LdDT+wFVElVjg2T3J2ah5ralvaWR4UQtlELM7Q9tOSJXg1DkhE3ktD6avUz3WHhuevGojIfQe8EytpdpXV0ZefNzvxwj89OIl2Nev4KgLoLpiBG/u125kYJuUpmN20SQR4k7Qsy4l3YEDpCAp9CiJUfzFc4Lg1YdkJokipNL352oefLv0X8y/4v77gHhRJbHxOj8oeYtnVqFf6TUw2+K2euE6KmZjMsrYtO33XP+VT6dGHq67QWsLtM5RHjF4M6asMdRopb3wW3BjjhFQD2qoh+ZLt2uhtXZRHdyT4t35Unc9VgyKu74laQx/hHGsROiIaN+83ZeSmn0+QBOWw+9daJA+JtA5Rjw+gVjhEI8tqWvPV3N8QkoAwkR5sCj8xgVgfkmuJYqjRkC4jJ6lAbW5M7JIZNc1aux59clQsTEZ+/xSI5Yl/pYHkrxGYT7y9+fal6A1Pprz4CUpAeAM8FjBxC5NxKf4bYWcV1AaUQNFSChRfKFK8OBQrUKBocJdS3KXF3Z1gLU6K
*/