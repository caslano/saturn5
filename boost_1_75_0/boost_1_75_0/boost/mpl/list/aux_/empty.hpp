
#ifndef BOOST_MPL_LIST_AUX_EMPTY_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_EMPTY_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/empty_fwd.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/list/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct empty_impl< aux::list_tag >
{
    template< typename List > struct apply
        : not_<typename List::size>
    {
    };
};

}}

#endif // BOOST_MPL_LIST_AUX_EMPTY_HPP_INCLUDED

/* empty.hpp
ahfoPQb2y17nbXktdJEceiYlGDIFPfxSCDA5ED1UswwsxGZsLpF6Ac6fGO/C1P5G2fNH9AMY/5ey6f/3qj5NZ/vvbtb/mqXvbTDsIe7WWt1usZpMFUxlR2JOpt9GP6ErF6gA+bIUbywp95NYx0hxeX7AVmc10kHys/a3nPQBWvRMgeh25W/ZZRjZJri31vClHA6K0r/uP9iQrv0csskWsAk+tFOUXnmzsvT04FBu0p56an35lXW1AfA6nMwZzRHmtfIE3h4g1AfuDyxulyjaMBHMra/ysLYtoGDwfMX7uPC0vmovoJP7LvvaqSTxgTiznVQs0bPbZ1r5T6XBPJ+EC+C+VP41H7bqWMNkX4EZjkXYrqnk+4XUW99Js85RLT/HjucZ39lTPWnp/H490nIrJ/B6ns5uf6O+TW4o3Oj9tLhaGWvKF3ae0uIVGlu8w8xuV7QvLywE/95qbrDnZjnoxhZa+Pti6+nq9Gplv7sf4JdVW5mM3n8Wtjxqf9L1pwlm+SCddbI67SeEmZwTIvYgMb2D7dazDqad3oAjzUsVt1lJ/n2rfHXkgEf+/CaVom3PObeLjWMidony0bt7Ko/6k419/zGf/p7hzm4woK4VwaWR+La53lxCWP81O/oWYpsA5Vm+uIzNw8sbqMBbnJaE1hK+dgc1s1wbTbN2JsPykSrgJpl8/kxtNIKm+BLwCIuN8pBq+XMDvjPBjm0f
*/