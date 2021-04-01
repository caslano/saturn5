#ifndef BOOST_METAPARSE_V1_TOKEN_HPP
#define BOOST_METAPARSE_V1_TOKEN_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/space.hpp>
#include <boost/metaparse/v1/repeated.hpp>
#include <boost/metaparse/v1/first_of.hpp>

#include <boost/mpl/void.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P>
      struct token : first_of<P, repeated<space> > {};
    }
  }
}

#endif


/* token.hpp
+LDdrvJEYx3q3I+ZHwAsu2rmAKk7XUt4ngEO2F1NvZFJce6d5fjwIdUmKv5uPsk3cUvohB2HLVU6BdlcQ5pFcKhlx1z/RoWtMJjZCli6ODoSXxvxdkVLUSo7Pd3d/felz31vgkhrH++RJbA9hB6q5fX5HH3iTELvYgv68XOPP8gf3iB/1b3AKzRxrB6HRF1rWu3+dCi4UTGxDIa0fmp/yzDSFAfYWdyCsFFSYDDNqHxDbFDpNd5Yt4UaROSscgRyezo4KgykVV1HKLgMNrCQh7y/Cw8d2A0H7sCGjvbqx52if74XpoKUn2QLviN0q2ApaxRykAHh/4D0poo9Y/QI+8Qkg6jdg3iX53DhBfktRozQFC8/PMNf56WcUjs8ImQm/gmibjK3DeeiYJChJH83sFFqNglJiyFxRAgVx68NpJpF11l5cQ0Ljt1wu1dSLShIdmB5b8+raqqiHOkTlDwtXh+WA+Avnr6vCmpazHd+yop7EBw8y6IjhrhqRvEWuHW5Mn7nI4Ymk88Te//fAo/ynbOegoB8YYq8yGR8nCMA7FYLKjh0Vo7EiPOKGw==
*/