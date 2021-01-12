#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_POP_FRONT_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_POP_FRONT_HPP

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
        template <class S>
        struct pop_front;

        template <char C, char... Cs>
        struct pop_front<string<C, Cs...>> : string<Cs...> {};
      }
    }
  }
}

#endif


/* pop_front.hpp
471/YloS+3vVRm6p96uC615FM1svVsfa4oi/314f5nda+uTCa0UYnpCaNT497BOJx9H8UM5hjKgjhoa8z69Qwvr6V17Gzz/3Fq2ruWyjL6D4OTYqTxbSmxPe0Z8laoocIb0aXElO7/DxGtge7SI+drxXbttT5rAo3b/wOmBc0fYoTE3xc1i70D5+rqgu0sXTpp2auC7p43RVO3pI6vi8jF9SnjNq03h0+nDzCde9MK6gRxFp
*/