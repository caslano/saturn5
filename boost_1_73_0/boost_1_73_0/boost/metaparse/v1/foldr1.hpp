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
3MZjfyXMNUq+YxYXripBG2plgRXSXVPGvvOPhWc3E1uhdFvspz5S5TkKt2vQb733wSni875Ua/V87UwXtAaRO2zAFQhhCCiEhTdEDVe2MO6K8M6gHsKjOiNNmRJvuH8fnEFviIjMvfZTuFwTkRe/TTrbesreIl4YNnx9WK0fF38iMpMSax++ZtcRWYZR6bmhnhBrOivVB0YkOqd6SejvRC9V/D+anJ3U5ewoOTv9MP4CUEsDBAoAAAAIAC1nSlKHzNtNCgEAANABAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTI0N1VUBQABtkgkYHVRPWvDMBDd9SsOh4xGOA0UgvDSJZ1iGtNdkc5YVJbMSUnxv6+s2E0zdLqv9969k0TEEJUMWDNhXOdT+MLp25MONTu2bcPKspPGlijJTkzwx1TwO4Ft2AbOSDekMhiNTBCOdkoALaOccWtc+pnwZg26uBBULhIkZJma9TGOibCWIJwcksUnLyD4vQtC+WGQTj8DoK92L/sD59vj6dy+N4ftfE9z+mh5tdu/wrzj32la/iua0sVfdv6JZLoJ5qNAdhEJYo8wvyP0MsAF0UEReh8LJm4ZWydWQz565S0U2VYBzkcI13H0FFGDJ9AmyItNuXFgzUVd
*/