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
cAKG+mGeDuLq14RbCVQr+3pmIcK/tRsRpuUNftd0ibn7hWgbu45i5IkW9igpU3Dr4/z8KY1qTXo0zYLKRv+ygnXHa3nnROwQo/NxA+gj5vDOCy7AjGPIAXPwOJxz3mCMh52lkCpa1z2QQsyRy1pCi2whpsn7ewCWo3FHbcbVrrZAVqysusjWKwd0d8cnPAmGhuwjJXINPaVR9KC4DkTzYu7NWS5IjvjRgQwqG9cN+KwJUAdEq6TvhFJqTGEX4q/DUda/MACJRZIvlJp1isl074pNheujtUJdqJD82ONTmISxVPbauzgX/q4VNll+/reZvfibPFYuK1ahsy1E7Rj+0bjo5TdQBr2gaD8y4LlfXMC0Vozv9wiYuIxQ3u9dqnFTcBk7nEggwMR+wHfEq31+lvyJEAPcJrSQciLWfeDMC2kuK1cgMduWgancL5CAMgQfuv+4vxaTAd3t7NYuMLI1kw0eWRdYXLE0Lyf0XEKU48uagdxuPIC5AlT7pjwuAXs2LCO/FdMe14Xno9ZftKI3MLkERl2t8Un5bojjCopzOkdVyd36jijPbbX6kw==
*/