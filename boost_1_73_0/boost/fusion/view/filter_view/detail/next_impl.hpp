/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2018 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_NEXT_IMPL_06052005_0900)
#define FUSION_NEXT_IMPL_06052005_0900

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>

namespace boost { namespace fusion
{
    struct filter_view_iterator_tag;

    template <typename Category,  typename First, typename Last, typename Pred>
    struct filter_iterator;

    namespace extension
    {
        template <typename Tag>
        struct next_impl;

        template <>
        struct next_impl<filter_view_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::first_type first_type;
                typedef typename Iterator::last_type last_type;
                typedef typename Iterator::pred_type pred_type;
                typedef typename Iterator::category category;

                typedef typename
                    mpl::eval_if<
                        result_of::equal_to<first_type, last_type>
                      , mpl::identity<last_type>
                      , result_of::next<first_type>
                    >::type
                next_type;

                typedef filter_iterator<category, next_type, last_type, pred_type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(fusion::next(i.first));
                }
            };
        };
    }
}}

#endif



/* next_impl.hpp
aAbeUdGaROgpDO0ggYtLccz4zTyb9HQUWDFv9m14POy6APUBtKaGdRLEd3GHL4th1F5c56tujh2+Nm/P03x6HHSqpAgz5A0GpMdBGodfwbFTThZVOEXvW/AAzrjcLl4PHF//FJFb+anXAOvVAvWz7xL59i0fvQi6kgLge2ERghLD/46TbP5MLtYjZzhfZaHrRLV5iWKrU9AcJu/f4fg9WGNFThjAF1w6pXdvpo8fy7ynWV4o
*/