#ifndef BOOST_METAPARSE_V1_LETTER_HPP
#define BOOST_METAPARSE_V1_LETTER_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/error/letter_expected.hpp>
#include <boost/metaparse/v1/accept_when.hpp>
#include <boost/metaparse/v1/one_char.hpp>

#include <boost/metaparse/v1/util/is_letter.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      typedef
        accept_when<one_char, util::is_letter<>, error::letter_expected>
        letter;
    }
  }
}

#endif


/* letter.hpp
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
*/