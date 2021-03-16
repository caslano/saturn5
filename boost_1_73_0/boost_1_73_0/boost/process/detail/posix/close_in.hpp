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


#include <boost/process/detail/posix/handler.hpp>
#include <boost/process/detail/used_handles.hpp>

namespace boost { namespace process { namespace detail { namespace posix {

struct close_in : handler_base_ext, ::boost::process::detail::uses_handles
{
    template <class Executor>
    void on_exec_setup(Executor &e) const
    {
        if (::close(STDIN_FILENO) == -1)
            e.set_error(::boost::process::detail::get_last_error(), "close() failed");
    }

    int get_used_handles() {return STDIN_FILENO;}

};

}}}}

#endif

/* close_in.hpp
jthd7bsgr+rZ6KeJ8GfwaVOQlze+lmj8TPiL6vBBz8BvVkeOhnZ8HoTs4JJbQ/+mYSxRB/x/hpifglh5+ecmNWTrb9HHBB2/HeObO5HD1e6GeIvc8Jkl8Hvo87daQ2/3IUdDLB4BuXyC/LNWDtHNo9C3k6B3iC9VszFmeAg5Nnzqzp8s+hpjqJPgKYJc+xN8LkLMOok2fQDffj5sa/3LyOMQv6ciX0+GL2oBm6zVAbn/PwbtgD2uA8+VbyIaiXE=
*/