/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_AT_IMPL_09242011_1744)
#define BOOST_FUSION_AT_IMPL_09242011_1744

#include <boost/fusion/support/config.hpp>
#include <tuple>
#include <utility>
#include <boost/mpl/if.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace boost { namespace fusion
{
    struct std_tuple_tag;

    namespace extension
    {
        template<typename T>
        struct at_impl;

        template <>
        struct at_impl<std_tuple_tag>
        {
            template <typename Sequence, typename N>
            struct apply
            {
                typedef typename remove_const<Sequence>::type seq_type;
                typedef typename std::tuple_element<N::value, seq_type>::type element;

                typedef typename
                    mpl::if_<
                        is_const<Sequence>
                      , typename fusion::detail::cref_result<element>::type
                      , typename fusion::detail::ref_result<element>::type
                    >::type
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& seq)
                {
                    return std::get<N::value>(seq);
                }
            };
        };
    }
}}

#endif

/* at_impl.hpp
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
*/