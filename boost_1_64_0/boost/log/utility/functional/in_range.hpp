/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   in_range.hpp
 * \author Andrey Semashev
 * \date   30.03.2008
 *
 * This header contains a predicate for checking if the provided value is within a half-open range.
 */

#ifndef BOOST_LOG_UTILITY_FUNCTIONAL_IN_RANGE_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_FUNCTIONAL_IN_RANGE_HPP_INCLUDED_

#include <utility>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/integral_constant.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/utility/functional/logical.hpp> // make_common_integral_type
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

//! The in_range functor
struct in_range_fun
{
    typedef bool result_type;

    template< typename T, typename U >
    bool operator() (T const& value, std::pair< U, U > const& rng) const
    {
        return op(value, rng, integral_constant< bool, is_integral< T >::value && is_integral< U >::value >());
    }

private:
    template< typename T, typename U >
    static bool op(T const& value, std::pair< U, U > const& rng, false_type)
    {
        return (value >= rng.first && value < rng.second);
    }
    template< typename T, typename U >
    static bool op(T const& value, std::pair< U, U > const& rng, true_type)
    {
        typedef typename aux::make_common_integral_type< T, U >::type common_integral_type;
        return (static_cast< common_integral_type >(value) >= static_cast< common_integral_type >(rng.first))
            && (static_cast< common_integral_type >(value) < static_cast< common_integral_type >(rng.second));
    }
};

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_FUNCTIONAL_IN_RANGE_HPP_INCLUDED_

/* in_range.hpp
yaJtJMO28WO+8BY+x2Bb9WVtdZq1lbZXxuwpbRPaqiCtMCErqaAQHcnIrk5hCr7jb9ReTB6zq+Ff2Agzu3ZguqaeYmtA9oY3JLkrvFmta1ZuUmp3eJT8QDfwe+AV5KdIEuoXBLQZ5rMb6hdWS/2CUD/Wr5h8vY6tTrN7d6xNu0B6B+oSUa1jfm5hPuiojQnAm2OoD+TX/OtvAZLmT6oun4r5jPX2MmlXZ5khUKYfGwdANjynCHW4yergK7na+1oL2E+srkNBYW5+WpfO1e0cpkjASy0olCTDepTp6lEkYX31/UH7nfWVWre/s9wQVi7zbzamzRHqcuFFza/xz8k8CfZYr6sLGMS9LprPbMB8foZ1W6+rW7hB3db/C+sWrqvbTfj/V2wwvv0OZg+bbXrZO2Gb/3agQWRcWsRwnx8kCaZf4N8YMKZRUau1a16oH7nW+8rtr2D9pzj5DV8sXfNT+OST95WMeGbF80+fl6RoLydffjyjabOF3/VseKthYMhzyR9CvNfu5O/bvnvQUsXj9oCUe/fnXL03CcrGckc3XJO97nL/yrcLYqpS/KfuBTmY//qasMfan8n5afE3FceWVNwDe6WjbE5+3oXsFd/eaHnunYcGNmr3aY9ToL+nkx+qpg5/a+z17DbNN91fOnf/t5I0FfWcF7TppZdmN5xwYWfmc1daT+0Oe3KY/3C/6Js/9er+zsYvf/9qii3lTehnWO7RdbMfbremasbv6/184NtWTcCmf5Gd/Nn3tA6rrLfhmR/mHl351v3fjJOkx1CfMUf3jv7kl6eG/2X/I+U+TzbfKkkLHU7+T5df8tq8cPH6oR98l5QxtfkVwIbIHzI6peGnk2+2885rdGVRt1ug/3Zst4iI3eO/ePvH+uMuzW80blujs5L0FOr/9vx3zv3y7bqbc1ffU+/wmql2aDfU8+73Unyzpo9c+rH3irxmrWN2SVIblL9704xxlcqfPjr5eItfHt2wEs4ZfAd2jJLwD+aIatoZUhL7/8MgzWL/Pw5SDvv/iyFlwv8vYePQN5AOQUpsB/4IdK4Ev7HxqYLjX+iKMlAZOoUdqAK0HntuzJ7D2HNL9twRqCfQfow/EKgX0GHseRR7jgHqDTSWPU9kz4nsOQ2oCrQAaB2gJUD9gH4DNAY3FKv1nsX0dkAaxM8pgd7hQCcC7QA0Dmh3oFOBRgKNBzoMaBLQWKApQL8BehrSeib3CSY3BFIlk/sW5LMBvQDUE+jvgKpAL7PyPgLaEujHQLsC/QToEKBXgMYA/T3QSUCvAp0C9DOgSUA/BzoD6FdAM4D+EWgu0OtA5wH9E9BSoH8GWgb0JtCHgX4LdAvQ74HuBnqL1SNdBrt2qK7H0MnV9RgBKV5m31yEfPWBLmd6LwHakT1fALoK6OdA1wK9BnQd0KYgbCPQPkA3AZ0G9AjQ40AfBPoSe/6GPf/Anr+G/vAc0G+BHgH6PXv+kT3/wp5v+UvSUaBSQPWzDPQoUDt7DmHPfuCAVUBDgR4F2pA9N2bPbdnzXeCgx4CGA60C2pI9t2XPPdjzwOYwNgLt3Q7GEqADgR4HOpg9D2fPk9nzaJi8TwCdCPR5oHHseTp7nsWeE3rBnAI0BegJoGnsOYM9l7DnnP6wLwm0GOhJoPex5/ngoKeALgX6gpPPnlez53L2vHYM+C3QR4CeAvooe97Gnp9kzyegM5wBehroaaBn2PN59vwme36bPV9kz7fBYc8CVcGPzgGtC/Q1oB2Avs78rQdfozMMUMK/B8zPiEE+G9BIoCFA+wJdDjSKvT9MWwPD+M/et2N+9u8Ks/eHAvUFOhqoP3sOYs+zgcYweRF8bQmkLpPnAakZk9cF8uE=
*/