#ifndef BOOST_METAPARSE_V1_CPP11_ONE_CHAR_EXCEPT_HPP
#define BOOST_METAPARSE_V1_CPP11_ONE_CHAR_EXCEPT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/error/unexpected_character.hpp>
#include <boost/metaparse/v1/cpp11/impl/is_none_c.hpp>
#include <boost/metaparse/v1/one_char.hpp>
#include <boost/metaparse/v1/accept_when.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class... Cs>
      struct one_char_except :
        accept_when<
          one_char,
          impl::is_none_c<Cs::type::value...>,
          error::unexpected_character
        >
      {};
    }
  }
}

#endif


/* one_char_except.hpp
Jo+kbjb8WvvXvlxC1FONySOpVYa32KNbNJ5A1OHG5JHULYa3NmsXL+pKVN0m5JHUrYY/5YeH9GKjr/5NyCOp1Uj54/n7X0oKETW/CXkkdZvh16roMZ/1sOuakEdStxte8s/mtGUzxINNyCOpOwx/K/eV976KqBpNySOpO5Fq5fneKP+dtdi9m5JHUmuMuK8rprDeIb8peSR1F1L+qHL79R8dJuqepuSR1N2Gl0bCO3tZC3CgKXkkdY/hz2tqxoQ=
*/