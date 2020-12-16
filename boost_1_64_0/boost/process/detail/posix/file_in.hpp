// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_POSIX_FILE_IN_HPP
#define BOOST_PROCESS_DETAIL_POSIX_FILE_IN_HPP

#include <boost/process/pipe.hpp>
#include <boost/process/detail/posix/handler.hpp>
#include <boost/process/detail/posix/file_descriptor.hpp>
#include <boost/process/detail/used_handles.hpp>
#include <cstdio>
#include <unistd.h>

namespace boost { namespace process { namespace detail { namespace posix {

struct file_in : handler_base_ext, ::boost::process::detail::uses_handles
{
    file_descriptor file;
    int handle = file.handle();

    std::array<int, 2> get_used_handles()
    {
        return {STDIN_FILENO, handle};
    }

    template<typename T>
    file_in(T&& t) : file(std::forward<T>(t)) {}
    file_in(FILE * f) : handle(fileno(f)) {}

    template <class WindowsExecutor>
    void on_exec_setup(WindowsExecutor &e) const
    {
        if (::dup2(handle, STDIN_FILENO) == -1)
             e.set_error(::boost::process::detail::get_last_error(), "dup2() failed");
    }
};

}}}}

#endif

/* file_in.hpp
yrimIf/pOtN6mG6YIhrNQWcZVznHNnJWh1sZ4+eY9zjXcj1olyt5lxoXPdqWOZdtR+gMjOMe60j6zFgn8t5AWUj4xIe8OKwsZsn/7J2IScGsw4wksenjTFkUl5XOjCwL0w8NFL2LmBvldSsfwrHLJ/k4ygf9yPIx13SuuE1jPOp3rAtgKnW53abPFZ3mpkwdZ49zs+Oh2nL0LaK7lHlZPm2vJ3b+iFvZJ0eUfbKWfbnINa3Mo+4lcTPPtHnQ3i/Cnq32DmqvinC/KML+8wj7fQ67s76zk2uP7c+k8Hfa9V1ScJzjevyY/mUUQg/rN13H9KrrHNtNTPr7x/Sh6504kUmcYXk82FjnkeKxiXJAQJZj8lhaWFMVdl/trH3b7aJT5TuHEKewb8GHmH5erzUX8z4mzhdtxkHMRCym9q1UPePnwPiA343MZU3gnOcpluM8XtR4LlW9daL3mTWcPu9n1hmsi0lyhlmCsjk3qPMEdElLA/t6kLCSa8VZFHk/lvy0k/wsIYSR5jrqEJBhj+ZfH+rDj+wnjXjvIfdEm52SIdyBCfBV5A/I3z/cpyfBjySOe70J1hovupRDSNe8GzP9f6LodrNa839oDNIqNyDrjE4OeQr55VHWcZ7+ZeJvG/eNOOr5ErPGZ42UWaNa17H/GM8NL4i+bd8qdl13MqH2WXWtbZl5bnhrfO1z5FYhi1zHEm3L7LP0cmuvO5mWG7nGxNmHF0kbCcnaioy26JBViUzaXaSe+nWGJ16l3/hZTvh6j2dzw/uVvWq/rGXQPmF8uHt+hL1wvK3vHIdvTLXk1yYIKx0zoDE8x75Gq0vy6EirLLcxaqdzdI26vVbRPFMkw54Bd2yBs1k/J9zFxPe4nN/JEa5xflZh6ZlYJzDGH9406HAbJhZzK6YdsrF2msvziyoi+05zr5wuequs3la2a39KOPZzlrwnCQRX6dafontiz9aRYWt5mX5igriv4E74U9NPTBLZ1awcbGeeHXaKLJ3rLVb1QrLWItP+/ZjPb/4T6N9JJzIpg2M+9zrb1OpmEi7zkzEwDiYGGsNEu354sJNITB3JO/0M066iRHecS/1oOPyz91UoNWV1mrjdSLwrzBrnHSIbyipE3s9YPkf/fIHZa+BJ1dFn8LC+u4W4tSCPjcx6wLYi20eYsZxj0f5H9zIJL1/NK9flPgmHZ/M0S+wfO+zONn9Ay7RhEOjy1aQx8UwKlalcoyf0fvFAc90rRMecqzArAmeu2WFWy6CT3zHHnaJbZY0/1rhzkn19tD2ececku27bRo47xS3X6ifPtM5xZ1WFc+3tuaI3mDrofHzjT9Gfb03+J44/20ZcH6nO8adJs45BJ0WMQSPs2Wq/XPv6ogj3SyPs10fYb3XYnfU/vIX7O5iddv3rgOLHx4fOcKP0ZlJMXusp0ynoZ+1wzZp5+/kZsfvzM/7sPjMlSdpgeYl7+0E38rmlyrSBgP9USeFczuq028vvJwd89Ax8D7AizsEX9xxxtzwB91MJbZB1MWfCpOqzDruInBfc/6OBOR+yLCz8BDt80clPkaffcudZ9z8L6BD2BtpfR+zbtN9+Dd19Og78AHMh5nW1v6F8E76FeRuzA/t++A7mXcx7mPf/ycblmdh1PLfjPHv8tlH+Dj/P+HJb1iskq7Jl5v3wFFtmxnnDbZkZq3W1ZWbsl2JkPfuHZN9OqT2WfMeW9Q3J9tgy8755qy0z+Vhry0w+ltsyk48yW2bycY4tM/kYZMtMPjpOqX0WcrItM/n47tzaY90PbFlvkzdbZtL3K1tm0rISWeQa6/NsmSmXHrbMPvvZlpn8PjbZyDJC7+ZHIXO+i/9+UsjeW+zfGHuviPc=
*/