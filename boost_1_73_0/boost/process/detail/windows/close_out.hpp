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
06ptWjm1jt1ah4+CffSoVsePavW80jheRGtZJ8J0LvwuNo4+a2LoOpO8aDuWbbebst7IUzY5AMX4JcI122xHNoLDZGW5BX6DiEkFnVgFykZJt1GxbTB0DEV1v4SMrEFV9PEWeVQCQxyBZFhvYuDYhkNL4m8sZ9P5ioNIu9baubDwVsiLNwB8bdcT/t1THUOw5Cg3LBmx2AbRmDxNUVpqijK3KWBFn4f4Hnn1iBOulwU5614O
*/