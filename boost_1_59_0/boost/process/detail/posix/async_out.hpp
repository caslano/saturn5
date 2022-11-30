// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_POSIX_ASYNC_OUT_HPP
#define BOOST_PROCESS_DETAIL_POSIX_ASYNC_OUT_HPP


#include <boost/process/detail/posix/handler.hpp>
#include <boost/asio/posix/stream_descriptor.hpp>
#include <boost/asio/read.hpp>
#include <boost/process/async_pipe.hpp>
#include <istream>
#include <memory>
#include <exception>
#include <future>
#include <array>
#include <boost/process/detail/used_handles.hpp>

namespace boost { namespace process { namespace detail { namespace posix {


inline int apply_out_handles(int handle, std::integral_constant<int, 1>, std::integral_constant<int, -1>)
{
    return ::dup2(handle, STDOUT_FILENO);
}

inline int apply_out_handles(int handle, std::integral_constant<int, 2>, std::integral_constant<int, -1>)
{
    return ::dup2(handle, STDERR_FILENO);
}

inline int apply_out_handles(int handle, std::integral_constant<int, 1>, std::integral_constant<int, 2>)
{
    if (::dup2(handle, STDOUT_FILENO) == -1)
        return -1;
    if (::dup2(handle, STDERR_FILENO) == -1)
        return -1;

    return 0;
}

template<int p1, int p2, typename Buffer>
struct async_out_buffer : ::boost::process::detail::posix::handler_base_ext,
                          ::boost::process::detail::posix::require_io_context,
                          ::boost::process::detail::uses_handles
{
    Buffer & buf;

    std::shared_ptr<boost::process::async_pipe> pipe;

    std::array<int, 4> get_used_handles()
    {
        const auto pp1 = p1 != -1 ? p1 : p2;
        const auto pp2 = p2 != -1 ? p2 : p1;

        if (pipe)
            return {pipe->native_source(), pipe->native_sink(), pp1, pp2};
        else  //if pipe is not constructed, limit_ds is invoked before -> this also means on_exec_setup gets invoked before.
            return {pp1, pp2, pp1, pp2};
    }


    async_out_buffer(Buffer & buf) : buf(buf)
    {
    }

    template <typename Executor>
    inline void on_success(Executor &exec)
    {
        auto  pipe              = this->pipe;
        boost::asio::async_read(*pipe, buf,
                [pipe](const boost::system::error_code&, std::size_t){});

        this->pipe = nullptr;
        std::move(*pipe).sink().close();
    }

    template<typename Executor>
    void on_error(Executor &, const std::error_code &) const
    {
        std::move(*pipe).sink().close();
    }

    template<typename Executor>
    void on_setup(Executor & exec)
    {
        pipe = std::make_shared<boost::process::async_pipe>(get_io_context(exec.seq));
    }


    template <typename Executor>
    void on_exec_setup(Executor &exec)
    {
        int res = apply_out_handles(pipe->native_sink(),
                      std::integral_constant<int, p1>(), std::integral_constant<int, p2>());
        if (res == -1)
            exec.set_error(::boost::process::detail::get_last_error(), "dup2() failed");

        ::close(pipe->native_sink());
        ::close(pipe->native_source());

    }
};




template<int p1, int p2, typename Type>
struct async_out_future : ::boost::process::detail::posix::handler_base_ext,
                          ::boost::process::detail::posix::require_io_context
{
    std::shared_ptr<std::promise<Type>> promise = std::make_shared<std::promise<Type>>();

    std::shared_ptr<boost::asio::streambuf> buffer = std::make_shared<boost::asio::streambuf>();

    std::shared_ptr<boost::process::async_pipe> pipe;

    async_out_future(std::future<Type> & fut)
    {
        fut = promise->get_future();
    }
    template <typename Executor>
    inline void on_success(Executor &)
    {
        auto pipe_ = this->pipe;

        auto buffer_  = this->buffer;
        auto promise_ = this->promise;

        boost::asio::async_read(*pipe_, *buffer_,
                [pipe_, buffer_, promise_](const boost::system::error_code& ec, std::size_t)
                {
                    if (ec && (ec.value() != ENOENT))
                    {
                        std::error_code e(ec.value(), std::system_category());
                        promise_->set_exception(std::make_exception_ptr(process_error(e)));
                    }
                    else
                    {
                        std::istream is (buffer_.get());
                        Type arg;
                        if (buffer_->size() > 0)
                        {
                            arg.resize(buffer_->size());
                            is.read(&*arg.begin(), buffer_->size());
                        }
                        promise_->set_value(std::move(arg));
                    }
                });

        std::move(*pipe_).sink().close();
        this->pipe = nullptr;
    }

    template<typename Executor>
    void on_error(Executor &, const std::error_code &) const
    {
        std::move(*pipe).sink().close();
    }

    template<typename Executor>
    void on_setup(Executor & exec)
    {
        pipe = std::make_shared<boost::process::async_pipe>(get_io_context(exec.seq));
    }

    template <typename Executor>
    void on_exec_setup(Executor &exec)
    {

        int res = apply_out_handles(pipe->native_sink(),
                      std::integral_constant<int, p1>(), std::integral_constant<int, p2>());
        if (res == -1)
            exec.set_error(::boost::process::detail::get_last_error(), "dup2() failed");

        ::close(pipe->native_sink());
        ::close(pipe->native_source());
    }

};

}}}}

#endif

/* async_out.hpp
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
*/