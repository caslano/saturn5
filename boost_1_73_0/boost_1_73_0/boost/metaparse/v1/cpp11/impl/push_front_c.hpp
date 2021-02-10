#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_PUSH_FRONT_C_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_PUSH_FRONT_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/fwd/string.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class S, char C>
        struct push_front_c;

        template <char... Cs, char C>
        struct push_front_c<string<Cs...>, C> : string<C, Cs...> {};
      }
    }
  }
}

#endif


/* push_front_c.hpp
1DuAvf/1e+YYvuJ4zlfWAILhkBwv8OeMedpbT7IJoLcxD+Dp6A/gWy0hOFj7Xo1PTs/HTNrAbr7mDIdwignRcc5DuKOn9WKoK+3Tkth7T9m/DLK5tj0lkEPK3rK99yb8v+4dDon+qLdP5dAUUnGxl5mFfHv0C7WEfs9FHwCa5K/RX+RNnsH+qN+Hsr77M+bgrTem96KK3xafLf91nTsBfJY5FmYtgMRtyKSt2ZilpiT7zQ6igi/QCQzeqdLkqqDS3XMK+0iBUPslr6pGQFWXJWGJ9yBy3UplckKKhMhvISBK1GLBCxEzz3MA3hZwc5DmEkGqe99tg34IRGfk+wuuVyP6zD/tfr2czs4mo11iNLm8mvlEdosbOX8b7rj7FKULVuJWpKmSUjVW5aZRxLLAipSuERKN3JCYm8xCWC1bo6TWki3oGckQ1qEtP6pLe/cA3OWpx7QLEbxiHD43Dom6JWzzs0mDS9AN6jxdgU0g8NSg3vYXajsV3CG1qm6VKdNl0dLZEkSplVGJkjG7no6vwL5Yh1EGpnY5p+Xtacf1yA6b/ZqM4aTjmmWH/bg+o2/kPwJE/hbVf+y6vwFQSwMECgAAAAgALWdKUlJ7UCL9AQAAswMAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9k
*/