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
w529/kB1zsDub9sf1/bBXn+vsX8Y2NuaYDoKz6Ye/HDGZyNjSiVeKUJnOor8E9xcLba2x9RFUZclr/BqaK6rxvHMO/H8cy/y9dmiQAWXTc+ZwWgEzjjw8RTdnz6VHpjYodgoT9ppNWH8D1BLAwQKAAAACAAtZ0pSscLFoxgEAAAQCQAAOQAJAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxJTkZPX0hUVFBfQ09OTkVDVENPREUuM1VUBQABtkgkYK1V72+bSBD9zl8xx+kiO6I4P3pK26TVUYderLhgGdLUkiW0hiVstWY5dkniNv3fb3bB9iW5KPlQrARYz7w38/bN2p3bsPvLLsvVcPDslZi/BC+8r5MmtfhGU/X/CUlyB+0HE+d4fwHVALZZd0kfXpR1Bz2TlXRcJ/o5SV5AN9dF6n8DnTxP9COutJld/lBUq5pdFQp6wz7sv337Bl7Bwd7+kQOnpGSUQ6RouaD1lQMnmVn5qyC3t66kHxygCgh37wHGBZMgRa5uSE0BnzlLaSlpBkRCRmVaswW+sBJUQSFnnMIwnMxGwd8O3BQsLTqclWhAFqLhGRTkmkJNU8quW5iK1ApEjgiInzGpELNRTJQu0lNQtF7KDkYXQbgUQK4J42SB
*/