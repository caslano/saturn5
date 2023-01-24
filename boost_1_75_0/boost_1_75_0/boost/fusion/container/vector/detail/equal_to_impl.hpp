/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_EQUAL_TO_IMPL_05052005_1215)
#define FUSION_EQUAL_TO_IMPL_05052005_1215

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/and.hpp>

namespace boost { namespace fusion
{
    struct vector_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct equal_to_impl;

        template <>
        struct equal_to_impl<vector_iterator_tag>
        {
            template <typename I1, typename I2>
            struct apply
                : is_same<
                    typename I1::identity
                  , typename I2::identity
                >
            {
            };
        };
    }
}}

#endif


/* equal_to_impl.hpp
t4rGJzgZjguTuv1Lu3TMcu62y5g1FwKZ4k7ZsyDBHdMfHQcHx5jI23f3CgtfTsuy1a211Yx/kP3gi0k+vpB/6sOq5tZRZKlQHX8+Sos4m3P5VGXpPRZiW6t0br33Uas2IE2TilUd6/E9kjo9By4r/ywvv4YzfoE1jD56H+XsmHD4AfGTduS9jxIlWqsDjMQSsk6tXI9yvlqpF7oa3mGy3RW8yVKdgwpjJhdAGPl96xZyZsBsvos/BKKphe4hInx4LVHdffxZsxbJ7nb+cyonyu/A60+UkZX083n6OZj/HMhL9YWn8n5/ZLDd+cfL1tMxb9tKXV9upFeStGDpZNfIuSlEr2Qayskc33sFpE8WcH2y9yNWbTOVV7nsWV9IPr4HIRGdhErWOi4iRwqpm87kAD2v5QXq9AJ1vICWjrItL3OYzzcVwM0Ar/hOb4hCKvaHfRHRXtLlrOPPoctBEY3oreJEby0neqsQQ+58mK8+z2OdzVEJiAiUMJ5MPhhJKQHzuR5H0aVBlF18B9fjqNLoh604GMo5iNmtcNfuE2QLpyUlioZco9O1GiPHgjLtuP62z6Tpb5gnrABSFVKubdTfVArIAFYax4qHdF3tu0jS3xYY3u2PFPrbEPY2WATX/jFrqGPGMtLfWCWTlwGFU7juVv4QULg6BF8ZqrvtUZZNBfqWxcnbFXAlcv5UrrT99CAobV9nY0wHH5pCb1i7
*/