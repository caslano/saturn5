//  (C) Copyright John Maddock 2001. 
//  (C) Copyright David Abrahams 2002. 
//  (C) Copyright Aleksey Gurtovoy 2002. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  Kai C++ compiler setup:

#include <boost/config/compiler/common_edg.hpp>

#   if (__KCC_VERSION <= 4001) || !defined(BOOST_STRICT_CONFIG)
      // at least on Sun, the contents of <cwchar> is not in namespace std
#     define BOOST_NO_STDC_NAMESPACE
#   endif

// see also common_edg.hpp which needs a special check for __KCC
# if !defined(_EXCEPTIONS) && !defined(BOOST_NO_EXCEPTIONS)
#     define BOOST_NO_EXCEPTIONS
# endif

//
// last known and checked version is 4001:
#if (__KCC_VERSION > 4001)
#  if defined(BOOST_ASSERT_CONFIG)
#     error "boost: Unknown compiler version - please run the configure tests and report the results"
#  endif
#endif




/* kai.hpp
Vegjsv9DZgTSdkh+Nj7cI9riVJwBZqrLLINTkcOYy7QtbAi5/zQqTWM6+eS7zAWrnUaGHe8wi0bp/7uBDjJ8Gz7NSNpehm6682sVC7GwRyyUyuU+JVsQ1yh92qB6J1bW6BXOgWzXceWWue5qz2+8ASPf96yhe0NuXTkO1MQQ2XmhC7zUehpmBHHAbWg+4tR6ut2RftG0xhZDIf8iW2PXXrSusbXidlRk3tese2GtGQ6xH70Lbohn2XmZGc4mDF000XIPQ+GJi9xe7KKVlrtPkD8QlmIcBiK2IMV7qZfRhm9cNOH796HwBw7vk2nf8TRWDuNSoYw4yiBtm9Yf/s9M33E9FEo+4/Yvn1nh7BRPXn5+KIM3Wz+bts/f+xnFteWps2BUBwrkB7y3EN5L6UC3fmb6jt1Q+Mln7Duemlb/ZqwcxEX0OyrJd8xg73f+M5PN6CUoXPFrBivr11bkdqdd2oMbAY+UcB9TCtCHc5Gjg/EZsV9znxNLIVPxa2ucpqTaARtXvtCBg6hFYLGjKYx5AENJw+g1w7gfkroaXusRamBKtcJraR9ZJv9O47/mPliegswvfp06S26O5lRp9m3FtHfujIcrj+IWglBBkUJNslJ+WNQ9Vl2n63N+bnoxZAo+T/kUq7QoKOjq9vThOiDaw0IhIOAw/JZjg3jbRk4SOd0mCUiKsDnO6OwroQ/cQGc703T2qs/5WZUHITMJ
*/