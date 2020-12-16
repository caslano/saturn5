//
// system_timer.hpp
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_SYSTEM_TIMER_HPP
#define BOOST_ASIO_SYSTEM_TIMER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_CHRONO) || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/basic_waitable_timer.hpp>
#include <boost/asio/detail/chrono.hpp>

namespace boost {
namespace asio {

/// Typedef for a timer based on the system clock.
/**
 * This typedef uses the C++11 @c &lt;chrono&gt; standard library facility, if
 * available. Otherwise, it may use the Boost.Chrono library. To explicitly
 * utilise Boost.Chrono, use the basic_waitable_timer template directly:
 * @code
 * typedef basic_waitable_timer<boost::chrono::system_clock> timer;
 * @endcode
 */
typedef basic_waitable_timer<chrono::system_clock> system_timer;

} // namespace asio
} // namespace boost

#endif // defined(BOOST_ASIO_HAS_CHRONO) || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_SYSTEM_TIMER_HPP

/* system_timer.hpp
LlOG1buHLcWaM9mBtacda89crDtttBR6ONNeoGpav74ePc/Zpa1WK3XMoGdV+shmqY9UPts7zPQt8KnN7wzI+7jtkJ/nWnf4hQTtSJ85IUWrhl9Iq3IvwJuCp9IqY+00fwAUqN5HmaPM84jnme+ZuN7v3+2Qd7h/lLTuH2X2bzlWW7PNeTJa8RXVrfuATH8wRpeB+rLa3HbDzbk8gbmdTbuGG6YMvg/niXnwJCkLwL9/Cmt6FHeat98Qo5PfDV5nxpdnC6bfnYmUhV8DukeGgdwwnodxTpzOgY3Oq+EPrmMUrS683Ok69O5PxuhJUOsZlXwY5qMvTL0B9oJnI6xtp9Q9K78x2z4ao/M/FqMROz/huzxu+g6y8L2gm1X5rhjPQ/IMX/twD18pY3fE6M+g9pdVymGY6G+fcaveOa/is4o+G6NNoNtUGRo2y++2ypylLHJ+lM6HLiKz03q7NS9mr3gPoQk660bquztG3wetf7mqo45VtQmQ9VoXpXUTteYdq7LSSIixMW77eev/EtZP0D2qLIbJ9w0bcDZQr+YwuJjy65Sm7q/E6AnQfpUPw6QuIQVemDR1CWXHWzyTCYxV+KO6L0bvB63boPLRsOpvL7F9uvy7uh8SITPI975wJn2SqQt5ULQd9pXe9jXyPqqwpfDSZY163IeRYQ0hasB+Quai7FGaqYD7V+/9Zoxyr9B0qMOtFvZ70FaJgxgmbJbgA5XlI+MrzKctgt/zG2tNqMeakLbPiIfsNeEZ616EblraL7Ox5XgnkN+JLD8Uo+U/i9GuMzXe44Ib8K0xiv7nd85MvX3p4Rh9/pEYlSt5kAPz5W/Osdfi8r2S2dN/idELQZtfqdV3Frgahz7PJgWvY+m8x/11UUvuzIDnZnLCj7ZbuVvjtBW2rhei/S5Av0lbNMVf6sTZo+Iv1e4wd/8dYxa09SytDVxxYphsZ28fWmMxyNCgh/S8XXHSMH8+TMuROG2I4p2UV1XyYNgB6gAtnZCPPp7tr6nT3hQuOHytmTYjONeKT9Za78dv+0+MxkH7tW/imGG+NzxqntSKnKSMBrkmZd7NwFtOI/+M0U9A686u5MOw6m+PbY/H6RuJOF2v5cExyXOlvjGdilMPqGiGy/5muMyLY4Y1HuHz+KIkXYT3J/JYx87LJmBPbr7wJG9Ke+87q4Z58l+mG5S+hOVYlnf9W+L0ddCtr1bfwDCW5yx4/RyfZ/dcd9IIf6qbzBMw5r/PHEuwtfgxqH9QrnVBipr+WVmYescvbN0L/zvwDNrxEhkGcsEcefi5c8rrjncDbBvxnLAR1+8mYq96NPhZcqM2jhh+gL4uynZLCb9Dpk9SpN+2LE47QJds1P1IJi2sBLpe4iAXjKWX31j93dRtsPvasgR+jLS8OCbXkqrnkvB59Klh1Nk+C3G3A+U+4E6I092gkU1aO88Cl3Om8rbqsXF6G6i4SX0Px3iaviPi9CpQ8DUqDcM81xc6Ok4fAa15jVbPWeBc3186Jk6BYzEe9HQMr3onwGXPw9cZXz64+K/J94ekh3vd7y3kFdjAmn7X8+j7p0HH5fQ7eSCEk0s4Hw953JX5DWhbTvv+WeBynZW/lbrzt2VOidP9oKcc+XGct0F1eWPktDj0cXFa/1otXwfuT27pe0mcvgPapufD8APqw5n8KV0xC9ljhnHF4zjfK4pQJ3jRy0DD51TmG8OELrF3EfSHbbbv0WJjQb7GYfPXqP0uQInJIcJerB/6nM+CdqsyGOayp0D5TWeAt79Oa/NZ4FXb2jp3ha1TtmLrlHf439+CuQG6pFIOMWzmdpdhbnLVrNcqx3vtXDZLWfdj8qBlmyt1ZZhoJ59xfd+h8JA=
*/