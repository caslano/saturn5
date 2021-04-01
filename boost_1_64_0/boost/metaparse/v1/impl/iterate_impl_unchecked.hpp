#ifndef BOOST_METAPARSE_V1_IMPL_ITERATE_IMPL_UNCHECKED_HPP
#define BOOST_METAPARSE_V1_IMPL_ITERATE_IMPL_UNCHECKED_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/impl/fwd/iterate_impl.hpp>
#include <boost/metaparse/v1/get_result.hpp>
#include <boost/metaparse/v1/get_remaining.hpp>
#include <boost/metaparse/v1/get_position.hpp>

#include <boost/mpl/push_back.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <int N, class P, class Accum, class S, class Pos>
        struct iterate_impl_unchecked :
          iterate_impl<
            N - 1,
            P,
            typename boost::mpl::push_back<
              Accum,
              typename get_result<typename P::template apply<S, Pos> >::type
            >::type
          >::template apply<
            typename get_remaining<typename P::template apply<S, Pos> >::type,
            typename get_position<typename P::template apply<S, Pos> >::type
          >
        {};
      }
    }
  }
}

#endif


/* iterate_impl_unchecked.hpp
eciaRmpzFtCKwV8NXnYlzKrye14nYCJ82AkaxB2HyPFDq47tx07JR+DcjthFoR4sYoptMsDDR7nJnuYcM6bVmAfndykIj1+8Rrz8KoRpp/Yu/5tnNpCIxNfINurQOnKcV1+hNarvHL8GD/lvgKhl0j8PT8CxfArXxygnQUI53r3TvqfhzIAN0QNGI5zhfrvbUf6ZNMZ0fSdvtiLpe+Dcr/voYBOjMedi9rWsDCO6cMWHU2Rf7rZ9EUSuvgTZR65z1flpK8wzHMGx9JVvKUObm7CZI7QORsadOhwORA3P5wdwg9V4SVjbgmRhcDGZ5PB42P+/cLiV4q+jy1J64dbKHgeYU0JVQe1N9UM/vZWu47jK231jKoQb3pCy3ZBkqw46HaVsA+JTNp/OCbBt0BA0C2Ixr+O+IXUTKjsNvoHPVa5ulqkChmS0uok5InLsMhoZDFdDIJQnfz4gRlJuCqlLk+f/6C83PdptE+lmctUrB4iMrY3PKkdtzoB+ZxinK7HOH0LhQ2vZCh21nFJ9Y+UY65dpcaA9Tl5iRnp9avD/UeevdlseSc/eAejJJA==
*/