#ifndef BOOST_METAPARSE_V1_TRANSFORM_ERROR_MESSAGE_HPP
#define BOOST_METAPARSE_V1_TRANSFORM_ERROR_MESSAGE_HPP

//    Copyright Abel Sinkovics (abel@sinkovics.hu) 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/reject.hpp>
#include <boost/metaparse/v1/get_position.hpp>
#include <boost/metaparse/v1/get_message.hpp>

#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class F>
      struct transform_error_message
      {
        template <class R>
        struct rejection :
          reject<
            typename F::template apply<typename get_message<R>::type>::type,
            get_position<R>
          >
        {};

        template <class S, class Pos>
        struct apply :
          boost::mpl::eval_if<
            typename is_error<typename P::template apply<S, Pos> >::type,
            rejection<typename P::template apply<S, Pos> >,
            typename P::template apply<S, Pos>
          >
        {};
        
        typedef transform_error_message type;
      };
    }
  }
}

#endif


/* transform_error_message.hpp
w8sweWAzRjWoTR5JDTe8jTpYvxcrjXG1ySOpcw2/r3oT/mJj0SW1ySOp8wxvbYa9Pu1Sop6qTR5JjTD8Xf5i48AYoj6tTR5JjTS8zhc+FZhLVJM48kgqw/BrTXu9G7uvYXHkkdQow0tjw+qr/iBqURx5JHW+4e3howMLOxO1IY48khqNVEvPF7dqwP1EHY0jj6TGIOXPK/e1brqAqEZ1yCOpCwxvAb657HpWhqPqkEdSFxpeo1788+63iSqvQx4=
*/