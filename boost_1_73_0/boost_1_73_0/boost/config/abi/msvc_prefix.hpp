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
ppM2XfmPV+RStlYju8N5NYGaPSZKvC2i8TJoGB6OVw0bU3siUPOcLPONnlC86mSo37d4N6HhVScDC3FxZKj+HP0tCOU3z/GG42WQX9WAJgw1B/GJFUW15wI1+TKTVCPs6agYmR0Kx92hxJhhY+KHinFToxgcjTyLVh+xa8lYOnryXFUgWF+CtRQrGtCIy7Zqd1UVB+sHago/53SIEv08i+hg/XpgGtEUXhtTR09aVeS3s8lF1R+DW09MaLZbX6M=
*/