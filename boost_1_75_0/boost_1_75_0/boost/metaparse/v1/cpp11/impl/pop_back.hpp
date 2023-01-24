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
9tj3FrK4qKHsvNhZSD+O7JAjHU7p7mtJKzPDqbsyCuJmiN6UnRnQrdJJSaR/spJucOcBCrtU/aV+ZRswwKfRCUroM+s8ymVXu5ms0ltltW45qoiV/3jfHINKxDVpqO5ZNbgcmN0x5VEnBqiVe927wpK+3gtimgOac3LUWlMKXZq7M7+9PJqHzqcYbuMafS6sursjlB7ktttQq/bOqSRHqHihPPp2JQEdgVheONaLQOTcF6GswOKOwQAuaQnFD6kPL6clVeei3XVXDL/X0ct6U/mkwrGV4fZAWVN5dK2/khRmqX7SNU3MxCYip5IB/XV7JWnT6/gRV/hUVLcWObUPMJYb6elNYqRYT8y4ucq4ORN/+pV3QeopDFtCN2jru3Q9Vqq7Pr/AaokW6K734DO+w266QOww9sM+zbg+w7iO8WR8aYJxSdlDXT6BcRONsSnaPDThJ+zagcaD9FgYH2uOjTTu/nx+4t0r4S45SqPBH3csbPGBL+Ju5U2rPrOyd7LrolYK59XWNYNT0mq0J4d06VvbbL9086difvsXixEHaJx0fV78L/y24nViZOfuuoaFF+S3A4pW3eLuqL6JTq70ftrmFywW913O6itkZTqIC+nnaqvhijLZqUNzTQ53x4KtcSfxjPPZSZye5ZRAXWNFCTJ0OaeBoP7BPLapatKaZRZLg5b1bZyfNM7x+VkkB4AsPfccVBlOd2gTSQKg
*/