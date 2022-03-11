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