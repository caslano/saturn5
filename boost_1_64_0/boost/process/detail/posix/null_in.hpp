// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_POSIX_NULL_IN_HPP
#define BOOST_PROCESS_DETAIL_POSIX_NULL_IN_HPP

#include <boost/process/pipe.hpp>
#include <boost/process/detail/posix/handler.hpp>
#include <boost/process/detail/posix/file_descriptor.hpp>
#include <unistd.h>
#include <boost/process/detail/used_handles.hpp>
#include <array>

namespace boost { namespace process { namespace detail { namespace posix {

struct null_in : handler_base_ext, ::boost::process::detail::uses_handles
{
    file_descriptor source{"/dev/null", file_descriptor::read};

    std::array<int, 2> get_used_handles()
    {
        return {STDIN_FILENO, source.handle()};
    }


public:
    template <class Executor>
    void on_exec_setup(Executor &e) const
    {
        if (::dup2(source.handle(), STDIN_FILENO) == -1)
             e.set_error(::boost::process::detail::get_last_error(), "dup2() failed");
    }
};

}}}}

#endif

/* null_in.hpp
W8nlPqj1Vw5mAzHpW+eg9OxMZGGnnS3EJgi4ZU1odqBSRhEaJnir1y5+2Oe7sNZsvB/48P9na+oCtir05n66knFZGS7WXmmbRkekAXP99zEpVyJvi6GhLbwWQirdWlRG//nwgqgUbD9FI3bt46RbqCx5RR9S/eF4DrIYl5Y1Kw6Gifb8wEOZUhaONYqB34d3h5d+Ud5zVzWA3cVmFjfVbHEqOCtMO8Vbkut0S1VSPVWZL+FCBBG7evLRcnPtjVo8DZza33JfPQWlsXlCa3s/ZFRaAfagKRXyA955pDoZ7M7MYrz6IiKEWcOyNDTP0QPUf5T1MgN63q6xpOD42Ee7VUI1aSvEQv4mEmqWDxe/b80BU7t70/WPoPgut57gSwTFJXfOd1FLyQV+ZL7SCS6AkNiqGIxdeYXBrvfhbH65KMl6CdVSlMulckka11/u9KIclXx7GDUGtaHQngIVd4LIIX9gyEVqcXwAPxUmR3FqhAuxz6TvKyZEtaRJ8fH0N1RFnm3RyyWC09rz+z0fW4zTPN65dL2OSbQaTMjSvtq7tt1QFMwYCh1ytUcZ6g==
*/