//  (C) Copyright John Maddock 2001. 
//  (C) Copyright Douglas Gregor 2001. 
//  (C) Copyright Peter Dimov 2001. 
//  (C) Copyright Aleksey Gurtovoy 2003. 
//  (C) Copyright Beman Dawes 2003. 
//  (C) Copyright Jens Maurer 2003. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  Comeau C++ compiler setup:

#include <boost/config/compiler/common_edg.hpp>

#if (__COMO_VERSION__ <= 4245)

#  if defined(_MSC_VER) && _MSC_VER <= 1300
#     if _MSC_VER > 100
         // only set this in non-strict mode:
#        define BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP
#     endif
#  endif

// Void returns don't work when emulating VC 6 (Peter Dimov)
// TODO: look up if this doesn't apply to the whole 12xx range
#  if defined(_MSC_VER) && (_MSC_VER < 1300)
#     define BOOST_NO_VOID_RETURNS
#  endif

#endif  // version 4245

//
// enable __int64 support in VC emulation mode
//
#  if defined(_MSC_VER) && (_MSC_VER >= 1200)
#     define BOOST_HAS_MS_INT64
#  endif

#define BOOST_COMPILER "Comeau compiler version " BOOST_STRINGIZE(__COMO_VERSION__)

//
// versions check:
// we don't know Comeau prior to version 4245:
#if __COMO_VERSION__ < 4245
#  error "Compiler not configured - please reconfigure"
#endif
//
// last known and checked version is 4245:
#if (__COMO_VERSION__ > 4245)
#  if defined(BOOST_ASSERT_CONFIG)
#     error "boost: Unknown compiler version - please run the configure tests and report the results"
#  endif
#endif





/* comeau.hpp
lpu6CcPgXUx2z/lp2l5g/dT8tLzdqRQMuhryzm4ZynvQkRnyrt4o5z3w8PQRxYM7qsibHBvKg66DvF8M58FdVeR9aHwoT+a0Tre3dSgP7qwiT2wbyoN7q7W/3k/w+yGun7u+Fd/w/RDoY1+V/YZsxTG/IJ0Rc2OSv+X7sS1DOMadh+NjnMc3Kev+k24zedAxyRnVdhNHQxXkvG+As6SyTc6DJgY4mG30A7FzgNNtyR69Xr3av7jeJrYCB25icsFOkdwtNHEYFcg70gu7TByWUjwxmv/dN2vi83r4xQBnYxVyxc5Ybm5wiB8pvHtL7v+rswY2vq6xO8L8zHTN8A2wl+j5moqzSfaVuxBHm3G05biric0gdvFpBDPyutklmJHeL54JmHH3WLftiynG0zv5MYIZcf72k4CxO9K137VPmDakuW37N34HnM4dV5WvBWo/tX+0Hw55oOEvG1PhG1KAhLvbdLgUIDrQmQYdsFMr8aa7fXdoo3u1TccDKfboAf25dJDgys0azFt+eSs5Hlf1MLcsnaJJbGVB3yF5+Z4RJXGM3QH+ifxZGfEeU7aUjJzr0HugU1sAr97ExbCbjkKYuses7YGrsEFdv/DfMczrXFVOcjd6ZJxgg+W88h8qy8t58eN1OedIOU9jOe2Bci6Tcs4dPjhtlnO5oZzLDeVcJuWE/LwY1hQfo/UePUZjLwE/EhQDt3Mrs9W86xWkTUrrUVZG50uwGcbbGLHJUYKpOkX7vzGKYZ3i3OS+WyWOedEvCtZzjAO7KQ5ln6rfLh/A9NdmBDk/uT3h9O3L5fx2DoZJrMOFOwAH1oGVLzcM/10VLl8KXefhH7ojhHel74c2AHU8ezD80Iyq75Owfvko0Q3SFnPQThQjbfFUojdNbfEUpoe8LRAz2mJkjGANbXF1HHCVl4a2uHJ7ivO22LwDxZrb4pV3pJzmttizBzjQFkcO0Tp/H4RXbcHDT94JwgfbYs9eDAcB9F/3ua14Zxz2wM+MEOwSwbptdRdenyER7LHHrGPtXirz7sGeGnIE5wSUA+398tvJ9qnau++tUOqjLHpnZKds72/I+rOjAtvqsvxZghCYR1Q8tkaBSBTe1SjOxU4gBgiciMlFXW92uVVtARLb/zHG6y6ubSwv9K+KYj2OjwMHNkfkJtwDD2L4xSq8kpuXGIZ/bxuGM3+Kne0YDhMjDP9bHS73CbsYHu7AcJgaoQ5+bSeGy3ePK/3Fur34EaiW1Q1p/davYMBIfS6q+gIG1aEDWwAbLONPqnBgYxnVmIbhrIyXMBwmrd26TsYxnJX9+FYMZ2X/3DYMZ2X/wnYMx7Lj22sfYfuabuRFiefbYqW9sgabaOCHrL3Oz2BKKmP7IrDT0I7TSPTXtUcPc2E8N0Q7JCrvJCIOYZe8uH57yyX5l6jb7+yHIT6ZKDZfjV2uMJkxAsP39bFyXIBWVb6/alsv+XMa+w8IyUJAm6Pua7wLKOrJCRLeT22k1nnAaj3BdnniOISrNPoqgdgbtlKs+4zV+Tq+E9sU1levuq/s0OEQVx3+LwwH9arDl2+qw425wS4dDmpXhx+6mQ7vbNB4zt5chffVrtb3W6jwvtph2X5xSwiHWsIkUB+vfojtmcdWkFi+K/wo9eSG8lplG4D7uXqffUc9fkoPAm25kLE0to9ivTZ0YEv7AdlNMPisyHMV6Bt+rvCRD3O7YD/I/aK8YTVFe6BDNL7pMC6TIg7kzH6m9qsxrbkzlPvAKMvSJPKBOgX0/pEB2pBQ7oPizPUD3w/FKcibjDrSEjru4ywfjp2mQZgmYl1yU22jo/2TLFDuwdIPfd8uHdEzz0YXKW/Gt5IsLyx5+3RZbu4oNyI=
*/