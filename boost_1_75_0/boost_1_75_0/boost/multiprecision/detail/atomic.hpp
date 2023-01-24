///////////////////////////////////////////////////////////////////////////////
//  Copyright 2017 John Maddock
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MT_ATOMIC_DETAIL_HPP
#define BOOST_MT_ATOMIC_DETAIL_HPP

#include <boost/config.hpp>

#ifdef BOOST_HAS_THREADS

#ifndef BOOST_NO_CXX11_HDR_ATOMIC
#  include <atomic>
#  define BOOST_MATH_ATOMIC_NS std
namespace boost {
   namespace multiprecision {
      namespace detail {
#if ATOMIC_INT_LOCK_FREE == 2
         typedef std::atomic<int> atomic_counter_type;
         typedef std::atomic<unsigned> atomic_unsigned_type;
         typedef int atomic_integer_type;
         typedef unsigned atomic_unsigned_integer_type;
#elif ATOMIC_SHORT_LOCK_FREE == 2
         typedef std::atomic<short> atomic_counter_type;
         typedef std::atomic<unsigned short> atomic_unsigned_type;
         typedef short atomic_integer_type;
         typedef unsigned short atomic_unsigned_integer_type;
#elif ATOMIC_LONG_LOCK_FREE == 2
         typedef std::atomic<long> atomic_unsigned_integer_type;
         typedef std::atomic<unsigned long> atomic_unsigned_type;
         typedef unsigned long atomic_unsigned_integer_type;
         typedef long atomic_integer_type;
#elif ATOMIC_LLONG_LOCK_FREE == 2
         typedef std::atomic<long long> atomic_unsigned_integer_type;
         typedef std::atomic<unsigned long long> atomic_unsigned_type;
         typedef long long atomic_integer_type;
         typedef unsigned long long atomic_unsigned_integer_type;
#else

#define BOOST_MT_NO_ATOMIC_INT

#endif
      }
   }}
#else // BOOST_NO_CXX11_HDR_ATOMIC
//
// We need Boost.Atomic, but on any platform that supports auto-linking we do
// not need to link against a separate library:
//
#define BOOST_ATOMIC_NO_LIB
#include <boost/atomic.hpp>
#  define BOOST_MATH_ATOMIC_NS boost

namespace boost{ namespace multiprecision{ namespace detail{

//
// We need a type to use as an atomic counter:
//
#if BOOST_ATOMIC_INT_LOCK_FREE == 2
typedef boost::atomic<int> atomic_counter_type;
typedef boost::atomic<unsigned> atomic_unsigned_type;
typedef int atomic_integer_type;
typedef unsigned atomic_unsigned_integer_type;
#elif BOOST_ATOMIC_SHORT_LOCK_FREE == 2
typedef boost::atomic<short> atomic_counter_type;
typedef boost::atomic<unsigned short> atomic_unsigned_type;
typedef short atomic_integer_type;
typedef unsigned short atomic_unsigned_integer_type;
#elif BOOST_ATOMIC_LONG_LOCK_FREE == 2
typedef boost::atomic<long> atomic_counter_type;
typedef boost::atomic<unsigned long> atomic_unsigned_type;
typedef long atomic_integer_type;
typedef unsigned long atomic_unsigned_integer_type;
#elif BOOST_ATOMIC_LLONG_LOCK_FREE == 2
typedef boost::atomic<long long> atomic_counter_type;
typedef boost::atomic<unsigned long long> atomic_unsigned_type;
typedef long long atomic_integer_type;
typedef unsigned long long atomic_unsigned_integer_type;
#else
#  define BOOST_MT_NO_ATOMIC_INT
#endif

}}} // namespaces

#endif  // BOOST_NO_CXX11_HDR_ATOMIC

#else // BOOST_HAS_THREADS

#define BOOST_MT_NO_ATOMIC_INT

#endif // BOOST_HAS_THREADS

namespace boost { namespace multiprecision { namespace detail {

#ifdef BOOST_MT_NO_ATOMIC_INT
typedef unsigned precision_type;
#else
typedef atomic_unsigned_type precision_type;
#endif

} } }

#endif // BOOST_MATH_ATOMIC_DETAIL_HPP

/* atomic.hpp
fhyhyBXo9Fj/2V5/rPQellOTlW6Fp520seuv1YpAK6s9h6bUQU7QzPagFfXH64L9k8WyOZazCZWVF/dEX4aUCF9X+I1LGYwZO0F/TBmMGTvT4y5PGUwZOyuc1c+TggskFImZAn5VPjQ0wbUXmwNqyJtmHMXEhjzXOC30OPjnA4qZk5YZmIx1HlY8JfJDZwBe4dO+M9VvW4jgNOq3XX4Zrw2art/2ucTLACWqr12v36Y41JYtJM756Cmt9F3gaVUpVzo2w0UVPWL9UXioBRxb4CfpQHCoU/19/VnMRRyt2ONg9NGUc1iJqO6+IUbCna89H9qZ2N5DqrgwhrILY9rh467SfxLBRP10ElFhIVSAyn4Oc54SRlrDVUbItuqWXtsH3kCkF1NyclvfFyCmQIMf7NSDNLKUj0UZtV6LzlGgUGTZ8eL+cjCq423nNDkFntzti8Go0aBjzQgKUr8eflT15rNadWuM0wi6l48wohavgOc95G6j5SRX9zCf0YoslLy4FX0kJi8G4s6ilMXbeiIOAIkKIFEBJCqAxODkaEQ5xYQHPXtwEXriS3jp7cNgMOyQjmG4sR/X2XMJOrpei3Vcc2glJeq4rsI680Yd1+nXOPQ6rr8PcOh1XFfzIS7Zp/EhVqzvFYlx/Q69JCbNUgCyKT0brOMaY0qJ2+GJUEpcGWshTjPXQqwht79dmnvkZuxpghNr88nB1hVy6pd3
*/