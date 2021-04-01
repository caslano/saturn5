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
xh3DbeBvANewxMdNWPBB+KWOSX8zUfBm2ZVuRPc7Z7B6/ULr47S0A5CCDosn8qGQP1jKIN+05RICVjXrx4DtIWjwksggkrnMEZmoTt1msPRDT/0VjzP1zxmUvZnHiccdTQEgRtmUWd3cfYwU73cO2kE948BPTnGNS6/t1GFCYn049aQ47BbV77y7nT7WelRziOBatB19qX3rxa08cOuvBdGDxffLet/WNw6b7Vk9vuH4xRWR4TC1oxNedX3n6RjL4W6mLchj8239AQECMUp5mMh4dioHMuLPQbOa/t+X0U7PNLwF7G6GrqvtDjZbri//WE3TajLV9eUgiEJZ+nAmieMF6h4WR6vqUW+72qs7fumzVwcWAya580oaDH7ocj1IWOba3Aok5BdXtu7f5UYmHA4Is17Y4gywmliO0JXFoM031+8OioVmqXFDOsGd9W7XzBHf/QkhLtLXZi+K2uTZuLt450M+nvi5Y8PztmZl+ZdEKu18Zc24hdolpnqyzfbOQBKCSE5+fprDJr/dgiWDezR4+T1RafBQ/yMTC13QAuSXSFUrY/C3jq9TGw==
*/