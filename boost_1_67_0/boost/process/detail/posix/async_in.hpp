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