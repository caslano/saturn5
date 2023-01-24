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
7xJYDcr/Kyw9EoqVoZFBiYzUjwJmfuKk7RRc9UIiHhgZXTdOWgAcXJpIz534Tmoje9sA89SCS2ntdf36hjlzFiv2cqmMgkYZkqF9pzKgcH5EWDgxLi5tV/Wq5lMee516DuNoPvaly8pGWE1EIMDfKUIZ7Q8nuvqHE1XbmXm6ef0nJ4qHByfDb7MfeTZ4uoE0Gripr24aSMhpU8cGSrxdmGfDxHGdX1geHU0fHdWysvLk5okAlGqX1OeVlChWKg6Au9OFk3+WS8mNy8qWjo3/VaYKO6I0sLeUVZecoYGUa/lniiI5Zr/N+vExu+BvzIqNauEIMywMj5dYnQkKoBz/lTvN9/H7zPtbCSwKvLCwqIHBTOgnm8etBI8MubKGY6d5bhsQtnBhENR60M0By85OBGtaBA797uXTwWTGqNQBTqjoMnoqLWmvppouUp6TTxq0Nh85nj8XF1w7UdLValNL6/2fZEJDauEqUJYqkTRWo+aRo2ibTsFCM42TosmfgVcfMcZShrPmwMZmBSUhoiAmWrCkW1lOIiPPA9XwRUllfDoH9IcSaGpnZqzJyfcM4zS+FaPmA/NvaJ4ssEqoNi9BJVSULtauzmJ/UEAJ6YHt/fZ27g5+Su5eWmzNfMMExSlj1sbEpHqAqpNmRQYbG5+Lp4Knp4mtrYLZwXJODgIOvVPDUkWByTNrZ0X7WvHCrsxX8bB8dVr6vybgRNCS
*/