/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_JOINT_VIEW_DETAIL_KEY_OF_IMPL_HPP
#define BOOST_FUSION_VIEW_JOINT_VIEW_DETAIL_KEY_OF_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/key_of.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct key_of_impl;

    template <>
    struct key_of_impl<joint_view_iterator_tag>
    {
        template <typename It>
        struct apply
          : result_of::key_of<typename It::first_type>
        {};
    };
}}}

#endif

/* key_of_impl.hpp
XH6hIuMH67Gu7JG0zZimiqnN4L/9hq/+mPX9mbip/7rn/VZ1f70Ge8fi+EkUGtX0gLdgUlEE2b6J0gRmqaVbHdoSctlUr54G+EwGThBB+LFsSZqV43Wr97dOi9+CcJv0O9EGBOA4Wgr8Zf/B8x685ofFvSZMfmLz8ufrDeHxA2rgXWg02ejLfP7qqnWeU36O6qPj0fsRCkyQLTvMKy5CXb3m3laaUlmaBVNFuVty1BauAOT4cgk9zgYF5Ewo8HAghWjtcLxnLIkEeb5UStriW0N8CuCIotlo9ZlehcaVxppbTHty0OiDAIsXnke4mUJUA9aGWbHxaN3kTOJPnOHoRKBSJvxWF4Atj+FOg9xkcEDovwKHXvGeIKnSaWzGWr62zpZWh89827LyGGzleqIeXB5OtDfqux9qA/uoXP1BRa1WWTM5MP6fRZS1m9WBjYKHfzigmYv6Ey7PhaxCcc5adyXvr4qCvygJ+6bDZ9aUMk1jEpn+zpztB75+sGd/UGl8FPlTufZLgUPfKv6Ouzx6XdXtty/SmypCOMWYkQhj0gk1hV+FY8J64DxAszqkEXqL4wxjqw2sqaFxp7MA9iIfjuoxzYBLMXpGIRh9SOZWj7fKEKmF+s5TjgRkfd/CR22hd8D07PDl9lbc5XJLq5ua8t45W53Gf0+8YF5+UcEM19LxuVZj9F+kYW96VtWK0dmJGjKr8Zbn/t/OjbzV
*/