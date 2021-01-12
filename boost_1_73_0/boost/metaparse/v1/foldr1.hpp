#ifndef BOOST_METAPARSE_V1_FOLDR1_HPP
#define BOOST_METAPARSE_V1_FOLDR1_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/foldr.hpp>

#include <boost/mpl/if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class State, class BackwardOp>
      struct foldr1
      {
        typedef foldr1 type;
        
        template <class S, class Pos>
        struct apply :
          boost::mpl::if_<
            is_error<typename P::template apply<S, Pos> >,
            P,
            foldr<P, State, BackwardOp>
          >::type::template apply<S, Pos>
        {};
      };
    }
  }
}

#endif


/* foldr1.hpp
yJoR17yd/ce1U27u/FRh30D/q30DbSlueX7lM0WU2OLYWLQR+gfyvEY+Y5hpov9S28hi//b3HHGPWCLWiF2i8lb7aNFdjBTTxBKR3M/Qzl6m3Tu/v6FabCPCfod6+vcIUfogOc4Xr4rNovRFxhftRX8xTtwjlog1okgfy0m0Eb1EjpgqFouVYrMommYc0UakibFimlgi1oidorz1sp7oJDLEeDFLLBHrxC5Rvq+6iO4iU0wW
*/