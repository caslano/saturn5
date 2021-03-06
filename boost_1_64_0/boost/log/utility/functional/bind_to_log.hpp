/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   bind_to_log.hpp
 * \author Andrey Semashev
 * \date   06.11.2012
 *
 * This header contains a function object that puts the received value to the bound stream using the \c to_log manipulator.
 * This is a lightweight alternative to what Boost.Phoenix and Boost.Lambda provides.
 */

#ifndef BOOST_LOG_UTILITY_FUNCTIONAL_BIND_TO_LOG_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_FUNCTIONAL_BIND_TO_LOG_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/utility/functional/bind.hpp>
#include <boost/log/utility/manipulators/to_log.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

//! The function object that outputs its second operand to the first one
template< typename TagT = void >
struct to_log_fun
{
    typedef void result_type;

    template< typename StreamT, typename T >
    void operator() (StreamT& strm, T const& val) const
    {
        strm << boost::log::to_log< TagT >(val);
    }
};

//! The function object that outputs its second operand to the first one
template< >
struct to_log_fun< void >
{
    typedef void result_type;

    template< typename StreamT, typename T >
    void operator() (StreamT& strm, T const& val) const
    {
        strm << boost::log::to_log(val);
    }
};

template< typename StreamT >
BOOST_FORCEINLINE binder1st< to_log_fun< >, StreamT& > bind_to_log(StreamT& strm)
{
    return binder1st< to_log_fun< >, StreamT& >(to_log_fun< >(), strm);
}

template< typename TagT, typename StreamT >
BOOST_FORCEINLINE binder1st< to_log_fun< TagT >, StreamT& > bind_to_log(StreamT& strm)
{
    return binder1st< to_log_fun< TagT >, StreamT& >(to_log_fun< TagT >(), strm);
}

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_FUNCTIONAL_BIND_TO_LOG_HPP_INCLUDED_

/* bind_to_log.hpp
zvwcvfNZKa3eMwRopTjL3OyE0K+Rs2X8aOQlooMWfNmxaN2uovJdeqqgM1YXWQKTGJnF6/Rg+miRKx4cjVahCybWWjr5TRKE4cL/ft5FHABFHoW2i2tapyK+lkc+2Oj2hZ1U+AT4gLtA9lEm7AnzykTdbwUoRGVSYvs4WiSBjKl/AjG+ZtbW4WuZp6BqU4lKrMhBil+pYIW8CWeGSABXCfCvFaVxjsEok2+9lFLAdb7w+8Z2kiysyF6jcqkcG+YwadglQXBoa30f7zv6oXfMF+qgFO2I3JIK8ngIFcaK5RH/QGrxjvo2bzGWMryYUL8vKo1PjWKYfu6Gd9/xQe5Hx/42TO7/n9PV4G9ps7xj4ppU5ssQW4xrt83H8PExmelEOrp2gtwUVBV1CaujQhYm5mK91OWSLQbTd84DCU44X8uVX9LEs+Tfxphsl86LgZ7glh0KghKrzF+qybweYiPYMGGu97rj1nA/pmAW68qxOlkq/f8HIdUx7Kb1iCRYgMVP5GYS6RXxrIis6bszcnKMd+QUxPpFb6gcvYbvwIG4exgTZ/71xKAwSK2PWQ==
*/