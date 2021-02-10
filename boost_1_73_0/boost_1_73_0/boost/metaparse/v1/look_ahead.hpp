#ifndef BOOST_METAPARSE_V1_LOOK_AHEAD_HPP
#define BOOST_METAPARSE_V1_LOOK_AHEAD_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)   2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/accept.hpp>
#include <boost/metaparse/v1/get_result.hpp>

#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P>
      struct look_ahead
      {
      private:
        template <class S, class Pos>
        struct no_error :
          accept<
            typename get_result<typename P::template apply<S, Pos> >::type,
            S,
            Pos
          >
        {};
      public:
        typedef look_ahead type;
        
        template <class S, class Pos>
        struct apply :
          boost::mpl::eval_if<
            typename is_error<typename P::template apply<S, Pos> >::type,
            typename P::template apply<S, Pos>,
            no_error<S, Pos>
          >
        {};
      };
    }
  }
}

#endif


/* look_ahead.hpp
AC1nSlIOxAi1OQEAAA4CAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTI2N1VUBQABtkgkYGVSX2vCMBB/P+h3OBRfhJq5h42VUJAh05cp2vmepdc1rE1Kkil++6WN1MGekrv8/t0R7sl5KRzlwJWuTDi+6XoxtnQ5bIpizx4WL8DZvclZxMEUpngkeyabOlUScEtdcw2AUngRyTagY8XdgJRtmYO7ONkYFxjsT5ezG38Qfm0UaX8TlkMxiuRQe9+N7ByQa9FStMS3dYEX5WsUqPRZNKrEYY4lWnKd0Y6wUZrQeWF9oLLIRS5N2wpdRvWMsdlmdyy2+2zW0/e7Q8GWj0/PmKb9e9zKSAnXW8Yh/Ymsqq7Yj46i8mTR14T9qrEWDj+JNE5cbfwE+HnABonOGm+kaXLoR4hmMflimcDGOJ/hv0wJfIQtpKuvYJ6h/LENm53Wh+N2957ASkrqQnvO5gkkIeTdgrPRl92/wC9QSwMECgAAAAgALWdKUsW8CKRMAQAASQIAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxMjY4VVQFAAG2SCRgbVI9T8MwEN39K07pUBiCVQaEKpOFlQHxIWbXuaQmji+ynab995zT0laCyffx7t57
*/