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
ckJhxm0upvGcknFbAE1AuOPwkghExMklcHV8bdVxZIno0ye96dt3SKmlBQZ2ZiTwtw+Wu7JK39Lj5uMSfeBHQExysuAaUflrI84E7/q2YN/TBHvEDXRGHT4Z4CSliNce5uZNIKLfKGGshuyDc/UPcSfPYvf8QsiQ3XThHl8ILCQmgAQaiPqMO4WVQ7P0tvtqbvAimUMa6Pvpme7ww88X7ll9qtP/neVQc2pSdNLfF2o74J34VnYK7JcNeEO8heTgirAEvCPdYh4u5KSI1oo6iVT57Qfs++8H4vgRiSrkqItW+esB3ngOUaYycjb83kNIVogmVnLcRJBEJ8hwYxksMCzYDnWnMKeUp+xEL/zXAUzQTIA31LpPt15TADKeKZmpkBzVnBgR8B98kJ/BOSARMMwbwu2HaJkoGO5KxErknAwNHfYapgK2AvpKFAzlg4jp1ybyNRZ+F+UZmRJOWkQ5FrmOpA6qDmMX+pmoDuEW1oLjUHYKZ0qt5fzLY1xPvQbMkww5i+PA3BPdwdb0S1ZkGjEIqFBEmLoWYRNDrOEj5Ghn698r9/NjUG65d8qJ3SIJ9xaGzoturgfLkrJQJX/KF2NtfdgdQ2fYVRBUMJH/g2XCoGFDc/vguWdbPRPi8hRhtZIXFaGnw37XgOXrjbuX4NVzXHbBuHTdMNijnqmfZdasRnIwlvPixP/7o6fp6esN35u80ZPKEXE33fe6
*/