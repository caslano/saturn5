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
AD1WNABjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxMTEyVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUhU6c6pEAgAAswUAAB8ACQAAAAAAAQAAAAAAAVk0AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDExMTNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pS/d1CUb4CAABMDgAAHwAJAAAAAAABAAAAAACLWzQAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTExNFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlKzczvetgEAAMoCAAAfAAkAAAAAAAEAAAAAAI9eNABjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxMTE1VVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUl5judPgAQAAbwUAAB8ACQAAAAAAAQAAAAAAi2A0AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDExMTZVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pS+vGUe1ICAABPBgAAHwAJAAAAAAABAAAAAACxYjQAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTExN1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlLp
*/