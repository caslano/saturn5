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
SLrzqur7dXU1F6kFwkpgXfivp/yNj5WIZVA6Qhczr5SwNm+sJkAeZsSAO8l5k+rWI7Ywl+uo+6CKQg2wXUs1xg1/sY+65uX++aVGqhdnr/4KxCIrdDjRuLYNsXIVw2YOgeh/JaFZWpSr81OPsui6Eo93xf/YQXZcpx75b27Zx6pSg5XW4o3lgU4BjWEY7NiASZteoaZwxgnwjjKwL3NrYjIDJMoA/UuFYt1AzB8nq0cth4QdzNosXzLbXKb36AVq+TThsgUa1ZGxYHEsbSNa6T9KSyqDO9Jl7Ky3kVgs8CnYYHUH4nVCDM/k4nuaE8+LHOZDWGV1MUu1HN1AKXoc6AujRmPM3bDtvo7buloTqwReAoERZyoVTLEZlQVhiu/xrUkd92X/gtU8iOMZhQU7OtUvVXU8a5sahfNe5wMdwJksMbOYLVVSUBxZZ6oiw4JNWIDMqHI2VTf0onyFuA9Dli70qiIUKLyRIZOg4uy52HfPPkzLWag9aua7rXUze8RGPUskYv8Ni+RpUVXpFbqoyXul1qxkFhbXwLusmSmoqdiHwh9GmU1nRXMMD9bgMixHYhm/qCJyTCusCR0QirSAHjGE6axm5kK3iJFRo69Rozh5w3DXy7iEQ6iaVZDXeWaZP/X+tMwcIv+nNXiM
*/