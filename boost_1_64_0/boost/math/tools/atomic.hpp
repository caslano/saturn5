///////////////////////////////////////////////////////////////////////////////
//  Copyright 2017 John Maddock
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_ATOMIC_DETAIL_HPP
#define BOOST_MATH_ATOMIC_DETAIL_HPP

#include <boost/config.hpp>
#include <boost/math/tools/cxx03_warn.hpp>

#ifdef BOOST_HAS_THREADS

#ifndef BOOST_NO_CXX11_HDR_ATOMIC
#  include <atomic>
#  define BOOST_MATH_ATOMIC_NS std
namespace boost {
   namespace math {
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
         typedef unsigned short atomic_unsigned_type;
#elif ATOMIC_LONG_LOCK_FREE == 2
         typedef std::atomic<long> atomic_unsigned_integer_type;
         typedef std::atomic<unsigned long> atomic_unsigned_type;
         typedef unsigned long atomic_unsigned_type;
         typedef long atomic_integer_type;
#elif ATOMIC_LLONG_LOCK_FREE == 2
         typedef std::atomic<long long> atomic_unsigned_integer_type;
         typedef std::atomic<unsigned long long> atomic_unsigned_type;
         typedef long long atomic_integer_type;
         typedef unsigned long long atomic_unsigned_integer_type;
#else
#  define BOOST_MATH_NO_ATOMIC_INT
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

namespace boost{ namespace math{ namespace detail{

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
#  define BOOST_MATH_NO_ATOMIC_INT
#endif

}}} // namespaces

#endif  // BOOST_NO_CXX11_HDR_ATOMIC

#else // BOOST_HAS_THREADS

#  define BOOST_MATH_NO_ATOMIC_INT

#endif // BOOST_HAS_THREADS

#endif // BOOST_MATH_ATOMIC_DETAIL_HPP

/* atomic.hpp
R1kAZXjF4qyaU3PUfcD+Lrnp1/I9wjfHQtW4ECkSH9mRv2deL8zAHLdnoJ8WMfZ/rK0c2G5XVtpsWajxk8OdTnvk7Vl8zESLdZ8a+4nejXKZaSQ4DNDfEOiAuT+nrpuWX7pUWw/zk66uIv0Al0MGujx44Ll9YRwf1ZIUi2MoIiPJYel72FWAnmbUxqmMgjyvni/dDMFC7xOa8dIQrsn1Acddf5wQO0h010eTRk0q9aV0rP5ySeoN7ekSaDOvLRO5BNyxluP1FKexs+xvLbkJncLBJiQr7YBwGwSckUYjgwsreGog3K9/OMZAiTulFHk/IqP5tjmGr8JVtFL7KGEm/8jm3PTUGwJ12Q0vQCgtazD5VN9DvKtUqq0vXR30fMzYnbtHWM/SRkqp6WTW8PDU+h8VLn6QVutF07Z2zDazt4+imB7lwNeSq0uJUeqpJuZibZu1xAQ0DFaInXpyR4FkW2lEvy/V1KjmFO9GFurLAnFfKxeWRgG4ExsMY+khY62EBW8NkjmX2uUPRDxGPvTgf9uVhcGeku1Ugy4m/9n6cdWZKslr9uGGVdXmMA==
*/