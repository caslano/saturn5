/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/facility.hpp
 * \author Andrey Semashev
 * \date   14.03.2009
 *
 * The header contains the \c facility keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_FACILITY_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_FACILITY_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword is used to pass syslog facility that emits log records
BOOST_PARAMETER_KEYWORD(tag, facility)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_FACILITY_HPP_INCLUDED_

/* facility.hpp
aIoyZhGiUpbsgTa4YE0YRAN1LQhqYNgMuEFA5EP5lOEQgJFXuBB3LKF5sKrBudWMG51VsjT5+e3xGHzTRs6DpW9WhVfYO+mKCIkfJJx75GqhBzj59AkwulgQG8VkkWRdc2r5G94m4m0ixUYbdxvBDqjIgPg5ZmICIppLWzoAyK/h81TPjKaktptV7M+lxAeMD47zGeI6B19i1A2fKzyTIAXZD9/nnCkoiiRWIRN0kzi5FiLoytE/eEkuA5ik+9+m4A+3mKPdmQuimDAOzN24aeCSj5A9fsz20gysW48/tD9Q/oCwpQZxFnD1hkqe/oGV55N5LG1cXGrc0BUWhY/BKDDd1oeHh4wNIxBBF71fu+ctBhpYQgmymdqbEBsOrNPhtvRdnHxkQ7LYYYWibcJ+j5i/AYNvziMkvgSDq9bC74CNcdLQqULdRbM6JbcBXCv43/Vg1O33MESOyx5H2cbvFofBYQ439zwApWypo4gYkWFFvoTPpvdZIAQWiFwW3AbJvQQDVlKczJEesyBNg3mLY0GEugf7IaEtMSLhheTAx6IV/qHQAcBAvJAsYgGU05y7UfQ9pxUgNg24gA3mewybKpojarI5YAwWNQJGGi4CbgKydDuF9QIr54Te5eAlkCVMP0pYjhGno3xGGMU4
*/