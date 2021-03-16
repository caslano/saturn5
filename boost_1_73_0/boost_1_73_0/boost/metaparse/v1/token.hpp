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
RR5JNUOqlud7uumV7K2cHkUeSTU3/Hmd2jcumajLo8gjqRaGvyn5B3cfIurhKPJIqiVSTTzfuOs7/kTU/ijySCqIVE3Pd3Bjp5uIwqba80iqleG9Q5Phu/sT1SKaPJJKMbzkhxQcWEnU2GjySKo1UvU83/82Ld1G1OJo8kiqjeE1KnTHugeIeiiaPJJqa3gZdnnt2oFEvRVNHkm1M/z9Kq/3zCSiomuQR1LtDW/ZHlo2M5aozjXII6kOSDX2fKM=
*/