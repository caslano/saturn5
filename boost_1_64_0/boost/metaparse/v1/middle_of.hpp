#ifndef BOOST_METAPARSE_V1_KEEP_MIDDLE_HPP
#define BOOST_METAPARSE_V1_KEEP_MIDDLE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/nth_of.hpp>
#include <boost/metaparse/v1/transform_error_message.hpp>
#include <boost/metaparse/v1/get_col.hpp>
#include <boost/metaparse/v1/get_line.hpp>

#include <boost/metaparse/v1/error/unpaired.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P1, class P2, class P3>
      struct middle_of
      {
        typedef middle_of type;

        template <class S, class Pos>
        struct apply :
          nth_of_c<
            1,
            P1,
            P2,
            transform_error_message<
              P3,
              error::unpaired<
                get_line<Pos>::type::value,
                get_col<Pos>::type::value
              >
            >
          >::template apply<S, Pos>
        {};
      };
    }
  }
}

#endif


/* middle_of.hpp
brPPckmx3jsJGSl68V1Kzq8WgZmElhc1Tg/QTd01eHWfogbqVZ9i5M9Llm/FzCg+bBEoIz0sWa0Gdts2jBqlQCmUgKO8Tl0jr0PnHwS0AfSJAqG8/QUa4FKd76JbDkaA8DkiVDhantcNW+0y9EPyrR0dXGaEFNN6nFZew2QOIaJvlp8CGt/NORZrbJKT31l3nKDeY+GhwlRrpU5SRZNCU/osjh9xY/mXzpaW29dwsLBhxdXhEukYRGMkCRUPmiAJ8Vq51awkrASR9yWMLakc7ucalM7t55N/+P0XBbfbQATpWj5pBQx/sa4rfIfcNNSvn64QHTsjDpeYeiOSyVPPH38m1Js1Bk3a5Ny40rExAsrbqgrz89Sd8F3clJQdH4WrgbP98xo3VRfMpsr117KOiY1MpU7v5LTbLPuOz3LAWQvpditQclE6rFwOOyQK56WbATRLTT9Zjfb7LZhVB+Nnq+h96YPyz0EU8PLSft5PjOYPr+0uhfio6ZJqhhnM3klUzZy+K4xixZgDR++zgRjAn8lK/EtGerfy2aN4ybp9zy0YAyCuGE1RIqcYYA==
*/