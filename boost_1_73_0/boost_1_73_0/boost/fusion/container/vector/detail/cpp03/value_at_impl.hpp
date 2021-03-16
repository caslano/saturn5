/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_AT_IMPL_05052005_0232)
#define FUSION_VALUE_AT_IMPL_05052005_0232

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/at.hpp>

namespace boost { namespace fusion
{
    struct vector_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_at_impl;

        template <>
        struct value_at_impl<vector_tag>
        {
            template <typename Sequence, typename N>
            struct apply
            {
                typedef typename mpl::at<typename Sequence::types, N>::type type;
            };
        };
    }
}}

#endif

/* value_at_impl.hpp
F/dT5qTdFJ8XK81VGymoRMfkKcUX5Hoi4S5MyHG7Y/RRtjuU5KwCdNVHyY0OqyIIMezErMamQF4J7srQLHsanZCwo0VbJwI0aQi7wv088EL1XukTMTEqHEoSJbsZBmkIgX3U3FQJw0M7OCryQ24rz7YmFqOL5wsFl83PqzA7As9I1ud/yhXBuhq9yvYJKugMw6g4A4EQBikeO1hVv9PqosWDuw6o2eQeROg7Ij/rpjxnT/48whAP9v2lJJT2Erg=
*/