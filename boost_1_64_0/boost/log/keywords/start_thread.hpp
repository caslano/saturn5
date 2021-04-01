/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/start_thread.hpp
 * \author Andrey Semashev
 * \date   14.07.2009
 *
 * The header contains the \c start_thread keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_START_THREAD_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_START_THREAD_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword allows enable/disable spawning a dedicated thread in the asynchronous sink frontend
BOOST_PARAMETER_KEYWORD(tag, start_thread)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_START_THREAD_HPP_INCLUDED_

/* start_thread.hpp
0T08narW/ZiPMY62xIycDN+hnl79z/7zPWyg5T5xKXoHXxF5A4XhvMGZxFZThUVq2R3LhhEnWgrTSZa5LLxDsVQUyPTflBk6ixxaR/fy2Pz7ti4xOwStNtve9+N3pOu7SldgwuFKlhgczs8XGTi4tQLONyl7tRP10shbwhVoaPXiA+a/7nXaOaCtWxQZsNIgMeI4VjEJY23CHC6dJi6ipzGfaIN5/sv7jPVe5IrXjFYDi0PWxNwp9dMpeMMdUp2kX9l++z/eL8iiS9BQw20uamyb7enU7EaOGfq7urbBWBifwe08mLFJN2az20dP7F40AFCFEmlCxqV3TSYyQJD8GDwWOapkxol8C72syfSWBBvFFDkRbd1+qE7Q9GmJ0/Uf0aJQ/gSfcXZDw9x7MPLBKnuHODW8CYS+kxtB1ZnPDKNgDtklRoI8ZZkRGz0kLQYtLUxZ6RUP4TKiFnkkXR/4bSFXqQbNCwv2qdCkAgZmvD+lwd1WUpYe+gr5GrWinAWQjvcwIwgMXuPGefy8OGRzy+GrQ03UXVr76XG9SYr2EqcZtUHRsBD1mdL93w==
*/