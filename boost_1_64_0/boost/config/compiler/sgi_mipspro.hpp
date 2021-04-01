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
jidzVb3equnFW2zm4nJZ12lXy9trugwSABDX/j/V7Bl9JCAkBPz7j3aNWF4MRrhoQXsTqZKnVYUVjuCHRcYYTmcgN77+bw7z72wPzxaa3VEzfglfl/9aqjTtJRZRS5JrsNaeF9JeJ7ygBDn3iFU97/OTfXPEaMXwhSFxcKu6jPRzZyAU5yH1oJb6n2Hf70PX2JUFPyBowxN6xHh7PRJ3IyFHzzLvMV3YIZtvX5RNiLPQgdqTt1AdVWwt9I2KDeWSQG1lL80/k+3MbHCe7HFPPfQWeTMavu7/Chh6TQ+Q1Ddefz5Vo3eWey5enM3HZ/zOF6N930pUjCWEoTxQiKUq+WqlhW+TxFxb66zrgbaueXmCYrBDcBfqeMT9xpoNxeRhlGrkEh0vO7xJ2zIyhodpoU4B8NWvWbNBFU1ctgG9mVZfCuI2PL+z1AdvqzM7M/u4USVUPfyTwxk0+bT6A2WZlJw4T8t7c3NCz1wZ0fKW9oiq6Ph3kO0T6cYF1Fg7gh7P04AoHk8O6wsb7irDwDmMhVs6VEsvbfu1Liw1uT2ew6WMR000O2gf3MgZlw==
*/