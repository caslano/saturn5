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
PulgdUzwQKXVcXk0seUZ38XySj0gvZ3wPTyYxx1d/4v1ZH64322s93QcxhXnO+0a0tk4Zhkjc8apyZnN9ARRF5y1Z7ofA+DAExGA5hjrOPaTcapL1g/qVv15vhiHxKRhxFKgD5i5N23ft/KqhwWjnkQsJnF826cC9vC0nBJRozJNXSiWUyrTcDrCgg5qceqQaVmPQ8acIUecDZWS4sgaXOochXZAVeoORaF2E2wTj9vZSfPq4uDg4/5ZH5GJ1j3r9tQg5Ype4LD7zLYB5z7IoWlkhyFzsplZLeXHOMGt8FmvdLtNtRl1+/7x5DVc4x989HE1uJbvN9IXcOLheQHgdwf60gn02k/dAifMldehVySdJAFswPIyjmx2No8kbU++rxbecaS31ettresPvdX0w9rPsN579/NpAz0tjdPXNtaEYUNopWYd+Xxg+7qhjuS32ead1vCi19voniipJ5XrYSRsX3f5oicrccumJdcYE0q2/6xpVrjSli3bGWIgV/djpfrybsC1oUahv2hxOKR6eXKHz5bcTSRFjtCHFgEcpZqhRf9LKaX7S6Zi//I6besulsG41Xxe7ItnqOaiRPgSNIs+1layKOJRXtNRSelu+P4dqyPZswtvqSbqlkh9nDxo+Sj880rvdrsyLndl
*/