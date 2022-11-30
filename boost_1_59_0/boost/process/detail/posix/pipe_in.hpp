// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_POSIX_PIPE_IN_HPP
#define BOOST_PROCESS_POSIX_PIPE_IN_HPP

#include <boost/process/pipe.hpp>
#include <boost/process/detail/posix/handler.hpp>
#include <unistd.h>
#include <boost/process/detail/used_handles.hpp>
#include <array>

namespace boost { namespace process { namespace detail { namespace posix {

struct pipe_in : handler_base_ext, ::boost::process::detail::uses_handles
{
    int source;
    int sink; //opposite end

    pipe_in(int sink, int source) : source(source), sink(sink) {}

    std::array<int, 3> get_used_handles()
    {
        return {{STDIN_FILENO, source, sink}};
    }


    template<typename T>
    pipe_in(T & p) : source(p.native_source()), sink(p.native_sink())
    {
        p.assign_source(-1);
    }

    template<typename Executor>
    void on_error(Executor &, const std::error_code &) const
    {
        ::close(source);
    }

    template<typename Executor>
    void on_success(Executor &) const
    {
        ::close(source);
    }

    template <class Executor>
    void on_exec_setup(Executor &e) const
    {
        if (::dup2(source, STDIN_FILENO) == -1)
             e.set_error(::boost::process::detail::get_last_error(), "dup2() failed");
        if (source != STDIN_FILENO)
            ::close(source);

        ::close(sink);
    }

};

class async_pipe;

struct async_pipe_in : public pipe_in
{
    async_pipe &pipe;

    template<typename AsyncPipe>
    async_pipe_in(AsyncPipe & p) : pipe_in(p.native_sink(), p.native_source()), pipe(p)
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