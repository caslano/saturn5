#ifndef BOOST_METAPARSE_V1_BUILD_PARSER_HPP
#define BOOST_METAPARSE_V1_BUILD_PARSER_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/build_parser.hpp>
#include <boost/metaparse/v1/start.hpp>
#include <boost/metaparse/v1/get_result.hpp>
#include <boost/metaparse/v1/get_position.hpp>
#include <boost/metaparse/v1/get_message.hpp>
#include <boost/metaparse/v1/get_line.hpp>
#include <boost/metaparse/v1/get_col.hpp>
#include <boost/metaparse/v1/is_error.hpp>

#include <boost/mpl/eval_if.hpp>

#include <boost/static_assert.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <int Line, int Col, class Msg>
      struct x__________________PARSING_FAILED__________________x
      {
        BOOST_STATIC_ASSERT(Line == Line + 1);
      };

      template <class P, class S>
      struct parsing_failed :
        x__________________PARSING_FAILED__________________x<
          get_line<
            get_position<typename P::template apply<S, start> >
          >::type::value,
          get_col<
            get_position<typename P::template apply<S, start> >
          >::type::value,
          typename get_message<typename P::template apply<S, start> >::type
        >
      {};

      template <class P>
      struct build_parser
      {
        typedef build_parser type;
        
        template <class S>
        struct apply :
          boost::mpl::eval_if<
            typename is_error<typename P::template apply<S, start> >::type,
            parsing_failed<P, S>,
            get_result<typename P::template apply<S, start> >
          >
        {};
      };
    }
  }
}

#endif


/* build_parser.hpp
CeFXuy7n3+JjlPpfBj9Zmd/7AH6CFj/1cZWe3xlX8zvjan5nj9d6vA5/LGT/lv1TKXwy3tK4GP+ux48X/g1eHJ//lPE1JT44iy93+l/k+OQS/GnH5fjkk/jjjsv6xVJ8ieOyfvEqPsN1OT75mT7/KKc7H0jd4/ibSv2qG75FqV91xzeVeH+b8++Bvy68k1N/rsMnC2/ijA8kvqgiv2L59UNG4IPxcIX1dGWoWL+/AD9VeA4344Mj8UHC921s1w+5EP+T8FtxU77VX1bxX5b3xFe0r7T3p8fr8Hcdl9//JL6Wf8Yc7xGz//Uj+GjhY2P2+XgUv1j4qpiTHwK/UHinDk7972vib7T6MT7V2V5+f+u+Yf6E4rGGqiCteB5/zjm+9N7b/x+/3cRx4m+Lf/XBzxQ+EDfXpy9+hvDZeHH9CXyw4zL+Nocf18jWn2V8+sf4vric39G2sLcf8WbCZ+C7mbfpt/QvCq/YxdYfD8BXi/kdF+DF/q3v9fsr+EG/v/rg2v3VF9furwSu3V/RH0X/l8jv0wzf13E5P7A53kGp/yfwD5T6dS2+3smPI/MjTcAXOC7X17wPv1l4v232/J/ARwlfiBfjc37i/RIqX3+8ABf5dUT+ZJGfQvSPLMdnl3g+zPV7Br9P+Mtz7NG+wbsIf6qR037BDxLertLpP/+Z/nttfjNepXgO76qtn4l30epHv9A/o82vxNX6C67Vn5Ke7VMeT3s84/Es3l/x6K+6J/GztPyH+ESlffMRfq02v32H5/zx3ornPR7/Tc+Pl8QvU8p/JX6R1j77vUpdvzWE55T7rw3+lJYfn+dotVJ/O4X/d5Lr8v4OhdX1+xIeT+JLHJfjk7fhUwKOY532s53fcC8+QfhleDH/QkXp/Xc38fX4OKf/UNb/443CQQ/t98W19l0aj2jPl8ezeDPFc3g7xYNK3eO42v7C1fa5x+s8+096PIWr7XNcfX/hu2jjUx6v93jO43mPN+jOi0L3qMdjHo97PIE3135fz/ZJfHfF0579Zz3b5zzbN3i2j+6ibx/H1euDa/uv8+w/5dk+49m+3rN93rN9sKvn/sK1/cdxbf+1nu2Tnu3Tnu2znu1znu0bPNtHm3ieL1zbfwJXnx/P9inP9hlcfb/h6vODq88Prj4/u3meH1zbvhZvq9UPPJ72eNbjOY83eDzaVPe4x2s9nvR42uNZj+c83uDxaJXucbyV1n/r8aTH0x7Pejzn8QaPR8O6xz1e6/Gkx9Mez3o85/EGj0cjYXV9sBh+vhOfLOdfHIyfhsv4WDN/vQt+ivBVdTb+73C8P14uPja/ezg4QYmf2Yb3V9pfiT3CwbnK9sfgZyvbn4v31OJv8JO1/Lf4QMdl/MrX+N6Oy/iVeDQc7FciPq/S9L/jHYVPqLLxK93xdo7L+WE98L0cl/PDDsNbOy7HTzPNwvz/Sv0GP1+LL8eHK/E9m/EaZX3bLfiJSn72RPNwsX+iutTvjw9xXfaP4Xtpzx+u5UfO4/219nULfftaj9fhF7ku+//w85T+hQZ8D63+1DIcjFbmNzTDL1bmN3TEz3Bcxu/1xPd1Xa6/iav9V7i6vq5n+5zxcvVvz/4bPPsP9tQ9imvxQzFc65+qw5sq45dJfB9t/RC8pVK+erxay1/o2T7aiveDVr/weK3Hk3hUa3/g2vXJ4Nr1yeHa+TXg2vWJtda3T+Da+dV5POXxDK5dn3pcuz45XLs+QRv9/GK4dn1qPdsnce380h7PejyHa9enAdeuT7CXfn3iuHZ+tbh2fVKe7TO4dn71Hs/rzkCjfn1i+Ghl/K0DfrEy/tYRv1Dp387ifZX9L8F7K/t/DO+l7D9ox++rtY/wu5Q=
*/