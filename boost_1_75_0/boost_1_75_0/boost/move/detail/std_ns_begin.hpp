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
ByHIkPWZ7iAUCmx3EF5DV9dzxaarexYyegdeM1Qlh/KCAlIvWDaXH13hZ57E5vJTyKgbqa4oBbtQBbEPuoreJPQN15vc8E0GvQnZ4CracmDbHdWgAJ83HI2qpzSH6j6nQpHYTHjM+4b4S+0i85YomfqETUIK5l+OT0Q+KOOr97blNDM6tYaUeQQeW51leoX1wmRs+i/kDPFfeOkb3r5XAPj4G7JX/KGYk2Pz9h1aZ32bkBDzsbQGKNA0wtizyOFXwxv6qw3veMjQ8jlDy1PfhZEoD2SVvPVO34WWv3KZYx4Aa/7qvJ/LqXSkAoh3tXCfuFoKy6TJLaiVrrfxMvAeOcB7aDBvR6DR6xmnRvAfseM/Acm7iiPYQBEASZCvZdMGFJLZOwG7hUKQSiBJpg0dnfp0zcbgZ7uJ264sDcjDZqFQrBKWEhM3Mo+ovfJIvnewSCJU/wVl6TxaCMC9kDaxb9g6gn5jjfUNarLxpKxdxHeLU4YBaTPQUvYNqr8YB+MVHKK/6IPy9N7MdwBALhn5IKkS39wtNonrxlhIlx5mdy650t8eyP6OhMYND34P42nCZOI8HlW+kA9KbTDqM6hag9ybjritaMKHtAuWrq8B8PzI1KHMhMxdBDFsV3daH6DqkmxBewrPllbBdh4GykQis1zL/mYPFKexpJ8B4CQk8/4gy/6mh1sv7KH2N+Mt+xt2B2U2zFEF5TUMh3kK
*/