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