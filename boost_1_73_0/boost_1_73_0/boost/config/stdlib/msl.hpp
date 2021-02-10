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
HLTdoffBsmfCdIMRYcPQDXRFWEGCLTKBUoqi1s0b51Wrhk+LyYfIU4MxLQWMS/cZb0fpXKrayBa1VVdJoWZIVPEaJ4SemsY30jrW6tuWpadlKwJ3Sd4gm8hzHHT1NGtnxnogcIDVGzpIu6Z1w+EfXkno8r+bJNeOPzWuHogZFDidGuTFaVBiX+XGfesex/nTaLZNXHSnoUPqMctB2jrDeT3FEYT8qSw4SJ0q02CNNLlyzgOPmJbaJsM09k9ruRKFqLsYeDHrarD31FXNqtCfD/i+EsdlYu83om1GaYDbLfT60FmeG/hDgrOM21M57yDx8+om7Eig5PQv9SsyvH7z1n6Fv9daH7QTGy7j9J/Jat76qwXQdyPzaT2P7UqgrZS1gtXYNuOyYFd+7RbqiyeOXkuCVn/SRC9erOh7Vnu6LCus1Vm3E61PvrWJ9x5+ydPr66LTh03abxvhmuY8KZpyudJvT9vDucCt7Ry5nhtNLCdN20NjO7CNQEiicejDheONiRWailSL6NAzXXG6gtsprg81qilLWeGRpj1mtYLLfkHNNmzLtG7LsMMIAcdjFE8AR+EqYtjSAuozgr1qRKDTPexhXmFxoHhplq6WsNHcPVoslbaL5kntP1BLAwQKAAAACAAtZ0pSjnptdAEE
*/