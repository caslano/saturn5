/*
 *             Copyright Andrey Semashev 2016.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/enable_final_rotation.hpp
 * \author Andrey Semashev
 * \date   27.11.2016
 *
 * The header contains the \c enable_final_rotation keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_ENABLE_FINAL_ROTATION_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_ENABLE_FINAL_ROTATION_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword for enabling/disabling final log file rotation on sink backend destruction
BOOST_PARAMETER_KEYWORD(tag, enable_final_rotation)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_ENABLE_FINAL_ROTATION_HPP_INCLUDED_

/* enable_final_rotation.hpp
bQqvQibhc40qcjHaoawMr5cizpqs8g+2GLySf3z0ayEyEWwMxOt4GPD/mkA8j8UVQQ0Cs10ADvp3NNJd8rSJdkpxLtMiGsMjBYwH0KiJmM4kkQD6rIgMmd7cF86U8PXNzqQwWRk4hl8GGH7mo9KahSoDvMGJ3xjhysEjXK/M+OnyGlbt/lFjOAph5LGsqPNLfyn8rI0rrd4ELvccfvBjctTCSz//0rrHhSMFSuOJ9vRK2kdigfsCjty3d8cxQFuJFfCyIYI57r0JERsD/FHd6Z7rg4fIqp5vDZK52UPWMX+a+tX0/K2/7mULfebsRyF9CSx5JVcHPN1iL0kh6YvlfoCEXkh9Bp9GoB2N64MzRv2gzRt/k90qmqpZ8AsuHaLgxsV3hMK+PGwQdgqvz8xPlW4lODXq7F/x+AiUWNL1JAWtgbhU0FcrYz5PM3QlXQE8JwDzG23Pxnt6lDBNYEhup8PFeimPJ095EBrzqh2M9Gg9L2CHB9eTM89E41+96cdS/qj6/SxBcHz5eFrV9jBvfN8q06+noXOOy9LFLPsaPsbQ7iOqzsBatESrDA==
*/