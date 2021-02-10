#ifndef BOOST_METAPARSE_V1_TRANSFORM_HPP
#define BOOST_METAPARSE_V1_TRANSFORM_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/accept.hpp>
#include <boost/metaparse/v1/get_result.hpp>
#include <boost/metaparse/v1/get_remaining.hpp>
#include <boost/metaparse/v1/get_position.hpp>
#include <boost/metaparse/v1/unless_error.hpp>

#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class T>
      struct transform
      {
      private:
        template <class S, class Pos>
        struct no_error :
          accept<
            typename T::template apply<
              typename get_result<typename P::template apply<S, Pos> >::type
            >::type,
            get_remaining<typename P::template apply<S, Pos> >,
            get_position<typename P::template apply<S, Pos> >
          >
        {};
      public:
        typedef transform type;
        
        template <class S, class Pos>
        struct apply :
          unless_error<typename P::template apply<S, Pos>, no_error<S, Pos> >
        {};
      };
    }
  }
}

#endif


/* transform.hpp
yd4z+F/Q1HPatYo/z0AMukSbrY9QdwB6Tdw9pdx8HZ1qByvEAlouNdQSan/SskFpDZnY5KFo3OEaeDkGT4yNowD+oHnik9v2BxsGCLhZm8v2cjRfvE8/PDGIYyx5uSu79a4reQtS8poubzfqB1BLAwQKAAAACAAtZ0pSmSkqM5cCAADNBQAAHgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDEzMFVUBQABtkgkYJ1UbU/bMBD+bqn/4VSEtEkLaVIKtAuR0Cga04COFtg+hvhCItw4cpyG/vudnSawijG0yGpj53nuzfdcoLHUcVRiyIIsTyT9PeK6loqXITtbzNh0Nr9l38/nC5ajVjEL3OfvgdtQdtgOzFGtUDllxpEFCguxpnO4SzEHLrP8AYyNT1AjPKAGnSJwTKJKaBBZqUFWuqg0pJHiTiw5cshyizLxkSEKBUrrggU80lGcYvwIS0Ie9zU+6X7ItNSRAH/AuKqflGMWABzB+Aiap3sxz8jz4SrW4PvgDSeDA9j7X94W0X+DeBGtDQC88ZiIl/hzwRzlbBZhPBi0cA9ePsMRfKsEeAcb7vX05PRiyoRxbNdbZDiEU4wpHEsewz2V1gmhKpVLrxS98zL61420aZtTMnJIt7dq8m7d/ytv
*/