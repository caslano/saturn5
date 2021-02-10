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
bcmbXXCBt9nC3lygmiG7yie5XmPgwr8N33Zb2FCqSol9u/XdO/IrilX3r6OYy8C/DM9/PAX1mDMFLwJ3iHV7IVhP7GX+2UbhlbxO/fn5uXTqW3BlZEDKcFqX/lNo5j6kOKu9A+om7wondN02Kz13ZvWNxnoyDXEF3kScXbdLNyUMQtjxLTfEo3fuG9gmmoM9WXP5i33PBej5425LXRHRbMHpJqlSBuZ0jktnop5Y215z7zysmtbWiEUz1jzuO8sI0KbFms7sBwgUQzA3hJzUYYofAGAMPCZyEk/vHO7iLqp9th1nQyTtWpthyYq1XzfXzEwaQxTcqQPQqh5NHyGDpwa23dU9gMkrROqJp5sumEynPbAFX5xfUhj140ehmuPhmWnhscZHFDQI8MVgUSuhYLxFrs8mN5fQ9Ny0Z3vpHT9czFuvzsU1xQoihwssvBCVmtXzxAbNvZm9Fh462j6Ajr01R9LpFF5s7yacOmM4Ez7RwsY+c8YyRyMsIzEvyTmfFbfi6Kx7sxWY/H+Vvff2qsQ/+FFX7xqlYtbd/cLZvl3zS5hgRrxZq7dYxAr7ro9VhxA53q25+3QRxD578mSeReKn32+ySK8uSsQC2ZmzbRj2ZGF9eTuwVTjcZjTe3q5WAxTIArfjHHobujfl
*/