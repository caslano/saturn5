#ifndef BOOST_METAPARSE_V1_ACCEPT_WHEN_HPP
#define BOOST_METAPARSE_V1_ACCEPT_WHEN_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/get_result.hpp>
#include <boost/metaparse/v1/reject.hpp>
#include <boost/metaparse/v1/is_error.hpp>

#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class Pred, class Msg>
      struct accept_when
      {
      private:
        struct unchecked
        {
          template <class S, class Pos>
          struct apply :
            boost::mpl::eval_if<
              typename Pred::template apply<
                typename get_result<typename P::template apply<S, Pos> >::type
              >::type,
              typename P::template apply<S, Pos>,
              reject<Msg, Pos>
            >
          {};
        };
      public:
        typedef accept_when type;
        
        template <class S, class Pos>
        struct apply :
          boost::mpl::if_<
            is_error<typename P::template apply<S, Pos> >,
            P,
            unchecked
          >::type::template apply<
            S,
            Pos
          >
        {};
      };
    }
  }
}

#endif


/* accept_when.hpp
xmDhyIw8IM8ToArqOt2XnnIt5fJ1l+Vxsl4yV7JLcynvV6sH1rrgpny2wzb3aJpqhMk/6Mqh8XLT80KtLXwh9rCwNbmFUCeP5VsMhhwV1IbiPYtS0D31Y0ffNpjePQN28oS/uhtavGNZPj1sA7E5bEEGIkqyfSDyjySCOBBZ/BnB5DDwvzWnb+9xHrDPq46SF3F5/fs/UEsDBAoAAAAIAC1nSlK9GICIZwEAAG4CAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTIyNVVUBQABtkgkYH1SwW6DMAy9R+IfrE49btEq7VJFbFPLNE5lhbXabimYgQoEEbdd/34Opa00TeMQO/F7z88yitBSqi36QpVNbjhs8XgwXWZ98ZJEInqOV2IZJEuh5LWi5Al8AzF2e+xubZmhUB221ZGrmSbtC3cK4I9MHwAsoqBCEzhlltpaLlgDmUELJT2y7omq5CDFHWZViQ0NHdL+wgDb9/VFTi2jzzdQja6xdw45UloAHQzkZcX6O1s2X6A31lQ7Qmg1FdxeyRMDVGrqWjdZLzmVcvy6iJMwmo5ZK1osEylzY+T9ZPIA/wE2uutBbOoi6PLBN8+zwq7Mj+AGBZ0TdkAFgtsDFNrCBrGBkS0MjYTa91get+0M
*/