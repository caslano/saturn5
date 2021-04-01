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
ZO1hi43Rs/qGDzNAUBWPgBkqg3lco+oSYTdidWQKcyBg0HGdR2N9IAHPjRchkxjICxjNSdBwzKKs69dlSwyttj3JVWFK7BkBTSM9Dd4y7jJ4ScuV67LZ0KNAoa1hbyFxOugV9H4Tmuya2fok46KaCFeasbTapLPlD9pyh9o96xwxJ1HV0NNiyyP0BI8z+VfEozME0k7TK059bYV6GagXVxYio7rJ3jQI50yJCJggyoaQp5bZPRa7m3kIzkx7+k6j/+pycEX8d+96rlZjus7BjgyxPqqg6s1NtIGOi7FryTn9vbEA81Vud3KkQCoDFJS6JStXsudZl5/vk24s72+oo6ejY0Zr74pG2eR5u1JCjA1FJxnZIcfFitMtPntzrzGM/DPM0wVSV6N4uNf0dhw2O+i/SiPds0h/oUnQtdkCTNE2QfszG9o9H4gVGZW4asgApvX7BlzBa9t+pXfiyz6Mn36Dyzz6okWHwTyUcFrLvFmTO70fTyU5MSsYHUANQtHiaSUxCft9eDVl9ZnrWSwz9t2tXxMFuQOFtuzmpJZ3HrojWDYEQePQ5gw3Yg==
*/