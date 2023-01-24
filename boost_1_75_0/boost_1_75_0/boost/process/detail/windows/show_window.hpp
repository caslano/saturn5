// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_WINDOWS_SHOW_WINDOW_HPP
#define BOOST_PROCESS_WINDOWS_SHOW_WINDOW_HPP

#include <boost/winapi/process.hpp>
#include <boost/winapi/show_window.hpp>
#include <boost/process/detail/handler_base.hpp>


namespace boost { namespace process { namespace detail { namespace windows {

template<::boost::winapi::WORD_ Flags>
struct show_window : ::boost::process::detail::handler_base
{
    template <class WindowsExecutor>
    void on_setup(WindowsExecutor &e) const
    {
        e.startup_info.dwFlags |= ::boost::winapi::STARTF_USESHOWWINDOW_;
        e.startup_info.wShowWindow |= Flags;
    }
};

struct create_no_window_ : public ::boost::process::detail::handler_base
{
    template <class Executor>
    void on_setup(Executor &exec) const
    {
        exec.creation_flags |= ::boost::winapi::CREATE_NO_WINDOW_;
    }
};


}}}}

#endif


/* show_window.hpp
7Ue+kkYZEb8tU5XIpYR5nxvmiva6vp2jlRvHVmM2cJEB72pNp1Y6Df4xzzeHy6LQIbKSQ2ZADxP5x/MzDJ1C7Yp6PcVa/4DMYO4u//bp0LeOFgdBbz1zVmp/quLj2Zsw2Jeovgd6/9GF6CNavoJkMTOSFp/sVPW3wPmtmpuVGbriE1WXVuUQAKBlMfdaWZg9U+51JD7vH6PnEVvmOXG7qrYxuvkw12u24UO8GXAD27j3l4IhOB+vOIcz4azr8ZAP71Q0b0vJN4uR/YLcJ//aA93+9qgXvtVaXTpvTf5Qre2WeccPgN4o9fAtWDJf7h75hyamgCGqEzJhV2nK0BHcnaaqBeq+/XVhOS5k764Rx14hy/XmF6Z8INE674sTXWceIkLVZ0Kbb58DyM7J/D/0Ermdbzw/L8VMnU+UU3y4ZopOcqvlSGNSTrIYvdxZ+yZXi6qx9v510/ROb6Sk3uhHbk8Yv7P4VGlnAneftzv3yWZQnOOfqNopPMSmhulEks5KsM6HGBIgSZ4FTcSpbVlnmu53s9zTZh1EZQcsTTaDit5Yj8hXOd9Z76+Y7C8ZH3mRuEhsyXY8ehhbtKdJf/q0NQG9Y/G0tfUHcUrqGsXwTyvt9mLJhLGPH6s0UjdF4cpaQ2m3FqBuJwHxo71lyib8ghmXjm9DaZhG+rjPj7ibi/X5GpnyfP4oUFkmUmJP+R6SfJFNtEVFzTytwcJy
*/