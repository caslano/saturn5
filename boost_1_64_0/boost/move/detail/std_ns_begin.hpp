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
oxRtrzvgsvAiwNoY4hB0y0KjWYEimL8bQxKjfr2sbUSUn2xAzLIBPFV5+9y//n+lJzaBc847W8a0W5+elaBlSZCQM5uIQiJg87yX0WtNHU6md3XNKXGqvdXdbbwZ3A+MLHUgYY5U+ezpek/T6Qb3q+FMtDKL7AHfqAFtUWdqp3TN/0E8r0/b7QIWybyvlpHFZDptG8JPPyGAGxETjJO/xz8fJfsXzj2fnJUtFw8A2KMH6eVnem1tpMZZs203Drl5aQ/3LsPeJvWEEpHuPS2o3dOcjGTTa6dgjrsh4z84w38GavVsrc5MVKYPZULHtQF4uoJW3bklBr5xhrWFTOf1/QyZdM0+ornhaYqrMdO2KJQEDlrRwhSIirPN3FFpvOczhFR5knzUhm+Mtxt44eBkr8M0PckB4Pqw9IengQG3A+nySkb5QR8o30v4ijlzQbG1o4luDRuB5vKXkztztLW5gH0aPa8hRUiZd7D4KGZFnHF0jITxd+bR2YSlmAQE994ILMg9MT2R1tvDGERyMHV+q78ijm54J0EKZ/EVOLdNdY7onjko+RPJ41LYtw==
*/