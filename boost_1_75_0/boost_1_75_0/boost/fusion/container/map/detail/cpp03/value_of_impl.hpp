/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_MAP_DETAIL_VALUE_OF_IMPL_HPP
#define BOOST_FUSION_CONTAINER_MAP_DETAIL_VALUE_OF_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/value_at.hpp>
#include <boost/type_traits/is_const.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct value_of_impl;

    template <>
    struct value_of_impl<map_iterator_tag>
    {
        template <typename It>
        struct apply
        {
            typedef typename
                result_of::value_at<
                    typename mpl::if_<
                        is_const<typename It::seq_type>
                      , typename It::seq_type::storage_type const
                      , typename It::seq_type::storage_type
                    >::type
                  , typename It::index
                >::type
            type;
        };
    };
}}}

#endif

/* value_of_impl.hpp
K/pTvcrtaWFicEqgY+hseytfgZjgWvQUhuLcJm5WLksz/FekroHbNxgaFJdAzfXMEYeF6q8ruqyljXixkdvojqtzUB1V8uJYDA9U0pBqwPaek66PBbqzZoF6P+BTCei2CiKs6/9h7t3joirawPGzwF64uaitoqlhoVFZUnbB7MIa5GJgVFa8aUk3ozsZFJYpBhi0YlhaVvZqZWnlW1aWWqaYppSmZqWmb0VXD1FJVopZ7m+ey8yZs7v4Wt/v7/f5/QGz58ycOXNmnmfmuT/e6qcM0OYd/yuElWtHpvocJ8kg9u7x4CdlYXREwff8Dm32CQSt6AkCiHYpgEgjkXcQ85iUBIa8GwhuLXebF/eUAoi7QQDRXxdAPCz6an1DCSBKQACB4jr5sK+nJYCQRsTXiwGBAKLUH9oACxfKHfKnt2oZ66BtBvLKM/HuOKrN9JPRRAVZ7Yi7Q/wgpPCLbTYPfKNBSCFqvkPj27w0jr+P3SWtMvsfiZYpIIXNrGp3gPhhr7fmesTzj8kEZ9Rt+wSuD56QnuatfjiG3ppFos+SfnCWrSPVLADbFfD+ofD+oeL9F3vAQmg31kDytWCTuIcyoywUix/xAeXjxEyn3tqFschdsFFummUJJT05HyYjVYySY3Pyq2RJmPaM9A29JfyZzVxxReQz0g3z/PBnmrni1MhnpKdiWvgzMkZRp8hnpO/jHzFhz8iYSGZMxDPS
*/