/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_PUSH_FRONT_10022005_1720)
#define FUSION_PUSH_FRONT_10022005_1720

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/algorithm/transformation/push_front.hpp>
#include <boost/fusion/sequence/convert.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct push_front_impl;

    template <>
    struct push_front_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence, typename T>
        struct apply
        {
            typedef typename
                fusion::result_of::push_front<Sequence, T>::type
            result;

            typedef typename
                fusion::result_of::convert<
                    typename fusion::detail::tag_of<Sequence>::type, result>::type
            type;
        };
    };
}}

#endif


/* push_front.hpp
z2qUql1nNLughPsh3OvmAIUKhKkhZNOy12yWtNTibjz9SfaURdpmzEWaFUfPly6qt+LcLlV1lBNnTv9oB9BJxRaHdi5KzwDw4rtmnlAwGTc28RVrilhx+ySHwjxiaEy3fE8WZU4uQcF/bB5l+xGDowrgv1MutIrBCYVumIgkJsGS1SaFWixSxTt/5v8k4QM8hDv2DrF6VEm8yZQqDz8N96Pug595xe5gz0w324uQ2N7l/erroF+3Gv267DHO1fM5V7fNmLO++oyq7zNGu8HfrxUfoDPxJDT8tcmG8OQ75jbZEECdeIBjpiG3rT1y+S1lIyV56DwpdMSCe0KCJI+2SZY6Zfq+MypmgIZn3XglNiIxvCqGVxJPDk0tJ0PLESvf1GhnNGyb/2FqFHM0w8bYOt3BJ9Jb079vLOKNTgrk0crc+eKfzTzlk44zD7CESxDx0wK+c6faB66LBnzdRCbozx2UGu67Ms0ZCeiHZYIjUqkQRmBH00ytcBE8lFKdQYdTvjfOGZw0FEPkqPYb/ow1jsDgu7DmHZs6Ru46g44UjUkV1sfXl6IoiEklFXn7Qgbdw4+2sqfSJq7BIxqHrNqi+0IwuCLrzN0fmE380awtmi2xfI+vr7aWGJ2KMpLv6g3+wMwNOtkfmDUR1JHcsWa2zWkBfa6YdLHT7+2zmZil4Nw0LPHb2gsxH899pL2MaR0HZcGPjdw2OD0jmm3e
*/