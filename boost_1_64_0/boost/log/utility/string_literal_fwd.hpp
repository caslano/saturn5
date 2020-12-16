/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   string_literal_fwd.hpp
 * \author Andrey Semashev
 * \date   24.06.2007
 *
 * The header contains forward declaration of a constant string literal wrapper.
 */

#ifndef BOOST_LOG_UTILITY_STRING_LITERAL_FWD_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_STRING_LITERAL_FWD_HPP_INCLUDED_

#include <string>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

/*!
 * \brief String literal wrapper
 *
 * The \c basic_string_literal is a thin wrapper around a constant string literal.
 * It provides interface similar to STL strings, but because of read-only nature
 * of string literals, lacks ability to modify string contents. However,
 * \c basic_string_literal objects can be assigned to and cleared.
 *
 * The main advantage of this class comparing to other string classes is that
 * it doesn't dynamically allocate memory and therefore is fast, thin and exception safe.
 */
template< typename CharT, typename TraitsT = std::char_traits< CharT > >
class basic_string_literal;

//  Convenience typedefs
#ifdef BOOST_LOG_USE_CHAR
typedef basic_string_literal< char > string_literal;        //!< String literal type for narrow characters
#endif
#ifdef BOOST_LOG_USE_WCHAR_T
typedef basic_string_literal< wchar_t > wstring_literal;    //!< String literal type for wide characters
#endif

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_UTILITY_STRING_LITERAL_FWD_HPP_INCLUDED_

/* string_literal_fwd.hpp
09CAK8TXvJhuCrxCXghaztvHEBFuNdGeJwmdI2Hm8LSbEBSGLyk8wyxkM0thfoqF1FNS2IuahRzXUlhVQwRJNaSwg0YLuWZMZm38QskUvxR2ET1oiLkjT9dAEd4QHp53Xr/EZeN4+S4RXpt0C+PxEfJdvHy343U7VMgmcN0PBlXFlxfeYb1YOyWNndMy2QhDJvNG//I8+he7eQC/5wvCzzqeb330uhgF03E9PzvEHELQ9rGRrI4yln2kjWTdDGPZdeNoNtXvAh0ZEElWB6QRHn/hL5GnUdu8POKyF3mchnFZsJC9y3VqR3hbKGSVubumZie+JvElS2b9lUR2R0tmcw3JLNI3mW33S+ZtZ6hwP4PHMdAchji+zJ5mccrT7BNtHEs1jGE3jE+z6X5jWG2hUzmYO7ysLEM//io7ycawHmjbf0f7PMcwgZXwRRh+k1kj8wT2WdBMlhViyWszud8YntYfBwXiSyKfsbEsTZnBbmvj2QzDJBbhO5FtQ9sei36B6y38FOf9QbM8vbmsKo9DYp7eXPYy1yPJ3JikIF5JrK+SxO5qiWy2oRXilcx2QO91Qo+KMMt5XGyhgeQQvURDSQDrj+9D5I5OXqEj5FCyUu5PrEoQaaLspX4og9W1AWSnFkC+0nbTF70t5KB3f9LIYCG9DbtpVWMEaW/MIl8aA8gfxh30XZOFXDANIn0wfM32203bo4yODuhPbqHmlzDvpRcDLcQ3qD+ZFRREdga9TScHW8im4L6kDNIrIeQE4f2uiOdKrutl0oKk62UrBmYDz/tZaJcvo4/NZtPQ9lm95rDNhmxWzzebHffLZqnmBewG+jDeZgp/pbm/Z8MsOPWlI3rY3+UZbLq2kEUaZrFtxvmssd9c9nnALJaJcdhvwYsZryvC7zDuV9XjUQ1G4vGbHaLi6wTX2Uw2HX1pmNdstg3tXgOM646hDc40T2e/Bc3Ky1fu79hrf/9eZ7CQPcfzxEl4uypkZ/g9pwarZKg8SZ7JwrUpbIv3FFYfbepHpiksLWAi+zlwOg87VPhpxf0YyCYRTydMMy6rjD7/C/QVlfANgXfJl1J5IslZdJgSRVYoB0kvtSyZrw6lmlcUqex1hNzyqkDKeA+iSw1R5B3DETLPpyx5w6c/reAbRVJ8j5CSprIk3jSIvukXRc75HSRb/CuQk/5DaUtzFBlhPkKaBJYlAwIH0TNBUcTbcoR8YcEKW3AWHRpShqwMOU4GhtrJ86Hd6d2waMLTWcS1Ik/TUJ4O/CwtmDI8bQ6gf3mDHWOTWFvlOfYz0mI80tmEMcsq9Os1kM48jYWfKlxn/7z05LIOvD7tDSpBkI5sGsZKEzBWmsYyUX9/w/hqNupgcYyveL6Ib93583C6iTgiRF2WyWUv4K9IXdZefOexgdQFzyf3Zc0jgrmM0u5usg/oaXrf7TtSrvwbrvdpmuc2AzKVu02JOE5GhYhwaS/ITbyNnxkYLO4FmR5uWZYaLMLl8po87b6ATjxcqZ+b2/uyCTQLsje4u0YsWPjNcnO3helyOhTyi7y9z4pYyXxCRBzoSMhPcPnUiBWsnpBPoGMgP8XloyPqSz8F58VjPOQ7ePgV8uJGJ0P2AZc9w4QOxAkZfz7Ek69wR+o+IJtA4h6USY0LyBAea/aArAFJeNAvS37wvqzNg35ZhwdlNOfvMv5s/AZ+//0ZtX9eG8KvblxfY7iRrJd3yRm0uGqTEwyTySWDUbrp65AcATvYlUAf9ofFIJvh73nhL5D7m6yHJcMM4bIpocHELjeTU6R12nWsxY+WShu7S9P8VpBy/orkDNwoXQxeQvP8ecF8zP11wLi5m5wpz6F3FU0yep+n1w3f01PG9XI=
*/