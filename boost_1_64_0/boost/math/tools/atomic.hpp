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
xGsmS7yXjXRdt3aqKAw5rxkapUm3qbd3a7wV9NUyj6sU621QiBy9D1wzZFRB5pW1468ho2fOHzeM9stdryrqsLRkkH0wFkWxi/uX3oe9IgnSFIe++urR53xuw3cY+aQ9XZ4EXupmxCg6PyZIfGMGX5RVbl1lATPOOCZfjnw0Lxe55xQ4P4ikYIKVQ+25TTs/W+PzWVlkQVWUKbtI4TNxJZE2ak2aF400oYSlX/jYNzFmF5/RUNes4btslbGs3SqONb5uR659brN2aXw59EknyIsA+Vqfp632vMtozzKB9TOsMilD1pWui3fd4HM9WETcPDf5sILJ/s+oIz/OCt8rU+Sj50HBRjrAw0O6Hm6S5nlZFC6T1xJ0fY2spxreAxqvz2ovj12Y/Cxe2pucaup4BHmpjouqgt5KvNb1PcqgvE8YeQ+82PHTpCIZ0uWclfd5I++l42R5neQmLw0Bsr95pcZbsyxN8qTKE+Jtc1Fnj/mrmhyXlXnte6lfMPOZGde7403fUvlq5jll7Sc4dEkDUdcLvVvnSd2iLusyUnjkSJD5+4WRv8CroEvFPjPVXY38/V3lq1gE+SvyMmHc8xDpdOv527FOexfO/CIIg6pk56eABWxJYc6UWsWy/wkeGiuJV3pVVCLTRd7ZR/miA69t0p5atv/sOq3vZG4JK3cSAm8X3E2TbTipM8t0R4x00ypwPMcJ2fQUNxMRkwMImBX63oYtTK7x5qx2y9TP/ZQbMQqVblhmZrjh4KKwhgYZQhPP6vvzZtmdvA6TqGZ8sJEY4YgImaca3leuM8ZtEkcFdGDBi9axhiH6VNNOb9fbKahhwKdexcBDkdm0K016V428unEKpXYisuuCI4xoYKwtJa+fMfIaJF6cJGFFvOAxYR4tYoy8/lDlrVjohEFRZ55kFVamRp+/oaXnMC/InTKPAtZqHkr7mKH1ehmzOAnzOMn6Nnm8B5qsVMZ9Gm/AqrDi2xinzysu9bomd8N7dL0xRquogg7lMb7tEmYQvGOJGrbmH9/gLT0vzos8IV5Uxu3qdrz1zfWaHa6fRoGXRRGDvens0gwasUjTJWs9P7tea5cqr5w4yFw0B5PG1JJPnmeNekqKIIkyBlM0bxjovJiy+IB7AWlfpPGWjJ/OgiINuE0gVhHMf2hxs9pVDcWt+4V36/n3q9BJ4pRLwkwIdUZ9j/hhLf0E5ht+fK9zppgyGZOOZav/dUNGGQZxEju6iM6iKYJsA1T+ksWu40ax77Pu7NIqH0IrHbnJlmvd39frtmlJWMNSUxaagTDcqQM7nU7QxH92imygjmzQ18yyDlIvCLN2PyNd1cQLs0RzX63JcqEB0qBI3IRsN2jQIev5pg5+Uev3STB5uUGYEyvofZl7hRktPZ9VRc5P5o5kkubuow3z+Yb3pUZei6xwksB3JS9OQsAp89q094d/q46ziMcGyAo/0u0UyQrIGi+v19L2WB5FfpUV7IUrMLqkwY5aT2Sn8V6VN2dVUoRJWiCvznOK++1/4SFo4wR0WVEnlwePWF3s6xhw+kWgX0s1OixRXU3P+8/w5w8Fp0/3z4wNEGairuxHY39V2i+MmesUTuRBW/hg+CaUstAwlhS0ZkDhVqppqbZ0V1RZAfTJxCvTOo/+F1lDf1PzFfI+Wbhl+T/la1aTlbC8ymrfzbNbkSX3ffqdaxRnceQ7FeMu8Lzg9MSkn5zGhlxueH4meGj/lqVV4SssYZIHDY9qBxXg3a+04sBbRrDn0vQjDq0bjJ2ZU96L18bBpcALyL9YK5buLFR/0ufWr40VgtUYsO14PP6JLNO7CfyF6puu6Mrz+OjflTLj9QauS5KFo9Yu6SMOq/3Ug0k=
*/