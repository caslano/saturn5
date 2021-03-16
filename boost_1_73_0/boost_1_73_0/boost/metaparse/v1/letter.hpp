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
blFBdn6hb6zwzBU5MAyCp5hdEfTf4qBdaHI+byk+B26bva0WgodXnhd++Iwoqq56QjtdnB0e6vn1BwF4KbPnZ7lX05av8V4SGP3Z+hDMLllYmOOs0GfkFftLXjgkMH7OtjSwPrjhkfIXwNDPpgJvIjTxs6FSZdvGABoIqB/QJdgWwkdK/XZmTmlpqMQ+04qF4dEWerCa+m0Jpmyt0gNNrv1iWXyMUB5Q7vnQJc3Onh8ebHpfQYtu1nBBaYTgmtA=
*/