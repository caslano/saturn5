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
eSprUPKsr8cjXJ4qqwkQRW5zYhiAWYE9k3C2Px/tSWia36s2bS4o65zSeEqVsNHkNii7OzzEF9B82CYR4/5cdGRe1iFncgT92lLcABkF3OWYT85DtrHlQu0HrWrixEPgn7/SEcdkgdfR6VLa+kHAt8daRfjr7xa9ltVzA7xIFVZG29mL1TLtMQmocO0iswRE3gvYGTzVrVGohpdCj/bH8xCpbUOlk+JZuz1RWCK43uT9hmmeh8O2tTVK3t4f0QUtLDe9+eu1KB6YiHKgTblDwBDlakps546lk7kGU4dU9fXnhDGBkfPzJgqfnciFqpdQUiydbwMkrrdeFfdg05XU+T7Yt0UzNhbbLQ9R6Zz2Z+emq65w7Uj/2xvDylB7KKl8sl704Yuoe9eF8Kvf0pTN++oD/6KEyRG6qCwPrAz7Sh4/onGJ4dzO2jrs9KFaKPQO5J5P+N2kZ/nDR6vIoCWqXRU1hzxho3vsX7SBzfYT6opq/2vFZ3UhEKQtw4UvhxnosE/siHDPNwQSnTOcRo8n9Qy27WHCGF05Y1Ih+Gr4lBe8D80RFfRkD4gQHQ==
*/