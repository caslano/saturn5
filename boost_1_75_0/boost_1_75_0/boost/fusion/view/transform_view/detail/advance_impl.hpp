/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ADVANCE_IMPL_13122005_1906)
#define FUSION_ADVANCE_IMPL_13122005_1906

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/advance.hpp>

namespace boost { namespace fusion 
{
    struct transform_view_iterator_tag;
    struct transform_view_iterator2_tag;

    template<typename First, typename F>
    struct transform_view_iterator;

    template <typename First1, typename First2, typename F>
    struct transform_view_iterator2;

    namespace extension
    {
        template<typename Tag>
        struct advance_impl;

        // Unary Version
        template<>
        struct advance_impl<transform_view_iterator_tag>
        {
            template<typename Iterator, typename Dist>
            struct apply
            {
                typedef typename Iterator::first_type first_type;
                typedef typename result_of::advance<first_type, Dist>::type advanced_type;
                typedef typename Iterator::transform_type transform_type;
                typedef transform_view_iterator<advanced_type, transform_type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(boost::fusion::advance<Dist>(i.first), i.f);
                }
            };
        };

        // Binary Version
        template<>
        struct advance_impl<transform_view_iterator2_tag>
        {
            template<typename Iterator, typename Dist>
            struct apply
            {
                typedef typename Iterator::first1_type first1_type;
                typedef typename Iterator::first2_type first2_type;
                typedef typename result_of::advance<first1_type, Dist>::type advanced1_type;
                typedef typename result_of::advance<first2_type, Dist>::type advanced2_type;
                typedef typename Iterator::transform_type transform_type;
                typedef transform_view_iterator2<advanced1_type, advanced2_type, transform_type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(
                        boost::fusion::advance<Dist>(i.first1)
                      , boost::fusion::advance<Dist>(i.first2), i.f);
                }
            };
        };
    }
}}

#endif

/* advance_impl.hpp
kHHytLN8PXzPcwLOiQ8z8pazVkm/wKFNZ9WubFa+3hRwkrjXcjzW8/2AhRk8g+MF8C2DIqu8PginXyf/KufnapWPmMLTgUv5X8aZUOUdL+vBBuAs4iALZ//KUSrxJdimRRE/zNPrJT4nN8ocPDRIpXfF85pVFE0ItmgI43TdL5qvB98IPBPE0+5nelyjkT5F/8GLDg8TjK/X+UwwtcCqMcofh6Pc8tnf7eUtgR9blUe1F3iuB9c2Pm4TRmxZ3w86f5bUeMJdGXiikTlbD7Yh5o15vuka5zwbd537Nq7y6Fw77y/2CE6nNujAmKVL7E86SiWnTvW1CaZrwUWG7Wwv8sG9cnZAOdbABnkm18nGCZsRdniSt5CvNwfTXTyPao9zEvAs+bCzt7SvVNZAYPD/uXzEJHSTWB/YfsC9iX+F94+thvEQawk/z3W9RVqn0fkrwvVQMmNwTLt/ugzmT+DzYJHO9YjDqA/R4XsiV6YjZt9jkaZhal4bnkqKvr6uxyQe+qf3yPsR+zA/Uqs/wefo2WCr4tyzvkXERd6bG7Uc56WRjuCUbbrJRVDZKqNVtNtd1kOjWaMzG7yU/TD+udDOOHMCjh12n7we7+kmtlo3PY35jEbpA097YFYI8T4IA7zYfD265psjiwMbkevdrDfLu4Edn0iavAM843l9kEyyZ++RtW30/opwfWE5/NM2qJ5VQe/n/bz3VtHMGOY3
*/