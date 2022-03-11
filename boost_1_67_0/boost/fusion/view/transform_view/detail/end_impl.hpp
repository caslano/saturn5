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