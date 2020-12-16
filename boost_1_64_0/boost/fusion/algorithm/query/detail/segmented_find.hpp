/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTED_FIND_HPP_INCLUDED)
#define BOOST_FUSION_SEGMENTED_FIND_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/fusion/algorithm/query/find_fwd.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/support/segmented_fold_until.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename T>
    struct segmented_find_fun
    {
        template <typename Sequence, typename State, typename Context>
        struct apply
        {
            typedef
                typename result_of::find<Sequence, T>::type
            iterator_type;

            typedef
                typename result_of::equal_to<
                    iterator_type
                  , typename result_of::end<Sequence>::type
                >::type
            continue_type;

            typedef
                typename mpl::eval_if<
                    continue_type
                  , mpl::identity<State>
                  , result_of::make_segmented_iterator<
                        iterator_type
                      , Context
                    >
                >::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type call(Sequence& seq, State const&state, Context const& context, segmented_find_fun)
            {
                return call_impl(seq, state, context, continue_type());
            }

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type call_impl(Sequence&, State const&state, Context const&, mpl::true_)
            {
                return state;
            }

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type call_impl(Sequence& seq, State const&, Context const& context, mpl::false_)
            {
                return fusion::make_segmented_iterator(fusion::find<T>(seq), context);
            }
        };
    };

    template <typename Sequence, typename T>
    struct result_of_segmented_find
    {
        struct filter
        {
            typedef
                typename result_of::segmented_fold_until<
                    Sequence
                  , typename result_of::end<Sequence>::type
                  , segmented_find_fun<T>
                >::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type call(Sequence& seq)
            {
                return fusion::segmented_fold_until(
                    seq
                  , fusion::end(seq)
                  , detail::segmented_find_fun<T>());
            }
        };

        typedef typename filter::type type;
    };
}}}

#endif

/* segmented_find.hpp
+Hd4keLGV8NP4Ab4KbxdcXcbYBx27jMA/XPdNXYGe9rnuivOt/Hvi2AXmAe7wXzYAxZY0mlWOj0c0jlf6Xxe6eQqneWwO1xhxuXVuBboiuTa4sgWKR2P0imGWjMRGJvi2oWumZiqejQNjofT4VQ4Ay6GM+FtcA7cAbPgg3AufA7Og7+E83W9smEzXAB/BxfCeOzmwNPhYpgCl5hxujXupDqXa4vTPVJxikfBwXA0nA/Hqt6NV73LgOVwgurZxED6HTSOpPGlXGSI30/f8V3Vm0fg2fD7qj8/gBPgY3A2fBwuVXz+AvgELId7VZ+ehFcq3vD18Gl4M/wx/Bb8Cbwf7oePwGfgHvhT+Cv4M/gGfBa+DZ+HH8Am+A/4c9gbn38Bh8KDcBj8JZwNX4Rr4GvwCvg6vAq+AW+CzbARvgkPwrfgi/Bt+Bp8B74Hfwu7Uka/g5Pg7+F0+B7MhofgQvi+Gcdd41DwCvv1U9znVHgznA5vgfPgrXAh3K5yvE3leDvcBO+wpH9Y6V/pkP4WXb9r4Ex4LcyG18Ec+DXohdfDS2EdvBzeYEm/fpp7+juU/k6l36D071H69yr9XUp/t9K/z58+52tMAZ6j+y/Rl2//kad5Wh6YAYvhuXC17JTAPFgK18E1cCNcq/pWBq+DFXAr9MIHYCV8HFbBF+AXtZaplv99Aq+AA/HnS/BsSFpqr9T/h+kO7VW61uaMhD3gKNgbjobD4BgzHfXn4VKndk/5zlW+l8Op8AK4CK60zHOrVTrnOcxzG8+fe8KJcCicBEfCyUp3ispxqtLbghxWeg8pva5wU6BTpf2f5sABMAuOgHPhWDgPToHzVY+zYS5coPq7EF4DF8E7YQ7cCc+D98DFageWWPKnPi15D83fGbp/ku3xkuRHD3g+7Kn08EH9SvqbSq8zLLOskesL++v5OABOgwPhfDgIFsPBqk9D4HY4FH4bng33wmHwOZim+jXckp/8Oe2ztuvPkLyrL4cPqpMdkDOU3lzzPPWz4NhWzsvXeX1bOa8uK7zdV9tz3mRszmRszuT/2ZzJo50vubuBGORIx3uIj43kIpuRBqQJ+QRJvZeY38gGZAdyADmMnLGLfQ6QMmQr8hhyEPkEGbAbnd2xOZixI3bEjtgRO2JH7IgdsSN2xI7/r+P4zP8vbLf1/yNb4v/xjUlxiZAT9d3kgQz+M7Jl3sWMxdnGtIv0PKZd4DOL1asiniO8wTdvtLCyLC54XlW9g91G7KY62TWmzSzzFjET/ajtppzgbDfTyS7TwdrL7p4TdLJsT0MexG6+k92q0tXlBdU1lZ7I52KbdvVbAhza3fjNS2r+31KM3/gPvxWUrQ6eb5YWH1ouD+Hf3lD/iH9w/qL5s2ZG7Ntr3UzfgmzWO9h8GJvNDjZLq6pqPJVtK4+g698x1OZ3jfo+KtSmWe2iuA7k1dFunYvdVAe7VLujthuYV9VZc/EH+s7FHvLBOOp7qN2WapfH3K4o5jBS1o7Xt1a2B8h2H+QR8uy1244iloZsul7fTie1xMdMRiYge7BZb7NJYzrScoFbtat565RzUBwRzfmqXhdnv94ufhx28oMLfqz8SDk51I/vG+3d6BA/dI8Zk+vb7odbXJV6+VGMJCEFyGMZlJODH6oLrc7rU4xY0wetE3CMqzIu0M510nxvnXc5ksn9kDDG5kdFZXUkcwuDfSg05yLP8dXPSvtcwSBfdsuXm+RLnXzZa/OlxptX6Slu3RfNa7O2BXb7QW3DgFNC26THM4yPeC321dZH/fzvqnZprsohaN2dg90fGveom11mb1ew+xCGZ0byLA62vSHIdi/N9z9Ntk+V7b1utpl8WFpQtrBm3SpPZQQ=
*/