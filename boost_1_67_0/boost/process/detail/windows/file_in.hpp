// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_WINDOWS_FILE_IN_HPP
#define BOOST_PROCESS_DETAIL_WINDOWS_FILE_IN_HPP

#include <boost/winapi/process.hpp>
#include <boost/winapi/handles.hpp>
#include <boost/process/detail/handler_base.hpp>
#include <boost/process/detail/used_handles.hpp>
#include <boost/process/detail/windows/file_descriptor.hpp>
#include <io.h>

namespace boost { namespace process { namespace detail { namespace windows {

struct file_in : public ::boost::process::detail::handler_base,
                        ::boost::process::detail::uses_handles
{
    file_descriptor file;
    ::boost::winapi::HANDLE_ handle = file.handle();

    ::boost::winapi::HANDLE_ get_used_handles() const { return handle; }

    template<typename T>
    file_in(T&& t) : file(std::forward<T>(t), file_descriptor::read) {}
    file_in(FILE * f) : handle(reinterpret_cast<::boost::winapi::HANDLE_>(_get_osfhandle(_fileno(f)))) {}

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
};

}}}}

#endif

/* file_in.hpp
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
*/