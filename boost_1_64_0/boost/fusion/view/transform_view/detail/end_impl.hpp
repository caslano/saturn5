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
1H6kRhKNYXtn+lMxIiEZGi4wT31oKx8DTcdtgPCuqNJLqrmStpeJ/RM1puikOOKs1vYo8L8PhWXq3eJTuVP8C+z17jPufBfD2DHxNouRLFrUd8fGBypRrSgsdaAz4TjY0RG8isbAn6GHn81eutxkLNpJg5Fh2ueTuFrA17t5b0j4ERbI9jvU2uwc8KiIfWyH+GLtctbbKDEATcIx//frVs5PsDP4FR/MQQe3T7IuLRss2NTsEQsDOBfY7S/6Qi1spiOCSVGWCDmSYsBYZ64TiWe5k5S4CF46ZZ0gA0MN822gzPhzKs7LrHR/HG2HicdEaJ1+WtGIgjApnFgW+NL0GLFD+SxfqSsyB7LuApk/o3h7gY48XNMr9XXaOECpyT3vXMo6TA875EwyOeRQCaHJJMI1hiu9EBS0awDLDqSv5Ubk0cqcLYx3Ud3+5QiCeLp04bSoR5MkhmFhVOAIZgvCeX0b7xf9L2F2okC7NRNBPKZwoyi2V6Ugm+F540gx7X07sftbvJs2vSkamYtVZ3bl2Jx7jTvSlrIUKWfD3sU8QA2/SC4c/7V1kpMijg==
*/