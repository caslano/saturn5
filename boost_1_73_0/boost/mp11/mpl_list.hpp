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
HWNwBo7BmTgB78aJeA9m4P2Yg3NwKj6E9+F8XIAP43Z8FPfgY1iCj+NH+ASewCexDJfiJXwKf8FlWMODY02sg09jU3wGA3AldsRnsSc+h4NwNUbjGrwL12IqrsNMfBGn4Uv4AK7HefgKLsUNuBo34gv4Gm7FTbgdX8e/4xb8ALfiYdyOX+IbeAbfxB/wLfwVd2L1KrQnWBN3ow/uwVb4NrbGfdgN92NffBdH4AEcj+9hGpag
*/