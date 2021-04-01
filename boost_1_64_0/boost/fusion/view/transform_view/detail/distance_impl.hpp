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
7HkAmM37UFonuO2MX3PUOdIMrn6IqS2QcdBV//6iEKIbxWdgvbaMV5BU59+RvWyzBIg8ufXM3K+sBkCKqy07PEWMBddgfysJeybFkCx5uX30/u1KPuYsmIuIbZIUnuo0s82iMsKVqVZkF8T4U7VeMNfWUep6he4tiw1k9+qL+lrT+m9zp9FoPNeWm+s351rNHrdiEV+KivD00pNwFNJXzW6KSFw6E6mNoVG6XwdUopcEgww+cehE6wQBMtTsgPiRMt/+K3sXbSNidMjR7EzCUJg+gqKbQ2bItiGgKv+nkedNLKkYVGvayVQmH0e2yFU7fe6IDRxHgJmOGwi4Mf5k4ciWLgBHzVOQnSW6OnTjYaYBqUDfduf18mky4XPeOGd4v0a139EyiJqIc6lxPE2Zbtd8VEtYcsomLZ/3o/W7zn6iq/FWtPKJgs1rhNpQCY3gOKKDqv8G8j8mPVEFLp9DU3S1YxUpNZdHk12YX+OeFGSZhOot8X2mOoT6LJBAzV3+ex+Gkz2kJivWYIDAJchzv8s3W16q945iKF+jBj9YY8WadwtJcI8j29LnVA==
*/