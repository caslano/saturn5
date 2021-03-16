#ifndef BOOST_METAPARSE_V1_SPACE_HPP
#define BOOST_METAPARSE_V1_SPACE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/error/whitespace_expected.hpp>
#include <boost/metaparse/v1/accept_when.hpp>
#include <boost/metaparse/v1/one_char.hpp>

#include <boost/metaparse/v1/util/is_whitespace.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      typedef
        accept_when<one_char, util::is_whitespace<>, error::whitespace_expected>
        space;
    }
  }
}

#endif



/* space.hpp
fkU45AeqvuvVQDV2vRqolq5XA9XW9WqgOqGKaQRzOlTJoPqi6gBqEKo0UMNRZYAahWoKqLGo5oCaiKoC1HRUy0Flu/xAzXb5gSpw+YEqcfmBWujyA3Wlyw/UtS4/UCtcfsnQ/rn8QN3p8gN1n8sP1IMuP1CPuPxA/dflB+oZlx+oF1x+oF5y+YF6xeUH6nWXH6iDLj9QH7j8QH3i8gP1hcsP1LcuP5hg/+TyA/WHy68xfprB5gcq0vVqoGJdrwY=
*/