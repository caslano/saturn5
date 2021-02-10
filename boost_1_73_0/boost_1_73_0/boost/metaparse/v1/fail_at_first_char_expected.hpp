#ifndef BOOST_METAPARSE_V1_FAIL_AT_FIRST_CHAR_EXPECTED_HPP
#define BOOST_METAPARSE_V1_FAIL_AT_FIRST_CHAR_EXPECTED_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/impl/void_.hpp>
#include <boost/metaparse/v1/accept.hpp>
#include <boost/metaparse/v1/reject.hpp>
#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/get_position.hpp>

#include <boost/metaparse/v1/error/expected_to_fail.hpp>

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/equal_to.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P>
      struct fail_at_first_char_expected
      {
      private:
        template <class S, class Pos>
        struct apply_err :
          boost::mpl::eval_if<
            typename boost::mpl::equal_to<
              Pos,
              typename get_position<typename P::template apply<S, Pos> >::type
            >::type,
            accept<impl::void_, S, Pos>,
            typename P::template apply<S, Pos>
          >
        {};
      public:
        typedef fail_at_first_char_expected type;

        template <class S, class Pos>
        struct apply :
          boost::mpl::eval_if<
            typename is_error<typename P::template apply<S, Pos> >::type,
            apply_err<S, Pos>,
            reject<error::expected_to_fail, Pos>
          >
        {};
      };
    }
  }
}

#endif


/* fail_at_first_char_expected.hpp
XJ4HImBSPpFuIt/xV57+R/4BUEsDBAoAAAAIAC1nSlKA90hEiAIAANYIAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTIzOFVUBQABtkgkYO1WTW/bMAy961dwCYptQFMn7se6wA1QdB0WYFuyNB2wU6HYdCNElgyJqecd9ttHKWlS9BfskItNUXyPFGU8OiP0lEuPI5EpU1p+rbBtrCv8SMw/z6fxAbPZD5El+50s2QSLrujCHbondD2vChSZw1q3HOCjM6+KkWicIixQy3YIKUNfbHXh7yDt92HRch3wzlugpSR+YAuFNW8JSkWgDFBj4XyQxkDIl2uz8u9FVkiSYGy+xHx11WnRd0aiP0hPz84vPlx+PFgH62AdrP/bYkEMMhY0daudUVRvtEJDW1HN42KnqiNBJdU7JQ0yeq0b2XpYKa2DekJU7c02kGWNJJBliTkLqtXaNso8QpB+fwzFGpmAgvQqH51QW+J8SmrdwgqxjtGvWBdr30IjFfEm40vrQHKaJW+dc0xuTeE5J4UCdsRLyT7tUBYtO1yljOTRcML4iQFvK4RaS2KuiuNMATfjWDoau35cAqkQIL3nWbFAahBN5A7lB/aACGUa/E2b08EgPUujn43TY8jl2m8PU4Ujl1Lp
*/