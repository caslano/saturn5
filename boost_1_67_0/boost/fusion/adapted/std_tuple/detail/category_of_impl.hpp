/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_CATEGORY_OF_IMPL_04202013_0940)
#define BOOST_FUSION_CATEGORY_OF_IMPL_04202013_0940

namespace boost { namespace fusion
{
    struct std_tuple_tag;
    struct random_access_traversal_tag;

    namespace extension
    {
        template<typename T>
        struct category_of_impl;

        template<>
        struct category_of_impl<std_tuple_tag>
        {
            template<typename T>
            struct apply
            {
                typedef random_access_traversal_tag type;
            };
        };
    }
}}

#endif

/* category_of_impl.hpp
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
*/