#ifndef BOOST_METAPARSE_V1_EXCEPT_HPP
#define BOOST_METAPARSE_V1_EXCEPT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/accept.hpp>
#include <boost/metaparse/v1/reject.hpp>

#include <boost/mpl/if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class Result, class ErrorMsg>
      struct except
      {
        typedef except type;
        
        template <class S, class Pos>
        struct apply :
          boost::mpl::if_<
            is_error<typename P::template apply<S, Pos> >,
            accept<Result, S, Pos>,
            reject<ErrorMsg, Pos>
          >
        {};
      };
    }
  }
}

#endif


/* except.hpp
xn/XQWshugLTkdy8sgqTTnSt/Q2z57Ik9svKmldHCD/j16G4JMwrzfok+mKxtOS/2E3DB5l0CSLT4bFIdlxFm2tLIgdj/ljm9C2kvkxg4MuZU7mcDZ6440p6npyheA/1glBFsg4psZBN68NLA2MEJp7ZJfy5SdCg37MaG/mo3UH3/U5qtaPJMADSD757lK0wh8fN7ZSPEvWWpWWfOpdEhZmeoUyKZYujYO3K1JbAZ76UPXgO2ZxWkZ6SZ7HdpytK0IXpNmg8+6deY6JzHuULYsvPotuRQgocqgT/F86VDwi8FUKlmhQs/JDx/2JyaGLJEACpBCDNNQrKe4F5ooxLjFwdtAkosUjxEY8gSX4UuxYj19RvD9k5vPR4z5lErvYlLaIdWoSW3iI/N/WXwuZAQW0u3/VW3ALsEhrp20GzwpSbgxwlFZp7dMMJcnMmkws4OXZn65mIhSHr15knIYTXnMK4TSZIhZeeMpET83ycmM/UhAIbjJOdRzXeNctog41MWsa8SwW61TkH1mBSlRS2CZ8PX1anQIn+t3eGJBtyWjbv/sjABB3PhT4RLQ==
*/