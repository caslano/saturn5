// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_POSIX_FILE_OUT_HPP
#define BOOST_PROCESS_POSIX_FILE_OUT_HPP

#include <boost/process/detail/posix/handler.hpp>
#include <boost/process/detail/posix/file_descriptor.hpp>
#include <boost/process/detail/used_handles.hpp>
#include <unistd.h>

namespace boost { namespace process { namespace detail { namespace posix {

template<int p1, int p2>
struct file_out : handler_base_ext, ::boost::process::detail::uses_handles
{
    file_descriptor file;
    int handle = file.handle();

    template<typename T>
    file_out(T&& t) : file(std::forward<T>(t), file_descriptor::write), handle(file.handle()) {}
    file_out(FILE * f) : handle(fileno(f)) {}

    std::array<int, 3> get_used_handles()
    {
        const auto pp1 = p1 != -1 ? p1 : p2;
        const auto pp2 = p2 != -1 ? p2 : p1;

        return {handle, pp1, pp2};
    }

    template <typename Executor>
    void on_exec_setup(Executor &e) const;
};

template<>
template<typename Executor>
void file_out<1,-1>::on_exec_setup(Executor &e) const
{
    if (::dup2(handle, STDOUT_FILENO) == -1)
         e.set_error(::boost::process::detail::get_last_error(), "dup2() failed");
}

template<>
template<typename Executor>
void file_out<2,-1>::on_exec_setup(Executor &e) const
{
    if (::dup2(handle, STDERR_FILENO) == -1)
         e.set_error(::boost::process::detail::get_last_error(), "dup2() failed");
}

template<>
template<typename Executor>
void file_out<1,2>::on_exec_setup(Executor &e) const
{
    if (::dup2(handle, STDOUT_FILENO) == -1)
         e.set_error(::boost::process::detail::get_last_error(), "dup2() failed");

    if (::dup2(handle, STDERR_FILENO) == -1)
         e.set_error(::boost::process::detail::get_last_error(), "dup2() failed");

}

}}}}

#endif

/* file_out.hpp
XEbHCX5LPsmReXeER04znULobmRae5vnUePIGR+meXKJfxKiW2zMsVvy0PTkUSnykUYeUwZlwVfsQOmqNfQds3GrIKqFcR+Xuy/yWM/02aDKgQF4XA6VXWVs1S5REWQAUWS3pRrVWKDXKDk21+9Odjwylm7/Vn+lEym25nz77HH7tsGXENmEuiyU5Lia0dLK2+kidHqSlrVv4u78vWPzYLxSC5H7nRKCwsPfIrs2G9ZUiRvYJYG/NBcw4lXA9DWaGgzgc7TSIsSXYUyGNhzsattEaicJW7LOYkjYziptcl+Jc8b7gKPJoMGCXPvgVISRXsHjDl5D2IaTvT/7Cia8IA/NxSVqmYdBzA0hHF9n42W/G+TZ1nA5rrilCbMAdKUkrBuseVm3udd1H70bVb517IpBK/2BGE8RJzW6Pmaz7K3aJ+SLRXGLF5VNNBL27EYAs1soGHIIctNLyDFTTH0qGACsCYFNV18YbvrH5QTQiD3iAg80GClBEKsHMdLBitrgAcqRftbSz3BCZ5pc1bQHhFY641edKd1yYCt0eO0BDvqR1j5rQvMDogNw2w==
*/