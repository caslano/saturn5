// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_POSIX_ASYNC_IN_HPP
#define BOOST_PROCESS_DETAIL_POSIX_ASYNC_IN_HPP

#include <boost/process/detail/handler_base.hpp>
#include <boost/process/detail/posix/async_handler.hpp>
#include <boost/asio/write.hpp>
#include <boost/process/async_pipe.hpp>
#include <memory>
#include <future>
#include <boost/process/detail/used_handles.hpp>
#include <array>

namespace boost { namespace process { namespace detail { namespace posix {


template<typename Buffer>
struct async_in_buffer : ::boost::process::detail::posix::handler_base_ext,
                         ::boost::process::detail::posix::require_io_context,
                         ::boost::process::detail::uses_handles
{
    Buffer & buf;

    std::shared_ptr<std::promise<void>> promise;
    async_in_buffer operator>(std::future<void> & fut)
    {
        promise = std::make_shared<std::promise<void>>();
        fut = promise->get_future(); return std::move(*this);
    }


    std::shared_ptr<boost::process::async_pipe> pipe;

    async_in_buffer(Buffer & buf) : buf(buf)
    {
    }
    template <typename Executor>
    inline void on_success(Executor)
    {
        auto  pipe_              = this->pipe;
        if (this->promise)
        {
            auto promise_ = this->promise;

            boost::asio::async_write(*pipe_, buf,
                [pipe_, promise_](const boost::system::error_code & ec, std::size_t)
                {
                    if (ec && (ec.value() != EBADF) && (ec.value() != EPERM) && (ec.value() != ENOENT))
                    {
                        std::error_code e(ec.value(), std::system_category());
                        promise_->set_exception(std::make_exception_ptr(process_error(e)));
                    }
                    else
                        promise_->set_value();
                });
        }
        else
            boost::asio::async_write(*pipe_, buf,
                [pipe_](const boost::system::error_code&, std::size_t){});

        std::move(*pipe_).source().close();

        this->pipe = nullptr;
    }

    template<typename Executor>
    void on_error(Executor &, const std::error_code &) const
    {
        std::move(*pipe).source().close();
    }

    template<typename Executor>
    void on_setup(Executor & exec)
    {
        if (!pipe)
            pipe = std::make_shared<boost::process::async_pipe>(get_io_context(exec.seq));
    }

    std::array<int, 3> get_used_handles()
    {
        if (pipe)
            return {STDIN_FILENO, pipe->native_source(), pipe->native_sink()};
        else  //if pipe is not constructed, limit_ds is invoked before -> this also means on_exec_setup gets invoked before.
            return {STDIN_FILENO, STDIN_FILENO, STDIN_FILENO};
    }


    template <typename Executor>
    void on_exec_setup(Executor &exec)
    {
        if (::dup2(pipe->native_source(), STDIN_FILENO) == -1)
            exec.set_error(::boost::process::detail::get_last_error(), "dup2() failed");

        if (pipe->native_source() != STDIN_FILENO)
            ::close(pipe->native_source());
        ::close(pipe->native_sink());
    }
};


}}}}

#endif

/* async_in.hpp
kIabIA+p2dlyXLdHqf5qAA0VFgNnqUGUshYF9JvUfvSOyqH619l3wQVEJQ0AMQl0ERmHTJ/KRpa9H7LpUXgze0uQUZhQiS5Sp87Tvq+BsCffDgNPOVds0N+xCr8vB11stlgJxyTHzzIR1AfH2e20GBdL9CHR/iHbMUVBSt4BmDxcjfnu8rI5czU1FEps3wu5Q6lcMH7nHnoJUkhnvC/89oYTMEs8IdFzMbPp7HSlhhcgdRGKEuF2mkNNF2oxvcjhy04p98lN5ClfQoK7mkpruUsmQp15VKkPgHZqASzH75T+eM6ThNvd/++8j2HaviLCvp75HiEyyx35FKqRWeHd+CNwWWfeUJ5mrnsBs7TILWBYMHu9bxOd4KOQ6+sZChmsE2zTYJjzuYqom5h850L+YJsut87nGZFscTxxOldY8bWrkJgSjk+Zwh/71/DAgTmfoJy3sB3wIv65WnPAm296f6g3g+J/o5VN1BScog99wZlASAj3z9GUTTH+vwxTxmff0sCv/ih7xb+pghzK6jRdEnMjJI3DSMLVhM/UPZkJDj4X3buB3tCOX979fw==
*/