/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_MAP_DETAIL_END_IMPL_HPP
#define BOOST_FUSION_CONTAINER_MAP_DETAIL_END_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/basic_iterator.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct end_impl;

    template <>
    struct end_impl<map_tag>
    {
        template <typename Seq>
        struct apply
        {
            typedef
                basic_iterator<
                    map_iterator_tag
                  , typename Seq::category
                  , Seq
                  , Seq::size::value
                >
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Seq& seq)
            {
                return type(seq,0);
            }
        };
    };
}}}

#endif

/* end_impl.hpp
ypJHUp8a3h+2D9++hKjocuSR1FmkvGeHWm3i2Z3Sphx5JPWZ4e/rwaTqnxE1oxx5JPW54e8r43hf9pS9tRx5JHVOUPkaPmArS5fKkUdSXxj+eVUqVzGOqKjy5JHUecPfV1LtQceIaluePJL60vBzdZj4ZjmiJpQnj6S+QspbkR474Rc2Vm4uTx5JfY2UN984NCUinKjT5ckjqQuG92wRTz7Fnui9rzJdyEZ9Y/i5dq6ZztZS6lYgj6QuGj4SffE=
*/