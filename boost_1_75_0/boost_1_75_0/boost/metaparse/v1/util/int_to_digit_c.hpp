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
aQh3A5CzL+FZwocvlfyk0Oirinpx77aotvkAuusYX0JqhWF3ms873PH96LLUr2i1wIBQSyWJMvWzvU3zARmGG0vm9JNBaWCtYU8FtWXayeXaCPjHfSm7pAXczgrtAkOV7wSKqwJhHVGPtX/9Sj0thZk7fszi1Haq6mY3FhtAj+23akt8ExNe57w/+zStr0fxvtNXSQa05Dolt8u03E9VMSlvpc+XQu1dUfU6L51s6PB7EReJ/JacgCOPb1teH6+M8ub3BtgiJUUs78fv7F6saBjb4FS+meg/2z1csKUq8AN7Y6YwCE04xXbOpWemgP+HxxC2jQ75Fn9v5lZez3LJ9XkKFqDs6dKaXzd8/irFHfmgl5DazzOxMaxeIXuQLrU/FV4K+e0nuitBaH4IQRywpAVb8oIMS67u9uHdRzDxTwnNFJDscDiN+NXyAdhrDGUkhLcxfUf8RyBjrzV40XlzE6T+OoIK4kHw+CNw0gBybfLdCaMFFJau/GiWq1FZJfEDj0T8qXNisgRBv14MrAjGBW3nYPJ0sapzhx4624MzwMrhZh17pnPU77pVcAmxR/mGJPhGbxsvbHlzCRdeUe8tTSklWRkjHHbGCKfWjjz2sOtfRyi9YCGvjWOvXDW4cOSWOnOU7HFVSnkfPeh/u9vEUwxkpW16Pyf42x5+E3O7PUcBGIKSPD8nPWLw45pj8AtHSda02iklygxF8qHU
*/