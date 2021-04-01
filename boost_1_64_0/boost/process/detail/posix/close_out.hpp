// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_POSIX_CLOSE_OUT_HPP
#define BOOST_PROCESS_DETAIL_POSIX_CLOSE_OUT_HPP

#include <boost/process/detail/used_handles.hpp>
#include <boost/process/detail/posix/handler.hpp>
#include <array>

namespace boost { namespace process { namespace detail { namespace posix {

template<int p1, int p2>
struct close_out : handler_base_ext
{
    template <class Executor>
    inline void on_exec_setup(Executor &e) const;

    std::array<int, 2> get_used_handles() {return {p1 != -1 ? p1 : p2, p2 != -1 ? p2 : p1};}
};

template<>
template<typename Executor>
void close_out<1,-1>::on_exec_setup(Executor &e) const
{
    if (::close(STDOUT_FILENO) == -1)
        e.set_error(::boost::process::detail::get_last_error(), "close() failed");

}

template<>
template<typename Executor>
void close_out<2,-1>::on_exec_setup(Executor &e) const
{
    if (::close(STDERR_FILENO) == -1)
        e.set_error(::boost::process::detail::get_last_error(), "close() failed");
}

template<>
template<typename Executor>
void close_out<1,2>::on_exec_setup(Executor &e) const
{
    if (::close(STDOUT_FILENO) == -1)
        e.set_error(::boost::process::detail::get_last_error(), "close() failed");

    if (::close(STDERR_FILENO) == -1)
        e.set_error(::boost::process::detail::get_last_error(), "close() failed");
}

}}}}

#endif

/* close_out.hpp
K7KHMFSTmisJHYT01pRCcHKg6Hy9ztP+GfFBUtmKDtztn6+jxrc8AmESqbv6hZT44ppOmVYPyfIjUKWx69UrOkP03TC2hClK/m1zGuIM/15OJShDh5SSbWWPy22br4gr2uiuTlCXEpdvQaO4X+O+JHk6ObtU7N8Uccx1bEnTXm+x9E3NbYNyoQa5iEPgndJznvlVm8xeg2Xak6wG8Hh4pkBLDHOy3tNNB++A0BTmYlwie8QjpvfinKdg+alj1Cr1Gx9iSLHdFcbCs53g9CGPxxpIMXzZaRnHMk7M3rZ5FRc1AN1hJY6j6J69z3HBXzu4xqfFuh64R8hBVD336swZhRb2YCKjP6bbY1VUzvrrf8I1VH1OovADKubsSgS/sUmL22XeIUxnSU/tUgHqezvkmCf7kxcrkdW955LIUuiga75UCO+ZmxwWdRgHEpPsMcF+YXBSQCjFSzLr2Hk6NYGEwlenxoZ5gNau5QYImn2OsAi48qbAcMREpSGKcY+PDt9uBM+ZhZlCHsgQt7EOH2nEHHnKPPgj1q5BHb97y0WH9C5vxwLTSH8JuWN5tg==
*/