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
UPLrNAyCKKEDKSM9SQmHJ4HY2M7qh0ZrpeOdXKuApQbfA/orb0Wb73PNg3TfR708rfwWtY0YLh4R/wwPDl8YW/e/epfGWTLEaT2o+iy3rW5oDAsuTZ+VvWSMSIr6WdUAxEClwGOz6Txq/fMxiV1H06Ox+iRXeoI7mkooat+GvXDVhxQAJfIz5ITdBEdHdKwUgwgC7YicL7a+5h5+MNa4ioy1e+3hpTcQbmUURLDCDQVi7Z/ZaoSNAVyKhwEM7LDuhrgJNeA44unRfeCuc0xodhT6kBFFudrBPOaTUjYyttTp0RTuhxu2ENy8mYdmlmDfxfRc/+px1P5OJwrbKZLSeokzfprm+6NeuZE2Ui2VmtRYj5BEIXVXCg58Fsni5NNDRJ1msdJf+dEmOdOb6cwVeUoYvsQjd4FoWc0eZDwprce4PMlArlmJDHgqpWyCGz1HVIrfw935abB6H5+QtTCqAm1x543f7jzwrPNwSz5SpPXQMRnWzkiJ/KI1Jk+fUQh+BL7SoqEC/kSjV59If4uk7Khdk66cyexaX/YkFvoKczvEWa8KfhKK6EOqbg==
*/