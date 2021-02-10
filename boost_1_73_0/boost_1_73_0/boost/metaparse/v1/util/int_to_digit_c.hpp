#ifndef BOOST_METAPARSE_V1_UTIL_INT_TO_DIGIT_C_HPP
#define BOOST_METAPARSE_V1_UTIL_INT_TO_DIGIT_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/mpl/char.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace util
      {
        template <int N>
        struct int_to_digit_c;

        template <> struct int_to_digit_c<0> : boost::mpl::char_<'0'> {};
        template <> struct int_to_digit_c<1> : boost::mpl::char_<'1'> {};
        template <> struct int_to_digit_c<2> : boost::mpl::char_<'2'> {};
        template <> struct int_to_digit_c<3> : boost::mpl::char_<'3'> {};
        template <> struct int_to_digit_c<4> : boost::mpl::char_<'4'> {};
        template <> struct int_to_digit_c<5> : boost::mpl::char_<'5'> {};
        template <> struct int_to_digit_c<6> : boost::mpl::char_<'6'> {};
        template <> struct int_to_digit_c<7> : boost::mpl::char_<'7'> {};
        template <> struct int_to_digit_c<8> : boost::mpl::char_<'8'> {};
        template <> struct int_to_digit_c<9> : boost::mpl::char_<'9'> {};
      }
    }
  }
}

#endif


/* int_to_digit_c.hpp
pkyBRI9qpEstaXvfEauxqaC3Xk1n8xWvyndzd1xIMr9UWt3VlaWxlObj5DXRXZEQ99Ev6+QbNmXegg1WkmtsQBdoUwFFouAdUYCrCqldFh4s1vTUSC1TWUXM+NkpnmLosBcSC+APBxz2g27Ee9yQOMVo31S89/a0Ws8Xrw57TFOsqXzLb83dU8dnCRZao8Dmx/3Nu/8g/3bUkw3DKxvOefmHTejGH57GH12Nr3RGQTjO3+FGBsfPMeWXH+8vUEsDBAoAAAAIAC1nSlIi+g5aGAIAAFMFAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTM3NVVUBQABtkgkYOVU226bQBB9X4l/GBH5JTJZ4zitQjBSZEex1Ta2bJp3AoNBxruIXbvl7zu7+Ka2X9C+LLtzOWfmzIhQo9JpojBiYSlySZ8ttj9kk6mIzeJ4aQ94fYlZyC+ekHfB7IaFDdZVS6Ys0QkImRaYbsdui8rtELh/58NwMIDFF4dNE40BxHvsw+AR3uSBPP4A/FEwegwo5vVb7LA1NgdsAjC1eco+eJ5s0WETKTQK7X1FsdFFAJ+sSWCqSykCSCuprqLitkaD8lPzQu+qi2NaqlqqskvKywpFssOxOfz7zw9PkBZJo1CP870Q7RPI
*/