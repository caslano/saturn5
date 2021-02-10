#ifndef BOOST_METAPARSE_V1_TRANSFORM_ERROR_HPP
#define BOOST_METAPARSE_V1_TRANSFORM_ERROR_HPP

//    Copyright Abel Sinkovics (abel@sinkovics.hu) 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/is_error.hpp>

#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class F>
      struct transform_error
      {
        template <class S, class Pos>
        struct apply :
          boost::mpl::eval_if<
            typename is_error<typename P::template apply<S, Pos> >::type,
            typename F::template apply<
              typename P::template apply<S, Pos>::type
            >,
            typename P::template apply<S, Pos>
          >
        {};
        
        typedef transform_error type;
      };
    }
  }
}

#endif


/* transform_error.hpp
f0zhTwb71A51LmTE91K9FO/3filXMBxY7yNAHf/V+6txE9PbnwyHUFT3f/ocvTdjqhd1fNd8pv03fW4F8EVkmOuNAGK7IUjTsyFLdEH4dgdBHi3RCgw+yEJnMqfW3bMK+wy5JF+o3CIqy4/AM9VIZHZCSoTAbagQxHK5jHIeMsexRKcz1B4kmUAQ8sG1W49qQGFMXHf369V8cT6b7JL/2dX1wqXQOmuBZRknx/2X3D4YQRtJJlIIWRtN61pSbDmWpGuFECuMNEm3To0Jo1wDiisliLmkshEUNs5NXNSHJlEPTKZmpoCJggqHnL0Lbl+49wbY3wb7rJs7HYhOtmF0REUxpTD33F6nvehbVFmyBtMIECUaVTenaHyVcI808vplKnWfBSuLJROFklrGUoTsZj69bvLoMbrSeZsE7e5Oe3be9tji12wKJz07eHvsx805/Qbus5HA7Sy7zxP8N1BLAwQKAAAACAAtZ0pSW/argnkAAADKAAAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDEzMDBVVAUAAbZIJGBNjkEKwzAMBO96hSHnoA8IX/oSkyhg6spgKSn9feWE1L1I7M6iFRmrLUk5AmXZqq8nf961rRphl2ydQynZJ+FAhFcaJpjCo2QW
*/