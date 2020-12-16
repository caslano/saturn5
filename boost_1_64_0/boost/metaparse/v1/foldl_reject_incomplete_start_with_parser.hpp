#ifndef BOOST_METAPARSE_V1_FOLDL_REJECT_INCOMPLETE_START_WITH_PARSER_HPP
#define BOOST_METAPARSE_V1_FOLDL_REJECT_INCOMPLETE_START_WITH_PARSER_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/foldl_reject_incomplete.hpp>
#include <boost/metaparse/v1/get_remaining.hpp>
#include <boost/metaparse/v1/get_position.hpp>
#include <boost/metaparse/v1/get_result.hpp>
#include <boost/metaparse/v1/is_error.hpp>

#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class StateP, class ForwardOp>
      class foldl_reject_incomplete_start_with_parser
      {
      private:
        template <class Res>
        struct apply_unchecked :
          foldl_reject_incomplete<
            P,
            typename get_result<Res>::type,
            ForwardOp
          >::template apply<
            typename get_remaining<Res>::type,
            typename get_position<Res>::type
          >
        {};
      public:
        typedef foldl_reject_incomplete_start_with_parser type;

        template <class S, class Pos>
        struct apply :
          boost::mpl::eval_if<
            typename is_error<typename StateP::template apply<S, Pos> >::type,
            typename StateP::template apply<S, Pos>,
            apply_unchecked<typename StateP::template apply<S, Pos> >
          >
        {};
      };
    }
  }
}

#endif


/* foldl_reject_incomplete_start_with_parser.hpp
1f7kuDr+EFwdf5Tn+HlcXh+Plz1e9Xjsfu1Jj6c9nvV4Hpfvh8fLHq96PPYLz+/3eBqX5YPH8x4verzs8arHY79kfE6tn4pPFusr9sVHqfhQvLPqv/Z4BVfr31bxjsJjD9A+EPW3JC7vLy7j5/BewvP4Bqd+afcfXYy/wr+7ON5vUlT/uwd/3vg5eHi2Lfgk409Oin7tt/h5xrtPduYXLie+SdR/q/gnTY33x/8C/8Bx+3zc+GAYv4nXmV+ex69x3M4vvw+faHyek//MQ/r5yHo8h6vnr4Cr56uE91b9s3hK7a9XZH6W+r7gp4v+pRIu3x+PBysYnxDx4U34YDE/phU+UMyPSeM7q/WLcRW/lMfl/pe4vD+43P8W76TaTyt1+ZnAfyg8havrn/F4Du+ofj9eEPdvCb7Iddv/jN8myu/X8Alifm32YeZHNzWefzoTPw/f1vF+/aL+vxw+wfg5eNj/NxvPGH8SD/v/5uCnG+++uzO/91Fd/mc9nvd4EZf1M49XPR57jPh4Mb+4G36N6n/GVfxFBZfxCdrpoPXEp+AyPsWTPulJn/J42nP8jMezHs95zp/3eMFz/KInfQlX5WPZ4xVcfh+e0J7AVfmUwtX7k/F4DlfvR8HjJVxeH/zxWvmVcHz7mr+PL8C3dXzsedHV2PdJxmeML8TD3ByNDzT+ER7+2mH4/sbT5zu1hVXR+GiXOvWvtvhhjtv3fx98BzE+ncFnqPVl8emifAl+rcd3m/Bhon28DZ4S7eMMvqfaXxdX97eIq+e37PEqLtsXT+vzJ3B1/JTHM/ihan9KfIhon5Vw+fzjHYVX8S/F+Tfjnztu5zfu/gzxYY7b+Y174E8YX3FO9FczvsJ453Oj9yP5LPM7VfwNfqR4fo/Ad1XjO3j3JjH+i+/ouD3+07i7P6Zt/zyDb3Tctn+exV933K6vFazW5WfC4ylclZ8Zj+fwsWL+32x8jJj/Nxc/SayfczV+gpj/dw0+Usz/C37jqZ/gnYUnPelTuKx/4Kr+lfEcP+s5fs7jeY8XPOcvevJf8qQve85f8XgVV+PzwXM6fQz/ZZ32Sbz290543qyP8lLPKD4qgf/M+Da9ovHr3vg1xq86N8rtRXgX4++75dcanm8nf3Z/6UH4YXXaT+H69YPxoaL9dBCeEu2ng/GDRfupspb4FNF/sc3z9H+J+YHt8R5qfwJctn/xqY7b+UEFfIQTP2D3N4utY/6G63Z9TPwQtf8aLvsfcVk/eIH4B/F9iuOLRf2oJz5PzF/phd9o/M1k9PxV8LD/bPt68Xf4Wa7b/Zde5Plw3d4/PKbuH36tWB9mNn61WB9mLn5FnfVhmsLvAz5LrA+zFj/A+F8nOu/fSzp/zbjK3/64yt8BuMrfNFzlr4JfINZP24BPctzGz72Lny365zr+LhYcJNavyeLq+kzB1fWZhqvrcwmurs9juLo+iZc99Rt8tOpfxU8R9cNj8WGiflj0HH+F5/jPeI6feMUc364fhO9W++/QFw939nfEVf7m4Sp/i3CVv+D3un6YwO9T8wfwZeL8w/CZ4vxVXJXPQTlcv6T++sbb4NuL71cSV9+nNK7K/6wnfd7jRVz9vpLn/BVcvR/Bq9oTuLq/KY9ncDn/C5fjM/h3QePxp6vwr8T9K/3BMz6Cq+sX/FGnT3g8hav43ywu51ficn4QLvs/8I7Cy7haf76Cy+fnT7TP63ifmrfH7zHrnxEfyjFr+xvgS40X8R3C+GV8ofGA979L7a8++NXGJ+At309c5v/PnvILf1yVX/ijovw6AL9RtP8H4j//npv9iV/zxCfgPYVn8GmifT4ev0i0zyfgU8X6PGfgWdft+ka4Wt82+Is=
*/