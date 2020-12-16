/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTED_FIND_IF_HPP_INCLUDED)
#define BOOST_FUSION_SEGMENTED_FIND_IF_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/fusion/algorithm/query/find_if_fwd.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/support/segmented_fold_until.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename Pred>
    struct segmented_find_if_fun
    {
        template <typename Sequence, typename State, typename Context>
        struct apply
        {
            typedef
                typename result_of::find_if<Sequence, Pred>::type
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
            static type call(Sequence& seq, State const&state, Context const& context, segmented_find_if_fun)
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
                return fusion::make_segmented_iterator(fusion::find_if<Pred>(seq), context);
            }
        };
    };

    template <typename Sequence, typename Pred>
    struct result_of_segmented_find_if
    {
        struct filter
        {
            typedef
                typename result_of::segmented_fold_until<
                    Sequence
                  , typename result_of::end<Sequence>::type
                  , segmented_find_if_fun<Pred>
                >::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type call(Sequence& seq)
            {
                return fusion::segmented_fold_until(
                    seq
                  , fusion::end(seq)
                  , segmented_find_if_fun<Pred>());
            }
        };

        typedef typename filter::type type;
    };
}}}

#endif

/* segmented_find_if.hpp
67HC2d4r2zfqXvwashfbTQ62uQ9s2W79+qsuqu5tMOe4TrC0DZqrqt9Ky+1rIks053+pfFwkH+vGOfoYVDzR3C8BH5OCfPSnFvAzNdRPsz05LD8nys+xyFOGYf98sNJRRRRfnnkLVa+qivx5Zrl/zHZtjX/+qNf0Q3M2izqHzhXdxD2cM96cs2ktMiaKRj5P9NJxmq9ps/mSg819xn3rbNNoyiK2+Ztk57mpRV1C56Zejn+NzjaNialRzR++dFxsbmpsbupnOzc1ebLx+zkDk3p2uX/tddd9/Luxg26ZG9+2uam4qj40zzmHuYgVej32wq7wYute+GH0lkpvmfTOt+hlhtFbLr0V0rvAOhdFetMd5tZcynmfg5fBZLgJDoFfgOnwcjgNftHix94wflTLjxr5sd6i1xxGb4301kqvDJrlPMpdL096+dIrsJZzGL0i6XmkV2wtZ+kNdND7kubuXAlT4WaLnvo9nBuqt0h6ObAPPK9ljhh9F/e41AN1XQZJbzDsD4fACXCoJZ3DYdJJUzrDlc4IpXOO0kk300FGu6fTW+n0UTqpSqev0ukHzTmtSqfYOqcwgthsw2EyzIYpMAf2gAWWOV75iN7puRahc8NHq7wn6DpNhFlwEsyDk+FaOAWug1PhRngu9PUZLPfPXtm5yeH+mSE7s+EUOEf3yzxYBefDOphtqSe1Y93r5f2qlw+oXjZa9OrD6H1Felukd7X1fpXeaQ56t0nvdniqZc6pF2mS3o3SOw0WSe9a1YPrVQ/qVA9ugCPh11UeN+o6boVL4U1wFfwG9MKb4dfgLdZ6M05zJh3qzV2y+23ZvVt2d6reNKge3gPnwXvhIrhL6WfE6R0STFT6HWGa0n9I6T+sdL8Lx8JHLHPicsa7z5173XJebYTnNeq8oS7nNUc4xy42vy42vy42v671+XU77o5ujl2v++LjZiJlyFbkMaQZ6Xh/fFwashSpRXYgB5AjSK8HmFuHrEQ2IQ3IS0inRmIbIkXIFmQ30tQYm2cXO2JH7Igd/4nH8fn+n7feu+7ov//3iOvcrdL47nzkxDietJ7igpoyAioUrCrz+P5Wzd9YAEcfwFtQWbBOf4nzzRv457A4cwxys77fz0F6aexgPbr1Z/reVYnMkLeqylNQWVjiTyKSseHA94t7fGOtbBNgiY+3y/fbqoIqjz0+nm9INXiM/4SWb03J+ta0wTCc1DKGff6sxXNnL8/LmbZ42gIjtk96nreirLRwYzSxW/x++spJ8ecC8S3MtIL3OZBf9yGJWve2EaXacH75iy/KsvP5pLF+87fqdV6Nq4eOrZo+lsRrXF3XdSxymVFfkt19HJlXUlFV3bZy01gv8SzM74bmPoj0r/QbMS1s1/gT+TkUOQXxjUmRUKObn4Vl1Ma84rKC1VVxEXzH0Xf1EF8NpX4+v3xJBX1rre6oBHR9pyBP8pfDbj4VV3o8baxvVrtx+s6+AumGLEMupyxyUlzsGh+2orgfA3UF2OoP956t/mxyiDf4RYzsDeeL8ck5irkOu2zlYNaJE0O/K9Ziuzmsba/HUxmd/Xtc7G86KTTvVxgF3N3dfl5BTXUJ+4Ku95RFbN+Wf7PsP5L9TNmehFzDQEFqGPv+iFWR1YVw1736ZOe8e8PZLvJ4q0siL3e3fB92sP0lbNeFs+27fSO37XbNvZ1CbV9ptEPhbJeWl0Rr3y3vhzqF1vnN2G8KZ5/XAk8UbaCb7QP6jl8Y73/OXgSvwvZhN9vkmw+8Ec2rCH6eFXmqqu3vAlWVhYqvNcRsk1sKtkdQfa2uyKtgPsglGCfjxt8GWP+m1yD73Jkyfa9fr/a8HPkKTqf3dslfWUXF2hqvL28=
*/