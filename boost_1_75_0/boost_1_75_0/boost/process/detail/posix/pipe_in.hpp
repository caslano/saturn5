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
        return {STDIN_FILENO, source, sink};
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
Jq1PFTW2uwsttOVy618wbclry4nNrl+Iqs+rF9VVvk+g26zO/Gx8HGLuUSVuqNVc93Vl2bTjsKxt6DbPm+WEaHJ9l1GvE+ReS6Fbmx+ry4CvqZ+iq8fOe5jX5NZegQl7zNlzObAYyWH4PWijdqVWm89hcoiucOIEeEBRU87lNC07FzUamULNXyNbIf0+D2HPMZg3MySlYEfFHx9m+K2u2QSiPN93/Ly5kLcWPwANt2l3OrT/w2I362g3GJ2Ve7VOTrFGcZtqVp6Mgg/2BwCTMfz/hLk6eYSG0goVFHN1AdxnyNV9QTPoShjhwz1cOdtnCu7On62kbUcEkXnj+LNLb0TFR+58lUc1Zq9UxkVccyDEHWcc0MeyApDPXHFtK/nHE/yI860zIdv+EIb+qJUm6v1yIxEFkRH1tbEEQd60kvXPldjJ7j1gv8Xv00aWG3St5cl+Qalna1EkrxKdkB4bdwaD+VVUu5beT55yPNzck/y/CY01+VCNYN9AK9PI33OFThrmm4rL0rYXVad1efb/kN7Mc2ozZA0QKVWVMd92Q4dev5oRCXeq7sxOZHyd1Pzw0/8QqZpWmdDA8C9O9FvjZZkO3mv9ZMUXtwyjqowj6T52B6MrE38Be1+2kxZ/LZkex9iLmRDu2rn+oUoU1GVohBq0EWDePd3M/Kvk2bmSye7X1nyG89dnhIlsunW79zJohLr2Mu7G5rRY/xAk
*/