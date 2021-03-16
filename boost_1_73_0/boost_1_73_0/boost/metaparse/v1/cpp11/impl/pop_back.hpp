#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_POP_BACK_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_POP_BACK_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/fwd/string.hpp>
#include <boost/metaparse/v1/cpp11/impl/push_front_c.hpp>
#include <boost/metaparse/v1/cpp11/impl/size.hpp>

#include <boost/mpl/clear.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class S>
        struct pop_back;

        template <char C>
        struct pop_back<string<C>> : boost::mpl::clear<string<C>> {};

        template <char C, char... Cs>
        struct pop_back<string<C, Cs...>> :
          push_front_c<typename pop_back<string<Cs...>>::type, C>
        {};
      }
    }
  }
}

#endif


/* pop_back.hpp
eR91gn2g9D7RHSZiKGtekbNy1Z+sug5Zr5iIoaztilyjDjt0Sx9Zh1qIoazPEl1P2RfOI2vSQgxlHU+s8dv3XnQBss63EENZJyhynf/UFWdK7xR/30IMZZ2oyDG/xPrDnyHrNQsxlHUSOeFh06ukO4eP2oihrJMVudpsvushaRs91kYMZf2tImfK9icOvhJZF9qIoaxTiOV/9cq1VyDrfhsxlHUq8bL+pV88i6zyP4o8dRHrNEXOr9fvWfo4sj4=
*/