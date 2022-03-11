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
+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
*/