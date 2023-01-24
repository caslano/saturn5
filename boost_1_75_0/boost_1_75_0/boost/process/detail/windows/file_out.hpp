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
rwihag9n/GFXpSuLhsQgJ9/+ftao6eCwUKk3Hh4zql4yYYmJqZBdzsRU5q/pqWP9ucnTGZuxsFjq0lUjxKd+dr3id+7w8LOYmKCftpT5I32CwoKK3rohp1n2bZXMlJpF/edqBaniKUuD1gKyzvr8x5EpxRKh9oqOretLKRVT00oZ1aQU9aSMjITURHxCbXUdnUK1tMRwRHFvcW8dUx1rcTlOXm9Tuds0Xf2l1tzf/xHtC5Wli7aCgrGEhNqUdIKWZoFqCsPnCgljL2kHdXFxkI0NyMcHLCnZuaSTlrW2MevkYbK7Ytd5ZnNRzEQ3HhpVxsDAUZi//51TIqpQqoIZNkG9rPSPpZZJmNw9bmCbi3ty+ADB0EQqyrqD/YBGwt8oDNb1IPE6KfGrukrT6uo89h17RuYLim48eC+/GNRlZma711cICQXStQnkCgUruGULLOy+j8xYOM2lC9YvF6vhlv2REkexjH6u9LWJ92w44d6WNIBsKDCUnLaYjJOz90PDUO6PpnkNXDRFFU3uxRU2fasuJVV2jz3BuR0dvk5uYLeHegb1l1ZPmdlZDiMjRBVlfq301taV+Mgi5KNpPkuXShndHOXP/o0MSaYyBdIlUgiozKNj1W4vfyYe0AgKnK6GhrKUlJGiYk+JyNkwVrrfH36xCe/FUVyFoA48PY88nEWst2tvvcinqXHN/eKaWvfNLShorKkp6ugoq6ys
*/