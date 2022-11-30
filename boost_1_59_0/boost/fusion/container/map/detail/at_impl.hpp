/*=============================================================================
    Copyright (c) 2001-2013 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_MAP_DETAIL_AT_IMPL_02042013_0821)
#define BOOST_FUSION_MAP_DETAIL_AT_IMPL_02042013_0821

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/utility/declval.hpp>

namespace boost { namespace fusion
{
    struct map_tag;

    namespace extension
    {
        template <typename Tag>
        struct at_impl;

        template <>
        struct at_impl<map_tag>
        {
            template <typename Sequence, typename N>
            struct apply
            {
                typedef mpl::int_<N::value> index;
                typedef
                    decltype(boost::declval<Sequence>().get(index()))
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& m)
                {
                    return m.get(index());
                }
            };

            template <typename Sequence, typename N>
            struct apply<Sequence const, N>
            {
                typedef mpl::int_<N::value> index;
                typedef
                    decltype(boost::declval<Sequence const>().get(index()))
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence const& m)
                {
                    return m.get(index());
                }
            };
        };
    }
}}

#endif

/* at_impl.hpp
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
*/