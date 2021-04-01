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
gT7S8c4Z3D3M8ib8coYRCBvc+Twz3qKVQSePTtpuw5kVy4Zt76C62k/Sc+b3yFiHqm4RmBOGmHUJtabAC6nEUCPa5jISQxvln/MsZrGHzYdq/fs47uQtFOujRkEfZ6Ymk9cH9k0lRNQXtUq2vbZMwSCVQ0VGEh5BD8bEIQmQeJj1YQcQUARbACm7tHTATeMi2nH74VcT1YkcKOzY5XnKQ7OoRQ/O1G/JBL3Ft0HMUOTJCbiqezKGxQ2pUAuk73kpX5vVatv59SCkS1IeJsnGUgDC9lnFOJToprjotd54dicj6zW66Byr0RTJZtAQ1DmQGldquMGwWqXPQcid1RpWQR4V+J4Tuu65pDj/2uTTgx0eg2QQeWQnpdEiVKl/ehBhBbfnTGmY5UyhXm+09BkFP5X92j5YcVuNvUnpc2gjG4nADDbY18eJFUytJGAUK6NwY2JRxe8sbGI2E0embxHEZgpcf4jMhhMpgd/cVkMHedPbhXFHK0CJARHl3pv068Br02/1VOa7z6wIgoq9qbWMR3aXlXZWOgagbn4H94xSvzWVPWlkFYZU93glaA==
*/