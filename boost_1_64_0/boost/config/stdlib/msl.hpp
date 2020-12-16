//  (C) Copyright John Maddock 2001. 
//  (C) Copyright Darin Adler 2001. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  Metrowerks standard library:

#ifndef __MSL_CPP__
#  include <boost/config/no_tr1/utility.hpp>
#  ifndef __MSL_CPP__
#     error This is not the MSL standard library!
#  endif
#endif

#if __MSL_CPP__ >= 0x6000  // Pro 6
#  define BOOST_HAS_HASH
#  define BOOST_STD_EXTENSION_NAMESPACE Metrowerks
#endif
#define BOOST_HAS_SLIST

#if __MSL_CPP__ < 0x6209
#  define BOOST_NO_STD_MESSAGES
#endif

// check C lib version for <stdint.h>
#include <cstddef>

#if defined(__MSL__) && (__MSL__ >= 0x5000)
#  define BOOST_HAS_STDINT_H
#  if !defined(__PALMOS_TRAPS__)
#    define BOOST_HAS_UNISTD_H
#  endif
   // boilerplate code:
#  include <boost/config/detail/posix_features.hpp>
#endif

#if defined(_MWMT) || _MSL_THREADSAFE
#  define BOOST_HAS_THREADS
#endif

#ifdef _MSL_NO_EXPLICIT_FUNC_TEMPLATE_ARG
#  define BOOST_NO_STD_USE_FACET
#  define BOOST_HAS_TWO_ARG_USE_FACET
#endif

//  C++0x headers not yet implemented
//
#  define BOOST_NO_CXX11_HDR_ARRAY
#  define BOOST_NO_CXX11_HDR_CHRONO
#  define BOOST_NO_CXX11_HDR_CODECVT
#  define BOOST_NO_CXX11_HDR_CONDITION_VARIABLE
#  define BOOST_NO_CXX11_HDR_FORWARD_LIST
#  define BOOST_NO_CXX11_HDR_FUTURE
#  define BOOST_NO_CXX11_HDR_INITIALIZER_LIST
#  define BOOST_NO_CXX11_HDR_MUTEX
#  define BOOST_NO_CXX11_HDR_RANDOM
#  define BOOST_NO_CXX11_HDR_RATIO
#  define BOOST_NO_CXX11_HDR_REGEX
#  define BOOST_NO_CXX11_HDR_SYSTEM_ERROR
#  define BOOST_NO_CXX11_HDR_THREAD
#  define BOOST_NO_CXX11_HDR_TUPLE
#  define BOOST_NO_CXX11_HDR_TYPE_TRAITS
#  define BOOST_NO_CXX11_HDR_TYPEINDEX
#  define BOOST_NO_CXX11_HDR_UNORDERED_MAP
#  define BOOST_NO_CXX11_HDR_UNORDERED_SET
#  define BOOST_NO_CXX11_NUMERIC_LIMITS
#  define BOOST_NO_CXX11_ALLOCATOR
#  define BOOST_NO_CXX11_POINTER_TRAITS
#  define BOOST_NO_CXX11_ATOMIC_SMART_PTR
#  define BOOST_NO_CXX11_SMART_PTR
#  define BOOST_NO_CXX11_HDR_FUNCTIONAL
#  define BOOST_NO_CXX11_HDR_ATOMIC
#  define BOOST_NO_CXX11_STD_ALIGN
#  define BOOST_NO_CXX11_ADDRESSOF
#  define BOOST_NO_CXX11_HDR_EXCEPTION

#if defined(__has_include)
#if !__has_include(<shared_mutex>)
#  define BOOST_NO_CXX14_HDR_SHARED_MUTEX
#elif __cplusplus < 201402
#  define BOOST_NO_CXX14_HDR_SHARED_MUTEX
#endif
#else
#  define BOOST_NO_CXX14_HDR_SHARED_MUTEX
#endif

// C++14 features
#  define BOOST_NO_CXX14_STD_EXCHANGE

// C++17 features
#  define BOOST_NO_CXX17_STD_APPLY
#  define BOOST_NO_CXX17_STD_INVOKE
#  define BOOST_NO_CXX17_ITERATOR_TRAITS

#define BOOST_STDLIB "Metrowerks Standard Library version " BOOST_STRINGIZE(__MSL_CPP__)

/* msl.hpp
y0yO64H1CeP7S6E50WSblQeVGkIWQJO5cO1oYbQ8wvT6enSPoVF9pUxDk/k6XDToiW0K4/rQXGgeYYmu9n+QBdEGCmu1vNRxjuuF9Qnje1ahudFkm7X94+aRhdBkLlwfWhQtjzC5T3b01tcEXLjPOpZ461+yKFopYTeTz5Unc/YxQzaTbi1+LFGAzN9XO/fVbM3ad4uTefuZoZyw9rs868lCaC9Em9VyZTCRuQaYYamIy/ndhQgZDDTDt8IKXPS24BrQEk0il8c5unGbg81QSdieWkWmkYV92tqaZoVHD+xI5vnEDDuEHRy8qi2ZOzltnl+1CA3nsU7B8+IE3Xatt9zk/oaaob6IK/Zrcc7TOQzXDoV99NPh//BYo60S9sfV1pU4z+FmuCesSR/LRxw3Iu081L577DeyCNo0YVUWVJ/FcSPNcEHY4bd6dCULjEq7TfSOzeI8Y6NxGxS2odatQmTeT83wEHTbuLFTMW5zLM6fMD6/RQsqLIQ2X1i2fssvkfk+wzVHYaNOruFtPoy2RliN8fWqcy5+PIYWph9DYxzaIWGt18+5zjYO13eF8fouGozH9V1hvL6L5omzh1kWnefa0aoLGzZv23gea7R8wir6X+4gc04wQyFhZZ9/vY/7Q+sjLP/8cgvIImhzhS3M2+YMj8tE3EcK4/UCtCCazPPG8rbvcp5oM026Zd/RsSVZdJIZWou4xpHTuTnPyXj+IIzPH9B8CgsoLKSwiKHh8RJaV62G0nhM9GTa6yL8ndtUfZ9cJu5YI4pW26TbH7XP3SbzT9fW4DU7O6rZX2QRtNzC5PewMMMM+YWlDJ3Jx2AuNPqNZll8YWiZMz+RBeeYYbmwriee3SPzLcI8Qbd1u7Me5FzQpibo9rnz+jkyWKqtHWpWNDl5A1kYbaywge8uWEvmXWaGusIGnb7TjOPQMgqT159F0HIL08dlWiIsN/PzGMqZXr8+8NusmmSOlWbYnqBbo3m2D8n8X5ohR6JuLz7wTiDzrtW+C9GscefNs8hc68wwQdiivUOek0XR6grj+tDcX2F9wrg+NA/aX8KWONpon0cpZfzr9e/Ky5s6dU/IvKIpWfBrM+wX5sjeuQVZYAOuewubesTxgMyx0QwlEnTL9HbBq2SRTWZoI+LKVd1Sncy92QxNhC3fHXzMuaDVFca1o0EIaxem117G5UA7rc1fBdMHKTv+Kf8OmXerGZYIO9343QS2bfj+S9Dt3ScL9TZ3mmEh6DZi06x/ySJoKcL+fnCxGLe5C2sQxjWghdEyCpM1RNByC+PtEw1241q6qKFe+8WLyXx7zBAWcffNofycy14zNBSWVHXAD5wL2jnRZrMc/Spz7fvNUE1Y6skrdD1D3eABPA/I9MYqmny9WpUosIbXpY6b+d5TlXCOTi5dXYvXZk6a+berlXFd4+1z4SJkITSnsA7vnN5CFkVLJ4zPG9FiccbnTmjwc1rjtRI0R5zxegGaM874PBzNJS1+DQmthbCLmV3duD60zML4XBQtHGd8PoYWiTNef0GLomUS5vzT9ZLHJS6O1yfQ4FTaOH6eBpoDTcbxmgCaMy5uSVLzzjwuMk6ug+GfG+2oZlXwhczLClrYIri9CKuT7ZsBZH60FcJm7prFn3Ge02aoIOzg/Fd1yYJofRJ025f4e0O2X7RrmzT75L/hYmRhtLLCsh5ZVp0MzpnhjEm3ljM7tuRcLqTNZUzqui7cH1ppYVU/KzWeLIpWQNjTo5Wnkzku4nd8whosn/qALIa2SrOq+IK91JMbXMMlPK8StmRu+n2cy2Vj818xQ8Ck2/pB+RayXTXDfRHXdvyyimSha2YYISw0q6uZx+U3M9xN0i3fiEo=
*/