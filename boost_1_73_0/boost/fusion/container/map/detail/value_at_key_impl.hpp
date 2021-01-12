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
s2PbUu81/jKGW1PGTWMgbu+JmxaKeo7r1tLP4Kp/TVXvDfcbd9f91m+A/TNMuy32DSJf3r11LDWxQr+99fztan81XXXhaLv1VWdLjjd0vezrmDsI07/S3W5VqH6IiC6bsq7e+tc0HH8uv928dd6I39i2oJv7no+S809YJ6kfnXMmfnK0b7FM/NxpJRFjY6u9NQxO5O4tgVnix7aWi5/x9BQ0wMex7ri6RuJKhyPF391WBmG7
*/