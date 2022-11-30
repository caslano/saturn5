/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_END_IMPL_05062005_0906)
#define FUSION_END_IMPL_05062005_0906

namespace boost { namespace fusion
{
    struct filter_view_tag;

    template <typename Category,  typename First, typename Last, typename Pred>
    struct filter_iterator;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        template <>
        struct end_impl<filter_view_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename Sequence::last_type last_type;
                typedef typename Sequence::pred_type pred_type;
                typedef typename Sequence::category category;
                typedef filter_iterator<category,last_type, last_type, pred_type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& s)
                {
                    return type(s.last());
                }
            };
        };
    }
}}

#endif



/* end_impl.hpp
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
*/