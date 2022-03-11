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