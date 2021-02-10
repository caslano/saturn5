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
ZptCimrc6WQqS/WacY5wTaiYUSKcbyz/BCOAxZ58wUPY9tAaxRmGhHDMGoGITYLIDspOJrZ+TGZxLtegNkpT7Mpr7ApwegIrjAeXeJY7UjHTlm2no/d4auQlJdq0x1orE7qW4tMTo2RIV5oUpYP83JpOhrk9XwRRMA6moXMZRXM37Htw0Y4hTqzM5J/R1Xw6cQYic2wczh/VFxNMu1goLHPNYh/+cwD2uDMLTdUZ2nHAZovCr1F2eAgjjDFGzzZYmxqHw6eNdHx5cDy1hrBZ7iDDe8CkRwPLCCBEozyJgw9wfm7kG7TwuII7DK/txvc2u26yhbLXRQ46C/3GBHrdd3twAO7Dad+ew1G/gwI2Ti2Q2O6fg9us9XfBAZQVtqHM7T2Y+l29wrfnWW1BCnPZmg334MFcv8X1zWle5J/wNdkoSDgloi6/Z79d7nj85gwyZvNi9HHkT0d/+VM/unFGadr8c9JcDVZgMYmuFzP4OJpeT5wF1XjlKnjggjXJua2Ptp/QtLnOG8Hr2YdZ8GkWB7b/GiUhdZO7vXAygdE0DPCu+WuxHyXoYS150NvLpG7D+R9QSwMECgAAAAgALWdKUoppQIh7BAAAhwkAADcACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0
*/