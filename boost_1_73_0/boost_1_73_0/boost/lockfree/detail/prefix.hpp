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
mqbSwOjE3vNSgJ6VjERuRAxuEAsTlXJGLzKHTQUSqQR6o6vbcHju4z6VUepIHnUFk+pKxUj5QqAUkZCLFUfBSwudUDqRx9JYIqys1HmHtAWsKDPjOJw8V0aDL7hUfEZC3CK1tjAfgyCqSkXVB7GOTBBt2u+kNnvq5JaKyPgjdGFhNSojfDikj0zHMnEzGULBopopaVL/uRqSyuNAlzBCKcdFeVKYVdkCk7U9voOhoIqldZPRuXFS96nOfgOSj44lqcqchMgHAsWabPZR0cEqa3Dd+UZi7Wlt8F+X5rneGDqnYrDXnSCc7GHGjTQ+bsLpxeh6ipvueNwdTm8xGqA7vHVkX8PhGS29JLES4qEohSHxEjIrlBTxWvPtRuA1ZB6pKhbYs1orZoStik6653nUREUn8lzpGVc9nSdy/snz3AoznSTMYi6s88HKTDQj8tgiSnmJtgvmPKN12EKB9rx+axFXQyZYXU9x86L7vc+u3YVEx3W5JTyp46tT5wHNDeImHH44bGF/H81J+KM/GqzuuNFgwKY4/YyjVstbaBnTpnlR7nMXm5jbhVt68P4486831RDKiKdb96Um92d+1ELPSee6YMZmluA5bXoE7f8yYmXFZvyLJaCVfyH+yr+DQ/4CUEsDBAoAAAAIAC1n
*/