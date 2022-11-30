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
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
*/