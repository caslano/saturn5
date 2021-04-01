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
aRa395MjY4WeX7hyM+N1hECaGGTE1Rgj1qqPXALsaeDWpHOcgi9P9l5ZX8Wbgy6QQpW2sDKYekIg6ahkillrjWvAskQsGCOQZzh28Pyp/wQjOyXVsJLhKQEtEJraBPz0Dp6JQeJLYwtEnmqOcxX/9PU0WYm1gWDi/cU8jkMBT3fq0A+CkjSiuWgY+7002CQV7u+wGgwLOvP/yA0FEiucFDolOvg5yBdy83ugLNOVzmAa4agdfyFQHxdt3YFul3jt1eBOTMNVO7IVKp0/VgEbz+mIgarmHuPdVKjsyp8uEKguQqtoVETy+UAl5SlMCeR27O75An6zMaZgQ8ZMhYVsLnoh6Epg/gPmTlYj2sst/43SIL/LY8fXCjdgMXdSsxVNXz4zLjTgbN6BqcY17PP772naDmKEYFoyaNIRBezZlNDaSc5gmlH2QwpPWXELat/fTpcICLVyR4N5eVzwNX31usULLOASIk7+HcuGLdKbM6PaklCpskfTVgIOQM0ydU1s5ageyH73jPUSPkeSyE3zP31aAzePvexwaYbxZUkZVCeOxG5+UeFRx5tUGw==
*/