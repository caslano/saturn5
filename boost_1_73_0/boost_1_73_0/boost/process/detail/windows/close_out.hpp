// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_WINDOWS_INITIALIZERS_CLOSE_OUT_HPP
#define BOOST_PROCESS_WINDOWS_INITIALIZERS_CLOSE_OUT_HPP

#include <boost/winapi/process.hpp>
#include <boost/winapi/handles.hpp>
#include <boost/process/detail/handler_base.hpp>

namespace boost { namespace process { namespace detail { namespace windows {

template<int p1, int p2>
struct close_out : public ::boost::process::detail::handler_base
{
    template <class WindowsExecutor>
    inline void on_setup(WindowsExecutor &e) const;
};

template<>
template<typename WindowsExecutor>
void close_out<1,-1>::on_setup(WindowsExecutor &e) const
{
    e.startup_info.hStdOutput = ::boost::winapi::INVALID_HANDLE_VALUE_;
    e.startup_info.dwFlags   |= ::boost::winapi::STARTF_USESTDHANDLES_;
}

template<>
template<typename WindowsExecutor>
void close_out<2,-1>::on_setup(WindowsExecutor &e) const
{
    e.startup_info.hStdError = ::boost::winapi::INVALID_HANDLE_VALUE_;
    e.startup_info.dwFlags  |= ::boost::winapi::STARTF_USESTDHANDLES_;
}

template<>
template<typename WindowsExecutor>
void close_out<1,2>::on_setup(WindowsExecutor &e) const
{
    e.startup_info.hStdOutput = ::boost::winapi::INVALID_HANDLE_VALUE_;
    e.startup_info.hStdError  = ::boost::winapi::INVALID_HANDLE_VALUE_;
    e.startup_info.dwFlags   |= ::boost::winapi::STARTF_USESTDHANDLES_;
}

}}}}

#endif

/* close_out.hpp
AMMBAAA1AAkAAAAAAAEAAAAAAAj/MgBjdXJsLW1hc3Rlci90ZXN0cy9jZXJ0cy9TZXJ2ZXItbG9jYWxob3N0MGgtc3YucHViLnBlbVVUBQABtkgkYFBLAQIAAAoAAAAAAC1nSlIAAAAAAAAAAAAAAAAgAAkAAAAAAAAAEAAAAM8AMwBjdXJsLW1hc3Rlci90ZXN0cy9jZXJ0cy9zY3JpcHRzL1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlIcQXELBwIAAE0EAAArAAkAAAAAAAEAAAAAABYBMwBjdXJsLW1hc3Rlci90ZXN0cy9jZXJ0cy9zY3JpcHRzL01ha2VmaWxlLmFtVVQFAAG2SCRgUEsBAhcDCgAAAAgALWdKUq+rF3oJAwAAwggAACoACQAAAAAAAQAAAO2BbwMzAGN1cmwtbWFzdGVyL3Rlc3RzL2NlcnRzL3NjcmlwdHMvZ2Vucm9vdC5zaFVUBQABtkgkYFBLAQIXAwoAAAAIAC1nSlLTl2xfYAQAAJwOAAAqAAkAAAAAAAEAAADtgckGMwBjdXJsLW1hc3Rlci90ZXN0cy9jZXJ0cy9zY3JpcHRzL2dlbnNlcnYuc2hVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pS5c5P2mwCAAAQAwAA
*/