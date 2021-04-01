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
Wj5SUr83/D/oi2kfLK1WteRtSFEJDmZZm8xl66yNNw1gJ6w92baREuvChH+LyNLI3i17cA7sZhlMGLYuHv/eKluc+vh9nQsbWA0YVqyp+lDXdStGlCelPu9mbT+MDJvbkhONivOPnFTrtg3jvlGkoLdDsDm7+pIUMg1K/uoaTasD7igxlqld1IKghbhk3LP3OlinbTRcVzJ8njxi8mam7QwBdXeY6Qdpp0xXXeq3Gxz3Wp2fyGit3db9vMQGj7Y6F09jQZJ6xrNdiknBbpI0y1ZxcdY0JjseQd2tmvi+CQQ+gIc1KMNCwVvqXoOFr/sPF3nCDjrD2xTY7W7tUJqjOQgEkyQm+XXbFezax6tHR8YWqY8fzhOc+163WVgD/u5YwE3kfk//lUSuYgRh9eoQtXMBaNKGUBkpoodJLIHBqHecQHH8nCjnK2h0QshbRtBEMp1QRjace6xfkEVIMFQB9o0IvwpBa8s9URvwcrJNGUQqx+gkinHYFl75gCP20OXihfYruDJulaIVZM/bqDJlXF9/zVxcK5CZh6eLeI+WB5Z8cW3Tz2Y57GwOUw==
*/