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
KpWbs8mZLx0+w6YjoDhMcjHv4pOamoDa7VbD7vtWsLbn25YKTwB67E/CTYiTk+W+ivR2jRB2N0i13y8Prq6uv87aL25zQlyjrOM2zqniGe/k2G9kt1d2H4bN/IgDAtlgWb6gfhaEhqogjuBmhCj0X9U1tJ/QJxienced9Krlx1Y3/bgWXbvZAWvZwHbTcRyySCJwf+DXX363+SH1y0wIM6iv3hURlEPWXXCsHz0dKLY4b9NleqnErL4p5KOyF+UhLQp0JOg0WTBdhTjDusKvCNViAAcEWRhssT/fezD2ervVKbWjnv71PpZfuZEIRtiPAX5c6c3gRDSrPJpPqDRfgCOD9pdTe/01W5spN0SWeFgH4A3o8qcLPQ53QvFKcMZ2fKQDvbzvN6ZFQwJrbEYDpUUriZcjPVpYcwr2AnWv5Y9E41Zz4sZQm7BHI1Mxf72pgP6yFCv+2oGxmdiO80Le143Sg9CO9GLc9ynohnAiVFWCaIO+Ux7s/MZLsY16jtKOm/9C3nD4Ceknkhmnxw7NIPMV9Uq3bxq1FSUcpTM45fSp2IGjyn6ZqOVnu3jr7dHkqGD0g5CF5JJwGQ7dAR/vTDiTFH+M+JKYAH/cemgviXloziCCk5hgwW+zWSLn75TdRVQc0BUG4BAChBDcgqdoCO7OoKE4AYI7wd3d3d2CuyW42+AOgzsM7oPDwAAzbTftou3p6fqt3uqe79zz
*/