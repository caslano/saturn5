#ifndef BOOST_METAPARSE_V1_LOOK_AHEAD_HPP
#define BOOST_METAPARSE_V1_LOOK_AHEAD_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)   2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/accept.hpp>
#include <boost/metaparse/v1/get_result.hpp>

#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P>
      struct look_ahead
      {
      private:
        template <class S, class Pos>
        struct no_error :
          accept<
            typename get_result<typename P::template apply<S, Pos> >::type,
            S,
            Pos
          >
        {};
      public:
        typedef look_ahead type;
        
        template <class S, class Pos>
        struct apply :
          boost::mpl::eval_if<
            typename is_error<typename P::template apply<S, Pos> >::type,
            typename P::template apply<S, Pos>,
            no_error<S, Pos>
          >
        {};
      };
    }
  }
}

#endif


/* look_ahead.hpp
Uj/RGs/wuruia5WXBdNNTR2Qt6zCcVP2zx/36rujcZf8wrhtgnHrTovGfTI+brDdDAzme/4hBa973BmsF5NFaXGVWKMO02bErg/tPSC3cfPWi6K/fE2WMll2v7DeKlLUpsqzckZYnvzhEvfkD794eHT9TYXg+pv5Im8fymf20HfTLf5cgVPZmnezG2ewJ+/hxZzJIbyXw3kfx3IW7+JsvsBHuIqLuIGLuYmPcSuX8ms+z+/5
*/