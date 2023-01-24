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
CN4WweYXWDVGtnn2B4kCohij7TtV2VLJYi6HeRlWsdLht91GdStuq8K+NC3nnaqOaFhG8gMfiPObxWtFGuvtc4uJkN1+/CT8i+Idua4UjKjw6HCaJHUmgMpKL2/X1aORotTmvLPuJ5oeIqhWP2JS2E+lKS9pB4qnbatSqyrEZAYIUtll/iO0LsmbWEO5YxvkIhPRlFNjdaUHnFvGbKEtSfnibadHuvhCUrySVzfVbLG6H+9TJNXP75NZ2Gu3cgxf00GoCwE9XwMp+v5DQf2JAKUS9d+Go8N4R/c2GavAjTpvyaUJeMb+XKd13FLSQwA1rlhyL70PnqD2vLTseQDQkzZ8XdXqUOYkJyVfL9oLlTqQvePrkeLD9R58lnuyBx9eWzwwe2R+tFCaqZv+A1BpvyI6gNzNn2NFe4b02s6a/e6caMZpWk5pzilqNuna7JHz0aEJUJbk68ddfM+Wcd3pni35UV1LCoSkP9qbYz2g8lFLpj5Iuu66vwxvv8O5vpKfPo1raOyS5p7Nm1W+b8zxfMP38K4cReAZn9iZMIozwJRXJhXeQtBs6KV3+weqNiMUpi/05vYhsdCmEIKDeumf0YM5BQ43Cn9b+oDrQ9VswkxPimT0z0FF9gQtXRpcQ+9nP2yECYPGO8+F8oyJG/3De5TRmPRph77X/o8YSA4kDdLXOPvqj/az2FUT8qurf9qXUUCKIFnd/emI59tO
*/