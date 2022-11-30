/*=============================================================================
    Copyright (c) 2001-2013 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_MAP_DETAIL_AT_KEY_IMPL_02042013_0821)
#define BOOST_FUSION_MAP_DETAIL_AT_KEY_IMPL_02042013_0821

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/utility/declval.hpp>

namespace boost { namespace fusion
{
    struct map_tag;

    namespace extension
    {
        template <typename Tag>
        struct at_key_impl;

        template <>
        struct at_key_impl<map_tag>
        {
            template <typename Sequence, typename Key>
            struct apply
            {
                typedef
                    decltype(boost::declval<Sequence>().get(mpl::identity<Key>()))
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& m)
                {
                    return m.get(mpl::identity<Key>());
                }
            };

            template <typename Sequence, typename Key>
            struct apply<Sequence const, Key>
            {
                typedef
                    decltype(boost::declval<Sequence const>().get(mpl::identity<Key>()))
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence const& m)
                {
                    return m.get(mpl::identity<Key>());
                }
            };
        };
    }
}}

#endif

/* at_key_impl.hpp
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
*/