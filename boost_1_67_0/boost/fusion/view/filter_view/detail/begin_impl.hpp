/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BEGIN_IMPL_05062005_0903)
#define FUSION_BEGIN_IMPL_05062005_0903

namespace boost { namespace fusion
{
    struct filter_view_tag;

    template <typename Category, typename First, typename Last, typename Pred>
    struct filter_iterator;

    namespace extension
    {
        template <typename Tag>
        struct begin_impl;

        template <>
        struct begin_impl<filter_view_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename Sequence::first_type first_type;
                typedef typename Sequence::last_type last_type;
                typedef typename Sequence::pred_type pred_type;
                typedef typename Sequence::category category;
                typedef filter_iterator<category, first_type, last_type, pred_type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& s)
                {
                    return type(s.first());
                }
            };
        };
    }
}}

#endif



/* begin_impl.hpp
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
*/