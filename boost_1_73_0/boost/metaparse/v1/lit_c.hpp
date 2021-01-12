#ifndef BOOST_METAPARSE_V1_LIT_C_HPP
#define BOOST_METAPARSE_V1_LIT_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/error/literal_expected.hpp>
#include <boost/metaparse/v1/accept_when.hpp>
#include <boost/metaparse/v1/one_char.hpp>
#include <boost/metaparse/v1/change_error_message.hpp>
#include <boost/metaparse/v1/impl/is_char_c.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <char C>
      struct lit_c :
        accept_when<
          change_error_message<one_char, error::literal_expected<C> >,
          impl::is_char_c<C>,
          error::literal_expected<C>
        >
      {};
    }
  }
}

#endif


/* lit_c.hpp
t0oabmo4eXnktnvftHrBtRrxXH256DrwvOVgyWlDyyG5zaNnOcWv81kZDA+NXaO5OrftTSd+fVv34Bp3/Yq6jph8z3id7ozaJ3NwRkbYLm32+33XEE+YUbAdxiYNj0wa7p403MlwvN3GHKpNrITJ1wsOkovW4Z+1kXG1icIlbwcbf9y9u+XhP1/f1+yK8tb3vDZcvqtgm74aTG9AMK23DNt2894zyC0LiWtpfgqmFd/WrPfa
*/