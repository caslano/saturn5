// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Adapted from <boost/config/auto_link.hpp> and from
// http://www.boost.org/more/separate_compilation.html, by John Maddock.

#ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_GCC_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_CONFIG_GCC_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <boost/config.hpp> // BOOST_INTEL.

#if defined(__GNUC__) && !defined(BOOST_INTEL)
# define BOOST_IOSTREAMS_GCC (__GNUC__ * 100 + __GNUC_MINOR__)
# define BOOST_IOSTREAMS_GCC_WORKAROUND_GUARD 1
#else
# define BOOST_IOSTREAMS_GCC_WORKAROUND_GUARD 0
#endif

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_GCC_HPP_INCLUDED

/* gcc.hpp
YnNVIGltzn4glohfWcImQsPCG0kMj9iFvR5w1gF5CVAKAcRrJYM8z5QRlDslZn9HpCHg7LMnWTWg2dPQDcw9shtpggyBhaReohDZdJxxBAl39tMNuA10j5p2GMA0X6Ka6qQNRGqzUWClrcBQYeiZCUOu55chZd8qZMMn2ZNRuWteQO2bDzf0sQ3CFfw64jZQ9Y7r3xolVHJl/FqjF6avC3f2mzmxG9/4Q+9nBdLga821D1vGQrdACYZ1ZqTk4NbAt2+Izt5dvbl8O+m0kUZBkofc1GlbrCOqidzR5U/jyzfDydAESA20ZcUulAJkU90jyGmBbIwrx9q2YmxMGzX2EamJAmLCDPM4k4yhxbAwVPvxz1YPl+e1SWaBr4RIphFPVr3A2FOv37Jna3FzZypEw7tEqHQb1sV4i7U+JqSup9AGsubRqk6kZycbKYNt56pcgINw7qmMc6SXGWM54ntwSl6my0tRqgRiGl3bkklM/jVh94OMs2cxz/8Rpj704iUniRBA7EfMlDxn3xS70GpC0nqcBZGX8TmQ8bhkatA66OA5ZUveN7VAt2IHnbpI9vM0vu+2cI7MpY/X0v+u3IebikaQo2B74ecWefPj2xPaIy1FCpSwZLkqiaRojf45GeMvYdj8HSJtEGlXRKIc
*/