/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_OF_05052005_1126)
#define FUSION_VALUE_OF_05052005_1126

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/iterator_base.hpp>
#include <boost/fusion/support/tag_of.hpp>

namespace boost { namespace fusion
{
    // Special tags:
    struct iterator_facade_tag; // iterator facade tag
    struct boost_array_iterator_tag; // boost::array iterator tag
    struct mpl_iterator_tag; // mpl sequence iterator tag
    struct std_pair_iterator_tag; // std::pair iterator tag

    namespace extension
    {
        template <typename Tag>
        struct value_of_impl
        {
            template <typename Iterator>
            struct apply {};
        };

        template <>
        struct value_of_impl<iterator_facade_tag>
        {
            template <typename Iterator>
            struct apply : Iterator::template value_of<Iterator> {};
        };

        template <>
        struct value_of_impl<boost_array_iterator_tag>;

        template <>
        struct value_of_impl<mpl_iterator_tag>;

        template <>
        struct value_of_impl<std_pair_iterator_tag>;
    }

    namespace result_of
    {
        template <typename Iterator>
        struct value_of
            : extension::value_of_impl<typename detail::tag_of<Iterator>::type>::
                template apply<Iterator>
        {};
    }
}}

#endif

/* value_of.hpp
oians0SqPjTRy2NeiQKR1jOhFQp9EdZH05Harc4YEhPqW1ZShDu+bTUIXW86dFBPEYbMvSZec9XH15EsijaFvU0oDuBgiQhbGBPJi1AF+LFcefY4I3Ime/pAn9hrzlWL0P3apHwR5CdJwaS2LbICbsHDsZNWVksy2c+RijpGQFbjY4aCHqokmWHQGVd41cAALLGSavUgFvV/cQuMEk2mqyZwm665y1zD+PRRzd2LskPmrvFKU2CmW1hLMOcYLHaWNZQR8VULTYcFCHt1yaNm0x8RwTWFncBVv6O6AiizippsocixnHQdfvx93wACscmhrqX52JKTH6dQBKvsknUQVwPnMI9GHJAsLjwjle3kCYkWgmiTQWtMCkx75VdZ1gC0mis3u75qQfSdkedTM94zQPq8g3y8zA0BuLEsnIYz5HLxmfsFjUYDw9RycdwignFz7vAXjPZrpkI+zPX96WG6FZvsVfG3uHxxyxWbsxJgPsiQyNwzB4D65kf8i+VAMBBJ7GyOsrs/ETtchjx5DbhOON+4zSUEjnJ/mY4Jvy+DXc8XLXXGlSTUSiwdzg==
*/