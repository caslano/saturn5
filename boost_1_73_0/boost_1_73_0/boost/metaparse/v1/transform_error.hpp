#ifndef BOOST_METAPARSE_V1_TRANSFORM_ERROR_HPP
#define BOOST_METAPARSE_V1_TRANSFORM_ERROR_HPP

//    Copyright Abel Sinkovics (abel@sinkovics.hu) 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/is_error.hpp>

#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class F>
      struct transform_error
      {
        template <class S, class Pos>
        struct apply :
          boost::mpl::eval_if<
            typename is_error<typename P::template apply<S, Pos> >::type,
            typename F::template apply<
              typename P::template apply<S, Pos>::type
            >,
            typename P::template apply<S, Pos>
          >
        {};
        
        typedef transform_error type;
      };
    }
  }
}

#endif


/* transform_error.hpp
G96Kxq2YcCtRn8aQR1J9DG9FH6t4gl0rIpY8kuorqPNe+ep1ojrFkkdSaUj5Y9G+KQ+1YWUYSx5J9TP8WhO35iwi6sZY8kiqv+F1/kC/5l8R9XQseSQ1wPD28M9bNrAR0Wex5JHUQKSCnq9/q+zaRMXWIo+kBhnestUsunQjUefVIo+kBhvRzhelriNqbi3ySGqI4fd1Zd+0LKJur0UeSaUb/laub7KnBlEv1CKPpIYafl9xDYexecrxWuSR1DA=
*/