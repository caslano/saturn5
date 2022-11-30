/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2018 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DEREF_IMPL_07162005_1026)
#define FUSION_DEREF_IMPL_07162005_1026

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/utility/result_of.hpp>

namespace boost { namespace fusion
{
    struct transform_view_iterator_tag;
    struct transform_view_iterator2_tag;

    namespace extension
    {
        template <typename Tag>
        struct deref_impl;

        // Unary Version
        template <>
        struct deref_impl<transform_view_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename
                    result_of::deref<typename Iterator::first_type>::type
                value_type;

                typedef typename Iterator::transform_type F;
                typedef typename boost::result_of<F(value_type)>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return i.f(*i.first);
                }
            };
        };

        // Binary Version
        template <>
        struct deref_impl<transform_view_iterator2_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename
                    result_of::deref<typename Iterator::first1_type>::type
                value1_type;
                typedef typename
                    result_of::deref<typename Iterator::first2_type>::type
                value2_type;

                typedef typename Iterator::transform_type F;
                typedef typename boost::result_of<F(value1_type, value2_type)>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return i.f(*i.first1, *i.first2);
                }
            };
        };
    }
}}

#endif



/* deref_impl.hpp
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
*/