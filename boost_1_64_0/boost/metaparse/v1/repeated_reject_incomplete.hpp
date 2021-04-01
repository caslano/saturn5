#ifndef BOOST_METAPARSE_V1_REPEATED_REJECT_INCOMPLETE_HPP
#define BOOST_METAPARSE_V1_REPEATED_REJECT_INCOMPLETE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/foldl_reject_incomplete.hpp>
#include <boost/metaparse/v1/impl/back_inserter.hpp>

#include <boost/mpl/vector.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P>
      struct repeated_reject_incomplete :
        foldl_reject_incomplete<P, boost::mpl::vector<>, impl::back_inserter>
      {};
    }
  }
}

#endif


/* repeated_reject_incomplete.hpp
WoSHFRStAYLpFruj/MCEr4pBVPU9RkxmnIR2/0KXgJ8FCN19q2PDkxF7XRyxb2Ta5hO7720Phly1PfuZJhsRHv7mPyj+1vXr0YQ5woRxBMTvoxLAYOgVwnRFQ+xnht8xnThWOfuNoT2LPcEqgsOIFCG9NL/I1LcXpBQjOVK0oPs9Hy1riSUv06St6GBMIrSTJYebf7Q90DMz0qz4ruh7L753n/cNPZzQIngC3pjYANEIErSmBW8z5kTEl0dDhby3cdkaPCqARMWMGTQPX1fojnmuWmF9XQQVQEYMrUkIZeljbVsqP5tidDSXHdl/9O9pcAa8w/EznduGY7FQun4exCGUjg7yaJk8LY+I7nxKbojoN9M0soQ4KY+RYKLepO0n543RcUhvA6dBT47KQ0HL4hdRNOKMc4Ey4kJl5YXQs/gfAKyOo88V/8RIXYz6ztzc2MbqFTQFzlrjzP9gukoIB9sEuntWm7nmDcAjzfycDs7sE46qJ2TD0pZQl7w7RJfaOXyiUYof+vxHoUYQFGrscQPwf68GfzkyD4ug/Fp91an72BtqRvwK6TcQFg==
*/