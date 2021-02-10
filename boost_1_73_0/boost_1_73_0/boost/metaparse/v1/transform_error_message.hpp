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
mzWvDLScwhPK7eAWQaq4jbekjZPtjf/vEw4zkKSXv3N2hh4JPaMO8CKEvw4c738BUEsDBAoAAAAIAC1nSlK/UP4JgwAAAOYAAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTMwMVVUBQABtkgkYG2PQQoCMQxF9zlFYdaSC4TZeBApnQwUZ1JJUsXb2zpoXbgKP3mf/0PO5ikaz0BZ1tLGlZ+PoovNUCV7v0Oqul3MtYOp7LeoDIQDJDy8MMEUzltm8ZPlpUHpLRphrHfWGaRI934krRy9Kv+mEY5lIIl7K/enQeiG0B3WMDw4wm8ijtdeUEsDBAoAAAAIAC1nSlI+5TiwggAAANoAAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTMwMlVUBQABtkgkYE2PwQoCMQxE7/mKwp4lF/EU9uKX1HYWippC21X8e1OL1tOQzBsmkYbagq9YSZJu2eSK1zOXWFfaNbXu08WA05GEpyc8cFpocedbgrZDTREk4TMYUVEeKCtpVlvzd5QNvu0F/wXCc+lE/d3uGaUOGnIER3RxPeF6pBrHAxT+VfJ85w1QSwMECgAAAAgALWdKUjJM9s6AAAAA2gAAAB8ACQBjdXJsLW1hc3Rlci90
*/