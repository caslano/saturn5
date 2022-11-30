/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DISTANCE_IMPL_13122005_2139)
#define FUSION_DISTANCE_IMPL_13122005_2139

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/distance.hpp>

namespace boost { namespace fusion {
    
    struct transform_view_iterator_tag;
    struct transform_view_iterator2_tag;

    namespace extension
    {
        template<typename Tag>
        struct distance_impl;

        // Unary Version
        template<>
        struct distance_impl<transform_view_iterator_tag>
        {
            template<typename First, typename Last>
            struct apply
                : result_of::distance<typename First::first_type, typename Last::first_type>
            {
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static 
                typename result_of::distance<typename First::first_type, typename Last::first_type>::type
                call(First const& first, Last const& last)
                {
                    return boost::fusion::distance(first.first, last.first);
                }
            };
        };

        // Binary Version
        template<>
        struct distance_impl<transform_view_iterator2_tag>
        {
            template<typename First, typename Last>
            struct apply
                : result_of::distance<typename First::first1_type, typename Last::first1_type>
            {
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static 
                typename result_of::distance<typename First::first1_type, typename Last::first1_type>::type
                call(First const& first, Last const& last)
                {
                    return boost::fusion::distance(first.first1, last.first1);
                }
            };
        };
    }
}}

#endif

/* distance_impl.hpp
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
*/