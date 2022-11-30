// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_WINDOWS_INITIALIZERS_ASYNC_OUT_HPP
#define BOOST_PROCESS_WINDOWS_INITIALIZERS_ASYNC_OUT_HPP

#include <boost/winapi/process.hpp>
#include <boost/winapi/handles.hpp>
#include <boost/winapi/handle_info.hpp>
#include <boost/winapi/error_codes.hpp>
#include <boost/asio/read.hpp>
#include <boost/process/detail/handler_base.hpp>
#include <boost/process/detail/used_handles.hpp>
#include <boost/process/detail/windows/asio_fwd.hpp>

#include <istream>
#include <memory>
#include <exception>
#include <future>


namespace boost { namespace process { namespace detail { namespace windows {


template <typename Executor>
inline void apply_out_handles(Executor &e, void* handle, std::integral_constant<int, 1>, std::integral_constant<int, -1>)
{
    boost::winapi::SetHandleInformation(handle,
            boost::winapi::HANDLE_FLAG_INHERIT_,
            boost::winapi::HANDLE_FLAG_INHERIT_);

    e.startup_info.hStdOutput = handle;
    e.startup_info.dwFlags   |= ::boost::winapi::STARTF_USESTDHANDLES_;
    e.inherit_handles = true;
}

template <typename Executor>
inline void apply_out_handles(Executor &e, void* handle, std::integral_constant<int, 2>, std::integral_constant<int, -1>)
{
    boost::winapi::SetHandleInformation(handle,
            boost::winapi::HANDLE_FLAG_INHERIT_,
            boost::winapi::HANDLE_FLAG_INHERIT_);


    e.startup_info.hStdError = handle;
    e.startup_info.dwFlags  |= ::boost::winapi::STARTF_USESTDHANDLES_;
    e.inherit_handles = true;
}

template <typename Executor>
inline void apply_out_handles(Executor &e, void* handle, std::integral_constant<int, 1>, std::integral_constant<int, 2>)
{
    boost::winapi::SetHandleInformation(handle,
            boost::winapi::HANDLE_FLAG_INHERIT_,
            boost::winapi::HANDLE_FLAG_INHERIT_);

    e.startup_info.hStdOutput = handle;
    e.startup_info.hStdError  = handle;
    e.startup_info.dwFlags   |= ::boost::winapi::STARTF_USESTDHANDLES_;
    e.inherit_handles = true;
}

template<int p1, int p2, typename Buffer>
struct async_out_buffer : ::boost::process::detail::windows::handler_base_ext,
                          ::boost::process::detail::windows::require_io_context
{
    Buffer & buf;

    std::shared_ptr<boost::process::async_pipe> pipe;


    async_out_buffer(Buffer & buf) : buf(buf)
    {
    }
    template <typename Executor>
    inline void on_success(Executor&)
    {
        auto pipe_ = this->pipe;
        boost::asio::async_read(*pipe_, buf,
                [pipe_](const boost::system::error_code&, std::size_t){});
        std::move(*pipe_).sink().close();
        this->pipe       = nullptr;

    }

    template<typename Executor>
    void on_error(Executor &, const std::error_code &) const
    {
        std::move(*pipe).sink().close();
    }

    template <typename WindowsExecutor>
    void on_setup(WindowsExecutor &exec)
    {
        if (!pipe)
            pipe = std::make_shared<boost::process::async_pipe>(get_io_context(exec.seq));
        apply_out_handles(exec, std::move(*pipe).sink().native_handle(),
                std::integral_constant<int, p1>(), std::integral_constant<int, p2>());
    }
};



template<int p1, int p2, typename Type>
struct async_out_future : ::boost::process::detail::windows::handler_base_ext,
                          ::boost::process::detail::windows::require_io_context,
                          ::boost::process::detail::uses_handles
{
    std::shared_ptr<boost::process::async_pipe> pipe;
    std::shared_ptr<std::promise<Type>> promise = std::make_shared<std::promise<Type>>();
    std::shared_ptr<boost::asio::streambuf> buffer = std::make_shared<boost::asio::streambuf>();

    ::boost::winapi::HANDLE_ get_used_handles() const
    {
        return std::move(*pipe).sink().native_handle();
    }


    async_out_future(std::future<Type> & fut)
    {
        fut = promise->get_future();
    }
    template <typename Executor>
    inline void on_success(Executor&)
    {
        auto pipe_    = this->pipe;
        auto buffer_  = this->buffer;
        auto promise_ = this->promise;
        std::move(*pipe_).sink().close();
        boost::asio::async_read(*pipe_, *buffer_,
                [pipe_, buffer_, promise_](const boost::system::error_code& ec, std::size_t)
                {
                    if (ec && (ec.value() != ::boost::winapi::ERROR_BROKEN_PIPE_))
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
        this->pipe    = nullptr;
        this->buffer  = nullptr;
        this->promise = nullptr;


    }

    template<typename Executor>
    void on_error(Executor &, const std::error_code &) const
    {
        std::move(*pipe).sink().close();
    }

    template <typename WindowsExecutor>
    void on_setup(WindowsExecutor &exec)
    {
        if (!pipe)
            pipe = std::make_shared<boost::process::async_pipe>(get_io_context(exec.seq));

        apply_out_handles(exec, std::move(*pipe).sink().native_handle(),
                std::integral_constant<int, p1>(), std::integral_constant<int, p2>());
    }
};


}}}}

#endif

/* async_out.hpp
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
*/