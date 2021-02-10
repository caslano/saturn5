#ifndef BOOST_METAPARSE_V1_FOLDL_START_WITH_PARSER_HPP
#define BOOST_METAPARSE_V1_FOLDL_START_WITH_PARSER_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/foldl.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class StateP, class ForwardOp>
      class foldl_start_with_parser
      {
      private:
        template <class Res>
        struct apply_unchecked :
          foldl<P, typename get_result<Res>::type, ForwardOp>::template apply<
            typename get_remaining<Res>::type,
            typename get_position<Res>::type
          >
        {};
      public:
        typedef foldl_start_with_parser type;

        template <class S, class Pos>
        struct apply :
          boost::mpl::eval_if<
            typename is_error<typename StateP::template apply<S, Pos> >::type,
            typename StateP::template apply<S, Pos>,
            apply_unchecked<typename StateP::template apply<S, Pos> >
          >
        {};
      };
    }
  }
}

#endif


/* foldl_start_with_parser.hpp
g0snK9KUg9rYjo/eHhbLp9nfhE2Uwp6Wr/hVwubhVFK6QBqVb43O4RmxTyddu8WEJdTkqTHBD2IFPz2qf1BLAwQKAAAACAAtZ0pSycA6QNYBAAA3AwAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDEyNDVVVAUAAbZIJGBlU19vmzAQf7fEdzg1yktbZuiyhyIrUtV1TbWuiRrWdweOBpX4kO0kyrffGUjSbS/YZ+5+/wzKo/OFdjgVqjYV8fKBhz3Z0k3Fj3whZvnwgMeHXMRxa8nTcY0tlrUVFTUN7RsqtK/JCCXPEEr2qGIkRrBEu0Mbu7pEoSy2zYEbSu31tGOQ6ZcUviYpzH+C27uiIYeR+K49ZpBv8RqSW3ihHdwkaQLpJJvcZkkCj7/ySPTIGQQ3sesKWekPHr8n49H4+BnNu19nkETieRCaQeXbTMrxbL7MnxbZmP0u5q+5TG8m37pJg0XfOGiJ2E+vV8lBf2fsvqkDR2+s6Apu6XVMxdr7VjAVDx2PlNEbjnyIEUo0B9hsnQfi15Zh4K+EQYeAeb4fUwVtNtqUAeCY+nEArrj3Oma6fyDicH4VzoOez7ZD9iffTHJC5+3gpXP5hrauDhACAF15tODX2EUOa+1ghWjgwq3JXwi1
*/