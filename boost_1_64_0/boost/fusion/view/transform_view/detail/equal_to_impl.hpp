/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_TRANSFORM_VIEW_ITERATOR_20070127_0957)
#define BOOST_FUSION_TRANSFORM_VIEW_ITERATOR_20070127_0957

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/equal_to.hpp>

namespace boost { namespace fusion {

    struct transform_view_iterator_tag;
    struct transform_view_iterator2_tag;

    namespace extension
    {
        template<typename Tag>
        struct equal_to_impl;

        template<>
        struct equal_to_impl<transform_view_iterator_tag>
        {
            template<typename It1, typename It2>
            struct apply
                : result_of::equal_to<typename It1::first_type, typename It2::first_type>
            {};
        };

        template<>
        struct equal_to_impl<transform_view_iterator2_tag>
        {
            template<typename It1, typename It2>
            struct apply
                : result_of::equal_to<typename It1::first1_type, typename It2::first1_type>
            {};
        };
    }
}}

#endif

/* equal_to_impl.hpp
PSDvCbYaZQyDN9M65RsFWqjkT8JnyI9KnrWFhModJQnNI4+QorgP0RDYZ30g6Fs0BuNCGY7zEH0I00hJN5GTJcr/P67K0BjvGrldvqHz7RMJ2Pm7HLCSUciRWfNe6F3V/JYM7iwwQuxp+1G+Fzo6yIjhfYq8CUGUaXHP59QQAUeHudXxfhVRsLLE/+XJpwgjLaoloIrnU0zg9ywTb8U3Qbf7zr30+RUWwWoKY5eg2wbD8bOAjI8/9g75YYSLmVn8vFU5/AIkpZWrBICO6AWRjwq3LVl1z8eSMLwuaF0MOHsGCn5srxdzrNRTCjV1Mj/k/55Nj/umjRTpFTlK1zp4niMReGQYiuadVZEAWMYwi4NY0NftNJctVkpPnoq1S4gh9K3dy4nWHQQxVGS3JIFO6VxafVTnFPRlWBt4//aTYNqv0NaZHZOffmNgZLlFaCGcY1xlFMIKeoUXFdXYzj6/Y1pNuvqeSEIbQnFDRzOArV6xA3tBqNfshIAnC5UeZVQ2DYQ5Yux8+2iBXZFcmB81du+X8JI7Hgw1vhAe5QCGb4HzKbs6hGH/tdsDNQ==
*/