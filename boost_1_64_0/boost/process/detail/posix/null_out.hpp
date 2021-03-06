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
wtzHbFTnIsOq6BL4ahW18NMNQ8aocY5EDvTLmKOHuJpsBO/JagrTB0Dg5U2YXnFkseVYoBbVQ5CMRwHTUXWDAHFkQ+WKayB/Z367wzzlkj+XJNDsk/Cuz2YvzimTgkFNNQdniki7URDHbL7Gf2sQHkoXALknrwVfGCAIfQCqq1ej9Iv4W9rep7ti12UtRMfTclcL2VzQn+474StRuk1JLZlhN0nryWpOrCOLcWUY18R1VvKSp0SwWXUB80sArgkjoOMzVTbz89xPr2yS/aJrQonOtKjoUkhW5vRtAA816wLoX1XaBpv38RvE7RjGWSKA7YFctDI6xYX07yUsZtmpeM19Od/fqYpgzf0eIOKb61OP3fI0BRcJkDfD3kuvx+8574k+Hqx9IUxLv2QImm+AAt22cxqRiGRP2TaOKP2CFqRR5cEapIStzhnWvBa7hsvKyIEBQ4xo2I+Xfzc+3eCzHV7JGmayYrCaxwUcWfn1jU8VOcPfbul7/Qjxu8upz9QR6gWtsSWeRCBnYTnuFuF4747YAwgQ1immkNjLKZAPZh5d5Yvq7wT+XguAgw==
*/