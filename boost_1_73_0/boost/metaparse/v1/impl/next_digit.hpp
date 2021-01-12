#ifndef BOOST_METAPARSE_V1_IMPL_NEXT_DIGIT_HPP
#define BOOST_METAPARSE_V1_IMPL_NEXT_DIGIT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/mpl/int.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        struct next_digit
        {
          typedef next_digit type;

          template <class PartialResult, class NextDigit>
          struct apply :
            boost::mpl::int_<
              PartialResult::type::value * 10 + NextDigit::type::value
            >
          {};
        };
      }
    }
  }
}

#endif


/* next_digit.hpp
DOdki+3jwcvs497L7ePfGOLLVtjHW6+yjw9OscU/kPixFMfP4Sxvxj8M1V24Py7WoT7NG3XHSN1zOBEv+RzOoi32x555hvgsQ9xsiIdtefG1tQ9BaWuS94gM7TtyTe34HSfPl3h38L6Da+OfDe8XOXpvcB3b1Zhmtvs95Tfp3xvUP+Mjz7qQbiQhO4naSNo88oxQkwLUB3sR9Vq3GfFwLrGN297STfbbwnHijp5ziW/OPwxD
*/