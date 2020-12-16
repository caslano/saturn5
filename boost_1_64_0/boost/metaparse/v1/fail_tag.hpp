#ifndef BOOST_METAPARSE_V1_FAIL_TAG_HPP
#define BOOST_METAPARSE_V1_FAIL_TAG_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <boost/metaparse/v1/fwd/get_message.hpp>
#include <boost/metaparse/v1/fwd/get_position.hpp>

#include <iostream>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      struct fail_tag { typedef fail_tag type; };

      template <>
      struct get_message_impl<fail_tag>
      {
        template <class A>
        struct apply { typedef typename A::message type; };
      };

      template <>
      struct get_position_impl<fail_tag>
      {
        template <class A>
        struct apply : A::source_position {};
      };
    }
  }
}

#endif



/* fail_tag.hpp
OG7H727Bd3Hcjt/VDaX+7Vw/W/+biLd23M4vnoZvhVcan7oPfziI3cbfP4ovcdzG3+eGJYMRjtv+zaX4cMdt/+b9+M8dt/2bD+H7OG7rJw/je7tu5z/vz/hOi9htfrcu+HFVdnw6zu/WFT/WeA6P8rt1w482HnSN87v1wn+BVxqfDofTvy3GH9vhp7pu2z/4r8T4fCMu15/yeBO+jfA8foxo36/Cx4r225v4KNF+Sx+g938QrvZ/MK72n8NV/9eDuOr/WonvL/afGqGvXy0u248ez+Cy/w5X5Z+Kq/I34buq+T94bzW/8kBP/yyurk/Ks30trvoXM7jqv6/HVf95I6767xfiqv8+7yl/QR+fG1z3v6c8nvZ4HR6q8Vlc9d/ncPn+8Hje4wW8rfCi3p4XgPbQ4ymP1+JJ4Rl8gno+8aNU/zo+QjyfefxYsf9V+Dix/0/wtHr/HqLLfxCuyn80rsrfhKvxlSKuzu9bXJ3f1iP1+dXhav9TcbX/mZ7953F1/VbhR6nfB1fXL3Oo5/7C5f2Fy/sL76B+H1y2D0dRvw4qj6+0woeI9vnW+CDRPt8GrxXt8wzesYV9f9Fsjdp3+CdVPOdg5LNupA+idPwZ+EfGH8O3Lx3tIvxl4+1ucuYf4/sZPw+P/iqOoX2lxkfwwWp8BN9dPb+HMT7hxEfa/p1GfH2Z+KwdSr4YL+AdYye/fZxfYgn+vvHd9o/z7yzF3zZ+Hh7FJyzDX3Pcrl8VZnT7OIWr+6/Ws33as33Gs32dZ/usZ/t6z/YNnu0bPZ7z7L/J43n8cxGfuQr/SMRnvol/KNY3fgd/V8RnBuN4P6vri/9MnR/+muN2/YYX8JVlxt9aR/U3/EnjOTwq/yr8EeODr4/L3/UIxreMX40395/jPwWV+x/ewYtB5fzP7+JfBpXzP7+Hrwsq539+H/88qJz/OTwqGeTL9D/URM8XfiseVsW+3Q1x+2sg3mj8UDw62un4MOM34c3rH+Czgi29xY1O/8gxjI+UWf/n56XyXYbnAvYWxv7QtbyjS3u7Hv+z8e/xqP/hBvxW44ddF7+/FuA3GV+GR+VrHJ8MNpb5fbuUyrcMX8U/uzo+uVv8fl+Ov2L8Vjz66w38ZuNf49H1W4XfaPzo7k58+HH0T4j8QqvxMSK/0Cf4CBGfthYfJvILrcP3E/FpmQlcPzG/YAL+aWD7D531C/GPHbfPxwn4Gsft83Ei/r7j9vloOD4ZnCG+3/PxrPh+X4OfLL7f9+MHGj/6Wmf9gxOSzflPwzL5J2rwFxy3+Sd64yvLvJ9blo62G75Crb9wIv17In6mBv+5iJ/pje8j8qf3wfcW+dOPx6uMDxzh5C85Sccv5PG2wgv4L1X/OH6yyv9Xlwxq1PxzvIeaf44PUP0PeD+VvxofIuIPVuODRPxB7UR9/dJ4G+EZXI3vZj37r8dl/Qj/t4hvn4//KNbfvgbfKNbfXowXHLf94y/hjztu+8fzk5LBXlUi/hMf4riNP/gQ7+m4jT/YZzLzf0T+o3H4FcYX483fzyk8vyL/xlR8P9G/14S78W+2frgCryrz/Ef1q2dxrn/F+LkX8KJo34XTksFZIj9lF3wqbr+v0fehKz7Z+K14i6h/H59o/Gs8+j50x0/CK31fs7+i/eacv21fzcJ74R0d7351/H29CO9k/AQ8+usW/KtgS78Xb14/DC8ab3eN0/78taf9fiqu+s9wOb7r8VqPpz3Hz0Reaf62Z/us5/j1Hm/A1fyJPP6AiM94Fb9fxB99g18m4o+aTtP7X4Gr/X+Eq/3nTk/K9eGLeB+1fst0+kfV74ur/dfjtWX6J/qU/Aa8Dd4pduJL4vVfFuCtjC/Bt40=
*/