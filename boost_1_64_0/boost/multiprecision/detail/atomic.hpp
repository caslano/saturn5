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
LjZkPq6kpTqPvjQPPYU2kWbj9cPT6KgokP4dDzuFnooD153HPfxUeiqSfA08FTOdB+wRSLsBN8GHx7g1zUnO7vOPHOmONrdTxL2lebeIR/qRno7YJ3pTLZ4LH4U0C/tbX4zlj3s0lqfg9n1xllskKz/atbJvArb1nY/B8v6SOmtFHjv9sUh3At9j87dsgq14WRnux79e0KRdk9bxnOEu/3FQvtqOuzpG/uNPpe9v88dvpo8jLbzxS4qhxPVVdofHPWFKh2a47Hvuziq6ninmpt2m7xOVDNZwxajHAL0LffY2veuoA9dVit6w2kyF/iMYI4zgOVOdEabRkhXmqx445nAkOMGq1muZklROTMzUtnFMcBXTUodaA678VFrC8E7yLoLTrKlcpbug2SpzdBHP7EN0XIV3Vre1ZNRKTdv58aJ/wMpaxw0rTdfF25RvEpxiXreh4z6wbMotkoHuHPcjM743+FmJ5aF1QnO2wpRdvhk9s0N96etoo68jo1+AtI8P2ylkGNraNq1mZPqO0sd3nDvFnY9uQmekIjgi/TF3qCTYhsVGdzBEkdFrl7QxLLWoyI29RfAV65pYVVVtWXlsX+J2hvG5neMckzJa711kQ9ZKsI1N3sbcRXi1rDPWKFnH4b3XTnqcBsv6yfKK7crNndluL5jxTrWoo5ZBtY3ReR3HcNlH66C6/7VCThp6nCIQDXVA15dvl1DCZ3YH/j8u+Attfc1rOz54SsqVZLysIeVVwIvQQbfeWOSitkpH01mWd/7GDEyTs6wzWA324wKpR7KqbaOHtiwfNy2kjRfoPXpr6McL31jojY6usXHxvmlztL7NlyMKjxzhX+V77NeQOipWV0KpUEMdI9s8efGAOyQ4ztoq1L7yrge+5eBN6UL8GK6RKe5dOS6w0FnR1FotYEtfE3yqRMbpvcU4dULy2LSB9VOrz7K8NPb39yV6uNPIsUIzFbjQvlZs7GDK2AzDA0PVtx9vsLP4D98nbVBMR13xlDjg6CDx3tzoGwHZoue44sLyjnm4Cb5mxvvIHcg6eYZBx3HAacLa46Ef599EcylH5bRtGjPFTx8KJjzub2+ibz2DaGuvHeu3wyvwkCu3Wc+G9r+G8NfM1imaUKd6YN/7t83gH4vlvNwfb1O+dW2lryrdw/unbQc41bcGvu8mfA0zojFKSzfm2d2bzdMkxYS7VP53CH7xNLoStShy7B4NZkTwgkFTFb7/eh/cc21fTu+70qJMH4Cl8vdD+c+wnDwAI++/vjC+/0qE+ACsG+Ic3KJ3kEZJ3gX5P+eH6+9TyB3cF6dnb/SdwZjod0M6uiHn59O79zTkHLusCPlNaHKvoZHO3aOkW96DpcHP72x/jHRk8x3Lz2J50v7hIw/L3T1pOTi10XxF95qW9+fC8d763pQmjV5exwdWlC86PM9yPJxbQZPFyfzIqvLD3rL4+g0yds+8z5R2MSobKUf9SPcBQlceIrKY//ed0vVDMPqdjzTzhf1rwRXJ8Ez/4fsBXWGj6c/0+H3w7PNA8z/YaD5I6UobDX4TXbh/ojvdf+mdpJzacH5Gyqj/0hsekJX1TB8y+FwuytL+dmY85/q7kT1KVL7S0huGsuFlHvC7YY7+LZrPx8Y6dtYy6utK/XY+RTGqVdoHFdnyPJz8KZKTCsV8c4u+3YzQwtZUPQY8W0YIYn6cYzw0qVEyWskyS88k3s2vt2i8m06LIJu0WydjNf1e+/sWjUERYyPrJkS21LTew2LiX3E3/EacUf+rOpo28JZlKji0bz5gnjmjMXaMrIQOnOEukIZviULMVcqn65paWtkMmOR8gnxwr50VsSAi90o6A6CyVzTG0IzmXJKVCk0=
*/