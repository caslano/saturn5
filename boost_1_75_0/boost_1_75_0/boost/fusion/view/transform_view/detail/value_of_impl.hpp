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
4wt6hvq79cDcFGGss2cDVmHOYHPAuvOul9bFyp331zgkZgmV4VypI9dJNtmdu8bGUlWj8z2P92HywL92P465LJjEZX/X3RK7NHMlfU+dKF8P5Jq5e8GU2H+Z5N8vihHJP8PhsCi3m8fTg/a+CzMCURkzv8oW7k/p9Gmuh03pT/zEnq1Xak8q+Sr0LFhf+b4R3zlzsgf1KLyU5SIfvWdUBT1fzf1Cntw2hzkgYPd3Pxg5uZw/AqR0l9bttIPtYY9gdyA+wntlNs0gC2Le1uIi3xRUtwrlboyMY7Im/q45Vqdw7htc1ai3mMtn/J8n2o1hPM2gSB2ErZl5SsWksBnwL9fnBTcLYpq465w/+L3NFxrCNZs2qCeDMHc9tApzkFDN8LxvsPxrkG/LzzPxOlqrDnMdGM+AFwkmEvQJ+Tq4oDz5p8nWa6V36Ni5yb8pD/1C/gCUAycHxEYXZBVBNuTPizU1XrQPMyODX+sjn7dTRCP/AQtSBKjcXD7jdPF96oB51fvrfiY8N7RzEfC+DIrN7p+XCd+cYiYgmg9lCvdbdfKH0CzEI0ximy/3A59iDSb9EUsuOs99uB41SZ+yu9xdPEbeVr5ep+eq4+RrMd+/tYC9dSRmhhjnarv444Pu7qb7Q4V8lz1fw/li90BTSYIRe5Y2Le7k28I9J+bvrKUPVumX4YieYNohejPL6ng5L11Qq6113zpFXJy/OdzV
*/