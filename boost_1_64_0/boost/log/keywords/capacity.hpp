/*
 *             Copyright Andrey Semashev 2016.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/capacity.hpp
 * \author Andrey Semashev
 * \date   23.02.2016
 *
 * The header contains the \c capacity keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_CAPACITY_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_CAPACITY_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword allows to pass interprocess queue capacity to the queue constructor
BOOST_PARAMETER_KEYWORD(tag, capacity)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_CAPACITY_HPP_INCLUDED_

/* capacity.hpp
i5T1p/4deURbS+sSIql0Vf2VZ7uFJfn8aTiD4ebfrLfwO5yR4ir3xbHTdLF3bK9Fr+fA+zHpT0dC3RTU4+P+BgBTVFcxdsbXFktIGPjlsH95OdPx3Ym65BeCyYNx1X5/CbOxCZ/fBGNXX1t9DqXTGgmvawIHYxeMy/bIYvG3BDHqdAc4G6jysrDNsZTn6RSPZJYmH1S4gCnQe8f/q1rzUC3yEVWoYWq/Av8WkQQ3ohlUVme4Fy+QIBk6JNK/Gn1QhfBO75D8/kpzJznuJdR7mFqcOMEpXlfJyBNytBkN7hLUoyTixRJQP9whckXPiXCNFdahe7DxvbWpTHTLpX/eYYX3XrWPnF5IQNtLvIYqYrpeddemTLHw14PaU9XJCvbIiVEW8VIe/Zw/1ikM5coM2mjN3CNT6RxFTLNQDHb71oCupOLuLsFlnGimFLvH/JnCeUzKaexaG9qNCmAALouX7fLAZaAmWKVgTYWYw+EYZCIcmzCuDkBqIheWXYZoAf5yHMKMKDmzlrHpbah+Wf2FLsE2t3mAFR56WALiJGHmMae1a+OL+wBbcVqPjw==
*/