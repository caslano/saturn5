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