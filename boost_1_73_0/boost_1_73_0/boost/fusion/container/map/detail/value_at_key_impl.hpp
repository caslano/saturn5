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
hw1hwJIKAdMSLFgn8HlyfhexOmh8b4b2a11VHvmD5z+IoAIHt88peWN7f3udDSRbyO876tytZ7tSydmsmFnYHkBZwWZb78MOUa51MKPa85RsLqC+LXgS8gnwTXrxRSkrHapd6pttyCw5cDOVtDH0wuUYJcZYQt0iP2uhjaTgJlkwBzfpACfjIfmrYra1W3g/CsCOkC2+wqzdkNl0MgvNKnjlKR6ZkVPGmG+/in7mXnD3olUkc7/+RWvIDmcO3m2ArVzcVZBKMMtEjtJstDgIgAj/gQ0tmAY14kG5oLe8XMmbF1dGv34J2vJqx7h8qoHMF4VKUZhKavTXqkscIsF/jp4UR/lkXmeWuKk5E4nlI9P6RIoYmEFtd9gmG6Wdpt9iLpNGvASdbBQmdHtyh0/U7YmZF1bz927zH1vN14PLzVqN9U2zVTTkENC2jGj1N+YsRJItF/N5N9whSBe4kDFGGsE0HXKRV7XUDU4PUv+CkV34iQ6ZcDFK/f2NxP+YzKJYXLKxmL5TvmgojIrMGYgCJi8fpvIDAa7PgWrW2TUfuT4FNifWDRfhF5ELePz3Rdpbwk/mRSZAzpsc8Tai4zm6jIIjNCmv8+VqTlkk+esARRNvu7aZ/PpqFWsPP0bllZJcPD/CUOIeyEUC2reK
*/