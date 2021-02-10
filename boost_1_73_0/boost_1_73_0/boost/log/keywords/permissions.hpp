/*
 *             Copyright Andrey Semashev 2016.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/permissions.hpp
 * \author Andrey Semashev
 * \date   23.02.2016
 *
 * The header contains the \c permissions keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_PERMISSIONS_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_PERMISSIONS_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword allows to pass interprocess queue permissions to the queue constructor
BOOST_PARAMETER_KEYWORD(tag, permissions)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_PERMISSIONS_HPP_INCLUDED_

/* permissions.hpp
oZ8F/x6c3ozHg+6b4aTXnnRrIJet1v8evAaT/uVufObhTZBm/x6MzntvuuPJbpymfhrO/j0ovW6Pe50ay+Dnw+9LBIFjxZE20dcbqRJ7uZVaDNcgSbDaurgxlWofdvM7cs0fVfBou6FKJ564KcwT59AKuuuzQ41aGGD5weGAskTyMWhXjRZgltuB/30NM+5N2qM3eBt9bidQVNPL8BaUOlbU9VV/2D4v7BTVRuS8N+r3wNsd9LVZmYcJHt3DcFxtQO0rcJg1ZbLINh6PdRalu24lBFky8wCcW607FOCgOxl1Whq78icevANLst23rKtCZ+g0m73bRzi/qHuc0d6oe17DuHsI2N6bwZBDLadeOf6OFUhQcZu45aKCy5S0AySj9mAMticej85hqMBelUm4im/CyBP+Wl2M+8M3vYGY3XHeoQnLwZ8uC9i2eHJjp05zGPgbjWx0iVWNlUHigtvrYp2SrBDR593txWXT3uVY8kce3JL3ydJ1ekYkUFy6a1dWte/eLZZjPa1rQ8K3F71u/7xE/lIXVcV4y0ecgwb3xuujjKyW8Tl88OKMLqwYvTHmSyCsPeJCXJ5XPi+eb6aY6DqkHACt7DA+QWzMzT3rpePAloq1oiN8gsDxY0EXvX0Sx5lWMdfZX906WPn0
*/