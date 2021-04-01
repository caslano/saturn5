#ifndef BOOST_METAPARSE_V1_UTIL_DIGIT_TO_INT_C_HPP
#define BOOST_METAPARSE_V1_UTIL_DIGIT_TO_INT_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/error/digit_expected.hpp>

#include <boost/mpl/int.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace util
      {
        template <char C>
        struct digit_to_int_c : error::digit_expected {};

        template <> struct digit_to_int_c<'0'> : boost::mpl::int_<0> {};
        template <> struct digit_to_int_c<'1'> : boost::mpl::int_<1> {};
        template <> struct digit_to_int_c<'2'> : boost::mpl::int_<2> {};
        template <> struct digit_to_int_c<'3'> : boost::mpl::int_<3> {};
        template <> struct digit_to_int_c<'4'> : boost::mpl::int_<4> {};
        template <> struct digit_to_int_c<'5'> : boost::mpl::int_<5> {};
        template <> struct digit_to_int_c<'6'> : boost::mpl::int_<6> {};
        template <> struct digit_to_int_c<'7'> : boost::mpl::int_<7> {};
        template <> struct digit_to_int_c<'8'> : boost::mpl::int_<8> {};
        template <> struct digit_to_int_c<'9'> : boost::mpl::int_<9> {};
      }
    }
  }
}

#endif


/* digit_to_int_c.hpp
8ZdvzsiBGPoAlAqRzYl7qR/IcnRlZqrYKenANiojbKt4ff3QZyVJ4vI3YA4y/zVj7bTH6BWozXH3/yWW4z/TAd2/edKUjx42Z8mj34EbE7ai9Dxzk8HI9vFZeZW2Iya9AQCakteSt2IZOdD3vdCGLwoAq/HMgJaOZSPYaKtTHdTIMGCp+3gp4I+hY0UNnknMnHGn5y983riS3G3DItmtdfDjNznYAbXThmfvA8hlEHCslshZrdo85EE6NkpvuOHjBPsOA1n2Q5ZlkbnBqVhyXxZCJQStfVVS83RJOZWKOIG8ZkrDc9Qso1SbCETjXoGsTQJIJ357Q0XarnL+dEm1jfMrHClsezUswgyVBmmGuoAU+werbMbS5T68IK6gZRbY3Y45FC6RNLXjx8I4r8tJepsmf2SDHYYMWx6OE6e11Ny11okKTB5+4gGAqLUqQoeisvE6Np6544WHn9GkPlM/eQ8BPnXvj7NmwYPfYggcKIDTNvaQmksEabt8Bvgfwz9c36oODu4z3f+CTh19Iq77Nq5FZZzWRDsyqz5R/+tbivltAAO2Igs++XzHZg==
*/