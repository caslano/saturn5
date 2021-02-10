#//////////////////////////////////////////////////////////////////////////////
#//
#// (C) Copyright Ion Gaztanaga 2015-2015.
#// Distributed under the Boost Software License, Version 1.0.
#// (See accompanying file LICENSE_1_0.txt or copy at
#// http://www.boost.org/LICENSE_1_0.txt)
#//
#// See http://www.boost.org/libs/move for documentation.
#//
#//////////////////////////////////////////////////////////////////////////////
#
#if defined(_LIBCPP_VERSION)
   #if defined(__clang__)
      #define BOOST_MOVE_STD_NS_GCC_DIAGNOSTIC_PUSH
      #pragma GCC diagnostic push
      #pragma GCC diagnostic ignored "-Wc++11-extensions"
   #endif
   #define BOOST_MOVE_STD_NS_BEG _LIBCPP_BEGIN_NAMESPACE_STD
   #define BOOST_MOVE_STD_NS_END _LIBCPP_END_NAMESPACE_STD
#elif defined(BOOST_GNU_STDLIB) && defined(_GLIBCXX_BEGIN_NAMESPACE_VERSION)  //GCC >= 4.6
   #define BOOST_MOVE_STD_NS_BEG namespace std _GLIBCXX_VISIBILITY(default) { _GLIBCXX_BEGIN_NAMESPACE_VERSION
   #define BOOST_MOVE_STD_NS_END _GLIBCXX_END_NAMESPACE_VERSION  } // namespace
#elif defined(BOOST_GNU_STDLIB) && defined(_GLIBCXX_BEGIN_NAMESPACE)  //GCC >= 4.2
   #define BOOST_MOVE_STD_NS_BEG _GLIBCXX_BEGIN_NAMESPACE(std)
   #define BOOST_MOVE_STD_NS_END _GLIBCXX_END_NAMESPACE
#else
   #define BOOST_MOVE_STD_NS_BEG namespace std{
   #define BOOST_MOVE_STD_NS_END }
#endif


/* std_ns_begin.hpp
A+zrT2l1sFacq95oMmo515PeaK3OYz8MntR2L0aTK8satfq967VlVKIl6HJkbIjERcZj7YtgQ+U7JYEMwC7m4xKT4LE4FhLLR25LCLHwwS6diTz1OKAjYbSswjuRI8uWkPEIrz+sJ+DYebC1KwSE1E0G8NoKVV2qoimQ9PISsVAxqJIV9VQkb+2eq7sBYmpABmL6CcETgUzm6Y+infHgwlV9byMe5LG+iR8q2FarvRu0knwOsmNZV7shK8nnIFu2PbSLitoB3G2j/NNybet8fPkcL7TCbgF2MXWW/RzwQuO/0FEYWx2+sU/da0kJT/GnaKGKoWD8dsuLOIvzZLW17maDcb9/ukLK0xhUezzS3e97cY+AhXJYJdmdm6TotCZd3Ut083dCt3+1/wBQSwMECgAAAAgALWdKUg/YI6sUBwAAwhQAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxNDA0VVQFAAG2SCRgzVjrc9pGEP+uGf8PW9LUNgHLECd1MPaUGBFTY2AEdvpwqzlLJ3ONkBjpZIfp9H/v7h0SD2MH9zXVB8Hd7e79bt+nuuSJdFnCT4wX8B5/PYhCoEmovK68Meoi9KMTo/6JT++j2EtOjLPhsK9e0OrZF/3eYKhHvgg4pJMg
*/