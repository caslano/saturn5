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
oUrJgbIl062VCadHucIGNzy9rpLMO+a9jGHEYUqYqQScpEwv2L4BUspYkJ9VH3SOSQFU4W+DMd+/eqcIexVzEB6iN2fr/M0/e6XXLZm4/dljZj1Nye5p0XRDLcHJnPVgbSlSCAMqjiX7+iMn4l3srkgsS4+d8gcWmiyZZ/7Plv2ZDzEPDGbVdNfnPfgX+F5n1xd4k8DJltKXRN8Cux/NO6/DX2vVHECc2vbsrrrIdWse88FdoEt9y2cEDIRO94yNEINsNbyg0uQUD8TdMYgTeXBoemlAykSjl2nOz2fywE7luXoNnDNZaxlD5MO0gIleUkMARCMxX9QCQ85AH6PMMARj+Ky88VHOn/Sx6WXqywEFjBL9oGc18LAVQoAXrTGVl4qT4bn6VS1w+QrIt9MXZvd6iZBHx0Tt/vUOem9sWIb4fbdlr20vR5gBJg1aLXD+5Y1D0HkYiODiXQV9BfO6QnN0TfC0zBGTPQP0L/wEF0z2TPa09oz+mTWxzvg7xiNAwMYapvDrjjAxSQCtmxRJPd5fPN9QM4gwICjz/Eh31PUar7yN08x+nagSZI/YCCs9FH8TlIa5hZHvvNjJrVg6DhQDbSGthMpijzpWxaUhUd81CDacrOOXP0N0DWEDdKXxJSZqeEwxzTb9+VShZyfRMn3oY+7M5i6iZnFZQgGzrzP6JDbekvMLK/Oa4fxWFl0pN+ER9phQZoRO10rr
*/