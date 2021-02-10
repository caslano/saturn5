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
TtoEHa0/sGO/7hQfWl9/ZI6CiyXLsWJ3Hk8ZOm0cYxGX8VAisKr5s0qBUlAp1I/Av/k5wOp/OPlBOPl3qvOnq68qpW1r25NfkLYGs6pVl8iGBCVOnhuRlBmSb7f2CjwsR8Bmr7LImM+HxrP5fDIwAljmoVEODra1IyN26q3hfH+YqEYNsomx9nCOKI91JSqwL4nYagVcVIMHnpaGE9sqxRHUEF1wq4YNxIQV41jSLOeEbVISMWzViu61Ci3OJoj4WB1r7wY0fqvRCHd+VAY/gAzwCxG9fTkbfkKE7F/M3TEddc/8nCdKWnmL5IWSk4tSzLDzaTLrDi9oh0Sef4OXrRBfFMhqZ5BlHieBsaM6O5x87FhJvFT3WzVcCLVT8pWyNcGUfVu7CLaX9RpNL4PQsizFVuOwZhJqcOetswRqSFNr1JuN1qFy8ORi5lqZJyNLnSGUNUk1r5FKxqEybTDZkW8JTLSKa8+oRUstVOcjD+a97V5ipumsulfSzjhU6eVHN1ujyL0HbWtHgGxVoqFjr4DHK8QrNY95K6m02MYo8gS2cYT95yJi8rlh32pafRmTzGfJubHNpu/zDtmWJBYnatX6TrYD4xK9YtIQlW5pm6zDq+5sPrgYbzF2v0o/AGQmTeJbUCjwD2m4g/qH
*/