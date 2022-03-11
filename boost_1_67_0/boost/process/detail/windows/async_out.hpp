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