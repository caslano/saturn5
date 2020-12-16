/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_VALUE_AT_IMPL_31122005_1621)
#define BOOST_FUSION_VALUE_AT_IMPL_31122005_1621

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/at.hpp>

namespace boost { namespace fusion 
{
    struct mpl_sequence_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_at_impl;

        template <>
        struct value_at_impl<mpl_sequence_tag>
        {
            template <typename Sequence, typename N>
            struct apply : mpl::at<Sequence, N> {};
        };
    }
}}

#endif

/* value_at_impl.hpp
Wdg1MHPO44VnDhlnKw10PvbphhAv4eOfrhpy4qNDSK5tvX62mzFOWWz7zm3rmtsZLtnjyQ9xj92dsYUwPW43qb1/YHxfX6+rHr7HlD/5fOuj/Qx0TLBbu7U/zWd34PTFhc7wjKed3dcVD8KX9mk6ff5AYb6NNGP+7CkDnrvZxrEgbn9qb8f8brst7kLtE3EtntkxHk8jDuEnu586v3ug64TFAwZ3ts01dk57X1gS4r2TnBfWDolXdlLXjL72vsXh87tP6m3vSD6NCeELf/zZNeb/+XXHL4pHMyTeXY/2Gi5+1E/s6uuP7yce12WPVk6zIRQUfrNHMhSr9cT4wrY/ndkx/U9M5pimM+Z39i3OdfY9uiF6Ztpf822wvnBAfM7Y+X19XhnJlprYEfbYXbWta+b5cTM7dNTuJ3X3zmjvPrVzbm/f4ni3zTc3xzrXI7Ogq6+3Z67zz2rv62qfEY/viCHj497HWgK7uXuKvRhvz3DN7pM62xd0PqV+3u4Te5Tau7te9+dfHNPTMaXQ1fPYQPZ5bKc9pYODn7yLZLO6ibByj7bu/jHd3b0zQ3hf7Bqd1d49vzOsij9NefzTe+NP8RKGh+Pnx6bv7+3utER21blNk/WWlKxm5x9/tjK/bpryZ2dMHzJ+UdfjcxlubJo80D22vTAw/4k3cLglrk3q7T1/fuHE+T2P3oHpsnVCLf7KWV19A/Pbu8/sWWjNfX/Y48yeOY9ulI7xi2Z2FuLmFjZevNAVPxN/9cvDn7q24S17tHX2ze3q8YA+Xgpv2H1if/Kht+9Ez66x5mx/p4WFvvboczO7s+/x2rfifm0CwyzEr5izQ/sfrd+USb41TTBJ4ZTxk08bP+nxt8zoMLdz7syCu3xlbP2d9lU2eLXPnONOjg/xV+cWQhgT1+JieEVcm9u7oNMbcuHMfuUQTggQWzguxGfMYXuF6dPHTu8vdM6MX57TH5sN9UPU+wc6pg94IUyPv7tO73jsW8n0bkMM4ayxk888rW3iqeOPGJkZFw8yjNl9+sL2fu9PX905ZHp3X++AkT/EmB4/0NTV39E1u2sgvLVp1sL4BWO8e+hzoHd+dzg0tvgewlGx9cR68O7TBzyBR48Mv91telzsiqsf1s/8QsEg17D+Qrvv6pP3GOjt7l2olonP7u70XDzSNM+SDIRXqriGsbwwNt8g/G1CbPF8hpe7z/aZfQPTu3pnTJ9lR4U3NM3yvuu3O13D29J3wKZZM+OXiz+9N83q7J0Vwkx87GtzmmbN6p4ff3c9v2nW7E7n7TFk+qwuI+gNFzf5acVavqVpVn9n5/nh0qZZA51m6kdhurM1CLe5r86BufHeD+vczaLHJihc1qSrzp4FIdz76J13zC+ES+LetPte09z2x57Ln+tnkeavfWytunqnz+y15j3TF/QvLHhTDxjprKd+LfnSkD362rvc1L27tw/0doUw8rF5NynTnnLOrOScpj3cUHzxMGMPu0pjY7Xus3oLpvyCJsTD454enZ/p/UYwZPrsuck6vtc9tnf7QSGMeHQF+gs9YVRssYQD9zAZM+Yb9SfC9JlzTIs1M5v93plHj+w66sjwM7PxxIfw/D36/SjTbmUbj85SvD0810+94/6Z7T16zcdj1saYYrNGIWyIV2COFYuf+unxPv5ccGLPrK7ZnuTpPe1uY+H09r7Z1mLeEE9C8qg+8aXOJ9/h/hbqT1r09sTLM33Aez1e392mP/4D6eNfsd8eewf/NF7JzpnzB/7spBuNxd70wlELGx7/NH3efN9fnKIY1qgyNvDY1V1gbpj/pE/vDCfvQR57c4X5+pjhZ9eO+KkNg8fg8b983PTs+O+injzGnRd/Hjw=
*/