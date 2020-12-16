//  (C) Copyright Jens Maurer 2001. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  Modena C++ standard library (comes with KAI C++)

#if !defined(MSIPL_COMPILE_H)
#  include <boost/config/no_tr1/utility.hpp>
#  if !defined(__MSIPL_COMPILE_H)
#      error "This is not the Modena C++ library!"
#  endif
#endif

#ifndef MSIPL_NL_TYPES
#define BOOST_NO_STD_MESSAGES
#endif

#ifndef MSIPL_WCHART
#define BOOST_NO_STD_WSTRING
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

#define BOOST_STDLIB "Modena C++ standard library"






/* modena.hpp
ltP4FYqBysx+HzjgLOWAFsuMzktoHhXzqVggrAGYCsfAXmH58V7JjplpTkmDInjdjFQs3dzPXaT5i8fAXFBs4tllL6W5S4Ta6G140Amzl4yBCcwqtp5YktoSF2qn4l49kOZFW8Is0G/Kn9KcpWLAzuzxu+JZKYfS4twqrMPgg++l+dCaaxSbMOynwlRmGXENF3apWmxFaeayMXCL2W0fjKF7SN8o14ACGoCt14vskuZBS6NRbHSOzA5pUD4GWoJijSKuFpfmQKvFTH+yb5I0H1ozZkbDEju1pYJYLwmbWmLRB2letM7M7u0f1pHiKsZAU2YdiuTPJc2N9h2zVtVBiasUAx5mXZYbVkszV46BGcx63Mj6nHJA+4XZ3Vr97lOfVYmBYsyKDNraVVoA7WdmM9Kkm0VlVg0fZ6oWA98y63+lZRbqa7SFzBJqXqV2WqqLNaawjp/1OaTZ0fIwW/1emyjNhVaB2ZHI7w5I86OdYzau8Il8ZDXC5eAYaq6pXI8K4j2yX9fqj0uzoOmZ0fvk0KypbOjJsYWl2dAuMytS2TdPmt0aA9eYTb1mbS/NUSsGCmoU69ds3mhp/tri+iDsze6ok9ICaGmZOXM+ipMGdUJtaKeaNegeIFqksEJ4T07Zr/QDM5pOWGFNouPXlF+vSbOkstelx6yWZkWLZpZ48NQoabZgfWT03no0O1pLZhknD8kuzYdWllnz+H0/SjPVxbW3RjHfl08x1Jb6MVCU2Y9b2+yQ5m0QWl+16llaUX4NxfVI2IOKv9+U5kIrxOy32a/KUJmp4hofHj2S+rNRDAxhltIpB7XFgxbLjK+hfSoWUDFT4/BmUTGbijlUzKViHhXzqVhAxUxNVPJTMVtYS0pwoHUQVkTTufvfcZ1aS/Oj5WUWO3xPaWmmpjHwmdni6aOipNm+FceDMHrXB5od7Riz0mPjX5E1i4ExzCKm495XGDSPgXhmTe1ZFktzprKYly0qUJxNnEOEBd+FIXJAMzOj9z2hWdFyMaP9O5rDFtrO/uffrKIyW4g1tDB6hhzNinaRWUnjXDP1WUsxRsJCxii8JbnQOggrqolLTq7/W31p0EqMnzAaPzQLWjQzevYHzYo2hlnEN8ut0vxo8cyKOcfel2ZvLfpaGL0DBc2BxuMGZazSWFoAzcyMxgHN3Eb0pzClPxMG2dCihRXTxPWgZ3vR7GhmZnOqZekszYVmY5ZQfNE8adA2BgYyi3lavw7FoRmZ0TtX0NxovMyCS6xPpJnahbaF8kOzouVmxvLr6UDrIKy4pmLnQwOazJPmR8vLjMYWzdRe9IswegcmmhltDLOz/Q93leZFi2dWuWHKv9KsHUJt7I13nSkOzciM3i2J5kMzM6Pc0aCjyF2YknvPOAtatLASeM6i5wDRrGhmZjS2aA40G7O4RleaS/OjDWTWYljrLRTXSeQgjN5vg+ZE42UOeJ+ujLQAGm8L5Ydm7izyE6bkB2BDixZWUjMknj+zbkczM1PyA3Ch2Zg1aZW1gjToIvITli6yekGKQzMyU95dBOBG42Ua715oKM3UNbQtSn4AVrTczJT8HIkOtA7C4jTTImedT/9Qmh8tLzOau2imbqJfhNF7sNDMaGOYbV46row0L1o8swLdbCWkWe2h1vNc5kkUh2ZkRu+CQvOhmZlR7mjQPbQtR24mJ0pzo+VmpvRLcpIPLVpYKU2Fcv/n6z7AnaiyAACfvPeoqRZ6i0gHIfQOoXeI0nvoIC2+RwcxlEcvoSM1ShNBCEgHIVjoSADpgqFKE4LCKrjAnv2Yc+a8fN/c5Xu735d/z73n3DuZzNxMZvhaVLQomlMYzzuaozvOkbAR1/7OTOZHGyjMVHU=
*/