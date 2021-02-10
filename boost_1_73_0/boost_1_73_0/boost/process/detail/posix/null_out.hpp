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
LgBjdXJsLW1hc3Rlci9zcmMvbWFrZWZpbGUuYW1pZ2FVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSy5x3zXUEAAB3CQAAGwAJAAAAAAABAAAAAABhri4AY3VybC1tYXN0ZXIvc3JjL21ha2VmaWxlLmRqVVQFAAG2SCRgUEsBAhcDCgAAAAgALWdKUpI3R6/3CQAAKRcAABkACQAAAAAAAQAAAO2BGLMuAGN1cmwtbWFzdGVyL3NyYy9ta2hlbHAucGxVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSVsY+j08DAADyBwAAGgAJAAAAAAABAAAAAABPvS4AY3VybC1tYXN0ZXIvc3JjL3NsaXN0X3djLmNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSKsV6BQkDAADdBgAAGgAJAAAAAAABAAAAAADfwC4AY3VybC1tYXN0ZXIvc3JjL3NsaXN0X3djLmhVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSzMEz4osCAACxBQAAHgAJAAAAAAABAAAAAAApxC4AY3VybC1tYXN0ZXIvc3JjL3Rvb2xfYmlubW9kZS5jVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUjJzeaBJAgAAAgUAAB4ACQAAAAAAAQAAAAAA
*/