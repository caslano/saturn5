#ifndef BOOST_METAPARSE_V1_CPP98_IMPL_LATER_RESULT_HPP
#define BOOST_METAPARSE_V1_CPP98_IMPL_LATER_RESULT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/get_position.hpp>

#include <boost/mpl/if.hpp>
#include <boost/mpl/less.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class R1, class R2>
        struct later_result :
          boost::mpl::if_<
            typename boost::mpl::less<
              typename get_position<R2>::type,
              typename get_position<R1>::type
            >::type,
            R1,
            R2
          >
        {};
      }
    }
  }
}

#endif


/* later_result.hpp
k8tviXZgQrQD2IqwlRHz1m6IGYxAuGO8Zmdz9Yi8JbUhsfgTMSmMMuTa7REx+k52/WJ2HfAFnmRFco39T2o8ybx+vLCwtEnd0VzlhrftvnEr7L6JK13+ieWu6dWgD6xWzNu34YMr2IsA4Vd2WofGlnlcUCGvGe+UeuFCG5ytZAGT2fghtZh1psQ+TnMKj3ayKjfCgN1QyPhE8/je1x4Grl3agd6xNBvnOCdaJM8SBpVYLRGENnZLNkYXZVa5kphbP9WGfhq/aBLsNRh+D4g6MJabl0SnOM/StAYGEZa9b2aHwxTzd1tJx1XMzzRypTWIfrWN0EdIb6kN2wuxP4jAe79zBOyCZF/qlHaKkmtSWXUVQotzVcGDPvuHwMkx3gYTHOHGB3h2N+12+Jp2O6yV7PNtPvunlLnaBcJrk6/gK8LN5nNVOP2uD332HxTzcBXS1gYOqUtAKC9EKKWX2Uo6g1bb+8Ddi/73Qa+gxagWFpvbfoIDTdGvbI8AbgXwlMP/jyzlnkrRb8dUJBgcDoajfSU/X40B/wDsu8U+T7XTP/L7Ryjyu0T0r2K16V0W+f5juCYx+g26tdgi5UVjj0p5JooJD90UQOHhGPndP3RTgEVe+zta1fZgHkuK+zYmkU6mmMXNFLNZiv2kxv47eey/q0RedVRRWOj/alEqeOHskf8zHz2vyH8e7S+y2H8W7T/Ml5fAY/qxmhjAHGgD
*/