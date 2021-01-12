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
bn3NcC+PMdQhnBT966wYR2Q9Z2muTge5Nasyvtyfi0qP+oeviLQCC+MT3rS2/ZoBdVeVxSx1p2SDv+7YYFblaVKg4YGvvhNEXZd6T3R6rE8Z+zCvl6qqQozeSc0BfVvUHoDjfWMex7ntRxqIvsp1RVu7OscXULWHpZJC1x2cX82wceDmEuuhuSNoIGHo2XtyfU5KPAbaJEhKu8VjKPTneNv0OF5N/eDrj+BZ1M5+RChkfqjb
*/