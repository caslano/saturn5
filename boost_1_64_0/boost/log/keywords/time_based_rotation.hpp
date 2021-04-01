/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/time_based_rotation.hpp
 * \author Andrey Semashev
 * \date   14.03.2009
 *
 * The header contains the \c time_based_rotation keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_TIME_BASED_ROTATION_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_TIME_BASED_ROTATION_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword allows to pass time-based file rotation predicate to the file sink backend
BOOST_PARAMETER_KEYWORD(tag, time_based_rotation)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_TIME_BASED_ROTATION_HPP_INCLUDED_

/* time_based_rotation.hpp
D0dKsmaW4AfMTigfg/5WlaKsikcoT2AZvUZnzwuZbY77Y/WA32IAwVNURHdnBiNaOWDoPkeCLW0CWYBd47JhkytZTVCznG/ZU38HefOc1zQ3Vk7u1Yq0M3x0yJMa0dKsqPX5wo33aZV84q9cpfKrPhfpntCmI6HO9CPPgWaCDIKh1PPXWoQX6VlbOVz5iesX5ugu0nf2GTNHK/SfEV95HrU3U2+Ne2AvkuCt7VYMttSUg565E3yetGTjrSp/hDS+i6pV+pzndFkO9NxP/HRcswwPzgTMKvbv9QF6Zi3gkZbC4x5mnpsfNW8cEDAVc9UAW81H7cSPojHremwj3iUcec4a3cE0mFxCF9QTcmq2Jjtcsaq6jukuEB/LbXlrPDsSP3vCDS2P/5FCNoJ4h4PbLMjunKGuM9RcwewLMRTLxuSzdtXkq88vhrd9bDh4npqLJj91BFrO7AF4HDpLaQvzydOntQn7hVrkhKVoNm/bqpdYqtezpkqD91lpOHLNKvCdFiLWAoo7IFRDAiJMNVk5puKXAeLQeQgszwRm5Rhj5R7CSqSFY19fp2Uomw==
*/