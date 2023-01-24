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
X3m8A/YeM0V3s0IcWIs+pWMfZ/XuBsPPcHPsDUQNXyYJVPWBGdx6OgIW50OgVqWFCXjnBb6Qw77kVTFeN5hi14gS/BlXnQ0B5emEJRgSdMLG7LQ+ZiTHk0jVDhWS159tAuMA/CpPYbeaJh4gupxEUFF2g2+QuEuBZPTeAJNBkY1pIHynyx4DuyTBRNN9Y76yXrryFIUFT/5TMBhy42iVdRGNAofYt4kIdBV0zWi2VRUw6ND88/2yUsmbg0AyA1p+PTEExqBvQLXJi3DoSQpC/wqG/opEfQUjX2DO5wXFQ/Ks51kNM53VMGdJ96JYUoZbsgbtfz9n1TZHmIPQA5wlb4VNZi1rE2eFb12b3PSGxpbrNdbwZ8u5xmP6se59zqotLyMRAaemQF95REnHuXoUtftFPipyOSubS0/TvsXbjEkdaILRpTPveXoXCCiT6fVRHXD/7nmC9i+N8zs4TI4x8gZI1q7mC/kMLWE0DL+D9h9qcaorsXrUXpe7jYN0ec/A6CVyFza4uIu7EwzFSB/BxPsWajY6vKGorFq49pfEl4GLYON1BsN2Q5dZuqAHCLPJUcgF0frds5bvy5cYAVwvCr8chtlzyNmD5WV29gweggycfQagYGWtBHU3F4sKK2aTdWty6VD7AT+BoZowl1FIuvHDdMOH/ov+/pCU3D0MieVc9FRhSXTqSBBPNautGnWEsdS4smVtV9b0qIVQ
*/