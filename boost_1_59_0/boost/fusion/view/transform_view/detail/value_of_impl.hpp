/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2018 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_OF_IMPL_07162005_1030)
#define FUSION_VALUE_OF_IMPL_07162005_1030

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/utility/result_of.hpp>

namespace boost { namespace fusion
{
    struct transform_view_iterator_tag;
    struct transform_view_iterator2_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_of_impl;

        // Unary Version
        template <>
        struct value_of_impl<transform_view_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename
                    result_of::value_of<typename Iterator::first_type>::type
                value_type;

                typedef typename Iterator::transform_type F;
                typedef typename boost::result_of<F(value_type)>::type type;
            };
        };

        // Binary Version
        template <>
        struct value_of_impl<transform_view_iterator2_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename
                    result_of::value_of<typename Iterator::first1_type>::type
                value1_type;
                typedef typename
                    result_of::value_of<typename Iterator::first2_type>::type
                value2_type;

                typedef typename Iterator::transform_type F;
                typedef typename boost::result_of<F(value1_type, value2_type)>::type type;
            };
        };
    }
}}

#endif



/* value_of_impl.hpp
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
*/