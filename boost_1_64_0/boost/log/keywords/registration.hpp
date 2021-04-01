/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/registration.hpp
 * \author Andrey Semashev
 * \date   14.03.2009
 *
 * The header contains the \c registration keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_REGISTRATION_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_REGISTRATION_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword is used to pass event log source registration mode to a sink backend
BOOST_PARAMETER_KEYWORD(tag, registration)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_REGISTRATION_HPP_INCLUDED_

/* registration.hpp
VKIfptMvbUluOjWkAJ49W1zVPMELxgConrcPGgmDvzsSlgIXHqdF2azj3PMbpkW1y8NoqqV99U+Z/2uuAdLtIz4uGBmlR+kj9sGU0emlzwkrAyzq3js9JZLy2+qM1twYr3dR24ym0QChg5GBwJseJQ6RdIqLzix/S2d2MLxIcE/bpcLGBZQT9zdLZKj6ulsuVjQRSb7oGxoCSaMYP/wSg7r3YsHyxlcqBeJ+Ndgjm0KoGsLXPShZmPLw9bA9aamn0GBfgb6ElN4gKiABJBFONsLQsFZgxitPwfS3usxtiPZLxKWQsaNLiEPgfMGNktbvU00UdS4937xY+7W5mS+b7qSo/xbkkKl5xmqJbKTdIy0Qm5XBIu9b0tfgyZBCvj+NKlI8XjFHxl4u4uKlqpVjkWNuGOYHVOSclQFx0oOt6pgh3BhjLSVAMRMvPuGjphoeOhWKNwW/B04vBmQ0WapVdIs8Md3BKfy4wU1lPQt5fQpyGha5RjNHE1QNHVUlQMiJFBlJUxz6FvNWncrX9OqBE1EAqdJg27tXiO5u9Ji1iiai1h2pBYuhWCNeAw==
*/