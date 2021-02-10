//  (C) Copyright John Maddock 2001 - 2002. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  SGI C++ compiler setup:

#define BOOST_COMPILER "SGI Irix compiler version " BOOST_STRINGIZE(_COMPILER_VERSION)

#include <boost/config/compiler/common_edg.hpp>

//
// Threading support:
// Turn this on unconditionally here, it will get turned off again later
// if no threading API is detected.
//
#define BOOST_HAS_THREADS
#define BOOST_NO_TWO_PHASE_NAME_LOOKUP

#undef BOOST_NO_SWPRINTF
#undef BOOST_DEDUCED_TYPENAME

//
// version check:
// probably nothing to do here?



/* sgi_mipspro.hpp
dERBoVQl3w0GaVNz7GSQiVQO0rUUbqGWD7qaYTVLsgJRKVACGkkd0PEOLEXGcn1HiXCxahacycLZloWEZTYQNUjKeQeHqYzKtgUKUaeWoyOhwuqZ0jcpSqnZbgqxvBeIsnZAeVOXSIeyYFwmUHgHmjKjtYk3QqxZOpWN5M9s2bb2DESJVYHtRTCKbFgQyaQDl6P4LLyI4dKbTr0gnkH4Cbxg1uGdj4JT9AZD1hrobVVTiVXUwJYVZzS7R/5LJ91y4zMYXkzHo+BTmJzF8SQZhkHgD+NheOrDIdgHb8BrrrTB/7TB5myhHQBH7uvX7h4u6LeEErlKrqhiZS70hqOvJEJHZxB4n33rafz5K8C0TmyzjK6VFaZT3PGMGoxoFoSTaBRZv7My5U1G4USztlYsPlgGX0fDo2J6+ivYLdAlHM3yZCEOcFFewW7VPzaUp340nI4m8SgMrAnBvSBQCVYq7RIcjDYan7oRMw1wItV25jQDVLW4XT3oyORvm/2noVK1Q1hThd7E3GvCGwo3jHNYUPhOawEshxK92qTFA7gbHO7NoLqm+Mk0jMNhOI4sXYRZ8r96nydj33LL3GolMbv4/j+KsZKpHrbP8p5e7MMPC2CjLJIe4/s2XFKFG21CW13DSZzgzQF7fVTQW4L2
*/