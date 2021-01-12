/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_SET_DETAIL_DEREF_DATA_IMPL_HPP
#define BOOST_FUSION_CONTAINER_SET_DETAIL_DEREF_DATA_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/set/detail/deref_impl.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct deref_data_impl;

    template <>
    struct deref_data_impl<set_iterator_tag>
      : deref_impl<set_iterator_tag>
    {};
}}}

#endif

/* deref_data_impl.hpp
VPsFap8AO8Ayx17P+/6Y3o8nzX3H6P1L97jvt6r/jTAN3g4j+dqh4XrbB+ZrM/788G4YUntY7aIrG9qEewQmwQdhM7gNdoIPwx56Xq+n45Dkz0OOF6n+p3kwDc6HuXLviQ+SCWlnFsGRcDE8By6D4+Al8AKx16889vJRfuBxMAj7wETYG4bVfiY8Ae6D15nxK+qqxpeKWWlxqP4iGw7U8jhYy+MQLY8XwMZwGGwFT4f58AxY
*/