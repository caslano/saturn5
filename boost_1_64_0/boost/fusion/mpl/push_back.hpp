/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_PUSH_BACK_10022005_1647)
#define FUSION_PUSH_BACK_10022005_1647

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/algorithm/transformation/push_back.hpp>
#include <boost/fusion/sequence/convert.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct push_back_impl;

    template <>
    struct push_back_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence, typename T>
        struct apply
        {
            typedef typename
                fusion::result_of::push_back<Sequence, T>::type
            result;

            typedef typename
                fusion::result_of::convert<
                    typename fusion::detail::tag_of<Sequence>::type, result>::type
            type;
        };
    };
}}

#endif


/* push_back.hpp
ah8woh/FNrsZ89i/S10A5awxKL76NbuydyYtrUsUal3yVFCSOelE3X5m17bnkMuaT9BD/hctp0d2RxsfiYtzp2BJ+9df53Yb48CXnvPCixuRiHlQSONukn5hjo8Z+ioLhcag/sdIimKFgM8WxcJ2ybYlJtYTUYoq4F98PPETfObcERm96B7v2yIwptPmqE300e2QIJfuhRRaXdOe2NYulIcwJ3BFjmpy/F04McdJMs1TrDL9sdXP3KDFIz3JIbyUCO0+BBSEVJbdV6nwFNc/PpkZszc+2VLddB+bhgxp2QG8isyTR47WOJ9DfbkgFU+wi87tqbgCrx8ahzv1eQHEuqlVX6Ow0O5jDQuvqTpzR3p0MhdOe4zEe94mLSPkzDX5ohsKwuzdsN7wIezmMX1cRJPw1Q8ETo7rJPIITpd1AI18bOA3KQwwp40hWq7SQSfzTwcI9RFfqtIFA8auzUCeDb0KuTtQfX85iN/y8xwQwbT9UMb1gvoguXH5kUykzDsT2XZCUk0LE5Wnw3BkhJfZ729Ih6eZSX3VH+bH4kNj/Mk/tU2B4iWRVpIqUg==
*/