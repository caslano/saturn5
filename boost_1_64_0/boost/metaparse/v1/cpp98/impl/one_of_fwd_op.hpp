#ifndef BOOST_METAPARSE_V1_IMPL_ONE_OF_FWD_OP_HPP
#define BOOST_METAPARSE_V1_IMPL_ONE_OF_FWD_OP_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/cpp98/impl/later_result.hpp>

#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class S, class Pos>
        struct one_of_fwd_op
        {
          typedef one_of_fwd_op type;

          template <class State, class P>
          struct apply :
            boost::mpl::eval_if<
              typename is_error<State>::type,
              boost::mpl::eval_if<
                typename is_error<typename P::template apply<S, Pos> >::type,
                later_result<State, typename P::template apply<S, Pos> >,
                typename P::template apply<S, Pos>
              >,
              State
            >
          {};
        };
      }
    }
  }
}

#endif


/* one_of_fwd_op.hpp
kVfPlJ3uOHONwlIKta+W1Dbjv6dkRdT+WJMabrI1joJGqnDb+YVPSFaMmN5iPcYS8FSxWcR8AXFFUOViJ6VmZwC88pGy/4bz0fiWSRgf0DUg32yL02xVkgncyLnhiAjta6KOG6OSJ2UWoCZHtYJpYn32oYw6H3jSEx3zLbMbXoSKO2GNfe4YhZ8GW+bSOuvwLmFerVfdV127AkBNQ48xoTXPk4CTvusDMYqtjOSb71au7SJrkZIEd3DKedMLsRQxEU6IMjXsqoqgxuXwdo0J5Fm699FYGzSqtnscVZwmghwkEEbCu4/tlgrENFrC1olulvS0knkg0HwaW0HZZYa8qfnaq8vBWX4FqaNwFwPtvfSRG3HROB2XQ8cebhKD5DuXo7LI0QnijSLgOD2B9o86Oe+vIFOqsUFAXIc4JkdGs+UaeRaRGTZo6siFR8kMBGm2f6+kaW73YFkakJTPqEmSOeK/raHfF1xXrF9JXsec26Ib+KHW03rAkJWzbvV9uXUGvFT/nZ5CjeUOo+NovPuONLsqMecGcNSgk9A+J95U52DWYamHXDrpWAUoow==
*/