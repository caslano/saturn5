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
c56BHx2K1EvwKUnuuxmmF28qXbkE9LXbD6dJaA70X3q+j3OE36YMhhbm1ZPzmdNOGrnOEf9JLL1Yhdugptve/OM04TKxjT1WH3KPRZqQWczLUlLanr9i3phNS2cZieFDCJ7QBWWTOp1KWfZ6nQg/IYNybZeJ1kRzLj6anzn9OH7Kqq6YueBUpTSVu6OIJd39zPdXcRkRx/eWPp6tp4pnaYu/uDzbJGYFQZsu394kSbhileeEsH9Iyo8PGPAgVAt6c/qS/9BTafl2Z3O9yFV+QoOt/wdmR+eZucLDIM9V0i/ZRYZYbthLTjgMn/Ea/1iyZs8vWTK+w8Zhl63EiJZttQEbqAtsiadpwWbwz/KLF/2D/e5Q+2iHJBp+fUkbj83DL0n+oEf+Q5LxqaJo2NLzx96kZI+3qgcugQKvzP7+G4HNPGGHXC03sPifEhCPthmIFG88a3zcGBwHHYcFcTliaTuTMDHwhiFIEvPaZIuJMf773K/kDnwmlzgpO+DxoaPa8Pey9ydGD+dY5Dx49hr189tVTB/CTIRSqAqzPTG7ldPmPNC4ca71uZNL3IpmVr5bqdCJkE+11eQw9b5QIx17DJMStxQJlXIR04iYtLa0TFnuW8X1TEwSUyj9ls/IaD5TlbDWN5qdWvXVDkW+Hd9l/KNR5X6XhuRmOXVvVZJnksDxB6X2hmUQQEGHuXH5OZU0D/Bz3rRL4eN4I7ou
*/