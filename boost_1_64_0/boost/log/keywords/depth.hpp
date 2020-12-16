/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/depth.hpp
 * \author Andrey Semashev
 * \date   14.03.2009
 *
 * The header contains the \c depth keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_DEPTH_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_DEPTH_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword for passing maximum scopes depth to the \c named_scope formatter
BOOST_PARAMETER_KEYWORD(tag, depth)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_DEPTH_HPP_INCLUDED_

/* depth.hpp
WJ9rLtFyvRTeAafATaq3XdeTf1nXk/8FzINVlq5TDmfD43AO/BLmw29hAYzx0E5hPJwHm8D5sDnMg53gFbAbLIJ94CKo120dQ8i11+W6Xc7hKHin9vNbtfwf1PLfrvm0GV6o+7lwI5wPH4YL4I/hlXr8GCwz4/i4h9TzNkZWOda398B2MAG2h+kwE2bADjAbdoTnwl5aTl3gRHg2nAG7wQLYXc+fBZer/lW6v1n3zTr074Rf1364Q686Qj3roNHj/WygXnuHXlKEehkuem7r7mdFqJcToV5uhHp5Dr0yxKlX4tArjlCvNEK9sgj1NkeoV2H0+AXpXerQq6xBb5ZDb1+EelUR6lVHqGcdqllvWiztagDrmCPzkXJkL3ISyRrIOurIemRHqXc9+pSTDaw+SAnC2uSyxnf2BNZTQNYj25EpN7BOOsf3sH0Iv9WwCLcyJOkCwn7JfinBMXTS4Ul4gJvvjK8bcJFj7XKkGPdSZARuR6tjrEG4ZeN3CrLJPgbLkTzcd8KduB2Ae+AJmMjN0mqObUH2Iodw74bbyRs5tpL1y9nOgNW4pwwibcgIpPhCiHsZnMx+Cdv5cCf7Vcgm9ncg+5ETyHzil70KXSQzF79IOuv3r8ZPDpzP/qpV6K+Nto4g5XaYuO2C23EvRucI24nnkR7cY3j4qIApNxEOboNgHrIvl232q2EJ++uR8exPQ9ImsgY73IbbGrgHboOriFsWx3axnQuP4F5ik/31MKuaNNj+byYu7O9GyolPJZJ4W7SVMpg8Q/I4PgiWwDIkbzDhwwx0NnGOI/jbw36cfUPKsbTvkZ9s5yDZbMftpNzgHnQrOJ5v67F/hP1ymM5a/5W4VyG72N/H+avZzhhCebGfSL0rwc8mZARulfA4Onlsx1xE2mE3mMma+dmrSast+JlG+tZwrJT9EcQ1F51ipJz9MrgDOYBsQmcax/fhvgx/29k/yvYJjsXcQrzZ7wyPw5gc4ot0Q8Yjubjnw7TJ5Cl+dyHL7OPs5yKr2B70MsfgfPa3wPX42Y8cRXaxX2r7RVK+Tx7g/4AdNtvH4Zpq4smxPPYPwDJ40ta300O4MUNJE8y4mDQiechqZBuSwbEsZA/bVchJpBL/ObilXEK8kCK2p8FSJJd2uBnGfEsecN7D6JZyvBypxP0AksGxXewfQE4gWT+gfIZ5HzrGs530LG2LcihlewuShvsu2Aemo9cNyUEmI1W4T8G9BP0SuAnZieRz7ABcDcuRncgeZATnPop73BrSh59DuHVmO8+OL/kRN4W6g3subplsL4NrkPFsFyEV9j7cD+OGo4P0QTbjNgKm3Up8YDnhZbG9B/fJsAQ5zPYO3MvZLkanFClDqnCrwG0z2wegNZV8hpV2OOTnCY5nrCWeuI+Ao2Eeso/jy9gvZXsTUsX+dvZT6E9X1Y+3tiH7kBNIZly8lYtci2xDDiAnkYwG8dZ4pAhZj+xADiFWPMeQ0UgRsh6pRI7b7gnx1ghkPrIG2YHsR44jaYnxVg6Sj5QhlUg1ktGQ8yDFSDlSiRxB4hrFW1nIZKQE2YJUIlXISSStcbx15nfmd+Z35nfmd+Z35nfmd+Z35nfm929b/7/46iWFPRbPXnDa6/8nt7OMzcYROg7oEk3LxUi5Pb/wMRmL7518ikWkQibV+5YLZsntWUuXXr14idrzWClzB5cYW3RN4Ajx35XvC7Hucw/luMdnr4wtO0y/HYVFctzd5ix+nWvsqF8xoGXscSwRnRTXufbOcx8TO3921vptZiyQ493M/IDSpMjnk6+UeY1LHPYxdK1ViWPQGkYm3oH2DtLrW/I7TNl0hnth62zeY/rLBJtLWTOX+ArGlEeIfRU=
*/