/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_OF_IMPL_05052005_1128)
#define FUSION_VALUE_OF_IMPL_05052005_1128

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/value_at_impl.hpp>

namespace boost { namespace fusion
{
    struct vector_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_of_impl;

        template <>
        struct value_of_impl<vector_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::vector vector;
                typedef typename Iterator::index index;
                typedef typename value_at_impl<vector_tag>::template apply<vector, index>::type type;
            };
        };
    }
}}

#endif

/* value_of_impl.hpp
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
*/