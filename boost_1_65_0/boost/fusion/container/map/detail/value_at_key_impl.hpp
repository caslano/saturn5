/*=============================================================================
    Copyright (c) 2001-2013 Joel de Guzman
    Copyright (c) 2018 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_MAP_DETAIL_VALUE_AT_KEY_IMPL_02042013_0821)
#define BOOST_FUSION_MAP_DETAIL_VALUE_AT_KEY_IMPL_02042013_0821

#include <boost/fusion/support/config.hpp>
#include <boost/utility/declval.hpp>

namespace boost { namespace fusion
{
    struct map_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_at_key_impl;

        template <>
        struct value_at_key_impl<map_tag>
        {
            template <typename Sequence, typename Key>
            struct apply : BOOST_FUSION_DECLTYPE_N3031((
                    boost::declval<Sequence>().get_val(mpl::identity<Key>())
                ))
            {};
        };
    }
}}

#endif

/* value_at_key_impl.hpp
x/KLkImkJM0YL20rz+ibaC5a7E9d3gjrpw==
*/