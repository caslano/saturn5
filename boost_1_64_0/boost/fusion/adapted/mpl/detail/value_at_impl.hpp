/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_VALUE_AT_IMPL_31122005_1621)
#define BOOST_FUSION_VALUE_AT_IMPL_31122005_1621

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/at.hpp>

namespace boost { namespace fusion 
{
    struct mpl_sequence_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_at_impl;

        template <>
        struct value_at_impl<mpl_sequence_tag>
        {
            template <typename Sequence, typename N>
            struct apply : mpl::at<Sequence, N> {};
        };
    }
}}

#endif

/* value_at_impl.hpp
YcCwCKhhwovozmsUgijOCPlYQS6JDZOpq6LhknprXXYxha1YxxvlF3IzvGFdL7pnZBFsX6t0Jcr8urOrQ4u6WRboRsxV8eF4SgusP8bVUWsTYwpXfCnaFnlHtwcC2FQ3s1TnM9fuz4dNHevMMBEOvRSOgWo/Zh+iInZllJY81xHm+7vR/Vu0W3LEx/bYR8DyKItiTAL736JKL9jQKcvX6jPwEM96TjMo0+u70Saml+pKnNhJ0SSqW6JWZEMo4DT7GrIFiyuw1hkbocldoykzEuVRplAn/8Evk812NYBWisR/5ubiq9had+tu01D0IgBhSVsTUi4KZyo5sqwN5Fx2GRFID3sutmnb4nKZABdH9zcmO0t783rtlLE24LYlq7WXVuUxJl86JF/gTahwswT1FwpTqR07eQpcTu8VpN5r28l+Ip2NzqW1GUVg+5XjDW7KDjuBROK7HbZzIGutqdmB7BVNf69IdKjMKLJRcnfcWUHeRtj/Mrhad7zrmBJjKr5rRR7Bupb6yeYkU44fM9Q1IpA0UuuIv82I0obRUtGKYIfU10nKJ324iRtF4A==
*/