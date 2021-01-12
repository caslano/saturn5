#ifndef BOOST_METAPARSE_V1_CPP98_IMPL_SEQUENCE_IMPL_HPP
#define BOOST_METAPARSE_V1_CPP98_IMPL_SEQUENCE_IMPL_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/impl/apply_parser.hpp>
#include <boost/metaparse/v1/accept.hpp>

#include <boost/mpl/deque.hpp>
#include <boost/mpl/fold.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class Ps, class S, class Pos>
        struct sequence_impl :
          boost::mpl::fold<
            Ps,
            accept<boost::mpl::deque<>, S, Pos>,
            apply_parser
          >
        {};
      }
    }
  }
}

#endif


/* sequence_impl.hpp
s/INbVLRgSOTx/IJAD4BQme+Q0z81lkH6fuEILOSQNcn0joWuA8hS6ahJpPy66E8jO/PfOOV8da1b+snaS6FtN2/l/MuLEtoo79/L+0LrvgAi+BDVPtTMMt07znoT6FYFtJjcayAJfBVLIXNsDT6YVnsi+UwFCtgBFbE9O9dn5XzOQfv07QjXW7shMWwM5bGLunv0cpzBtgQA7Ax9sT099Fk/rsJT7Vzy3ujNbAy1sTG6Iud
*/