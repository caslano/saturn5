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
QNzDp3l9TEGJg48dqtbhiebdErUsB6loAqS3xqG4ehrlXKATXKu5+uhRJ+uJSVpRbh3/xRgOYQxaNDWz2mCnFXD2PHwKhH6pqWhRl3y5yKzduUtkziZdspnzlj3oe5xg+l1HGWmZrWudx7RP3nGjvuBPjU/cwjpRutN4i0LQbeSOrb81rnAIodQU1d8dVHf65GhZq9h8CUPVwljZLvxk2/an91+qxX+J9j7v2KAd/L96/yXq/eeU1f1mpYr19vJqId5oBHlUgdmIFnef0hSsWMYyp2Bcy6QNcZo3XRzksCYNjqfMGo7iUN3xW8wciir796LSyg7+dGB7kd+YAv+26qhZ3sD2eTbgKApAWWU+o/coLsoS6zE4FX6qZpnYlsLt6GVi4wvjNFnBl204yU6lC6s8YgpnEV/BP0HrDaISyrS/uofDoXcKw+g6X49wH8sMY0SCU41h594wppIxxphzid6/qEyzO6qHov52rlatHXj8fsBhetg55ZHTJTGrg6sT0SlkfLdc/c0P+jsF3kamGZbNQGpGIxTHa4zkTPzdF0yMIIlEB7hNNe54c+tYPQUD6KZ0JTBKFw5MwoKh1q8sROxzMA75ItiximVRfclNmTH9Yb8FNNJCmaOugZOrncwVD9rcMfVw3NNv3N3S
*/