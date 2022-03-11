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