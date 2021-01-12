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
97iEn/BpfsOlrCRfnuPBfIFH8kX24UscwJeZwT9xFF/hZP6Z5/NVXsI3eA3f5PVczRv4DuWP/SI8+wrPxFLYQswI2+OkUA6jH5vxZLZmf7bnWA7mOI5gLsczj2dxAqdxIi/nZM7h6fwDp/AenskneRaX82y+zan++5Tn8AeeyyrSdh7r8HzuzwvYnheyO6fxZF7MdM7gBF7KKZzJacznVbycN/IK3s5ZvJ9X81nO5hucw/d4
*/