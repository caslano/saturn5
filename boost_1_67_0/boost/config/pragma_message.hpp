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
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
*/