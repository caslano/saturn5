#ifndef BOOST_METAPARSE_V1_IMPL_ONE_OF_FWD_OP_HPP
#define BOOST_METAPARSE_V1_IMPL_ONE_OF_FWD_OP_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/cpp98/impl/later_result.hpp>

#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class S, class Pos>
        struct one_of_fwd_op
        {
          typedef one_of_fwd_op type;

          template <class State, class P>
          struct apply :
            boost::mpl::eval_if<
              typename is_error<State>::type,
              boost::mpl::eval_if<
                typename is_error<typename P::template apply<S, Pos> >::type,
                later_result<State, typename P::template apply<S, Pos> >,
                typename P::template apply<S, Pos>
              >,
              State
            >
          {};
        };
      }
    }
  }
}

#endif


/* one_of_fwd_op.hpp
Mzkz58yZubOdmTOYgk9wI7qy/W3C3LgZK+MWrIVbsRNuxwDcif3wIxyIH+Mw3I1j8ACOx4OYiJ/gNPwU1eemOS+StoKnn5s+K891nceSeBF9MRVNeBkH4RU04zUcgddxEn6HiXgT5+AtXIO38TjexRP4PaZhU4Jy3oLNCZ6ErARfKU+afFfhR8yP97EuPsD6+BPK8UXOR9i2HRxfPiedG36BBfFLrI3HsDF+ha3wFLbD06ge
*/