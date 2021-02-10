#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_AT_C_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_AT_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/fwd/string.hpp>

#include <boost/mpl/char.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class S, int N>
        struct at_c;

        template <char C, char... Cs, int N>
        struct at_c<string<C, Cs...>, N> : at_c<string<Cs...>, N - 1> {};

        template <char C, char... Cs>
        struct at_c<string<C, Cs...>, 0> : boost::mpl::char_<C> {};
      }
    }
  }
}

#endif


/* at_c.hpp
tf+f8hdQSwMECgAAAAgALWdKUkxe8fkmAgAAnQMAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxMzExVVQFAAG2SCRgbVNNT+MwEL1b6n8YBfWCyLqB7koENxKiiI9ladUG9rgyyaSJSO3Idgr59ztOWnrYvTierzdvnifCoXWZtJgwUalC0+cduw9tcpuw+zRd9gfc3aYsfGSCH4OCD/nshAmDTd2RK5dOgtJZidn7LOjQBgMIj75FcD6ZwOInm0uHMaQtnsHkEp71jgLRBKJpPL2MKeXuV8rWaHZoYvDkQtsbvJDvyG60cqhc+IRq48oYfniPwsxVWsWQ1doec9KuQQ/x6XjptvWXf17ZRttqKCmqGpXc4swf0UUUXUFWSmPRzYpWqe4KdOMzZ9YZqTbIWHR+Mf1O0/tZvQr72UmGE7ipK9/BVjkykfVGQm5XVhYMkm1BKzIRcnxrN1CgdK1BcBpkXesPaK2/U3fIK0NjadP1DrqgryOw8BF065rWQaWY2CPQe/SIxOfoEYNyCSudayhyMIWfNfl6WPioXOlhpcrhPyJR5VBAeBTbJezmZfX0J71dp/OH1Wy8/D3ntd70DYa4yPR269H22gVKhwPnM7pVKqvbHIOBV8z5+H6xTh+W8dgz
*/