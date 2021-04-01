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
9u+sgI7POE0ycV/RVrw3+5Mwyo2F4HJ2m0US7sZdEVvfQ0PvHS12rphjSYiSieZ7xMtqJQg3yn8S37pDq6EYWTw7rTwPEITjNG4sWIhxOLOVeC1g4Ot1KHWJNmjQfvsjOAH8wwsBl2ub7NCVJr/m+u1a411Mya5EXkugeGyb2jSGMYJiMoi11eQ4aBC4dXnb6qJ+CPzzeJ0Fb1sisz+eyXHjxWJM4exbImGpb+2e0X+loMWLqbJHbSnEYRd+dSb1m0MUeecKoU7ejYYLRrQRw0E62D46PjAC8u4yeYtUZS0rDSKExbwpjCpa3pwAvgtpv47U7hzlY842gujpUJ1jfi0hVSu8lZd3HCrSYlDsS75orzgSg5zcI3JNCu+MlovexHHcgQikFvWJoZsokYRG/Vi9Eiuz9Ayszlu7LlLKiGTLArdObhj90wVTlDnHbuIBxSsj+q1rtavRDT2oaFbF8thMHEigiRViCeOXXBfXcoVy7i8E9VdJPhfP2neljOzi9NrL+Bzy8m77cP46OnmpDL1aQJg43caH1hl5HMtJ4u0iAQDNC2xtQCtRlA==
*/