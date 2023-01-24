/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_END_IMPL_07162005_1028)
#define FUSION_END_IMPL_07162005_1028

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/transform_view/transform_view_fwd.hpp>

namespace boost { namespace fusion
{
    template <typename First, typename F>
    struct transform_view_iterator;

    template <typename First1, typename First2, typename F>
    struct transform_view_iterator2;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        // Unary Version
        template <>
        struct end_impl<transform_view_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename Sequence::last_type last_type;
                typedef typename Sequence::transform_type transform_type;
                typedef transform_view_iterator<last_type, transform_type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& s)
                {
                    return type(s.last(), s.f);
                }
            };
        };

        // Binary Version
        template <>
        struct end_impl<transform_view2_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename Sequence::last1_type last1_type;
                typedef typename Sequence::last2_type last2_type;
                typedef typename Sequence::transform_type transform_type;
                typedef transform_view_iterator2<last1_type, last2_type, transform_type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& s)
                {
                    return type(s.last1(), s.last2(), s.f);
                }
            };
        };
    }
}}

#endif



/* end_impl.hpp
LH8KYqxMZ6+WhvMU9UY6CR/Jln2VfwXHC/1BfbZeFaB9RkUdrXJIjqfRp87WgueZFMeBLyru5NsUZxO/rel5bRsr5XP2OHsQjL1nphhsQ+d6dTivxAmD92HV/lo/d9LZnrNDHogq5Ha3nvmpi0NfuX9mOLKw5JDIfgzSfiA8uQ35emsYNQqe0F2/6AP8ye2IHEAfgP1bFS8tl/VgRjJKeZFPwv3Y5P/t0t70D9rfqQL27Xy+RhOeY2WuMDLp6Gf3729BdwjTeTjd4JyIdfL1qDGQLwPh7EprG+bzXXQmyW/O6ZPoGKmiv8hHFXyTH3iLShkR54d8p81/Si7YeREyD9f1wE/MQVV1VXbK8ZutWhunD0LsbRRQ3o8NFqcLerWp8J78DO5nZxY79UG4YsiHgZ656oMuQMCZP7tRxgz7a/vGiUK/wIU3y1OENSNfj1wJmQVzybtf1/lJWytnqmGQ4hRdz3MnD5HfdgeF/dNN61ElcfYDPOGobE550S/mL56OCLcJ8z838vSp0O/SDGSE6JLr5MPk8m2yUkaFjeF+dmb13Q6LdkuZ3VUWkElK5E5y+WrZSyxEGydedNbJQYM7+0ZGbZDPBm4gX48Ix3wUYB7MB1rJvg1hvkiqqjB8cJ7Ky/56klwbnrhn1DP9rm1c8YmgudZ0F8sAbbHcPS85PbKwIME2vT/jQWDfQXsvysAx95FY+FyPXBdTrcko
*/