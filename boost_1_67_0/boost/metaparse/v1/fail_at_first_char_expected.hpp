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
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
*/