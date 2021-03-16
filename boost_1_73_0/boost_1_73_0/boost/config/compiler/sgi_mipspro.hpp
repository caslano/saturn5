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
YzvqbuPF/inhBe42pm07HTFegGfXMELkRN9LiODCrwgRWvg14SLC/yJcRvgt4aOE3xHitbkf50H4oyOZ938i/Jyw2RGHS8svxg+bMED31SEME/oJjyUMEhYTtiMsIWxPWIoJDrU/g3APxk/4BeH5hCSbxa4kXEo43t3GN6ADtcN3NkyIj1y+Xxw2CwghGxzhl2npPsublqIk01LhrlZupnKzlFus3BLl6pVboVyDcq8q95Fynyj3o3LNyuG5FC4=
*/