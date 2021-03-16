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
gwvq/fkqaPii7g177s/v6b6tbp/cnzTCtpn62f4FqsbvXF2tqaub3VSfH8pIuX+u677TFMY4xNWUbRbBisoaf77BAUL91Kc+BQG9bvfaUqG5oXvfDLO7BztS6pjZXR0u6xnWWx+cIYztbsSFNgxBL/Q2YQ41rsBpmoIzJhcOAR3+YViBN3j86a+Fd/21wYYF+VZ+IgxWnSWRtnA6ZEoEFUXLnCn/kPyvf0mZ/IbvglrOpIRu79lJnYbhDV2uAVY=
*/