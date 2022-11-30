/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DEREF_IMPL_05042005_1037)
#define FUSION_DEREF_IMPL_05042005_1037

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/fusion/container/vector/detail/value_at_impl.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace fusion
{
    struct vector_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct deref_impl;

        template <>
        struct deref_impl<vector_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::vector vector;
                typedef typename Iterator::index index;
                typedef typename value_at_impl<vector_tag>::template apply<vector, index>::type element;

                typedef typename
                    mpl::if_<
                        is_const<vector>
                      , typename fusion::detail::cref_result<element>::type
                      , typename fusion::detail::ref_result<element>::type
                    >::type
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return i.vec.at_impl(index());
                }
            };
        };
    }
}}

#endif

/* deref_impl.hpp
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
*/