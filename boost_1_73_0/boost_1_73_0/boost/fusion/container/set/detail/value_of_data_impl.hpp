/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_SET_DETAIL_VALUE_OF_DATA_IMPL_HPP
#define BOOST_FUSION_CONTAINER_SET_DETAIL_VALUE_OF_DATA_IMPL_HPP

#include <boost/fusion/support/config.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct value_of_data_impl;

    template <>
    struct value_of_data_impl<set_iterator_tag>
      : value_of_impl<set_iterator_tag>
    {};
}}}

#endif

/* value_of_data_impl.hpp
ugcG4VGEaSxDG1SNA2/mdowE1dBMUoreALBBjnJFcRypQfFD7iZw9AzQCyBJT/j6dNF7BgaupjwIBY7koPRBXwuk0kjrSMDZu13s0cY/NsC6lFIcMV3LhZETJqPqdNGriDGg0ZBgiZUVdZqvzXjRgcpeyYpQRniqqWqsfbQpp7vrA0cAfgAkxwkC361rVDkxoLKbWbafCppJCktA4aI9uamaJjZ27oMzqNJxyDjWVgnML2+oJpEqwDxr7tEA8Mk=
*/