//  Copyright (C) 2009, 2016 Tim Blechmann
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_LOCKFREE_PREFIX_HPP_INCLUDED
#define BOOST_LOCKFREE_PREFIX_HPP_INCLUDED

/* this file defines the following macros:
   BOOST_LOCKFREE_CACHELINE_BYTES: size of a cache line
   BOOST_LOCKFREE_PTR_COMPRESSION: use tag/pointer compression to utilize parts
                                   of the virtual address space as tag (at least 16bit)
*/

#if defined(__s390__) || defined(__s390x__)
    #define BOOST_LOCKFREE_CACHELINE_BYTES 256
#elif defined(powerpc) || defined(__powerpc__) || defined(__ppc__)
    #define BOOST_LOCKFREE_CACHELINE_BYTES 128
#else
    #define BOOST_LOCKFREE_CACHELINE_BYTES 64
#endif

#include <boost/predef.h>

#if BOOST_ARCH_X86_64 || defined (__aarch64__)
#define BOOST_LOCKFREE_PTR_COMPRESSION 1
#endif

#endif /* BOOST_LOCKFREE_PREFIX_HPP_INCLUDED */

/* prefix.hpp
pt9uEVxsoPsDhrWaWgOIjnpoE+wMQbqYlf9E7Ar9bRwEaMmQX8kXmrsQ2NjiD9f9DKPcxSPB+KNBBydukPOO7quULUpkVGQk7OFP/bbIyVT32Jj3hu4fHmHChTScAtl7xJtE8U+06iYNvL4jFBgU12ivfWPgON9UmYHi5oj1EvX+qtMNlaapB8flprWzpcXGpdZNvpqzqs3UGpcArwvowyOfY6XDsnZN5QF1HJPXbjKTkmGgsyw12+c1TF3HhGaZ1q8BRuo96ehuhtra1hfO2qmpTXx8Dx1f1YsKSrf+QthxkWNHdjv7smY+4cBS5tOGyIMFr+x2l2MOgSvqp896JWKdXTEtul8kOgT+wPWVawsBkD7W4OAtYNVj3Vqx9t44z/e+IO2IvWY90zCrK9TVkdfIKXgxUzu1JmR4q5Xr5W2kVx6O9vpy3THap9TTKvjDqCD4M081dryEetX9lSk5+Yya6dK0KTExqWD6ORV4mdOYnFxcLHGsVIg3m0axRhLuA+UMSQgS9jOnFvpcmN5DMwpKOXsP/Xa76dF501Wwe3dlPDeuRo8Cg43rgrffJ+8mhc5L9R/f/yk8fUvt0XTxQY7uGBr147CquH3D137QA9zFfn73QapbbkfeBK5j2ltXx0K0eEbwmrame9736DJ1KWz0i3Ds6BvXGt9jVwWd1cjiJ5MasGNTc4tRv64e/wblxKJzuMmN/63Tr6sv
*/