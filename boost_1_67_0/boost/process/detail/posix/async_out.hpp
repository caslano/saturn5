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