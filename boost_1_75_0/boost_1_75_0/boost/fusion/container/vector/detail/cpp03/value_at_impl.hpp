/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_AT_IMPL_05052005_0232)
#define FUSION_VALUE_AT_IMPL_05052005_0232

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/at.hpp>

namespace boost { namespace fusion
{
    struct vector_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_at_impl;

        template <>
        struct value_at_impl<vector_tag>
        {
            template <typename Sequence, typename N>
            struct apply
            {
                typedef typename mpl::at<typename Sequence::types, N>::type type;
            };
        };
    }
}}

#endif

/* value_at_impl.hpp
Jfbxz9mc4tDPz2eTTLCQ1YERUUE6XkmyAXQF8AN6vTKk19vchrmo4e0c5u3gYYrjgdlixg2n7OIYXjtlt0fQlEfxyakJaSbfTStfzGeoWPc8+tboLL6W90AQw7XYgxitB2sNe4pI/c3gsAcbipzTVpqpGxbejbUh3djPKqoESl/o9GWRm0yO716k9UgfFs/iU0rt3jeLexIWc3127CwxDG12JswKWYXhswyWYNWRMStEm71GVFhC9yFpL5Ddl3aVXZRI5E3+MtPKxXmDBw34/8y0alRG8EzOJ96bKRxXp+t+RUa1NYEziX59m1Fbb/cTQb6NPy1Iv70XM8LMfg3jb4OP0DPdj0T+Ov76Kv7sxp81nLpXcWIeRssLiJZ/HNRoeR4KPmxKuFb6A9dKM8DqC7Z8WFNYsi+KiaQXCGNvNogFP9nLnowhkq6Ek3R4kemf+5dTPqQ6NhQTqQSKJXGiksMQTJyGMtwSdP3mGAOipnILo8TJRiqaJ24rNqqmWIZUU7qMovvsEP2PYTVyEzYUwvKa7MvkxctmkpXiMMd6cXqJCI/W6n0tyKgkzgL4kbxmgSIF9t0WpMBSKcvsovMosNev0RTY5+5spMBOH0664eQWjRTY6kGkwL5zONbgLA5flk81KrB9brLowpLyep7F0L0bPpt2HgX28VdCFdh/7hDxXa5yCk5ZnUud3GXTA7zoCmznQedWYEWfE5XX
*/