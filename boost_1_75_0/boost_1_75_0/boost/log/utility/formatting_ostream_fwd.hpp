/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   formatting_ostream_fwd.hpp
 * \author Andrey Semashev
 * \date   11.07.2012
 *
 * The header contains forward declaration of a string stream used for log record formatting.
 */

#ifndef BOOST_LOG_UTILITY_FORMATTING_OSTREAM_FWD_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_FORMATTING_OSTREAM_FWD_HPP_INCLUDED_

#include <string>
#include <memory>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

/*!
 * \brief Stream for log records formatting
 */
template<
    typename CharT,
    typename TraitsT = std::char_traits< CharT >,
    typename AllocatorT = std::allocator< CharT >
>
class basic_formatting_ostream;

#ifdef BOOST_LOG_USE_CHAR
typedef basic_formatting_ostream< char > formatting_ostream;
#endif
#ifdef BOOST_LOG_USE_WCHAR_T
typedef basic_formatting_ostream< wchar_t > wformatting_ostream;
#endif

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_UTILITY_FORMATTING_OSTREAM_FWD_HPP_INCLUDED_

/* formatting_ostream_fwd.hpp
G4w5GdY0v0N9uW68Sfz5rjr8dKUmWUiazHuUedVLAJGhwDQ2+tO5J8AwzrEjcu9xyv3HqUZzgNIF9kuizW3mubWAZ1OSiZ3z/vTJyVt2dptmkr83SPNoSZnEq8zvij1xMHKYzHY8FvDNOYctiHVsqiO/cWyrA8tdP9qk+ijBBBrQsAnQVeEtjpb2wU74a2jhUtNj21ZQKPbb0BntnxISD67riI2Wkn2D9kGb+1BKIZvbE7z205YJSD8HOZVT9k9m1LBkyJwkc7qLKA9akjIz2b9FNmG2agY7VxEMyDCgvTkSfUdH9eCtH644/EpBBtJDkp3DyOcuLXQtPuPI74lXXRgDNxBy8QIem6jLGTsssd9nLguCAfA24dIvK2yL/gxSANl0IHlBJOvtiF4L6nXuxSdQwZYhsBl9sWnZV36lKXaHCij+7vmOekB1dlGePP4LhNEOYgeCEISR5nrOLegdipNXLIARk56LdOcMao/bkbdowEe782dBvpzCSpvzl3O91Ts15GWykD/oyFTZZHlPBJmipaJRHcu5LIy32JwuvSCGzy3ujwDjJY8VEwhw2oDYQuijycpe8RULsBMoJA+Q3an6FHzn/BQOjPyXHJ2YEu8nlXR4ZwDTANE5LMV2PNDTD1GIdYn3vOjc6t3mHf99g1L0CXez/Ju2ndg26r47W3nQzy/sniB4d9tprxN3P+2Fd/WBtoG27nYvZZUz
*/