/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   is_debugger_present.hpp
 * \author Andrey Semashev
 * \date   05.12.2012
 *
 * The header contains implementation of the \c is_debugger_present predicate in template expressions.
 */

#ifndef BOOST_LOG_EXPRESSIONS_PREDICATES_IS_DEBUGGER_PRESENT_HPP_INCLUDED_
#define BOOST_LOG_EXPRESSIONS_PREDICATES_IS_DEBUGGER_PRESENT_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(BOOST_WINDOWS)

#include <boost/phoenix/core/terminal.hpp> // this is needed to be able to include this header alone, Boost.Phoenix blows up without it
#include <boost/phoenix/function/adapt_callable.hpp>
#include <boost/log/detail/header.hpp>

#if defined(BOOST_USE_WINDOWS_H)

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0500
#endif

#include <windows.h>

#else // defined(BOOST_USE_WINDOWS_H)

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace expressions {

namespace aux {

extern "C" {

__declspec(dllimport) int __stdcall IsDebuggerPresent();

} // extern "C"

} // namespace aux

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_USE_WINDOWS_H

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace expressions {

namespace aux {

struct is_debugger_present
{
    typedef bool result_type;

    result_type operator() () const
    {
        return IsDebuggerPresent() != 0;
    }
};

} // namespace aux

#ifndef BOOST_LOG_DOXYGEN_PASS

BOOST_PHOENIX_ADAPT_CALLABLE_NULLARY(is_debugger_present, aux::is_debugger_present)

#else

/*!
 * The function generates a filter that will check whether the logger is attached to the process
 */
unspecified is_debugger_present();

#endif

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_WINDOWS

#endif // BOOST_LOG_EXPRESSIONS_PREDICATES_IS_DEBUGGER_PRESENT_HPP_INCLUDED_

/* is_debugger_present.hpp
78Rt7HX7uWKXZdqm5cobLCu1yNU7nRs6ZpG0VFlRM02zmPMoFvmxjxdbBOZRNK8Boz9yBt9ZG8jraTNLp82WYXrpvIp454cDbn2R7bip1+8S+24O6eRZJ6t3THdirDGdNz5lgwLMZ/qQY8UF8NYG4oMDYlO2yEQpbCxij4+69UWtTZs9GvtkPtPX3dfcJsu4j3+PNLwx98elyXf6+SoYxeT4WlvXjy4TnkfgCMxN3tpFVt4XTg/21z/57ju3zXYL9fqjtM3OS+uW5Kdl65N2OJhFs+YnTxrUZgfHhiny/eMZJ/mpPzLMXthcMW/HrE57mZP3+1p6975J3u8kB5+FQK2zQ/Xz2uD8C2iph0fhhPQ4Ruq71o5P6uC0zyLqYEudmRK2vm5fS8dM0o20xIy0jJC5ewZrAdbAjICexKz6MyNzokK+tLKimMSKS+Zwa5MZq3wpb8x+1Cqxz6UdTTJt7SYxa2nqq1fUj9h5btkfbimb1jS27k1ooWf1HHmulzQlrNDN7nmGUNrNnrpgVmiTV5x1UMC9z+yv8+l+nWD/ZOJ+mb+3pSdurXvBbOUVXuteMFMevhP7y+WOigLI1iapH9bynCnhLHIG6lhscWC+tnS2p/7pLTzj0WmSrGbktpj1JM87iLvjBqu78tAaWaLwFDpNSLHRkGeuIuwO9fOFL0PGcOtcuT6aLWzS1z7MdLWt/WzlXw//ezH2voq86frV+9DfoQ9cjGNdta5+FXmOmeR51Nyq6QNZ9i6NVLncMVT1vPsIN9gV3MJ31u03chnoULkzBMHuUMCbuNYa8MfWZ7HJI7zx94W8vI8Kr87naF1w9udNxNYmh163Be0w0LtCgnX4M2LfwncEI7IroH9CnnbK7DH8o/A19+WRoj+BvobCZFvDUi5hmcz3hnvszzdyd4PYd3Dqmnsa65wp8eiaHWgnuoE1OF6UFXo/hcCfCl2MWQ/l6wler/aQzu3XvQb27Od1ze2r7Fn6X7H6aY+KmeRPzL66zDmrTGYMc+Q5DvLpuaNyZDL3C5HJkvlyO1jxQg4sW8dkfYXvMJs84kdkH0e8MXVMd7Ef7PTmv01G1X3Msd3RYt/KrJ/my3uqdewcez1S19XD2pnpEe24hFvSbaym21ZNtyZOCF8l3coC6VY+u9gd0ox39+jMok9ozp+eVLqoeN7CuRKnmsFSRmfHKM/qly8051NnXzY3rL3Eb8KN35rfJ2q4N/8oOtzb4a2KI9wXTp2zkA2VcYUd/yLvKCqptO99NrymHv+e8cz0nn+U7+n+b417xfDouF+N+2p73E+gFjZ5dWU98a0+hLy60sQhvL2YOSI6vD+Fd20d4dU8iivMaxuQR2sPIY+ubEAe5YyMjvNG3K8Li/MEqctMBml8H60nvusOIY8eNXEID2/KqOjwPgHvJnt4NYPiC++mBuTPpkPIn0fjyJ9g3/qgJb6XH0Y5NPEtOir/6OJR4wuKy+aXSeOh/Ya644p7s/51i/C6Tt2rK+zxVX7PXGQD4tvSxNesnd8iZuabYW3k2tEWmSQgteFxRhI1X1vXHdfaQ5HD1hr2iPFi9ZjoMCYdht9hYQzPkw315MleT55ckll/nuw9hDzZYMkTvhmZJya+lWOj4/u0G5Avw+KrpS2+fHG+jL+8OV8eQnlrXX952w/mJMTWQ/q7PNe8eU36iuld3xn22WMDH2w994SZsfWEvt3MNR/6Za+eE79YfMU9x5+Zsyf56ssc54TmrvkzrxbtvmtO+13fXbt29F+6PoCSyyNauObr3pvc+aYpdze9PG2bL/uLOx5puN7Skb/3Yf7PR158p8sduwfn/qpoxTMbitoyFzBE9IoW3jJm191zBlY=
*/