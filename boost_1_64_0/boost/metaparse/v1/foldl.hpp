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
fN3lqecyoinbGxMqNSonDwXiVXOd96Lnv4p+ff448XayWMFVe7wUQ//8kRh1isoQJUoXb1FY9en4EerqiKJWTKEBncQbEgu31iY548R1vNfrswT9OR9a//33dVkdaa9dPIHr1Rqnt1FEoN0iaHGEwDjAd0fGtX+3p0CpCEDA9YNkSAuihSrXqSWmgCu8o0+JMUWZXwiDWdAeaEdjs1+0WI3fnYSRIGaoQ9WR96P3pCfjHFlGZUYA5Xp/4d8PNNXMfYD2Oraxih51+3dhLqAJBOG4o9nUhGZ2MSVDOQ1Dd93akcng4Qm/9dkr5IZd+HdJfTFhcQmg6AUVqVYqYIaQ30Mk+G6ag2JCf92PwkBEPNNa6Ai2nAEdvtEfg5Od/AB6uLcOHoGsOgeLXdTNXuFux8UW/ilHRddmcS7Zv097pwkrjJ70zESIsupu5Ob86FOQbp/pWJkrBfpZC0qULNs7otfLSqlu/iWjQRexWNx72kYJ7RQHa1HkdAzdJPo/cQQj3MEaxF920uSyyhR0nyJh2e7uGAs/U57vrqeTU1iYKk02YkyyBAliMpgBjg==
*/