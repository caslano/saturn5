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
ewWF2XBOZNhrZPbT2SqtcIeTjoJUA9OlJ7+cYs7XWbXUJhWVbBg11wui0ayFkXxA8AKMxCNdTmodnP8oqN5iRZWZOo+DX4xB3kZOHO9fXqZPDbkfUuahyfEmd0OfC9NoVuqNjvGEex3SzCkYohzuicZzfBn+nc/b226VPMOAW0LzlQjwh5/HwTAxX+Go9NuEgbJJKRJIW+u7yK92EsbUIP6yoBzwXOHJDJcc0i7JX1ra+jE5BdVrm5ADF09PMHRQ64ZtW5OP+haM3PtH3UGSSt752zsIfvpUkkOXQwWHiPn+8mew7zTax8AcEf6XmIYrE6KVhtuHADPJLnl4dxdxearJQjqiLa4fjF6ifEY+tnFa8zyeuW8S2f+R0mZHzfRAjP/hbBGVNNEi40zrXNljDIGYOynC5jtORTZlUgFKdhLBcKeWf7BaXKU8eNKY/PGfAMg6Vn91P3jRXTw92+FU/4KrFU5zb83SfRp9SISh3p/0BPi0RVXuTfM1vLneTiFTI832s7+PTqrr23svfhBA3o9XedHzseSRipJCQLNmtYdhkAAbQnfscPFYsQ==
*/