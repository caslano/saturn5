/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_IS_VIEW_03202006_0015)
#define FUSION_IS_VIEW_03202006_0015

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/support/tag_of.hpp>

namespace boost { namespace fusion
{
    // Special tags:
    struct non_fusion_tag;
    struct sequence_facade_tag;
    struct boost_tuple_tag; // boost::tuples::tuple tag
    struct boost_array_tag; // boost::array tag
    struct mpl_sequence_tag; // mpl sequence tag
    struct std_pair_tag; // std::pair tag

    namespace extension
    {
        template<typename Tag>
        struct is_view_impl
        {
            template <typename T>
            struct apply
            {
                typedef typename T::is_view type;
            };
        };

        template <>
        struct is_view_impl<non_fusion_tag>
        {
            template <typename T>
            struct apply : mpl::false_ {};
        };

        template <>
        struct is_view_impl<sequence_facade_tag>
        {
            template <typename Sequence>
            struct apply : Sequence::is_view {};
        };

        template <>
        struct is_view_impl<boost_tuple_tag>;

        template <>
        struct is_view_impl<boost_array_tag>;

        template <>
        struct is_view_impl<mpl_sequence_tag>;

        template <>
        struct is_view_impl<std_pair_tag>;
    }

    namespace traits
    {
        template <typename T>
        struct is_view :
            mpl::bool_<
                (bool)extension::is_view_impl<typename fusion::detail::tag_of<T>::type>::
                    template apply<T>::type::value
            >
        {};
    }
}}

#endif

/* is_view.hpp
66j4bk98jy4A34cWgu+4v8D3ncWc7zNxar6lunDlOxJ8X9Lwfa+ayHd3iW/VpXcB8qV3AYVMeW3YQHdxtMgnfrGs7MYIQybx4+FD78o5e4ty1kOlmL/8D8tZEgPxvdwklrMYYWUecuazmE+Z7k1WlN1AUnZtwqz7amXXb7urEn4tWeYrQfhmIvFlEw79JfN1APNnlaJ7/DHjK4+B+F4/4itBKLzD5//JxFeCMJzzNU7qnFJzd9yTmAq2E1NLt7ky9ZLCVJzQWGaqqcLUn8RUdRVTLYmp4cRUnLDvHRxMHc+ZEhbxTWXHJjkzFa5h6vFWV6Y+X8SYGi9KL7a0vDyW85WaJ/PVn6a+swIUvtb+zfg6woBefY6xRu5Tt8Fdb+KOfBu6MPjFXTWDQ3UYrKwwyOzzf73KGbx3R2YwgRj86UWFwb/zGYP1iUH26qwFyiHnxpzBbQtVxv95E50ZrKJhMP0jvYlKhCm9Kim5OKp/kY/vQvlMVsN5bERm/fgHC8tqlRby8DbChrGtNGX5xXxI5yXz2XAcUORzNIlL5Y2xfIamGc8+us3Gs8tb+J2BZ7foyDJJeEOW2YWYCSTLIqT3X7kt10UhMfiaqrFMfMQYW/kIesKDeawR24VNt1ALDZK4vlAiVj5RL5ElKZVTgidLQZJZNQREs3Meu08yShx9BdYrB1F0duliFb7/pQPG4N+dx+D4lmwM7tySj8E/
*/