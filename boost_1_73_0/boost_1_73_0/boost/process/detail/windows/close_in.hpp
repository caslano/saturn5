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
ZXIvdGVzdHMvY2VydHMvU2VydmVyLWxvY2FsaG9zdDBoLXN2LmRocFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJXz8jkDAUAAI8GAAAxAAkAAAAAAAEAAAAAADblMgBjdXJsLW1hc3Rlci90ZXN0cy9jZXJ0cy9TZXJ2ZXItbG9jYWxob3N0MGgtc3Yua2V5VVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUpGIWoeHEAAAFh0AADEACQAAAAAAAQAAAAAAmuoyAGN1cmwtbWFzdGVyL3Rlc3RzL2NlcnRzL1NlcnZlci1sb2NhbGhvc3QwaC1zdi5wZW1VVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSI4nAa7UBAAA4AwAAMQAJAAAAAAABAAAAAAB5+zIAY3VybC1tYXN0ZXIvdGVzdHMvY2VydHMvU2VydmVyLWxvY2FsaG9zdDBoLXN2LnBybVVUBQABtkgkYFBLAQIAAAoAAAAAAC1nSlIJ8EuuJgEAACYBAAA1AAkAAAAAAAAAAAAAAIb9MgBjdXJsLW1hc3Rlci90ZXN0cy9jZXJ0cy9TZXJ2ZXItbG9jYWxob3N0MGgtc3YucHViLmRlclVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlLvsOhGawEA
*/