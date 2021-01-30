#ifndef BOOST_METAPARSE_V1_FOLDR_REJECT_INCOMPLETE_HPP
#define BOOST_METAPARSE_V1_FOLDR_REJECT_INCOMPLETE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu) 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/return_.hpp>
#include <boost/metaparse/v1/foldr_start_with_parser.hpp>
#include <boost/metaparse/v1/first_of.hpp>
#include <boost/metaparse/v1/fail_at_first_char_expected.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class State, class BackwardOp>
      struct foldr_reject_incomplete :
        foldr_start_with_parser<
          P,
          first_of<return_<State>, fail_at_first_char_expected<P> >,
          BackwardOp
        >
      {};
    }
  }
}

#endif


/* foldr_reject_incomplete.hpp
zQ9ObL5YDfc/uzLZiS5hl1E/6j6x2uX/nrCr6VnRZm2T1/ZnzfmtAx52jih2nvCQ9T+nxH+JRxujyOZ7
*/