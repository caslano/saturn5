// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_WINDOWS_TERMINATE_HPP
#define BOOST_PROCESS_WINDOWS_TERMINATE_HPP

#include <boost/process/detail/config.hpp>
#include <system_error>
#include <cstdlib>
#include <boost/winapi/process.hpp>
#include <boost/winapi/get_last_error.hpp>

namespace boost { namespace process { namespace detail { namespace windows {

struct child_handle;

inline void terminate(child_handle &p, std::error_code &ec) noexcept
{
    if (!::boost::winapi::TerminateProcess(p.process_handle(), EXIT_FAILURE))
        ec = boost::process::detail::get_last_error();
    else
    {
        ec.clear();
        ::boost::winapi::CloseHandle(p.proc_info.hProcess);
        p.proc_info.hProcess = ::boost::winapi::INVALID_HANDLE_VALUE_;
    }
}

inline void terminate(child_handle &p)
{
    std::error_code ec;
    terminate(p, ec);
    boost::process::detail::throw_error(ec, "TerminateProcess() failed in terminate");
}

}}}}

#endif

/* terminate.hpp
yuHq2n/rd91+ofGxWVxFoTzYQ4HPHHi9PwDNNRRsDSzP4F/8Y7sor+C4K5pB0Ufq7s7f2UVznaB1+UfUQ5352XvXVOsa3pORonsL4yRv/KVQ8phtFhR4QCO2EzSVlW8/uKyKC0Vegr4iwkHFCm9x2FKFBBY2OSL2Tj5Q7PmHlbr72fBpjTtmfwaZFB7+mrjgpwyCkowKoKyOPNIQ4wmzlnQ1GhzisThyq/6jqx0fKEQcUnOcC4+VIzQs8wLUJFPWot5OzuRVwKKj0tZ7XWd0hnCs3rh3JdmtMnPlq9TfO/OpHaT5N9V3DrHYcCsQSFrYQRD49WyHn0RkD/0zT1SCfR9BPvJURePghRlZKpq+9U3w4Ui4wUN1Sy2t+7fom2A+syLovl2B5bkGr6jmWu736gmjsOnhBBJf6oxYvANeNBn8dv5M+rVrXTfdZADqHqJMHIjSAoDqj4NUMB8NnXSgYxMPST0H/tF3NK6qUsj7sQDt2qn1s7HuFcorvvN9qSDHtfhponcB90ZPuz9VU6eCF37zknczX0Ua4DAo7yegb3ElInrQ9KrT11wlRw==
*/