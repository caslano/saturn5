//  Copyright John Maddock 2008
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  This file exists to turn off some overly-pedantic warning emitted
//  by certain compilers.  You should include this header only in:
//
//  * A test case, before any other headers, or,
//  * A library source file before any other headers.
//
//  IT SHOULD NOT BE INCLUDED BY ANY BOOST HEADER.
//
//  YOU SHOULD NOT INCLUDE IT IF YOU CAN REASONABLY FIX THE WARNING.
//
//  The only warnings disabled here are those that are:
//
//  * Quite unreasonably pedantic.
//  * Generally only emitted by a single compiler.
//  * Can't easily be fixed: for example if the vendors own std lib 
//    code emits these warnings!
//
//  Note that THIS HEADER MUST NOT INCLUDE ANY OTHER HEADERS:
//  not even std library ones!  Doing so may turn the warning
//  off too late to be of any use.  For example the VC++ C4996
//  warning can be emitted from <iosfwd> if that header is included
//  before or by this one :-(
//

#ifndef BOOST_CONFIG_WARNING_DISABLE_HPP
#define BOOST_CONFIG_WARNING_DISABLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1400) 
   // Error 'function': was declared deprecated
   // http://msdn2.microsoft.com/en-us/library/ttcz0bys(VS.80).aspx
   // This error is emitted when you use some perfectly conforming
   // std lib functions in a perfectly correct way, and also by
   // some of Microsoft's own std lib code !
#  pragma warning(disable:4996)
#endif
#if defined(__INTEL_COMPILER) || defined(__ICL)
   // As above: gives warning when a "deprecated"
   // std library function is encountered.
#  pragma warning(disable:1786)
#endif

#endif // BOOST_CONFIG_WARNING_DISABLE_HPP

/* warning_disable.hpp
NzaeNM39xewWJ0E9LTgpxKVauUxxy2ukpFCOYyhO7WU0OS0DfBxdbdsyIw7TH4FvALwTvAoyx/5NRYdlLhFigjeGWMw6jbMpGw0mWSvg0ineVVQQxYRmm7OYxD9rBxNSMan6nJRJCCW+5hRkonzWZzEJfRaL78XVEBNM4L44i4rMbFlUZDZOYS2eyyT0zIpvYO7pORSvCbdLtHrhNP0d4GG+uDhLLuDNoCW7Wbc7wGN/Mdnh+OtMJraEslm2uY/yumgb53TwWUMx7Vz2vQz0lMyaw0pL51x0sAoTvL9MPbSYVWhjFU6xHto8ew9NsB6yiUz5be2hKdZDU0yoOMWEivUyF6Ryed/cFRJrVcLUjAkmMdxsn9YMCiDbLBzlMsHF1m5LhSAyv744mwkcl8pM4DiQPgdNpxfrsQneR3OZHFXmk+jmr5g+aymTD9uy77/Wcvdx+ylcJ6wVk5Jf9ik1arNjl244y3QDdqdqfZ1xG/Yd8Xt9kwGvLxwc9bV5r8W5vpCRW5pn5HaHS3KLI6W5O6L5+dVRPTfhPeTx6msdN2DdFzP0sgJD7wMg+4qK4vHE2uLflPhKjZLSMkjlRklTRU9Jf9Uxe0ldZWnJ2eqVVcuXVdUNJffXVdSOLtOrikr04oOJfYXdDhtu3NBkNMebjJZ1rdVNWzpuwZ1Hurydz3b7O/N71nU2tS/Avb4+o7e03+jtWlnSW7wq0btx
*/