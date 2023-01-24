#ifndef BOOST_METAPARSE_V1_FOLDL_REJECT_INCOMPLETE1_HPP
#define BOOST_METAPARSE_V1_FOLDL_REJECT_INCOMPLETE1_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/foldl_reject_incomplete.hpp>

#include <boost/mpl/if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class State, class ForwardOp>
      struct foldl_reject_incomplete1
      {
        typedef foldl_reject_incomplete1 type;
      
        template <class S, class Pos>
        struct apply :
          boost::mpl::if_<
            is_error<typename P::template apply<S, Pos> >,
            P,
            foldl_reject_incomplete<P, State, ForwardOp>
          >::type::template apply<S, Pos>
        {};
      };
    }
  }
}

#endif


/* foldl_reject_incomplete1.hpp
k8W8b/kHGR3O4RcsGDFaKerwuuAyY4q3LTilwLFLNxMvWhHdg7ftflUigf7DiuP2TfDoEwlYwY/Nkkh5M+2rv9pE05jdTNfhf2WSp3G2uyVdh4/MaLbrsBt7hodHtqeuwy5912G2XoaeyGn9DIEPBULkSR5MSHvLcJ0vX8DB+kMUHG764E/A4V8fnB4O2/v/GThEAi2Dg/n0cEjJiA2HpCsJDhOHERzql7pNTfpSH/lOD4/m+8/v3WiJ1Zf6pb7R726m//yaK2x/sv/8dv8Z+s8H+rmlebhuUqbi+PsGNpNBFYFkw9avUhwXbMTU1njqRt9s//krNOpXMxABhr6/+v2jAGj1Facw3wZtgfU78RwaFuu30N8weP1G/NsA3ye+jcK3w+v1+BYNz3GXNYVnM7jo2UArEo+VPiKbmkHJgZcTSk5tEdAn3Ncs0M8DRwmj3UrwQHsVfuGR1vqhBMDfhqoAfHIAALD+hrym+Bb8xgCPZvHtjvUx8a1felP4xPzs4f3+TB/0G+89TR/05imS6IP++xD105/O1PphaH1RwtNTN2iVoB+qEyLcUAMIAG3tauj7besgbKARyM0AgA84kl3hEb3R5uxdh8L+UNz/fUgMXU1iqKG3R/b8QNVGy0MUwT4FH2JPz8Y/GtgEappFrx/fRzylEoL7CLSuAwyy9X35Tl4k4vld+6LKhtqhUR+K6An3QHfrEMgDUC0S
*/