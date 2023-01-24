//  (C) Copyright John Maddock 2001. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  Greenhills C++ compiler setup:

#define BOOST_COMPILER "Greenhills C++ version " BOOST_STRINGIZE(__ghs)

#include <boost/config/compiler/common_edg.hpp>

//
// versions check:
// we don't support Greenhills prior to version 0:
#if __ghs < 0
#  error "Compiler not supported or configured - please reconfigure"
#endif
//
// last known and checked version is 0:
#if (__ghs > 0)
#  if defined(BOOST_ASSERT_CONFIG)
#     error "boost: Unknown compiler version - please run the configure tests and report the results"
#  endif
#endif



/* greenhills.hpp
vQsZddXzwIyuI5f/IJcD5PIiuZwll/8lF/E4XHLIJUQuf0EuVeSygly6yeX75LKJXHaTy1Fy+Rm5fAAX8XZ7IBZcIqTmwkJokwO59lj1Jv3vmsbzASj88F02nhvfpeP56LuZ8x5283gunAO08BIBH0yNpwMt2GPFbW+YYb8PhfnvMdifM9i299Kwb7fA/iRLPC7sthMi/svaXvge578J/Fug8G0Ov+Y9Cr8+A/8GC2d//RzxLeEujC/hWds+moL9KGSegHT6PaYPvHQ8ZUty6D1qS/KTTC277eZa7hClk0AzH7Pjvi//DuFXpn5aAIU/+xX7DuNX9Duu/VW6hhzB3E+PkzM3t2P80OzfkfwV/467f2X9DvcLLC75l7Rr469M/fsYFH7K27WftWsi066Fli+/mfgRHMPXp30gXi4f/DwFO+sczAtIN5xj7fqzF1L96z1H+/cr59K1DGBzLbcJ0iT071smXu/yepLnUt8/rZ7qP+H7z5nG5TEo/PQc//5z7PszLVtgGZcvyLhcJxBN3Wzj8rkZdtb7QO+8z2Dr71PYV72f+WrL2rhKFE8Kp//o2qh53wR/BRS+z+F3Mvj3ZeBftMB/k7R9wZe2fa8Z9gQUfsVhTzLYr2Vgr7DAtpG2P/VH265/YIK/GAp/9QGDH/6Awr/xgzT8py3wHyVtf83+ZW1vN8O+Dwr/zmEPMdgPZWDfZIH9GsFJD6fb
*/