/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_SET_DETAIL_KEY_OF_IMPL_HPP
#define BOOST_FUSION_CONTAINER_SET_DETAIL_KEY_OF_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/set/detail/value_of_data_impl.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct key_of_impl;

    template <>
    struct key_of_impl<set_iterator_tag>
      : value_of_impl<set_iterator_tag>
    {};
}}}

#endif

/* key_of_impl.hpp
QxHkqjkT5GztBIpLWRltMAk4mC/YtZAHgxLYk65TfoUjYawlPBEQeOS1H5OUR2F3JcHqJZvxTMCGBf3ibelF6Mwd8md5bG7wIHoQkrZ0L6ScdVFi7oYiXqHJYJCTBVSTqHRD5aZQQwlX3gyVR8LZ380SaUmC+VJHGMERhfiybXHywxksvdWT/gqFGHYwsS/dbyn5i4gH5U8iQVZSYl7lhEIiWd2pHmprMMH4GdxrsF6KKJML6t7QdEtrazBMaM1OUrwjRs25RrrrF4fzS5R0HDlSsH/IIDUonWWjsvKCd2bbko7TBnzeRNqVvqkh4dOXVVRuq2K3io1V1ODdGtyv3qZicQ0F748Su/+9/3YJi92PGVxMGbz/u6uBWhrJmbo/Rj1Y1r/hS8vHw/pMVGS3FsZfkfArSJ03ot3MfSpEOb0vx96g6/uvPpxM3nHHdhTN//T7pMRwwH34mf3u6zhHwec7w7/TlqPgYHFkjgL4yL+fo2Bh8eFEaDipf0dfVTxBftVlE+BzonxLZ9u3gK2hfc1OLo6yZnNwzUYH6i9shz0huFbsCEv3JrCogGAWP6B1TNRlsbJL4Afc2q+jD5hzr5bbywM5g1SOkqIdXbQcJZAdVyzCUliEpfDm8eLNIN1Wi7DXz6vgrTlAe+nWLqRYSTMX+l1GAwnJctIpM7D4VwSyscfv9ZB/LAYdxLTIMO4080cwzwGC8ljxpqWe
*/