/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_AT_IMPL_05042005_0741)
#define FUSION_AT_IMPL_05042005_0741

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/fusion/container/vector/detail/value_at_impl.hpp>
#include <boost/static_assert.hpp>

namespace boost { namespace fusion
{
    struct vector_tag;

    namespace extension
    {
        template <typename Tag>
        struct at_impl;

        template <>
        struct at_impl<vector_tag>
        {
            template <typename Sequence, typename N>
            struct apply
            {
                typedef typename value_at_impl<vector_tag>::template apply<Sequence, N>::type element;
                typedef typename detail::ref_result<element>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& v)
                {
                    BOOST_STATIC_ASSERT((N::value < Sequence::size::value));
                    return v.at_impl(N());
                }
            };

            template <typename Sequence, typename N>
            struct apply <Sequence const, N>
            {
                typedef typename value_at_impl<vector_tag>::template apply<Sequence, N>::type element;
                typedef typename detail::cref_result<element>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence const& v)
                {
                    BOOST_STATIC_ASSERT((N::value < Sequence::size::value));
                    return v.at_impl(N());
                }
            };
        };
    }
}}

#endif

/* at_impl.hpp
SVgoJ7gpzOYwWtHj0TaYo8XC0s2ozJCqm0SlDzYij4Qyy3WGipAH3BQrpNmDHMtSu83O8zsVK04dwae7QrO2NwaVoTFw1BnB5egIpswI48HHy/HFYDKGj53hsBOMr2DwFjrBFYG9vwx6mEAClWngt3PNDSrXINK5FDxe6fx5V6uGZwgp7kgJLIpQHXdkoQs5VvUM8zM2jtAoYdk1pihxETPL7pItUlmGBwCmCkQsSrjLEtpfrE+RSomYaW4sTDkSjOfZDTp4L+ykoD/ovvd7RbYVKynlDqGhlEmQXOc+WnwsskjmMYcjK1K+wFpLjmq1lcUrtWRh+8FiAfq1Bne+dTFZw4SZBOhXm16ILzy0kOVpSBK0JBV6nPFbG679DEXcXsNQzpMdIJnBXZKzLJ/T+1YTgcl5SvIYZhjGSCpDFDpb4g3qDDn20DLOzBKaJJFrHhZI7dp3dOquK7yZBL2+HwaD8O9Jf3w5Gflwcrb9dhK8DwYfA3fovXBGiUxYwSQgcTknvVsSDuxD3/8HJc6J7Rm1KOo9Pf/N5B0mjAtdzKf5NSywvpz9RYUYDBuLtMJ4s88cM9hqBhHXlrlswaOCRKWKPrviA6QWETApsNiXbp2KRmP9rZ43zFs3PsqV+m2j8oAvOfJRH5b31x8U
*/