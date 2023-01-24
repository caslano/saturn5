/*=============================================================================
    Copyright (c) 2007 Tobias Schwinger

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_REPETITIVE_VIEW_NEXT_IMPL_HPP_INCLUDED)
#define BOOST_FUSION_REPETITIVE_VIEW_NEXT_IMPL_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/equal_to.hpp>

namespace boost { namespace fusion
{
    struct repetitive_view_iterator_tag;

    template <typename Sequence, typename Pos>
    struct repetitive_view_iterator;

    namespace extension
    {
        template <typename Tag>
        struct next_impl;

        template <>
        struct next_impl<repetitive_view_iterator_tag>
        {
            template<typename Iterator, 
                bool Last = result_of::equal_to<typename Iterator::end_type,
                    typename result_of::next<
                        typename Iterator::pos_type
                    >::type>::value > 
            struct apply_nonempty // <Iterator,false>
            {
                // advanvce to next position

                typedef repetitive_view_iterator<
                    typename Iterator::sequence_type,
                    typename result_of::next<typename Iterator::pos_type>::type
                    >
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Iterator const& i)
                {
                    return type(i.seq, next(i.pos));
                }
            };
            template <typename Iterator>
            struct apply_nonempty<Iterator,true>
            {
                // reset to beginning

                typedef repetitive_view_iterator<
                    typename Iterator::sequence_type,
                    typename Iterator::first_type
                    > 
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Iterator const& i)
                {
                    return type(i.seq);
                }    
            };

            template <typename Iterator,
                bool Empty = result_of::equal_to<typename Iterator::end_type,
                    typename Iterator::pos_type>::value >
            struct apply // <Iterator,false>
                : apply_nonempty<Iterator>
            { };

            template <typename Iterator>
            struct apply<Iterator,true>
            {
                // eps^n = eps

                typedef Iterator type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Iterator const& i)
                {
                    return type(i);
                }
            };
        };
    }
}}

#endif


/* next_impl.hpp
K4v3Dw7v7dzq3XQxUVyfvLB5Yy6FvnXt+HlMHXx/PTB+f1/fbQfC+9LftXeF6+7IKmJaPXBzrXdtbt7a/M8Bi4aL12FJv25M2TphXZR/r8wOkEKkhYcI4ofb6vJuE60VVKIDt6WsOpDzdD+hvdT900IOy/esPDZyMXa/NTxoUC9ynEUV9r3dw9D8xnghKPzobK0LKe5sVk6Vl72A7NVgUyfYPTk3zncdeSB2u7h0aPP7L5aMlH+A8lJdeSXvjXlYh3Fkd/nvvv5XbWX7soPDGRkOAxVfJ4W0hmlPzEXUfLpUj7bVcNWrPvdOqz69A5pBC7JX+p5HBa6RU5pbBtN5yukSZ+FNERcjAdgwrEWEicOjGSIsAeRs5Jk0PjK80zQ9Nz/SZnOkboEluLnka6IxJur4hbXVe6o1Y/HtSA2hsg619lteRlusCg3w8DZx6bDo5ivt69J6k/FoX/eXLBeEzwRywN1AceDbnppAl0X5W+SUhOXDgXHmdyUewbbkMF//T5NIF7aQni0ydFR51hYmvn/7318z1R2KiTTA5rPnra+0QQw3Y2hHt2pquyKythDc8w5yjopvnluKgGQ2RRC9QIB49+pGflZ0sW24wp5g+J4tbFV3DEcC5O8n8bzkNXNq1psfHpKlkYSzlN061oQ3ABxVizyM9avDd3xn3D4CeFu3b+vGctD5YJxgYqQV8PU5mbIycZfsZyOgcbjV
*/