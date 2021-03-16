/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ARRAY_CATEGORY_OF_IMPL_HPP
#define BOOST_FUSION_ADAPTED_ARRAY_CATEGORY_OF_IMPL_HPP

namespace boost { namespace fusion
{
    struct random_access_traversal_tag;

    namespace extension
    {
        template<typename>
        struct category_of_impl;

        template<>
        struct category_of_impl<po_array_tag>
        {
            template<typename Seq>
            struct apply
            {
                typedef random_access_traversal_tag type;
            };
        };
    }
}}

#endif

/* category_of_impl.hpp
u4qLR4mTIcfG+8gyx47e0Brszb1trI7mGBzhDfho+d+WwTGB0N2CXH8jY/EU3b6IEAfZPor3d4l8la5rUVZoiB1ULIzHx2ncED9L42U3x9I4XMeXaRxIkWpVexB+ncZmgG/TeJPYb9JMTIA0brBzpcHO1Q3sUsEqBFsu2M8FaxKsWbB7Bdsm2A7BnhAMjZaxUsdiSdV3kvKalg8h7d2IPVZ1L/jnqu6nKKu6w6DCqjtGEFbYZyiv6o7Nbb0+OYs=
*/