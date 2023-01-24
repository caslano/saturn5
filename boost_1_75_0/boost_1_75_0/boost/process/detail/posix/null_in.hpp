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
ldLB7bPmXuAXs7Sij+x/ESxEbV3vXwNXeqWgxCV8zgpmGJQwFh/8K0p9xDL/9Vy7IIjq6DnkfhZtlkpGo2Ft3IoFHKBnvHVJNT0EiFcc7syv1edTfnkmu4AKT//WQFQrDIoVIjTONa+BOvOtbKoBU7dUKN4VEgG1JOuEkPhf9Wt3e35ZnpMHTm7NMLcWVzjgXATnaZG0R3wXDL5aWVIJ8aeECuq9BvUZjiyuLKNa53cWA5PSgEL6ivkEBW2w5dMn6h2R7LYtwRbYUwLHdRcObAguRPLs9iJ+F+GXDXMf8aGGomk8U8xgHR+BJuJ4joGDg3xcEgjTJPAwgg4uGwcWETgp5HlETEw+v64XPUEfvq2hddIIUe/0jWk9f9WQTno4WrdqhrFxXr6EwXXrl6kBkXoxgEjEZ6LffXjrBQFc1VOI6Tc0F/AMcADmVoyHTCeazSaK7rIRQq0XjRMR8A9Pv+3Cf/uI9b88zfyf9tacAv/s1vr3ZJafo/qyGwAqK0EVyCKGant7zVz3hibUvS/SoeQ1kVg3sH+8n7fsJuXhLyJaEDVwj/T705+LmdxZ9ah7HEq/rs1zY62E4nj+qDGkWOEnCO3xZrVwvSpscp8MtpXE4S88cjmRrq+D26EQazpaEsZXmrwxEZetzssen8untqM8l63N1wig4d04cX7nAafiV5/KUNHRH3NdRbw7hcyLoZSnTyF6rBkO069l
*/