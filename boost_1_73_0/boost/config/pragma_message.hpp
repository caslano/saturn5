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
bQ4Z+PjaSdFtV3+9xd/X7d7X3V3/3tTv3XsNezWPoA22gJGwJbwNtofFYRtYA7aD0WK/qCh1FjaVdAPlb3PrK+n2g1HwLlgBDoAx8G7YGMZDp+3/Yx7D6z1X9V9tM0av9j8/+Tf/5t/8m3/zb/7Nv/23b3/w838iC7HlvgD4Fzz/t3ab/981X1lB8cM0Hjbn/9thPetmJuTEZ6ePzMhgf/XtiaHWOdffD9lhhIqfz/e8f4Td
*/