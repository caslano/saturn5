
#ifndef BOOST_MPL_AUX_RANGE_C_EMPTY_HPP_INCLUDED
#define BOOST_MPL_AUX_RANGE_C_EMPTY_HPP_INCLUDED

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
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/aux_/range_c/tag.hpp>

namespace boost { namespace mpl {

template<>
struct empty_impl< aux::half_open_range_tag >
{
    template< typename Range > struct apply
        : equal_to<
              typename Range::start
            , typename Range::finish
            >
    {
    };
};

}}

#endif // BOOST_MPL_AUX_RANGE_C_EMPTY_HPP_INCLUDED

/* empty.hpp
t6f5TNnCRdJlSVfAcYj/FUQjdwyD/wuIo5rWWXD9TxCn+PMStzcytjWTNXK1N7EUNgeaOUvbuwCNbG2ZlcWFxeTEmYAewGiVq8h5IYw30l8wlvcAAm7406cg0ff3dMinCMj5ZCUrVh3ua1lm7nOQ1zMHTukzLYFrHbe7w0lvB3NmQlO5WtMjD4s35GC4aLhge7mNycCHJ2pRYuoAf/o/6PczPmBiSZMZWoCMviELzzoc4Sy/2AuIsARH1n+NLOHw2Xbkg9THGB467RyPv/PFD2wgiTDb0qXRlNj8OlNcOabI/0ep1rwB3OL4npV0jCevbduxXa2PGgGvoKY6fTnkC4RfmkZN8xXWVBAGnJnMABPxeaHmIUt27NJRHzw0nlCTnL4uukUpNOeWY6/A00mF32VVPWXPCjgndqLe5VPvumZ/zNpkQzT3GobC3SEmboVqVQ9YZPb3qHxg0ZOkR3sBLRgvLLMC1ZvqQXqGh6Tq8O5VX5CH65TSBdRSJonkchJ9UM9dkxedhOXDP30+XLztmKlHxKOIIyNtcfHxamw3JEbdpQuO1FNH/ra7ZWqiufC2cob64dHCtfiqViGdnsELs8ix9bMkYnmxVbkRkejnKLOb28LpP/4slzdF/H1tGi/eW5q/N0lNU80TRz57U86gLyeTBnq/Yc/riQzC0QJMlr5NyoFc0FGKag7/0L4gTkQZS1QuGbvGeilDdBaW
*/