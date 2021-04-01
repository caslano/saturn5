#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_POP_BACK_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_POP_BACK_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/fwd/string.hpp>
#include <boost/metaparse/v1/cpp11/impl/push_front_c.hpp>
#include <boost/metaparse/v1/cpp11/impl/size.hpp>

#include <boost/mpl/clear.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class S>
        struct pop_back;

        template <char C>
        struct pop_back<string<C>> : boost::mpl::clear<string<C>> {};

        template <char C, char... Cs>
        struct pop_back<string<C, Cs...>> :
          push_front_c<typename pop_back<string<Cs...>>::type, C>
        {};
      }
    }
  }
}

#endif


/* pop_back.hpp
VkeHy7Qdvq0TnBmeKbeVb98usmpSJFq4sMH/Wp9LCWasWIksTjmHbTMqsO3VfVG5CvvMigpo7isD+FXPagYeg+0DolSqgcTE0VGQMwuGi8vFFbLXbgxBg4C4AAZv9LNYYiYzLcQw2+UBpF8Tz5hQ9hYoVJeh4Erlx/+gdcN3EkEDKvi7oNS4+RKTNFy6Ex9c6pmkw5qFP6L3oX5cVBCeyrGgqHV1B7qb7RWHrPPtZDNXJKKMdpr8IRP9fnHAcYza2byut15BIYt0eRI9a8Znc/G2y7OxgKzkX7qJ5LspBxbSADzyWagUzHrlrO9ubow+YWih4e86glBsyGStkAks3RIoynnqWBTkpO5xmEShrJntfOOkUQdYxKnjBldjI/hdhB/H398Q/s0GWnmFZllNlr9IwDZR/TKtv5KDJ51EyleFbTHSiDHpvU28N9CeMoBIRkHRyrKpRxNi/LH3sx+0Oi4kd/dAJQHKahqZVyTdSyU/DbonBxIOt8V0tf2Yo4HYiD5xZe6rX9/qraK0TRu8UHvqN2+X44Ol67SZhzpeKBlAhJXchMz+Qc9nyQ==
*/