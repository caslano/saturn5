#ifndef BOOST_CONFIG_PRAGMA_MESSAGE_HPP_INCLUDED
#define BOOST_CONFIG_PRAGMA_MESSAGE_HPP_INCLUDED

//  Copyright 2017 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
//  BOOST_PRAGMA_MESSAGE("message")
//
//  Expands to the equivalent of #pragma message("message")
//
//  Note that this header is C compatible.

#include <boost/config/helper_macros.hpp>

#if defined(BOOST_DISABLE_PRAGMA_MESSAGE)
# define BOOST_PRAGMA_MESSAGE(x)
#elif defined(__INTEL_COMPILER)
# define BOOST_PRAGMA_MESSAGE(x) __pragma(message(__FILE__ "(" BOOST_STRINGIZE(__LINE__) "): note: " x))
#elif defined(__GNUC__)
# define BOOST_PRAGMA_MESSAGE(x) _Pragma(BOOST_STRINGIZE(message(x)))
#elif defined(_MSC_VER)
# define BOOST_PRAGMA_MESSAGE(x) __pragma(message(__FILE__ "(" BOOST_STRINGIZE(__LINE__) "): note: " x))
#else
# define BOOST_PRAGMA_MESSAGE(x)
#endif

#endif // BOOST_CONFIG_PRAGMA_MESSAGE_HPP_INCLUDED

/* pragma_message.hpp
BR0IBS2PT5wOOlXz57R8BO2Rb/EJK9mUyZ3BKsXA7/e5tazdv9gaYOoJ4vJ1pDX2NFLhSWMtUXGsYlF976waee/+4hgT0GJ8+b6r4dStPCzmWXMSuqYlzA9S7I9EpU7uQqRm3//2a2ZNiaLFWsDefUkvwouCiSg6mI7UMWO6fTOtxrz2RllppdsBqDKUzttHxEtnhNlqARmplx5i+cG0f98dOeuKSOoWGJGwzpYjtYVsYJB4GrdgQrkwD58VlRa23uwcFEdGXpWaJsXenURI3FTbEUiCLugmKsxy5NGdLd9lQryhO0ts2DdKrCP1E934xfB2g7MHQcPducglt1cO77EooWdc0j0GMPie5hhDStKp2XIMABQI+gZyLmJ85zUT0R1swU7xV/rdwlC2y/PeN5X2qpyNikdALRLzbj78mMqnvRSw9N48SeA3wA/24zGM3rKehzN5Pn3t+sFcR3TNGIJNm8vmirsIj+Vco7Qr7mryhd58+Zz+kTkDQW5BfeWjFPZnBICdaRkg+3Pt3qnXu3v23293ve6L1qvbfUkEj/HQufxVEAfNWlOYsg==
*/