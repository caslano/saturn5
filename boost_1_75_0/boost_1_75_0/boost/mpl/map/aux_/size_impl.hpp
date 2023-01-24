
#ifndef BOOST_MPL_MAP_AUX_SIZE_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_SIZE_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/size_fwd.hpp>
#include <boost/mpl/map/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct size_impl< aux::map_tag >
{
    template< typename Map > struct apply
        : Map::size
    {
    };
};

}}

#endif // BOOST_MPL_MAP_AUX_SIZE_IMPL_HPP_INCLUDED

/* size_impl.hpp
TnsxJwcKgQ5vRu71plNUepMmTNScvrjEdSn5jnEoqDgrLw2f4vr7tbV1fwjc6symz77b7G7Tvmg36My5KNcFMczMUh6SP3MMwJ2eyx3bJ2QalOvaFPpGNafSDCh53TSg7SsG0gVllbA+cRPni59iMwUU5K9aoOzDQrqUlTjhp7FN1+SaNXQgx4Ik4fALMsJh7jJ9RFKxQSvzaccW1ouUCFe2PcDjSEDRgownG0lUEbMwjUScHJa7UMtW1n6fJcBc42G6MtM8/Ih5VMJHp7mf/aTa2tjSLMKeetCUYnyhprqcDezZgq930uEfaPpRSrk8x34o0cJd6/BpcQgjqMSe6CtqIXdMNReHhH9UV878BJW885hBpdaZVDnI+KtmU64Zc+8Yw/MUK0UTXAPxqlrBq+qEY631xnYuw4MQxnhnrjTnXi5ivNNj3JRBDA6z9zNpweHpGaFU4MI2wDuLseGpkNvbwoyZoSJua9PiMmbyjdKMTylX9fZv0r9QR4R9HDH/IWylEZqi8blyTdD9PV9ceKHuFcVYab5jRqgcSzdJH7eNhqLz0J4WF/pltOivd7swpxEo61FGx/Ou6nOf84ig2bk9CTAaVOKasnOfOWPQjBsc6rlX9FmAnxW/nrCdSjO5Nuf18KEIdombkPqQiOPcFV42kK2cuRdNNoncDzgklWk/NsLEjHfDhSorYZJAvxJ9lvTYr/F5hpyNykj6
*/