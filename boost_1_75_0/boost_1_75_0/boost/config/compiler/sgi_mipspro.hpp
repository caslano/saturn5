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
NMmyIveg5+fneIrbhu047Tc0w27ezw/A8grMn9ynuZ/NuyY1DR427+fX3Ok1ztv9RhzA/TzG9UFOhduXk5nhHpEz0HAVOOc5LK82cJXmrLfskSo4pR6uyOM9Uw1LPcxamLR9437L9Ji5b7w5L5kUtXCZnVUUtQccHxnOka4lzlKHXLeoQ4kpdnn6fN5xN8J/UfVhYPktzPswbut96rdcXLNo8B2Ov89Lr9VezfLutu9w3Gc457hG5izF6ZeqRwV8ogYJmCSnX/R7uLKS734u8+SJsrH4q4AxzPff2ZcYd8n6pb+af3Ul51/V/ifpf0iBWzTAYr/dOJqsI4tQRw5CHZmfVkdugTf1XNltsLwC8yeYQqUnVmHpZaV99F3N5Zmv70xUG8rvw+q7avV3ZhhGfsFrnlR9eRVK8G15Y140dtlXZzjKnWtdt+e0und6ZI2+Nn+K47GCUkejXX42tVR+71U24aq/pt6N7ca55Yq8rf3M69+f49VqWJbAhGBc+p2ASr/aA1UfNgyHs7F/es35gCP/EWOrfROKXNg5xX6DWKX2WKj12MGiAPnSez/QLsSgvgX8MCz7YX7TX9XRUgff0Kvq6IMpTfFXcLrjM90PGMZ6+xyo2iRf8v9P1tly8vNS76uQ8wqD4eB62pAhA4bntOGqrOEuhbAy3xxrXZafPjaoRN8VbVWpelEF32GEcsBnMpL70Lch2Fd0X/1O
*/