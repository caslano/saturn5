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
Ps1T+Azb8TneyaX8K5dzBV/m23ydNU+xHrAeV/EUrubpfJeX8n2O5hrm8ENew3W8ln/nRK7nJH7KKdzIO7iJf+Vm3sOvOIdb+AC/5kJu5yJ+y6e4k8/wB77AXVzO3XyDRQ6wP+N+XM2ifI/F+BFL8gsewG08hFVP9b0Hj2VlduaR7M5qvJrH8XrW4QzW5Sw25BI24vNswrVsyo/Zgt+zJXezFbu2cXzKHjyVQ9mGl7Itb2Q7
*/