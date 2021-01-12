/*=============================================================================
    Copyright (c) 2009 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_NVIEW_BEGIN_IMPL_SEP_23_2009_1036PM)
#define BOOST_FUSION_NVIEW_BEGIN_IMPL_SEP_23_2009_1036PM

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>

namespace boost { namespace fusion
{
    struct nview_tag;

    template <typename Sequence, typename Pos>
    struct nview_iterator;

    namespace extension
    {
        template<typename Tag>
        struct begin_impl;

        template<>
        struct begin_impl<nview_tag>
        {
            template<typename Sequence>
            struct apply
            {
                typedef typename Sequence::index_type index_type;

                typedef nview_iterator<Sequence,
                    typename result_of::begin<index_type>::type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Sequence& s)
                {
                    return type(s);
                }
            };
        };
    }

}}

#endif


/* begin_impl.hpp
2mFD+/4lurTllgbj1jSqTkpP07gptLSTlxI0qIPycvtLCxo0iTrStNOaJquIeB94GU1n1dDy/lHTZPXTm8qTl1V0RVqeX1XvdrPzfatv75zdCqssr5zc2jU9OTE9uW9yfHoSy3r11yR+028I6/hVzrvbt9MSpzpja3F93jLyH9+RHyAUOy2ScrT83SIm/STnLS3fxcnDIKtUAtP7H7qEJy334yEo5ImfU+2k53gBfBeR101v
*/