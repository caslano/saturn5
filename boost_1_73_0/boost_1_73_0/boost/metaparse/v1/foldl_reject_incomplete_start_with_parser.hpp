#ifndef BOOST_METAPARSE_V1_FOLDL_REJECT_INCOMPLETE_START_WITH_PARSER_HPP
#define BOOST_METAPARSE_V1_FOLDL_REJECT_INCOMPLETE_START_WITH_PARSER_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/foldl_reject_incomplete.hpp>
#include <boost/metaparse/v1/get_remaining.hpp>
#include <boost/metaparse/v1/get_position.hpp>
#include <boost/metaparse/v1/get_result.hpp>
#include <boost/metaparse/v1/is_error.hpp>

#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class StateP, class ForwardOp>
      class foldl_reject_incomplete_start_with_parser
      {
      private:
        template <class Res>
        struct apply_unchecked :
          foldl_reject_incomplete<
            P,
            typename get_result<Res>::type,
            ForwardOp
          >::template apply<
            typename get_remaining<Res>::type,
            typename get_position<Res>::type
          >
        {};
      public:
        typedef foldl_reject_incomplete_start_with_parser type;

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


/* foldl_reject_incomplete_start_with_parser.hpp
41hgG7qGjf2P/IzUs0gG3BVsKcU1tGPlQkgg+owxU/yVMVBcJrU6O1CXj/ENUEsDBAoAAAAIAC1nSlJT/UFwtgEAAGADAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTI0NFVUBQABtkgkYKVTwU7jMBC9W8o/jEC9IGXdIOAQWZEqhCgCbas2cDfOpIlI7WC7pf37Hce0RarEZXNwPPabN/OebeHReSUdFky0ujb0+8D9l7GVK9i0LOfDAI8PZZz01uz2TPATSPCYd8kuYYl2izZ1bYVMWOy7Pe1X0svIxbM/GVyPxzB7ZhGaQ6ifuiHgtfxAdm+0R+3TF9Qr3+Rwy9h7q1dUJxINfNl/EN4x9mXNkTELEr57HUTcd22ARxFqCAgSGQvWeN8Pg6O0w6KoUfqNRbLjYNBpRWi5xuLoIzgK4XXxAilUbV2jpQLRV+iN9YE3Zghl1mupq1g053w0nS3Lp3k+Clzz2aLk2fXNDaQ7ONuBNNW48/Br5pi+7Cx9GfapiWN1mn67MPjzhrat9xC8A1l7tOAbHGyHRjp4R9Rw4RrjL5jYDli6HAPGoTK6Aoufm4BeoyTl3kAt244JtNZYZSpSfntHRX/EguzxRpmuYMHB3+04XIyETY3z+bk3CXul
*/