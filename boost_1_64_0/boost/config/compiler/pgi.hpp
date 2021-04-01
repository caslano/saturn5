//  (C) Copyright Noel Belcourt 2007.
//  Copyright 2017, NVIDIA CORPORATION.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  PGI C++ compiler setup:

#define BOOST_COMPILER_VERSION __PGIC__##__PGIC_MINOR__
#define BOOST_COMPILER "PGI compiler version " BOOST_STRINGIZE(BOOST_COMPILER_VERSION)

// PGI is mostly GNU compatible.  So start with that.
#include <boost/config/compiler/gcc.hpp>

// Now adjust for things that are different.

// __float128 is a typedef, not a distinct type.
#undef BOOST_HAS_FLOAT128

// __int128 is not supported.
#undef BOOST_HAS_INT128

/* pgi.hpp
6jKq2SeLvDDORPAaU4EocQ/ECcd1wNAGOTh+wpnfpn2ROSSq068tYQOhOj7A36YqoU+Z+ki9Me/6HUvHqKYgvprNtnYiedfXYKQbfdQF03tIGJzJ6GAJ5nTtFYltGUPkbN3DFmWkYmVmAPLC5/ZyP8wPHDjID41RBpzW1QUoBunf8UF2i3F5zjUnLRCEfnd9o6f84bxgqu074tFZ2fwHeB5RzA67usP6IbWBFIVtMW9mAjFErChOoj+KHLilYvFPrSYol0DN3vu0782gpOhtdEobmtzhMI9EEdTwQgukLD2LqLIQ1lAVqbYT/4mfkWaWynjf9AsN4KGQx/Gh5rsE1rqvnGkjvrlsrKD3uVvxBqG/ae4pOZL3cd9MLjk+sMm4qQPrIW49bIAiL0EmXR8aqKWYeZ7QkmKb27Z5a1RlIpL07+8HhwQXp/hnqfJRlApphz3a9n/ddDCG5IayVqQlvisVLElvmAUqMFDCAFYr2+mLevDiVHI/0+A3rEf+n+HLEhj8bqTdgUXmuaL/f+cd0YjKM/e6ck4UuPmsDAFVG4b/+MJ65LIWz2GGng==
*/