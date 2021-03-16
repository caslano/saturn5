/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/open_mode.hpp
 * \author Andrey Semashev
 * \date   14.03.2009
 *
 * The header contains the \c open_mode keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_OPEN_MODE_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_OPEN_MODE_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword allows to pass log file opening parameters to the rotating file stream methods
BOOST_PARAMETER_KEYWORD(tag, open_mode)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_OPEN_MODE_HPP_INCLUDED_

/* open_mode.hpp
Dyj8DEe+Lws2NZ2rAQYlvWp9tnJmQ41wsSlB/+BOFbSbyEWLuz/QmwXtNaSXXgY58rWCwUCfBHqBI+dVUHZ0XPkQoDjbGQr0gKCzVdwvBe0/cvEMlRFA8QSVkY5cn7oQKPZJUPtdPIclDyievTIKKB4FORroPFmfXXxDEwxFFztN4HFx3XYspgsoNE/3QYdOj3OfdOiMOfc5h86Lc3F0gvbuvupQ7XAPOVTH3f84qFXhOiH52aKOIfnZou4h+dk=
*/