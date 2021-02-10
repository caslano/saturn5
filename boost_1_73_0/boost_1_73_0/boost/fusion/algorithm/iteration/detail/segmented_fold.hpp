/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_FOLD_S_HPP_INCLUDED)
#define BOOST_FUSION_FOLD_S_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/algorithm/iteration/fold_fwd.hpp>
#include <boost/fusion/support/segmented_fold_until.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename Fun>
    struct segmented_fold_fun
    {
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        explicit segmented_fold_fun(Fun const& f)
          : fun(f)
        {}

        Fun const& fun;

        template <typename Sequence, typename State, typename Context>
        struct apply
        {
            typedef typename result_of::fold<Sequence, State, Fun>::type type;
            typedef mpl::true_ continue_type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type call(Sequence& seq, State const& state, Context const&, segmented_fold_fun const& fun)
            {
                return fusion::fold(seq, state, fun.fun);
            }
        };
    };

    // The default implementation of this lives in detail/fold.hpp
    template <typename Sequence, typename State, typename Fun, bool IsSequence, bool IsSegmented>
    struct result_of_fold;

    template <typename Sequence, typename State, typename Fun>
    struct result_of_fold<Sequence, State, Fun, true, true>
    {
        typedef
            typename result_of::segmented_fold_until<
                Sequence,
                State,
                segmented_fold_fun<Fun>
            >::type
        type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type call(Sequence& seq, State& state, Fun& fun)
        {
            return fusion::segmented_fold_until(seq, state, segmented_fold_fun<Fun>(fun));
        }
    };
}}}

#endif

/* segmented_fold.hpp
0iIIijIWa+tiS4JIp2fEgbAiV9bGFJflLv1yyI+/Z3ZJvSQ9NAfURkxxtfOyM888M5vh7RH982/7CYasjv7yZ+H+LfCDZyc0q/Vnmdk/F1gsvpD/heAtnt9h6ph2Ul8WffouqS/Uc1KL1tZb/rxYfIe5W3aS/xyz8O2CP2LFS7byZ7p6rtXd2lLvrE+nL1/+TAM8Tl+GNBKlkgUlVpZLWd+F9DZ3K7+uxdPT0MhfQpKWRDE8UJiulSGjV/ZR1JLwuVCZLI3MSRjKpclqtcSLKsmuJa1UIelsOrsZT85DelyrbN3qedYNmbVuipzW4kFSLTOpHryaStSW9AoaoD9XxkJnY5UuhzAvycp6Y1o17IQojCbxIFQhljAnLK2trcyb4+OsqQuc5DjXmTnOulAM13bz1alu4M1GPJOuLFlNjZEh8f6QNjpXK34iRFismmWhzDrcuQWDZX6sazKyKFp1EFXS+CNIStpohbyTKnivLD+MLg1be1zrzcFGhLVVtGrqEuYQFuzLNQIfUlPmsnb7XSA6K22UXcj/ImU733PSJbyioyihcXJES2GUCen3cXoxvU7p92g+jybpDU1/o2hy0+p7P56MgA0FqzXJp6qWBl7UpDZVoWR+YPxvrfRgmF7Q5n6QicESUUCuT+jo
*/