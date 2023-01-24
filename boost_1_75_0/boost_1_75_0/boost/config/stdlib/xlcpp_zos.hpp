//  Copyright (c) 2017 Dynatrace
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

//  See http://www.boost.org for most recent version.

//  Standard library setup for IBM z/OS XL C/C++ compiler.

// Oldest library version currently supported is 2.1 (V2R1)
#if __TARGET_LIB__ < 0x42010000
#  error "Library version not supported or configured - please reconfigure"
#endif

#if __TARGET_LIB__ > 0x42010000
#  if defined(BOOST_ASSERT_CONFIG)
#     error "Unknown library version - please run the configure tests and report the results"
#  endif
#endif

#define BOOST_STDLIB "IBM z/OS XL C/C++ standard library"

#define BOOST_HAS_MACRO_USE_FACET

#define BOOST_NO_CXX11_HDR_TYPE_TRAITS
#define BOOST_NO_CXX11_HDR_INITIALIZER_LIST

#define BOOST_NO_CXX11_ADDRESSOF
#define BOOST_NO_CXX11_SMART_PTR
#define BOOST_NO_CXX11_ATOMIC_SMART_PTR
#define BOOST_NO_CXX11_NUMERIC_LIMITS
#define BOOST_NO_CXX11_ALLOCATOR
#define BOOST_NO_CXX11_POINTER_TRAITS
#define BOOST_NO_CXX11_HDR_FUNCTIONAL
#define BOOST_NO_CXX11_HDR_UNORDERED_SET
#define BOOST_NO_CXX11_HDR_UNORDERED_MAP
#define BOOST_NO_CXX11_HDR_TYPEINDEX
#define BOOST_NO_CXX11_HDR_TUPLE
#define BOOST_NO_CXX11_HDR_THREAD
#define BOOST_NO_CXX11_HDR_SYSTEM_ERROR
#define BOOST_NO_CXX11_HDR_REGEX
#define BOOST_NO_CXX11_HDR_RATIO
#define BOOST_NO_CXX11_HDR_RANDOM
#define BOOST_NO_CXX11_HDR_MUTEX
#define BOOST_NO_CXX11_HDR_FUTURE
#define BOOST_NO_CXX11_HDR_FORWARD_LIST
#define BOOST_NO_CXX11_HDR_CONDITION_VARIABLE
#define BOOST_NO_CXX11_HDR_CODECVT
#define BOOST_NO_CXX11_HDR_CHRONO
#define BOOST_NO_CXX11_HDR_ATOMIC
#define BOOST_NO_CXX11_HDR_ARRAY
#define BOOST_NO_CXX11_HDR_EXCEPTION
#define BOOST_NO_CXX11_STD_ALIGN

#define BOOST_NO_CXX14_STD_EXCHANGE
#define BOOST_NO_CXX14_HDR_SHARED_MUTEX

#define BOOST_NO_CXX17_STD_INVOKE
#define BOOST_NO_CXX17_STD_APPLY
#define BOOST_NO_CXX17_ITERATOR_TRAITS

/* xlcpp_zos.hpp
tR6rnFizHSrhgffyA7iSIsfzIeXegk5EBlsw83y/dLzdFseiYUYUZuWeuVB9osFyINA6MVt+GSXMlu1lES9nE9xCpi5pGORJPsAlc7C5S/CXX72jGwM/vZG2KvDgVtn2bjHxS6D5k9tlvKGlDJiiFvt53VJTNilBNYydRl1708RZQnTYT0JP6fUPcapqugK4vka1f4yjiAghqGiL8KErGSUOPpk74/fyStipaYtvl+BMfQ2DCo05i2qdOQvwa5WBX13kLNHlR+YkPnVYq6hS5uASRFtpaCkbPuKRH3dly82jC2D3VHPhVETn8pYfok8bxtZn9d1ZXT+JTRvm7DNv5O0sdlhuTLbzglxwm+BESyEkJ3VqrORp1OWVuoy9SIzBCU4CZJHLmCPQH7ZBHxfpzPewlLOE+dHVlVi6vlgbhjuyxAMI2bDCWJqtH8hDHyY2azEcpTVDgdVPXfeiBfMEey4bmKo715kzLom9WnNHZVXooFT9b12Mgea1ZmnySp3Z3B02I3j4yu2VQKo9lmtx+hP0YwsfU/avtZNBxeCmvytQqVERaQfXGmkvVLS3KjCRzDzMhjMBGIC0msvd66i2yD85p189TgAh6FGr4MRQ1bPlU1uCFk3uuOQYi3wQO7QM7HfC/df3HjRBGbXzaVZ0mVybE93HlMxjajCu+MnQGhVBMrwG0qBmK6mBIkRXWP6RBQt5PITkBo4WxhtO
*/