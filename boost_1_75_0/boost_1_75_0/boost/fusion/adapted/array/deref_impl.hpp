/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ARRAY_DEREF_IMPL_HPP
#define BOOST_FUSION_ADAPTED_ARRAY_DEREF_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/remove_extent.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct deref_impl;

    template <>
    struct deref_impl<po_array_iterator_tag>
    {
        template <typename It>
        struct apply
        {
            typedef typename
                add_reference<
                    typename remove_extent<typename It::seq_type>::type
                >::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(It const& it)
            {
                return (*it.seq)[It::index::value];
            }
        };
    };
}}}

#endif

/* deref_impl.hpp
DOeqbU4O57XlMTuyGp6AM2Iwx/TwaIfS7WjJ40LOBCjFXbh7GSyUXY/YkDINznL7qEwE24Vk2Iz5OKInH43j7HJayq81AYyfq4C7elNNwB5r63EkzvK3fbhAKWl9zq52FBw7Hm8iiBfnseV+EKwsXKqjJ/0Zh0boaDt2iImTOIApK6e8CWzhL7M46DZY0JQPd9C1BA3nTV9mUVgCihrzXwsZuuD8bx/Cp4LUVvczaas9qtSj51sFgx2D0BgFrWsUjRrbRgdJOCISBEgmoa8uy1u/exNNPWfT479vEsB9RD/vHkc/36Kft45Dgpbqayg2OabyGqBE6b7I1A6Ogia+e8M6uMMKYn33RnZwRxZE+u6N6uCOyo9zB5anF5VFuovO2F7Yimz0yrZlK+uST5+vMMqnwSPYJJ++bnAt+fQygAxLweOCQ5BQr6TTYwhQwkE6HaOk0wAKLPXTPz9xJdLpXq0vJp0eNdKgf+IzkFUOd1cYVQ4CW1oOMmBL8oCmKqJHQiFhy+x/EVuW/IzY8u7PTobcGQMJW5IDzt2PMbYkawu6BGNL1BO65Y0o9/2dMrDQPuotYplG8IK0wJSPJebCaMG6jjAQDbV88GKserG6a6FVwea7j6tkzrXgbbVSUjS5qbaSgpbu/hG6nZFp3237g/USZk1Ny8dJU5Osa2qSUwYUFrwC5/kbhnvVW3IW6jhfShbx3Wu0JuLOCghX
*/