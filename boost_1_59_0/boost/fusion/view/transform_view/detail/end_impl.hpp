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
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
*/