#ifndef BOOST_METAPARSE_V1_FOLDL1_HPP
#define BOOST_METAPARSE_V1_FOLDL1_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/foldl.hpp>

#include <boost/mpl/if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class State, class ForwardOp>
      struct foldl1
      {
        typedef foldl1 type;
      
        template <class S, class Pos>
        struct apply :
          boost::mpl::if_<
            is_error<typename P::template apply<S, Pos> >,
            P,
            foldl<P, State, ForwardOp>
          >::type::template apply<S, Pos>
        {};
      };
    }
  }
}

#endif


/* foldl1.hpp
zkeZ0sh+mEdwCTvwOXbiy7yQr3ICV/AWvsnb+S5n8X2u5of8kOu4np+y3ImOU1iBW3gat/EMfscR/IGjWKSE/Q335XyW5Acsxb+zLA9ubD3kYTycdViRDXkU/8CjeTqr8XwexzRW50DWYBaP50iewKtYk+NZm7exDu/kiXyQTbiYTfksm/FlNuebbMm1PIkHNLG+8iCexnS25cXswJE8i+N5NqfyHM7kuXyQnfkY/8gV7M61
*/