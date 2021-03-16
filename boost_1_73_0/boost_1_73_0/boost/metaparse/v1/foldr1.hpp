#ifndef BOOST_METAPARSE_V1_FOLDR1_HPP
#define BOOST_METAPARSE_V1_FOLDR1_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/foldr.hpp>

#include <boost/mpl/if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class State, class BackwardOp>
      struct foldr1
      {
        typedef foldr1 type;
        
        template <class S, class Pos>
        struct apply :
          boost::mpl::if_<
            is_error<typename P::template apply<S, Pos> >,
            P,
            foldr<P, State, BackwardOp>
          >::type::template apply<S, Pos>
        {};
      };
    }
  }
}

#endif


/* foldr1.hpp
br7tcYL9j09hue/fVdmMcxQ8xnWYa1zqC5TO3ePk7m9r1F1VO1A/y9+Qb+BEuf3xcNewGwMzpSc55din3Y8Sapcvf/Sf0E4DUM+Vrnt2/2Qu+pdMF4WqA2FDRiKCg1JNI4FjU5XAmqH5SjWzQrMqGmfNaKqtEo/vX3Idepw2U6FUOmkaERPfOZQfcXwpqo8RZKFLe3WV5/mrgvk+YVR/dKlkrr8hMGNBqL6ioWJOflTD3LMTqA36Z/oblDbrXKI=
*/