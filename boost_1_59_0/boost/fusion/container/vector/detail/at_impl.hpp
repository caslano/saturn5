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
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
*/