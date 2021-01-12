/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/log_name.hpp
 * \author Andrey Semashev
 * \date   14.03.2009
 *
 * The header contains the \c log_name keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_LOG_NAME_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_LOG_NAME_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword is used to pass event log name to a sink backend
BOOST_PARAMETER_KEYWORD(tag, log_name)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_LOG_NAME_HPP_INCLUDED_

/* log_name.hpp
2Q9mW5v87J6hkdrzOxhRGvWun2mMdj7c0B3TjPgamTUz66+9egZbovG7dmYNuPlRfcB9LeW+Ku0HXhUHPSBcKsw6eCa3oFHhQy63DQ79if9aGTxZjTU7rb3WWHetgxA47b+2jp+k4m6dXSMVZl2dhr9vh9No8fnFgs4aa62z9gaZNeifhasb1Z0WzvlVBxwODcf2xg/w19wRCVbdrAg+PPzaKvw6vzX8OuRO4hqMMJxvatUR
*/