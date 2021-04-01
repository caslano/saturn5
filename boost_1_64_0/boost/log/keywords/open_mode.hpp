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
xTREFZQPI6RxncYa5p/VNlbkHeVAlNtp9b42jCDj74mc7J9ShKRo9g0AwH40uCBLzoTXs1sj6Enu/BgtLvdAoyAK3iErHkbi1D0sEjJENfCR+YHmZO81k+ca/+qTHEqbCccLdqNcZYlZJEfYEXrwcOMOxfBk8BuqaTp2S2g44KM2W5ToVWtZwaBNAJSSO9vXWOx3Qphb4dy+3AzaArDuJPdPw9iCyTop3neeR7Ux9hwEg6vfnqoHLAEiZI6VcqjYTLjQWQBbTuoUic8Uc9nc/hh0JbCnmMXykuH53Z16hdvM803leNWERSoYiLlAAVArRvxgMnhJfslXvbW+VOZVTAEUlZusRAK6pot9+zM9A2XyYGuA6Tg+rSOGxaQMUSueQK42w0jLCE78iGMcEjIKzLOa5Y3/sEun71tQa7hYAEEWz6U4Vg11p+6OkleoZ8qM4n/ZQR8/rBQW8f1nS/OaVkB3Bb1na+N1RqnJhG2Wn7mOBzN+8DqpBEVJ8zd4kCTdnKjtkPMQLH9eSe3UMeIQ5Fob02BT/5xmc3FwetTox3LFPsEib9ZrH/aH/g==
*/