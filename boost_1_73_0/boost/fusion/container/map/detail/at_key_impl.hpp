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
Tb+E+eY4R+5jP4u1bK4xspr+DonRNbbdX/w+y97mpJ76k+Kqq/dgInVmA4K4Cz6M2cTv1ZiH9dzNzjmtVwGPeqXvhFKH3p1m6pBXv01MPRL5aD3SuqZlpqm7HtW+7zF9PSbfpp5dJGlgPndMveqim7m9pGX+RcfgJ3X6AfVK3+Nj5lboPW8s/pcwP6OzZ10iPlPeeouQJDrsuu7eOY9tmPMdRF3f3ZrvC1IYDqYHk3kKhv0+
*/