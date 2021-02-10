/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/time_based_rotation.hpp
 * \author Andrey Semashev
 * \date   14.03.2009
 *
 * The header contains the \c time_based_rotation keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_TIME_BASED_ROTATION_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_TIME_BASED_ROTATION_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword allows to pass time-based file rotation predicate to the file sink backend
BOOST_PARAMETER_KEYWORD(tag, time_based_rotation)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_TIME_BASED_ROTATION_HPP_INCLUDED_

/* time_based_rotation.hpp
YBG7Q3YZz/lNcvyObL2DzqiLBz3xUP+oOxn9xpt9/7N5prCKdwSEyx44p4M3HpWf2K0VsIiadlltxSEl7EvrR2FacTrJ0YR41b3gcvL9VDL3a/+Tp3aWa/DdZftX1NN1azwZ4GvUKevhycxh/73uKm5cWx7FMf5QKlFwQvhGxd/ntUvGodwA9taru11jlKKPEfJqTI5NDrOPFAl0vgImwCrVmPxYCxMsspgl8dfACKyoyWi4gz7WIWoXQrNZbWRwNVDXnU7FPpoZBNL68dB3rMbXqpapH40C/zP9wbtJU38TemAL1ra9wFAd/4DFVttXPQ8Mz926v9hXFdI//GBOfRFpu8ztzj0sjvLuqqQmqfXeqhD+/nkpwmIfDFzLcMZv+HyguQmeag+Vevuydr6H0dsX4v0lGD8M1wosJfM+L1F37jImWE1meD0wS5l4/ozuE63hRfHKlyQGuoOJh9aBfnKcjq4GM0ftaA3j7w9P6iro8bvelXfVHr8HxWGijMeVwT2u7OgHUw5VdYQ677I7eTs8t+PJ2BlquHWQLeN5aU8nJTyCBc1WVCumlrVJcQCz1kwOoW5qkgJi1cZUkOwimZ9LBvXDgzirP+mOxP78ZEhl6coY3OC9PEpK9/qmgR3sKFF2DpdCbCeE8z/p
*/