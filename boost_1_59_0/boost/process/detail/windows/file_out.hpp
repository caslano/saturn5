// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_WINDOWS_FILE_OUT_HPP
#define BOOST_PROCESS_DETAIL_WINDOWS_FILE_OUT_HPP

#include <boost/winapi/process.hpp>
#include <boost/winapi/handles.hpp>
#include <boost/winapi/handle_info.hpp>
#include <boost/process/detail/handler_base.hpp>
#include <boost/process/detail/used_handles.hpp>
#include <boost/process/detail/windows/file_descriptor.hpp>

namespace boost { namespace process { namespace detail { namespace windows {

template<int p1, int p2>
struct file_out : public ::boost::process::detail::handler_base,
                         ::boost::process::detail::uses_handles
{
    file_descriptor file;
    ::boost::winapi::HANDLE_ handle = file.handle();

    ::boost::winapi::HANDLE_ get_used_handles() const { return handle; }


    template<typename T>
    file_out(T&& t) : file(std::forward<T>(t), file_descriptor::write) {}
    file_out(FILE * f) : handle(reinterpret_cast<void*>(_get_osfhandle(_fileno(f)))) {}

    template <typename WindowsExecutor>
    inline void on_setup(WindowsExecutor &e) const;
};

template<>
template<typename WindowsExecutor>
void file_out<1,-1>::on_setup(WindowsExecutor &e) const
{
    boost::winapi::SetHandleInformation(handle,
            boost::winapi::HANDLE_FLAG_INHERIT_,
            boost::winapi::HANDLE_FLAG_INHERIT_);

    e.startup_info.hStdOutput = handle;
    e.startup_info.dwFlags   |= ::boost::winapi::STARTF_USESTDHANDLES_;
    e.inherit_handles = true;
}

template<>
template<typename WindowsExecutor>
void file_out<2,-1>::on_setup(WindowsExecutor &e) const
{
    boost::winapi::SetHandleInformation(handle,
            boost::winapi::HANDLE_FLAG_INHERIT_,
            boost::winapi::HANDLE_FLAG_INHERIT_);

    e.startup_info.hStdError = handle;
    e.startup_info.dwFlags  |= ::boost::winapi::STARTF_USESTDHANDLES_;
    e.inherit_handles = true;
}

template<>
template<typename WindowsExecutor>
void file_out<1,2>::on_setup(WindowsExecutor &e) const
{
    boost::winapi::SetHandleInformation(handle,
            boost::winapi::HANDLE_FLAG_INHERIT_,
            boost::winapi::HANDLE_FLAG_INHERIT_);

    e.startup_info.hStdOutput = handle;
    e.startup_info.hStdError  = handle;
    e.startup_info.dwFlags   |= ::boost::winapi::STARTF_USESTDHANDLES_;
    e.inherit_handles = true;
}

}}}}

#endif

/* file_out.hpp
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
*/