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