// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_WINDOWS_INITIALIZERS_NULL_IN_HPP
#define BOOST_PROCESS_WINDOWS_INITIALIZERS_NULL_IN_HPP

#include <boost/winapi/process.hpp>
#include <boost/winapi/handles.hpp>
#include <boost/winapi/handle_info.hpp>
#include <boost/process/detail/handler_base.hpp>
#include <boost/process/detail/used_handles.hpp>
#include <boost/process/detail/windows/file_descriptor.hpp>

namespace boost { namespace process { namespace detail { namespace windows {

struct null_in : public ::boost::process::detail::handler_base, ::boost::process::detail::uses_handles
{
    file_descriptor source{"NUL", file_descriptor::read};

    ::boost::winapi::HANDLE_ get_used_handles() const { return source.handle(); }


public:
    template <class WindowsExecutor>
    void on_setup(WindowsExecutor &e) const
    {
        boost::winapi::SetHandleInformation(source.handle(),
                boost::winapi::HANDLE_FLAG_INHERIT_,
                boost::winapi::HANDLE_FLAG_INHERIT_);

        e.startup_info.hStdInput = source.handle();
        e.startup_info.dwFlags  |= boost::winapi::STARTF_USESTDHANDLES_;
        e.inherit_handles = true;
    }
};

}}}}

#endif

/* null_in.hpp
kQbeFPgFiyievqXx7sMGp6rWEFfSPOMFGyzcztqXXphxItSZmzIMxfJmcUgBQGusBN+y/Ns2MNQiK2n50vsYgzYQsp6KGX9QgKpTlGBY6Joum9Zski9urHxO7dYV3AzOc7/Y0yEQ86LnazGSWFCa48nI+geFv3WIcKZfa7QezjrrDWpIwgApsdROIXOamsrk5VB0OMIhXW0s1TChK+WvbZypXn3JEsJwbljh1RqebNk/XxlIW4Fqg3sIOsLzVlsnHY1tdhkYROwhVDKLkWXNlUgfnHGpTz3axydcH8Bva8xdip5QmUUinZ5oIjjSTzUdpJdmiHJaIssaM90l4Mb92uMIee+mLT7c5d5ntTaEv7M/+pdqpJDRopNE58qDomKNG2d4dCK7g7j5Xv39Gymy5vXUaiNNnU0PGmpux1oot75dMv/65t8Xh3GjJO7VTdB77L6CPBRffGknAtEzTbVYH6HFp9GAfFvN0LijEBzwb49McrAMiW3YbaoSX8YnurH2a7Z3jCrZadUzuh99ktEJzxiJEX8WNfAZE3ozkN3TaSKquI2tq3ezZDiScg==
*/