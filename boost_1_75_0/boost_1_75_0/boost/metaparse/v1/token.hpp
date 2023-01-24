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
AxRpCaBIM97Eqbcx/YBD04xCXx67+rjNn/X/ofkHkpovrjxeBKFQ5ycZVQy12m0nJxX9Jt11glpN6L9OMzdH4DTeXw+faaE6HDePERuvdAxfKBGfxfjJ8qYL3tnqXT0e9l/bWb6keh1X8ibqpHIcVzlq7hpqCV8UVCY7Kexyu/YGMZWHZWWYrFxseHJ+/jfcZuU5FqJk6KppG9Wl47uhjViDna+SCjYkau61fXlqly72bGSLflBaf5UzErOGiefOlVX7muIUS7PXSdxL1KpeilWmZxdzceqDesazWakW7eHhVgsw5ry3i6hAOaza9uUplrY3H0RPCJPHdsbnNRQRTpaV2xyy+wvT27OPHBllSXT3/CL8rayMlJUrnQnenmfCoOXIGJjsTUhTbnJahEyMHBeVEtwar8GHJbJzL0mcBYhkqr0YJ4ECOxXZ/nGGWSEcZrVjJMzqj18c09sbraGMN0XsmvbPYVajo2ajG1Gr7sdB/5e16lISa9V5Lk0oVFeB+X+2mkJkcZFyyC+sG4c4EsZjZgKa/FcrHR0ekiO3kPah4C94FnGhYZIehwmXCRAQ7U9fzJknsvBCTj3OhVT4TXYmg1001XtYnCd/niUsSMyoQPch/Uy8nsbWEtW1do6olGMkomrCQHtZmVIpR6eCeDSlAz4r2Y9BhBhlxW1UvVBkkskVahsWxyMnjHvpFjaPIw5wWXCa600rhKwo
*/