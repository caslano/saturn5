// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_POSIX_PIPE_OUT_HPP
#define BOOST_PROCESS_POSIX_PIPE_OUT_HPP

#include <boost/process/detail/posix/handler.hpp>
#include <boost/process/detail/posix/file_descriptor.hpp>
#include <boost/process/detail/used_handles.hpp>
#include <unistd.h>
#include <array>

namespace boost { namespace process { namespace detail { namespace posix {

template<int p1, int p2>
struct null_out : handler_base_ext, ::boost::process::detail::uses_handles
{
    file_descriptor sink{"/dev/null", file_descriptor::write};
    
    template <typename Executor>
    void on_exec_setup(Executor &e) const;

    std::array<int, 3> get_used_handles()
    {
        const auto pp1 = p1 != -1 ? p1 : p2;
        const auto pp2 = p2 != -1 ? p2 : p1;

        return {sink.handle(), pp1, pp2};
    }
};

template<>
template<typename Executor>
void null_out<1,-1>::on_exec_setup(Executor &e) const
{
    if (::dup2(sink.handle(), STDOUT_FILENO) == -1)
         e.set_error(::boost::process::detail::get_last_error(), "dup2() failed");
}

template<>
template<typename Executor>
void null_out<2,-1>::on_exec_setup(Executor &e) const
{
    if (::dup2(sink.handle(), STDERR_FILENO) == -1)
         e.set_error(::boost::process::detail::get_last_error(), "dup2() failed");
}

template<>
template<typename Executor>
void null_out<1,2>::on_exec_setup(Executor &e) const
{
    if (::dup2(sink.handle(), STDOUT_FILENO) == -1)
         e.set_error(::boost::process::detail::get_last_error(), "dup2() failed");

    if (::dup2(sink.handle(), STDERR_FILENO) == -1)
         e.set_error(::boost::process::detail::get_last_error(), "dup2() failed");
}

}}}}

#endif

/* null_out.hpp
viXjz2KYZy2DuiOcG15TE0GEvXJGhI6ijkiOf7lC3Y4zQOyqckmvO4zXeggo8PbS5fan9m4WFo7VGA03pI5/8MmD7CedojS8St93NLddmuZvaiHm9z2kGAHManZmBKUE98gfZX0AbfxY8eSru8lh3iaosDPZ7G2Xmoij195viovZNPkrxDar5CtE7fZJDKkoJejpmdCx+7mAN23BN3dQiDdXm8idnuf0nQULwn04+OX5ATN8rxDfB4i3JoxGoS7p/0DSWAgMH0lTLAKeyXlCNo5BOv6sbBr7JwASneUOgSvP7faZ3KA0FsDHmnxCYvm/AJ7lHqKW5QFi6pHVXjCmYAYJzf7ygcZiJXUutCca6TsB/0ZGR+YjPwEyRAJBIBEScUo01TnCgXopam1rIogP2QFpS2788B/RNU1kt227Xh1VJ1OWi1bks8CzSCjvLOo2RW9cr/c2vRGyI1cd7jEyLEg3UDfI420rUnaXgMd2D34bRhvZynnzUT0KSLyWhftk0/jyyX7j8u9e/0dmC/vvaqe6hUk5Xb7ZwujC9hy0AQbM5QDtDwpmHdw/bTrdBlLID00lmg1CtuILkbgsR9ReoxKzzp1+Iy034LOI+GKuRWUOpbmPULJTeFQUH1zp78RPz8AHjLv4TYY2eiKt7h/aWWrOtDYZlxXcM8s3NeYd1eJX3UajsuLTjjG10AdITrl3GVVOqerwzfsh1k7e
*/