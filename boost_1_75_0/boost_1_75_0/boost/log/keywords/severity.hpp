/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/severity.hpp
 * \author Andrey Semashev
 * \date   14.03.2009
 *
 * The header contains the \c severity keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_SEVERITY_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_SEVERITY_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword is used to pass severity level to the severity logger methods
BOOST_PARAMETER_KEYWORD(tag, severity)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_SEVERITY_HPP_INCLUDED_

/* severity.hpp
5B7yaL1J1FVxU+F6uyn9SgK+ffA333QurN7wx3SkH+o3XhYSAnoJ88P+kKsc2xut7STAAfukLRA/H+fT+6sTRYV1M7rBEu90ebSeWR0vNJ5gbpVHXsdIov+Rb8xCTCzxaNYQKGW0699EXM/L8BDxtktXr1xFgIYX+t2MUXvZQDNYq4WkspK08oy3qkXr+9JWta5rc+PX9rLCUQbVdwTymQOoJpU2aOeQs8zpG6dWn6yWaGW9LUzpxWgKs3Rd3OOEJdbv+8CRV9pPMTER+2+iIipUAzVFRSbPPCO9GJw6co+mz5G6MLt16/ReCSvygz1w7JNnqk8yxNrq8eyPvWs9Ri8bzJD4kU1YZI/4VhGoBPSzdzgXWru8g3KJu21L0q3gb8MeGN2jtEWdXjPjfbJ1/Fe/2n+ZteThZKne2dvsyDisx3tma7b2l3/eADnfbNbIu1NXUBQQ/8bmMlO0XEVbWdO4pisbbKcDcaD8Q975mO+yrQXWg6TTjt9Jsy9nnla+0Q7vZrrN98c1k5O4bCwzepwxY4jr5WiK0cqh/GbntNDSBDRgquuK0GvvEKP9Eehl1eO699q9Ps7uJR9Ys/V6w5vV+6ez9IDTyCcp0dLGkvRbAZeuzMdhHOX94iqjBNzFMa+DW4HjmKqvnWWc6JAuTQFKMK+V5WtR+n1z9wewaMBoZ8pRF0bHAT1l7jVdSncJC4avu4bfq3dMvmQ8
*/