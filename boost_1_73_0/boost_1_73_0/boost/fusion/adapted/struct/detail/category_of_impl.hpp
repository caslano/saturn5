/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_CATEGORY_OF_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_CATEGORY_OF_IMPL_HPP

namespace boost { namespace fusion
{
    namespace extension
    {
        template<typename>
        struct category_of_impl;

        template<>
        struct category_of_impl<struct_tag>
        {
            template<typename Seq>
            struct apply
            {
                typedef random_access_traversal_tag type;
            };
        };

        template<>
        struct category_of_impl<assoc_struct_tag>
        {
            template<typename Seq>
            struct apply
            {
                typedef assoc_struct_category type;
            };
        };
    }
}}

#endif

/* category_of_impl.hpp
40PXTq+9wOvBHL48rYZTpvr9M+JEpbJTBrW4dWDOgG7N1DC01XMyeAnDEKaNJw22iZgJ/PV7ophUNyv2kfk0UQw11HLaEzANIl2Yhp4jCmsC9eCutXz9rl8rRNlTXRuUtsR00TUwCego8cg/a/I7lXYJqL0lULorz2EcESL+QHS4w9c5iejLREc7+nuWrnEGx3B4lgyHZ+kh7TzBLhBsoWCLBbtesJWCrRZsjWBPC/acYO8I9p5gAcdi2Y7FNgo=
*/