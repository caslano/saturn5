#ifndef BOOST_MP11_MPL_LIST_HPP_INCLUDED
#define BOOST_MP11_MPL_LIST_HPP_INCLUDED

// Copyright 2017, 2019 Peter Dimov.
//
// Distributed under the Boost Software License, Version 1.0.
//
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/detail/mpl_common.hpp>

namespace boost
{
namespace mpl
{

template< typename Sequence > struct sequence_tag;

template<class... T> struct sequence_tag<mp11::mp_list<T...>>
{
    using type = aux::mp11_tag;
};

} // namespace mpl
} // namespace boost

#endif // #ifndef BOOST_MP11_MPL_LIST_HPP_INCLUDED

/* mpl_list.hpp
A1W1BdmXj5s02ONoTNy8uFGZezOCykyT7YSvDU7hKxXUoPN89pk1K0eWokTdykaUoVczE1LbSDReHgsZx3EUSERPNJFxIy1JvGGj5zuQXgG22822k1aeA1w2PoTTSXw4PbC8/v+RXiLcyYDjfMROSckQTuxwy4l0ZOLEbB4zVTXVMWBqTIcxUee/diBEwfOGpXYHgM1RQTHQd2lCA6InHCfFm4e83LuqrAtb7+lJAtOy4i7sJB5T2gnAAili/2P3k7QkF8U5oHKeWEJsN66oPJNWoq9pGy6WcdaII6vOhhFQ4e42l7MjA+SLauAfAXG0GI/+tJvgXEDXyZdKoKHcsSI5db0X2Ia3kgqStr/EeOP4q+kHTNmOrk3Rb26U4XeuKGXQJrYZ7aGdxPva6MVGICSK9LHMo6LKTsm54I6mz5v/q8h4TPCGG4qBb0k3z7w0o9wSKPyLUoG3Gwsa1gN7Ob+zB2zAozZ1XzlNl6IWUFxtXoN7fD6LcREJ/c/Kqc2JmPSC6yBMHSkgJjU40H/ketvlxDK/l7OfK8MMFSFKVnJqbBGgCLQ+8oCHpA==
*/