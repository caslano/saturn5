/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/message_file.hpp
 * \author Andrey Semashev
 * \date   14.03.2009
 *
 * The header contains the \c message_file keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_MESSAGE_FILE_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_MESSAGE_FILE_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword is used to pass the name of the file with event resources to the Windows Event Log backend constructor
BOOST_PARAMETER_KEYWORD(tag, message_file)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_MESSAGE_FILE_HPP_INCLUDED_

/* message_file.hpp
jI94jNhmvDQ6AcaVHuOR/wJjN8WINybjwSsV13cm13dBrvPRUEGvH/uV8UzfHb8UwcN95OIRFF6x1mZNE362Q1lLOWoj8YFfaR0GV0S9MvQf9loIbbqa2vSJmg1vqfYczPKFrGkqJsZ0vzy3WPMnjyeQIKhIOXKBS256G/iW75E+nTYH98nhaj7c/Ybq6JEpmbnQr5DqqkzVnXsU1eHb7rTdNd5BxwJGa/ZikuSaks47iqSPdbXAjk5t6KOEElc=
*/