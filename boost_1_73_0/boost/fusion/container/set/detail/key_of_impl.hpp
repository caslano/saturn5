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
h6Hf/bxR/fvDPZ43l6mXy2EAXgHT4GrYDF4NW8I1MBteA9vAtdqOXQf7wJthX3gtPBneBIeJe0S/L0bT0cdDv2+xpmO63t8STUepXncmbAvLYQ+1R8pptcbb2KOcnq/xToCNYL4Jp9+iMNMjXIGGmwozYCFcg1xH8+JehqnGbMLsxDi62vrnIAsqZDV8Lefn625z6Wwz+tr64raH6zgfC5mYLpiRmGLMSswmzE7MO5jPMS69
*/