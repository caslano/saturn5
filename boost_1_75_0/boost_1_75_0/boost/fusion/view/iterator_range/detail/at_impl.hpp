/*=============================================================================
    Copyright (c) 2007 Tobias Schwinger

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_ITERATOR_RANGE_AT_IMPL_HPP_INCLUDED)
#define BOOST_FUSION_ITERATOR_RANGE_AT_IMPL_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/advance.hpp>
#include <boost/fusion/iterator/deref.hpp>

namespace boost { namespace fusion
{
    struct iterator_range_tag;

    namespace extension
    {
        template <typename Tag>
        struct at_impl;

        template <>
        struct at_impl<iterator_range_tag>
        {
            template <typename Seq, typename N>
            struct apply
            {
                typedef typename Seq::begin_type begin_type;
                typedef typename result_of::advance<begin_type,N>::type pos;
                typedef typename result_of::deref<pos>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Seq& s)
                {
                    return * fusion::advance<N>(s.first);
                }
            };
        };
    }
}}

#endif


/* at_impl.hpp
3BzAHVkKqIUJlG6wDAQlh6ZGjSzC0bJ+H0C6QXw/QcuaAiiRpyF5pSrYl+jXR/+mYmVj/0jGlX8+VSw/YPbW4m23CgRNncgLtDO4gU4GDyBzABmedljrjX0G2a4qAGnkLbO2pfZBej0C1HRke6T+dFQKV6sEfQF71TItK5QmmbYhDcUPZbd8RYqRUr2HG8mluQDLo7zuPsSDC3xMA95X8kLev3o8kPW17IyENzOlWn0uW+d8QUeE70AK0YqxGwqRxrJbGKiFwS3p3YsbnX6sdxWO8Tp7kabza8ff6GQS6LJx89SFfU1H/QuA2abbAbAtWg7ivzBGjSTzwa0GGX+HAP4GaySiRTkerHMhmzqswcJYXdn06O/AN7pCZpyzc1IUCGtsTd0h3IqAWe+p1wOWVeeZ58Ewqo/kcRJjVzq3DpA+5RM8otpJHhsodVJjL6NzeWReOUDkbEYRjMwA1CrJbdot6r3qIPA101zcgtpiyPOjuBsOzNFhqy4+++924MLX/+P1V0enDrT1x1Kxqif8xvxV3zDG7FfnL4xpo+2nq/IeqyvAkfrlUjNOd/Vqn3fhYiqcgUMJnyCEjWYIwXI1PMw03gxLfme4hXM9HFFFLEfCR44bpctvFVj7x1+7QfaJLBvtLJB6obw+XJFsMgOeP8N4qZJd7dxn62JAUStr1f7gYa+Lu87HwLPnM8Dbn1PPAW/+ZuoY/97zUZRl
*/