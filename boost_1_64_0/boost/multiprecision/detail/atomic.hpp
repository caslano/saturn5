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
33H0AnK1FC0wqD93h26WJGgj6cqz+xIc9+jkz2dPAChEJ8ddV+XsU03tXD2OUtAjA3Il5lBkkLPkV3YUoVgBFT3gW4dvdkrL+BfczevYFT/CkZPzGBf/ZHGjGHLQl0lxba0C7QeQ6zyO7ajVhW3in3CKCXLGyGUsf889JxpUFl6bVTGpssYbdIixkiSW/lomHQEJbCBIDftrWaBwXsbUvM/dlInw4TfvG/65/n0rx7sCvro1468W/pnkI6T3FBuzZYVdLgJYmd+R6thnRU7r4ZF5ASQ+hWvPnISxnkl1h9125CIdE0IR8HrucXy2c7HeChBxX4P+Mn2Rbxl1x6LM3BA+kHyWzB8JN3ycipk81xpA3oK5v+NjUBvGAIDhedZ1EEXjT7zEXkPcuGIKSz8j5iR5FjX/H9cRDcpvYK0vG0gbgmtgWUOLrsbZ0qYNRrn6kbwuPoyB3VELzd8k3UuOW4Qw/4CpENW14def95IkD/fTKDbgxxgYIApB/SoOuQaaiIt3JZTQd4IKmrKxbh8dcLiEjO0MJqhFatggunXTza0k9a4Opv413FfnfA==
*/