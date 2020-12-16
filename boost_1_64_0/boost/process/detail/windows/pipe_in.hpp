// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_WINDOWS_INITIALIZERS_PIPE_IN_HPP
#define BOOST_PROCESS_WINDOWS_INITIALIZERS_PIPE_IN_HPP

#include <boost/winapi/process.hpp>
#include <boost/winapi/handles.hpp>
#include <boost/process/detail/used_handles.hpp>
#include <boost/process/detail/handler_base.hpp>

namespace boost { namespace process { namespace detail { namespace windows {

struct pipe_in : public ::boost::process::detail::handler_base, ::boost::process::detail::uses_handles
{
    ::boost::winapi::HANDLE_ handle;

    ::boost::winapi::HANDLE_ get_used_handles() const { return handle; }

    pipe_in(::boost::winapi::HANDLE_ handle) : handle(handle) {}

    template<typename T> //async_pipe
    pipe_in(T & p) : handle(p.native_source())
    {
        p.assign_source(::boost::winapi::INVALID_HANDLE_VALUE_);
    }

    template <class WindowsExecutor>
    void on_setup(WindowsExecutor &e) const
    {
        boost::winapi::SetHandleInformation(handle,
                boost::winapi::HANDLE_FLAG_INHERIT_,
                boost::winapi::HANDLE_FLAG_INHERIT_);

        e.startup_info.hStdInput = handle;
        e.startup_info.dwFlags  |= boost::winapi::STARTF_USESTDHANDLES_;
        e.inherit_handles = true;
    }
    template<typename WindowsExecutor>
    void on_error(WindowsExecutor &, const std::error_code &) const
    {
        ::boost::winapi::CloseHandle(handle);
    }

    template<typename WindowsExecutor>
    void on_success(WindowsExecutor &) const
    {
        ::boost::winapi::CloseHandle(handle);
    }
};

class async_pipe;

struct async_pipe_in : public pipe_in
{
    async_pipe &pipe;

    template<typename AsyncPipe>
    async_pipe_in(AsyncPipe & p) : pipe_in(p.native_source()), pipe(p)
    {
    }

    template<typename Pipe, typename Executor>
    static void close(Pipe & pipe, Executor &)
    {
        boost::system::error_code ec;
        std::move(pipe).source().close(ec);
    }

    template<typename Executor>
    void on_error(Executor & exec, const std::error_code &)
    {
        close(pipe, exec);
    }

    template<typename Executor>
    void on_success(Executor &exec)
    {
        close(pipe, exec);
    }
};


}}}}

#endif

/* pipe_in.hpp
nN5nUl3ilucja+FhzjAZ6+Y1cp8Es3sZlx/vQlt5r2uv7/4e9TDLZBxT4161z7eH15ehi90nc8XnEQnnRfUutL8OT0MJT1npl+UmyPmJ6t3o3L28HO31fUxX+HugPyQMff85vU3r9VonCx3fcqKTbtaprHQ2oHM1Ah2/OdMZgAX7JQWX8rZvJlK5OYibC9KHnbMs2LeUeV5U3z/2PvYWOsIYNGeT+ZsCR6D5mwJPyzML0e3kG3Lt63HvBPz8WfbjzG1osR9H3zsTva3lRC/CpWOOxwp0GodKPK4Z47HZ5NfZ+9ReheA575vjccwiHm9V8tyL/Y1cB3n4Gdyd+cNQWHZuN29xiEOnjUMnZO4ws47a/yD57w+1z9TYzgffpp1vWPk/6xtLW29R/4eY6n9ZS9Ztiq7zRDcaxihz6jJ93jx1FGa6jpK+7uoYz75vQYxnX/n9GM++8kmT/g8xnn3lRqr/0Fm9cPua2of4KnyqAn3nyu42icC59xEYvxGjyvZPojvO/pItz3qOp7L3tki+uwLfFp1NMqZtwzsYIxDLOaDKlt/A0vXMKulHf8wo3pc6uI0tUO8rmq7n6DeITiy1ULjHeDWT9rl/L1d9uL1lcMs5rVpgPotJksReqk5sqV59qCSvPjTkV6xjmBpQwsc3d7EetBa7fqyswtRawnTeVppzucYRsvnMRh2xhUs9vYL7N+ul6sWI3AMWY1XR6dHLNVad6FFX1kO/lBpL/klC3kCMY8hpQuvxZIDFu8sDYnWZMb3LoPOGt3Kjx43HDOPG+CqeeTWBa2Pensm1MW9XiTWdpxVrfTbF5UT3+/TByGikIv2trFiPvO0QWYBS+8mwExPdfueK/v22ptb7/fDP+/lZc8Wuv3qvTK/ZZWdmeX6/4SnRiyMMpfVapk2ti+lvzYhOCVkr4OxbOdv2opyREOxosuzVvK/hiX4++iHyHk2CruPJE8YyosuD0d123F2Sdi72ljbOdf2vSJV3irE3w5HGESqNjWOZgr7msQyCv4WezyvHVtyxTKy5zyiurccysXc4lom9g7FM7B2MZWL/t2MZaV8k3rd/d684YxnXszrf3xmAIDvlEF5AhjgyfFX9rPSegjB3vEdJ6Fzv8Ny4ebOh6J9078WQa+szmfBbP6NBal0xKXkyBcm9L26d6NQn3S33COKHZfuhxxFtxH4vaaXOxuAejlvIISmGsUpT0ftQ/KkcpfZqp47SY4fGYv+BXgOV+l7ZOy7vEvuDYl9a3mE3fHuRdDHum9Lz/+KmrO5PfS3XJfQ+KtoaqdOLiMjKMPT5vRo5gIxW3y35BoZCeQ/HXrz3cBx1Pveyfn+N9DHX+TwbzI3PJlTiRDz1uxPGPsjzg503fsqH8QhcAwegG1LNnZfGpc3wOp9eXfQW+ljkGfzwWq71eLqr6FTyqYGPbW3pVvlG+xNpeH9sxqg0tVvHso7ATfHrCHR1GxIs+x3SdF6aI3bplvWFDpe+Bymlp2nd+bqOMy19LMbH+GEuE/hh6FPVF/sN9kB7c/plHfTY7dPqDvPjfzmulriHSj7GU3dbNrOGrGWJ3mXV/7pEnXJ0oKv/dTL3S/XuKWebc4a56n/lfkkHLM68WnDH75662ufm1fVagTleMiYN576vIGqtIM1yrUDpHUSc/a85pUxjVeKG+SDXOkAnr2sAfau51wA6cZ+yNue9l/KwfsFts3B3nC5z/ataF7iCXJX1gTsfA02q8Z+NgSoY2xNjefDSppRRbQr5G7M0cR+tdTzzrfVYyD0fSp7CXOUp+oA9qnn2EftzbVx7iK9u6mNybexjTufa6H6ZSX+11vfco+Y3wpmYY7HsAKG0DdtruOuurHE=
*/