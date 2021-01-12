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
TubpnMszuIAd+RLP5Os8m5+wEzdxBlufZn/EtryX3XkfL+Qs9udsZvN+Xsa5vJ4P8CbO4x18kPdxPudyER/mYi7m4yzT1v6Hh/ApDuDTHMTXuIyv8yWuYJV2PodZjStZhx+yKTezE79gV37FOdzC+dzG5/g1l3M7/8Yd/IDf8O/8js3a26/wZP7IydzNKdy3lN+pWJRVT3cexGNZgk1YkifxALZjKXZmaXZnGV7Mg5jJsryc
*/