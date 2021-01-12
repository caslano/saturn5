//  (C) Copyright John Maddock 2003. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//
// Boost binaries are built with the compiler's default ABI settings,
// if the user changes their default alignment in the VS IDE then their
// code will no longer be binary compatible with the bjam built binaries
// unless this header is included to force Boost code into a consistent ABI.
//
// Note that inclusion of this header is only necessary for libraries with 
// separate source, header only libraries DO NOT need this as long as all
// translation units are built with the same options.
//
#if defined(_M_X64)
#  pragma pack(push,16)
#else
#  pragma pack(push,8)
#endif



/* msvc_prefix.hpp
7TBirGHcItIeSUEmrfH3t/k3/+bf/Jt/82/+zb/5N//m3/ybf/ttmxMZ9Ef1/2ekJtyT2/t/y33/Ld3G/heXb8Rb2XinCevBz4vxzuItq99GHdswVF/KOvYKYUaVgkzFWVT8LrbNjPuJskVKORRStm+ULULemedRtp98vn/neLq/pj3H4MtKFS/CLV7EtfHYMnW/znGVvl2/l86n9HLqHXch9FNKv533y/mVLRzthLKVNpxY
*/