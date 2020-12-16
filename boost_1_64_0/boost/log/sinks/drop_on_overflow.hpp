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
j64D4pGypvxxo/xj1jHHVnU/S+Ztj8i24pKCiflFFXmWzNte/mfJvO3lf5bM216xZ8m87f85z5KjtLwHVbPfp5Nfqu7B3+Iq72xpgz+7dkxY5zPA+e2emDLZVY4yiVl7dfYT7tF+n2hTortN7Y7co9xc+drS7gq0pd0VaEu7K9iWdv8HtaVI311c3d2WknfYcraNqDw6CMk7yt+Oknf869pRZ1NL7q9FTSO/C0lAZDAMsliYtUO/uxJ9f766DPchw091rzRME//9qp3nPCNrq7htNzPwuTqOTk+Wu7ys3l0vcT/XO8WwFuJVMQO8BNEZTLJhL/SWmIk2TrV3fSdFnreTxC3gZZigGcxq3Bcm0Z7ZUvisnFdCSjWkHBK6GX5aRL5zUI6SOA63z/Btcj1F3T0zX+JJdcVry/IUCTPMN0bJK5o4vtTqCfYX93O84/m/meeZPhj5JpWeQ/Ga6qLpd3nlm7Zt6/lpv3OL+fkzjdKkXWlf8dd9tH5Z9LPcjpO7pfxV8msMZSbXv3vWXoflmrbHH1L0/BQca8Gd0MNP8nPaHrWs02LaoVq7+pyG9Ryy0NHnnnPKQvvNmobivtlrbqqzbt3T07am4V7wanhdbHxq75KXdqw4/I/hPpNuKjtlIuHdMtQ9/sa/U6fInvfURNwf8Y6gZJZ7CeKvtvjjnVjjDOk7loWXMY4dG0+S8P09n3uhX+d6mrhnefPM7+y71Rq5x7r2u+Vzxc/RUd98KxlTVibzxf1rk2LetrqZN4vdERKmcYKkO3Gkb0y/Utwb+M93su8JNULpO/IT8tvYdy5MqD22FrcW1F0le3ZUithtxE//lNbIyz1UzLA61G/NGfcFzICUI+h31Yz0NzvGXl9Pxtli7uD6DRjpZ8k/o9NJ/srG0Fxvk2saTlEJX2EbazJi+6Jt//rsczwPkxzPw2TH87CO43mIX2kTtcN+C/06pI3FLk/69HapA84+aBTu00don16SKveHTRn74GdEWJ+fCMP7J47FzjPZQ7h29WP17x3gGdj4ZP+YgPjIm8Qn+SO85s+vo1ZxnTO37lrFdZtWi+7aBZ+2+eLmo7K6VHr1jFfnZe75Lp6OV8V1y9y6a/F04yqui+bW8fr1dNHcOmfxddTcOnnxdNQqrgsYT5fxa9uPw3KhL6xHmcm5LpH5Nlhf9aSDGHlVV92nEMfCDDhOdXC+tfMfMidGOIj5GGNUp+ZEuBMOh8/DXPgXOAP+Fc6Gu/QcnlfgtfBNPYfkLbge7oFPwXfg2/A9uBe+r7pUH6ou1UewOfwYHgU/gQPhpzAPfgYnwr/BafBz1bH6El4Pv4Jr4bdwK9ynOlY/wc9gSBD8CANQy03fLd3lNlLLbZSW22hTFm6LhqvtCLdRw22CqfB+X7jdB0gvR8Planp5vnDJO+Knd6+GW6/pbdBwVT0dh+rYOxSuIeYHDXeehpsAk1T3rXvILzwJzlDdrpla/2u1/u+GefAiPX9mttbzPLhVz/15Qc/7eUvP+/kbXAy/1nN9ElUXrha8AabAy7UdLNN2sFLPX7oDdodr4bF6Ls9xer7PMLgK5qh9rp7XdD6cAi+w5/hg7+nYRcd+k1UPc6zvu2WJsB6s6zuvKQN2UZ3Ko/W8qp7wUNU9awzP1nOaSmFTuBg2g0tUV/Qe1RW9D7bS83haa/m0hV/CdvB72BV65KkbTIdHw6awO2wDj4HtYA/YBfaER8NesCfsqucb9YGD4PFwMDwBDoV94dnwJJgNT4ajPdXZg/3hBDgIToWnwBlwMLwEngpvgqdrfzsTboDnwE1wOHwWng13huy1/FtEnq/6fO6LCajMCf3SAuH2WA/y2DqQ7p7q9/12Onw=
*/