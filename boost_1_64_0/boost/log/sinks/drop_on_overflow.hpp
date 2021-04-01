/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   drop_on_overflow.hpp
 * \author Andrey Semashev
 * \date   04.01.2012
 *
 * The header contains implementation of \c drop_on_overflow strategy for handling
 * queue overflows in bounded queues for the asynchronous sink frontend.
 */

#ifndef BOOST_LOG_SINKS_DROP_ON_OVERFLOW_HPP_INCLUDED_
#define BOOST_LOG_SINKS_DROP_ON_OVERFLOW_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/core/record_view.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace sinks {

/*!
 * \brief Log record dropping strategy
 *
 * This strategy will cause log records to be discarded in case of
 * queue overflow in bounded asynchronous sinks. It should not be used
 * if losing log records is not acceptable.
 */
class drop_on_overflow
{
#ifndef BOOST_LOG_DOXYGEN_PASS
public:
    /*!
     * This method is called by the queue when overflow is detected.
     *
     * \retval true Attempt to enqueue the record again.
     * \retval false Discard the record.
     */
    template< typename LockT >
    static bool on_overflow(record_view const&, LockT&)
    {
        return false;
    }

    /*!
     * This method is called by the queue when there appears a free space.
     */
    static void on_queue_space_available()
    {
    }

    /*!
     * This method is called by the queue to interrupt any possible waits in \c on_overflow.
     */
    static void interrupt()
    {
    }
#endif // BOOST_LOG_DOXYGEN_PASS
};

} // namespace sinks

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_SINKS_DROP_ON_OVERFLOW_HPP_INCLUDED_

/* drop_on_overflow.hpp
dk+RZFBey552m12KtZxg5dwd83WRrNWffH9m/M874O793KHBp3p9C+bAqOb/o7SjULOMVYIVS/OJdz3gH9QHV0hc6nY225YKLfEGz4FzoaOZc357+QF+eLac2dx/up1CkeAqai2IgSOjPqCIthvTXWUQCrSI6Woc5h6UEa47CNrjQH8BFvd30eKiUF2ZeXhprbBWSl5t7DP2ReF7JprfxNvT8/w/C39pCOZQgyTxF1psukO3jdrT+gymiucgDhyxg8r+bF241bi9FUVJbpZRlEQRi+qOCU9vJKB36yAjw+1sRmeh9hBosiuqvtEatUjE84h9Fr0xHRE2zGAE90+mSSP2X/iFeNvZkNWGLuUKq+sB64WDLRsoMuQlYt7RVYP13bmVkFloVT1qjAUhPy6CzX9BfM08vFM0gLDmYMdhzo6abriPwDPbjCJK0IFNtzgrF+JDQKQPhvHPpLF2jU2vqjY/ZJ7284zOUnmRKiphTWZFvai70OOxY1j4ILBZhK50Qpj2r97UwepqplvP/PyGQ6BfhFyiVDO1M21kDLaLSFVlgJuAHSi9IAQwGg==
*/