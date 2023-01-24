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
VeJPgPlnvD0LT0PTF+Yr5GEQcsDQY9a2xrZFkMG2RYDx9lEATS/odTgwHz8PzV/0kd7x1RDFP++R9Ypr6DKQX9P1urE1vXZz8aYP+MrCf4sdXZ8zt5sS1V5Cq0SiLshUzCtITL6YzEhHLx27UGI+lBESbGCOwTzQYDlUfU74IOgTsynmAycUfdOmCBzbGpBZYHnwe1g+93vgY/4LysKqlklefA4tXDOQICtTw4KgJmGaSZonVzWWSfYHZ4KuLeu0jEWeTDO6SJKCHjttgES+4tU89qzSw2yKnILiV1d1izUP1Y0/t5qHmXtmZ9um2BS+54UhCSKuV/UjXlfXeK00Z7DLcE34xYiY8zEiEE37WohlfF7bbCnfT0goPVeHP8WP5Tb73IlZ0Yx4ag6bi8rcP/VJ+pCqISJxb/VcftRH8BaaBeWkklv6S27q0xSZmmHe1Mvn29tJbGJfPdY/VlQUJokgW0cK/GOQdgkDkX05H0YR/+icIQ9Ud0piqh86r1lHIA/NvufBoCrvtqKaW0VR2sO46d8IZhOJ0DwFMx/X3w2MtpME/FjcvVRvQZ0E1x3il8gJywbKgH/Mu7WhouqFEkz2kV19EB3oeUPSFl1vSgo9qiNxGXFs9aekGTWL7RrjGT01NIM7swIRmmdgmSMW/jzSR6qlG/P7+9MzAly626xg5cjSO7yEJLxhyqr63VK35jzAEhTN48nhGXim
*/