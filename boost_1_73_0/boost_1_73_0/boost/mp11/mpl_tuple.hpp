#ifndef BOOST_MP11_MPL_TUPLE_HPP_INCLUDED
#define BOOST_MP11_MPL_TUPLE_HPP_INCLUDED

// Copyright 2017, 2019 Peter Dimov.
//
// Distributed under the Boost Software License, Version 1.0.
//
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/detail/mpl_common.hpp>
#include <tuple>

namespace boost
{
namespace mpl
{

template< typename Sequence > struct sequence_tag;

template<class... T> struct sequence_tag<std::tuple<T...>>
{
    using type = aux::mp11_tag;
};

} // namespace mpl
} // namespace boost

#endif // #ifndef BOOST_MP11_MPL_TUPLE_HPP_INCLUDED

/* mpl_tuple.hpp
5pDMOkPmSp/MbT6ZK3wyVcLb9ot842IuyVwv8/n95lkb/ONrHsm0MvQz15fP7SSDd1ZxnO746a0T/fncQTKFRj63+/KZTzL3Cc7nd9u/a+vP506SCRn5zPflc5cw2/VElyU7/Pn8iWTSDf3c5cvnbpKBSpC3ONJ6wEt+v3EPydwtdH3u9uVzL8l0kflMmLqhjz8farXzupHPvb58FpAMWj625t7s0lX+dt1PMmcY+lngy+cBkvlB8J251Sktl/o=
*/