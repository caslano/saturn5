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
J68xsgKHSV77EC+Q11KHvOZYM/sH89pId39VdkKB3Pkl9fcvKO+TsgzhUh+DiJd8sKpuGabYF8HlZyaM+fJ03NbU+jqoqvP6OlOeT2hLuBPNiZd9+L5DnqTC2vLkQrm6Ul+NbYI+XwFyT39vopaU1QbytdIhX7bK6fr96K7UTSVfN7Neg+Te+beIZuKrSt10zKtUTmtefVxog5dWM9xzaRierQz/RXXZ27jMcm/lJhfaZ1s5
*/