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
YXRhL3Rlc3QxMzQxVVQFAAG2SCRg3VTbbptAEH1fyf8wIvJLZbrGcSuFYEtRHOXSNLZskr5UijYwmFXwLmIXu1bVf+8smDhS2x/oC+xcdubMmQORRWMTYXDKIqkyTa9X3O90lZopu4njRfOA66uY+Xcs4sdgxNt8dsKiCstiT65UWAFKJzkmrxNvj8Zri/DgYwCj4RDmX3psJiyGENc4gOEZPOgtRYIhBONwfBZSzvXXuMdWWG2xCsHB801j8Ey8Yo9damVRWf8e1drmIXxuXAoTK7UKISm0eZcV70t0VX5YnttNcQzMpCm1ke2lTBaoxAYn7hGcjoNzSHJRGbSTrFZqfw66dJkTYyuh1lS/x4LR6fgTseBmdmwcOCA6TuCykK6HkSmyKGmMKbltLg1USLYBrchESPGlXkOGwtYVgtUgikLvoDbuTP0hlRWNpqt946ADuntUzJ+DUCn4d6BrW9YWpBrQPanWTeHLx+X9c3y1ime3S9iKSoqXgsAcOtH+ms6E++iJWp6nLLe2pEhnRo6V6ZsQYCdt7tpTa4fgL4wOwJ8R2JSQUZ32OlWntO2UvUc26S++zXih1027Nh4lerNxhQ+ce0r77YgDOkmVFHWKXosy5Lx/M1/Ft4uw7/At5suYuwU6cA7iDHzw
*/