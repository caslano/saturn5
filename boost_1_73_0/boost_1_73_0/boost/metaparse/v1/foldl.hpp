#ifndef BOOST_METAPARSE_V1_FOLDL_HPP
#define BOOST_METAPARSE_V1_FOLDL_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/accept.hpp>
#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/get_position.hpp>
#include <boost/metaparse/v1/get_result.hpp>
#include <boost/metaparse/v1/get_remaining.hpp>

#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class State, class ForwardOp>
      struct foldl
      {
      private:
        template <class Res>
        struct apply_unchecked :
          // foldl never returns error
          // I need to use apply_wrap, and not apply, because apply would
          // build a metafunction class from foldl<P, State, ForwardOp>
          // when ForwardOp is a lambda expression.
          foldl<
            P,
            typename ForwardOp::template apply<
              typename State::type,
              typename get_result<Res>::type
            >,
            ForwardOp
          >::template apply<
            typename get_remaining<Res>::type,
            typename get_position<Res>::type
          >
        {};

        template <class S, class Pos>
        struct next_iteration : accept<typename State::type, S, Pos> {};
      public:
        typedef foldl type;
      
        template <class S, class Pos>
        struct apply :
          boost::mpl::eval_if<
            typename is_error<typename P::template apply<S, Pos> >::type,
            next_iteration<S, Pos>,
            apply_unchecked<typename P::template apply<S, Pos> >
          >
        {};
      };
    }
  }
}

#endif


/* foldl.hpp
Kjw6n0mHIROFyS29vrE52Vq5kL2mMYufkzVbRemKCX6tCN6LbyDB+oj1nSsUMlFjpRuqKullyE4ImTTgfKE1ODQK2nvAIxoocqhOCnJZaDcgu75DuM4tK1VImfH7FuLNHB4nU9jpg9xDYw+Qj8d6cK5GcbL+tyz4HyfBz1yE+6ILNP6Mm3Ufl9iQ5b66tIYMhJEldmMAZU9GW6luO2RULRgJeK8AkdmylEZ1FjPOR2/LJF3EsxH1xstVyicPU3K+qOh4ziamNdZF3vTDkbnHGvweoV0M7KWDHdK8hm5v/ZCJY6clg6q23mZWh+wziVYgjTVNaQ8uaDeWAGE84Y8sK433lEq3m3nA2nl1Anqm2ziCRcCSxVcEhBd0W+5PH5+LNCDIa4jgl2R+/WV+AVBLAwQKAAAACAAtZ0pSaTfjt2IBAAB3AgAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDEyNDBVVAUAAbZIJGC1UktrwkAQvi/kPwwWoRXiJrW0IEtARKq0NKKpl9JDTCYPGnfD7qr47ztJfBx67ml3Z775HsMKi8YmscGAiVJmio4fPB2VTk3A8kptt6XM2TyKlkzwW0fwDnwHa9QH1K4pU2RCY12dqJvGNg7aKe4PfXj0PAjf2FRJ
*/