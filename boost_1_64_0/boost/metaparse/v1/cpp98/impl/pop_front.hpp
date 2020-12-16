#ifndef BOOST_METAPARSE_V1_CPP98_IMPL_POP_FRONT_HPP
#define BOOST_METAPARSE_V1_CPP98_IMPL_POP_FRONT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp98/fwd/string.hpp>

#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class S>
        struct pop_front;

        #ifdef BOOST_METAPARSE_POP_FRONT
        #  error BOOST_METAPARSE_POP_FRONT already defined
        #endif
        #define BOOST_METAPARSE_POP_FRONT(z, n, unused) \
          BOOST_PP_COMMA_IF(BOOST_PP_DEC(n)) BOOST_PP_CAT(C, n)

        template < \
          BOOST_PP_ENUM_PARAMS(BOOST_METAPARSE_LIMIT_STRING_SIZE, int C) \
        >
        struct
          pop_front<
            string<BOOST_PP_ENUM_PARAMS(BOOST_METAPARSE_LIMIT_STRING_SIZE, C)>
          > :
          string<
            BOOST_PP_REPEAT_FROM_TO(
              1,
              BOOST_METAPARSE_LIMIT_STRING_SIZE,
              BOOST_METAPARSE_POP_FRONT,
              ~
            ),
            BOOST_NO_CHAR
          >
        {};

        #undef BOOST_METAPARSE_POP_FRONT
      }
    }
  }
}

#endif


/* pop_front.hpp
qJzc5pvn/t0SlBQc4Vfi9jfozw/kEjIJ8rCJKvNe0dHASYLEvgyx0Me/aJwaH5hxLnYxMJsHdi3mx8EanNd+sw4Vj/2HvOsAj+sowhIBAgmkGHc7tuJekG2dSxxCkyXZFrZlx5KTGATH6e4kXSzdHXeSrYReA6GX0DuB0CEEQigJoYXQW+i9hA4BQg0E+PftvDezu3PyPcH30b4vkpWd2dnZ2d3Z2dl5s7YNsBGv2AnnTd3Ll/l38IA1vl9P5PeSoP/he5mvs23TDTvfrst5eZnah9DHsij4vo7Pr+G31uF9/8YA7gTmyG8nwlg4Miilb/MVS4Pv+QiLz1oxzbss1Wh22C9JUutsnPXVt9rXztX20KvsOkM+0oFD/XapOXvcOx14+K73s2aR3vDssy/aep1dXYcOdnbZvD0xzZtcWBDf91UL39e/K9u7L8ox5PL0tQDujuUdZunfRPtnlV/63/qgldgu+g3tm5cA73DqMTArWvO3bJVjwPYm2kKcla5T/fz9bPwl/f1zorvhfgl0N49Jy/JoLVHIixtT0OrAwrfdT3TglBfEixWuj+YyW7exjlu83F+7oY18RoCj27ZLlvvz0LXZrxT7ChauND+SthYuZxwssgAviRcGHtknbNVhLDY0RwcbDr8jFNJjKzOW34qY3rmujbiS2wm+4VvFMOfdobUoN/sz0cONC8eF/GWZy7eZLeQ4sQKQ7wwwz7QJ4tp4EmperJ/1AgcKi7Z6HpN2hsdBJcifyGPit0OOQefbuYUKnpnh0ue0DTAbAg89zetF1wEQltTT21FXxasnnj+22YErNjTnnbn7EYwya1JWTfc8snaZUz/Qe13L/T3TvSfo9uG8UBOcHuD4esT//uA+wIGcHSKY447t0SvXu5f3YY+Eed957ee5LE027ZtiOFR5rh9Y7th7jmy/79mCdSaczKNvhzg0HxGqL/baLyt44/WR2DhM2vxGiEcWCt+Jb1zu6hz40AYwCbPHShOjmMzFfMn2fTqaZtY6sTfLnb3RkcOb3X2TeDLapj4tzjjcriWspelx8rVKndfP5xVec3kEF+awwmVMmIKHLANF8v1P23djcsv9+LuafOq5pG/nLnG+da/anKUmEorn18HltBd6+X0HknJQ9Xz558Ww5JodT23DCSp5u8DBCWMuOmlN+evOf9vvVtIBoOLZ/YxzONJ1LAeMMBTihBPD/yDgwGag416Y/3QQcD5Turb51e5eyUpZ6KKHOPIiDsin8FDAbn0FvicB3gNT20bROlPs04vnarn/CsG+bwn48QgPYv3hITHO8HLHhuJwJtHvI1b2tJ3jQSgvbuyb86J2ELbHTThvCy73bVMd71xLRz4vrfJcjfjhtco4zHPNtoltk8HNvpVmxwV7e8NzwxPnpn2zjGk2GutLVDv4ye7eweobfWnGT2/b1e5vLp2rvaU9gt87+rJD5cyoE9N2meWD3XNCrHHd2Qtt7CaCxTJj5ZYU/Gn3CM+cm/YbBEsL63JYO2c8Wz3rvcTOJWQc2UkfFxjzj/XCKwF3Yno4KzT4DWmUytj7xbe7d3PtYn/P4ByMFs/Q4DAdsT+dEtIhFKZxBXD6DIVoqpSjaLUsdHqG4KdpNMxdP2/MJu9JCUQ5j9485qsuLpPwXHpJvk95gkIbuDRhxffywOvp29Xb1xPnSOO5V54dw6yzMYlf5zqChRaO4VFs+PECw98qxgcwc51M+7DOO3CIb+7f7LB/iXdmSIzBS7VxFLp7bkiHXGkWc53fpxAPQ+SeOV7ut4ndX+rV+Y3bBCbPsb+GcrRX76nWnwnA1dbfG531l8QU09lMumg93znuwKvBnmz23BNWoD7wdt0Rd8I=
*/