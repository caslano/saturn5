// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_WINDOWS_START_DIR_HPP
#define BOOST_PROCESS_DETAIL_WINDOWS_START_DIR_HPP

#include <string>
#include <boost/process/detail/windows/handler.hpp>

namespace boost { namespace process { namespace detail { namespace windows {

template<typename Char>
struct start_dir_init : handler_base_ext
{
    start_dir_init(const std::basic_string<Char> &s) : s_(s) {}

    template <class Executor>
    void on_setup(Executor& exec) const
    {
        exec.work_dir = s_.c_str();
    }

    const std::basic_string<Char> &str() const {return s_;}
private:
    std::basic_string<Char> s_;
};

}}}}

#endif

/* start_dir.hpp
8f9FVOeRcqlSRdVGsv2OYK3yLdllHov/9hHBevwqAujsAcrTo+U5ah8zb7rtK4ntVPirNH7zvmreXaPTv93L1GcW6R5MPUENkcx/iOSCQRmZrDFjThOzI36eieB3k4wZsFEvtHR8upbpwHFKxnU6/QnIOGc0PyvBH7J9rM2777MZWmUvj2Fak+6aXmXRW7w7Pht5VDp7HfwHJ0q2TQ7qeQ1Q/A+gsVv+H5anZ0JKuYjOjUDnWqBzEJSft7t0cDg=
*/