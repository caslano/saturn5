// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_WINDOWS_INITIALIZERS_ASYNC_IN_HPP
#define BOOST_PROCESS_WINDOWS_INITIALIZERS_ASYNC_IN_HPP

#include <boost/winapi/process.hpp>
#include <boost/winapi/handles.hpp>
#include <boost/winapi/handle_info.hpp>
#include <boost/winapi/error_codes.hpp>

#include <boost/asio/write.hpp>
#include <boost/process/detail/handler_base.hpp>
#include <boost/process/detail/used_handles.hpp>
#include <boost/process/detail/windows/async_handler.hpp>
#include <boost/process/detail/windows/asio_fwd.hpp>
#include <boost/process/async_pipe.hpp>
#include <memory>
#include <future>

namespace boost { namespace process { namespace detail { namespace windows {


template<typename Buffer>
struct async_in_buffer : ::boost::process::detail::windows::handler_base_ext,
                         ::boost::process::detail::windows::require_io_context,
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

    ::boost::winapi::HANDLE_ get_used_handles() const
    {
        return std::move(*pipe).source().native_handle();
    }

    async_in_buffer(Buffer & buf) : buf(buf)
    {
    }
    template <typename Executor>
    inline void on_success(Executor&)
    {
        auto pipe_ = this->pipe;

        if (this->promise)
        {
            auto promise_ = this->promise;

            boost::asio::async_write(*pipe_, buf,
                [promise_](const boost::system::error_code & ec, std::size_t)
                {
                    if (ec && (ec.value() != ::boost::winapi::ERROR_BROKEN_PIPE_))
                    {
                        std::error_code e(ec.value(), std::system_category());
                        promise_->set_exception(std::make_exception_ptr(process_error(e)));
                    }
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
        ::boost::winapi::CloseHandle(pipe->native_source());
    }

    template <typename WindowsExecutor>
    void on_setup(WindowsExecutor &exec)
    {
        if (!pipe)
            pipe = std::make_shared<boost::process::async_pipe>(get_io_context(exec.seq));

        ::boost::winapi::HANDLE_ source_handle = std::move(*pipe).source().native_handle();

        boost::winapi::SetHandleInformation(source_handle,
                boost::winapi::HANDLE_FLAG_INHERIT_,
                boost::winapi::HANDLE_FLAG_INHERIT_);

        exec.startup_info.hStdInput = source_handle;
        exec.startup_info.dwFlags  |= boost::winapi::STARTF_USESTDHANDLES_;
        exec.inherit_handles = true;
    }
};


}}}}

#endif

/* async_in.hpp
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
*/