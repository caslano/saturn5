/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BEGIN_IMPL_07162005_1031)
#define FUSION_BEGIN_IMPL_07162005_1031

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
        struct begin_impl;

        // Unary Version
        template <>
        struct begin_impl<transform_view_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename Sequence::first_type first_type;
                typedef typename Sequence::transform_type transform_type;
                typedef transform_view_iterator<first_type, transform_type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& s)
                {
                    return type(s.first(), s.f);
                }
            };
        };

        // Binary Version
        template <>
        struct begin_impl<transform_view2_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename Sequence::first1_type first1_type;
                typedef typename Sequence::first2_type first2_type;
                typedef typename Sequence::transform_type transform_type;
                typedef transform_view_iterator2<first1_type, first2_type, transform_type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& s)
                {
                    return type(s.first1(), s.first2(), s.f);
                }
            };
        };
    }
}}

#endif



/* begin_impl.hpp
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
*/