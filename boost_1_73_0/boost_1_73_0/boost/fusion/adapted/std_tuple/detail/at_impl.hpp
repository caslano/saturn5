/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_AT_IMPL_09242011_1744)
#define BOOST_FUSION_AT_IMPL_09242011_1744

#include <boost/fusion/support/config.hpp>
#include <tuple>
#include <utility>
#include <boost/mpl/if.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace boost { namespace fusion
{
    struct std_tuple_tag;

    namespace extension
    {
        template<typename T>
        struct at_impl;

        template <>
        struct at_impl<std_tuple_tag>
        {
            template <typename Sequence, typename N>
            struct apply
            {
                typedef typename remove_const<Sequence>::type seq_type;
                typedef typename std::tuple_element<N::value, seq_type>::type element;

                typedef typename
                    mpl::if_<
                        is_const<Sequence>
                      , typename fusion::detail::cref_result<element>::type
                      , typename fusion::detail::ref_result<element>::type
                    >::type
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& seq)
                {
                    return std::get<N::value>(seq);
                }
            };
        };
    }
}}

#endif

/* at_impl.hpp
SDXlKypvXTgt7cofNbm/9xT94ALVQBrvCWBWMwVKVHpDJAV8blhBuaIlEAUlVYVkK3xhHHRNoWINhbN4tgijTy5salbUA85WdKBq0TUl1OSOgqQFZXc9TEukBlEhAuKXTGnE7DQT3EP3FDSVazXAmCBIowSQO8IaskJ3REOtdaveTSZFJxvMZFKKQk2KHRVerdfPslpgNGuyBdFq0AI6RV0w511Yi5JV5o4U4WLbrRqmavcxLHTIy4mQoGjTDHBoyqjqU6CQDmy55iS0GD3T5qYEV8bbphbrJweR1gGo6iRHd0gLnisFEu9Cx0sq7XlLxM7LwLKl/Acle4y9BMExKhj5KYTpCFZEMeXCTZhdxvMMbvwk8aNsAfEF+NFiwLsKo3PUBkOvEuh9K6nCKCSwddswWj5x/lM73fGySzibJ9N4luXzNEj8T0GUwTGMjk7gz46jsI9+HcGoYStTeTjxjk+8Q1wwbzklapsrqk2N8YtyUoiYXkLkXwfOS9jlAZZUw2WWzYwg5AG5pRy1RQnybw3TRRTP0jB1fmG8aLqSwqnx1Muu/uBY0ELg+vMAxmYH9msURIO6eOEc1VcTCfsd2XtvXZ0H6VkSzrIwjpwZQb4JtIJxbZSA4gfeNc2B0QPjxJTVFJjfDs1E1hS3
*/