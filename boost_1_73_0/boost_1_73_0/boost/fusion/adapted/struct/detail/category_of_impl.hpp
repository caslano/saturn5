/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_CATEGORY_OF_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_CATEGORY_OF_IMPL_HPP

namespace boost { namespace fusion
{
    namespace extension
    {
        template<typename>
        struct category_of_impl;

        template<>
        struct category_of_impl<struct_tag>
        {
            template<typename Seq>
            struct apply
            {
                typedef random_access_traversal_tag type;
            };
        };

        template<>
        struct category_of_impl<assoc_struct_tag>
        {
            template<typename Seq>
            struct apply
            {
                typedef assoc_struct_category type;
            };
        };
    }
}}

#endif

/* category_of_impl.hpp
ON+Q/EePl6yCMEq8xHjF6px3BYVzTWAQZPXB6GPlAvef8jrQ/8BRhVLhqJjnOJmwE6yAo5HQ4b99yEs3mcdelHphYERIEQisS2+0WZcRssXJuGWcw4aiiJToci2szR6mYvXyHLLDKRzmt5XKIO1Nt6W1mqb6t5xR+xpaVTrkU8qLZTDXrA5OD5GGZRi9HvGLuiOcYaQSxfM/xygOP8ZukuhcJ6chw4Wz9FNDnwEFLUnHFewI7+ivswIPDrKlukn4Eix9f3BEwDSch35iOHpEccf95nyJfNd4elCMlbBze8qx7Oq8PzB6P+fa8XznwvO9dGU4RTGcdCiyN9ZxbxC76TIO4Nrxl64RU4XzK/smuln4ubeYJa4Ljp+EqLyL+LcGT9WCGaZuwuyXwbUbX4SJO+0bPwFQSwMECgAAAAgALWdKUp2jft0sBgAAag4AADgACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX1hGRVJJTkZPRlVOQ1RJT04uM1VUBQABtkgkYK1WbW/bNhD+zl9x8D4sKVQ7bQd03YphiuO0Xl3b8EvbAAEEWqIiLhKpkZRdF/3xu6NenLgNmg91EMuSeM/dPXf3kP3rHjz5aR/WJzj44Sfy/xF+8NoazY3+
*/