// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_WINDOWS_INITIALIZERS_CLOSE_IN_HPP
#define BOOST_PROCESS_WINDOWS_INITIALIZERS_CLOSE_IN_HPP

#include <boost/winapi/process.hpp>
#include <boost/winapi/handles.hpp>
#include <boost/process/detail/handler_base.hpp>

namespace boost { namespace process { namespace detail { namespace windows {

struct close_in : public ::boost::process::detail::handler_base
{
    template <class WindowsExecutor>
    void on_setup(WindowsExecutor &e) const
    {
        e.startup_info.hStdInput = boost::winapi::INVALID_HANDLE_VALUE_;
        e.startup_info.dwFlags  |= boost::winapi::STARTF_USESTDHANDLES_;
    }
};

}}}}

#endif

/* close_in.hpp
ZfC7QsjjvonhP7lnj8yUGzN9UzAlnEX056ezkjP6Wpn2vTgro2cfvwRKV4RlUcnI4txoWokZielRido1Cc6apIqhucLId5RtX4VjiyckO5us8op6uLn8KEe2rLOKCsb0COdTjmxzx+pSvy50+fks7+LL+3UZ1xa6qZVdlD3CbVs1pGVeNNir8No3IY3ueeN7Febl2HMvp5eHPj20/hvydHFR+8v8wFmwEtWN7dYIeX5XORSsqxkK4r+mo887rhw=
*/