/*=============================================================================
    Copyright (c) 2012 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_CLEAR_10172012_0100)
#define BOOST_FUSION_CLEAR_10172012_0100

#include <boost/mpl/identity.hpp>
#include <boost/fusion/adapted/boost_tuple/tag_of.hpp>

namespace boost { namespace fusion { namespace detail {

  template <typename Tag>
  struct clear;

  template <>
  struct clear<boost_tuple_tag> : mpl::identity<boost::tuple<> > {};

}}}

#endif

/* clear.hpp
bH/MrlxTGg+mPFkoduurmZJF7iEpzv/a38RYIm7CZs5ltZjn2dnGjUnV0jJX3fwY8ftuq1TrC9y3hilWjrcRv7baA5y2pn2+6e+4XNyeZh1R65ubte/lEnF7Z/y9YHa3nWLtpplyPi/2XREx3yT3nm7CJlnW1KFKxE4Lz3Dp3EkpA57WPsUnYPT4WqG7vDj0PXU9ygPXWgP8cZcH8XnWtV6fvMf5uLyn/sX2L6+pE/x+Yu29
*/