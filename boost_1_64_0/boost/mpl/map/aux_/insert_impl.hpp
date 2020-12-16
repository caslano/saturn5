
#ifndef BOOST_MPL_MAP_AUX_INSERT_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_INSERT_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/insert_fwd.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/map/aux_/contains_impl.hpp>
#include <boost/mpl/map/aux_/item.hpp>
#include <boost/mpl/map/aux_/tag.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>

namespace boost { namespace mpl {

namespace aux {
template< typename Map, typename Pair > 
struct map_insert_impl
    : if_< 
          contains_impl<aux::map_tag>::apply<Map,Pair>
        , Map
#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)
        , m_item<
              typename Pair::first
            , typename Pair::second
            , Map
            >
#else
        , m_item<
              Map::order::value
            , typename Pair::first
            , typename Pair::second
            , Map
            >
#endif
        >
{
};
}

template<>
struct insert_impl< aux::map_tag >
{
    template< 
          typename Map
        , typename PosOrKey
        , typename KeyOrNA
        > 
    struct apply
        : aux::map_insert_impl<
              Map
            , typename if_na<KeyOrNA,PosOrKey>::type
            >
    {
    };
};

}}

#endif // BOOST_MPL_MAP_AUX_INSERT_IMPL_HPP_INCLUDED

/* insert_impl.hpp
uvaxXyR2wYGwjf3itA+71OV1KlurlG2SlG0CKYyymdLdlo1ZSXwrmxxrObYSZ3Eqq3p+d5leRGItruVX1uE7x7GxxxRa9kBMQatfxZMHWurAH53U56ri2w+4IGhLt54/3rqOOIxl/Y0vF315W3XkZ38uac58q+993/3z+ltoxCw0+mH8d2MZX1piGSOWtN1fsmrjuocPPLjk07GV1XsmltFgkOuaXO8yJObJd13GdZBnxjEEw/Bw7IFZ2BNPwXAswwg046E4H3vhQozCRdgbr8PD8CaMts5PTWqTclRIOfbFTClHipRjCCZgKk7CI3AyDsMpeCSWYJrtmXi5juAk2a76mfi+st1+GIPxGI8JOAATMQX7Yw4OwFxMwgk4EJcF+hZbiJnr2qdj01zHfh3blPckdf+O6nnUjUnWGMSqee76epDmeejvwX8LPp+6N8na92Mar2eT5vC6Cd3FLNacb49bbD/fsT/Ifo3sEymDVE5aSdpAcu4n0tbo2Fck4gLX/iINfJbK+1W4haTuO7JdWf9C1z4kYXy2ElPROTZSeKFrf5LGC137lGzhs0LcjrtIs3kdNr89fpKK1n4mjfPtfU1W8noTyRpb2cHrwAX2GEviAnucZdoC731QVrLO+gXI+x1o7YsSeJFrf5R05TMswiQ+M2Er75ehuzjN+ot866NiuJjzSCoiqfurNPC+jfctaO23skV5rfTxvtj//itJCz33Yclf6Lkfy4qF9lhQC693kIKb2uNCieguNpTb5F//FnNTe9xoGabzfj0WYSv+TLL2eYlaxPcOM9Bdv5dGPjfhCtzFZxtwO0npBxN4Cb/nsACH+FMUn7VgJqayzjTcxvsmnMz7NajuI9N6iWM/mYhLOebEqspJTXrMSl/0RV/+pqXr6/+mNEsHgE6o/8cr4/+H0+7PDSz/Bzp2TEGaMX/iuBOMx2adZByXl328kRE/yWMA6zVyQ9umuZ4yoiYj/cncAdf1NNjquLMlphAu45b1UFI69+VHWeq47jamDPnr8xj08Wy4xKlevVPyPEDyVNZr40Y+RTtPhmL1Pn96T45DLPuWUa7kV11bVlLNHzrmXSR1+lDJW/mwZzp/o513TcUZ3vMmD1ucJkLG2B8seSQrn5FHsToP5TtiLCkvH2wsMZvrjKVnGvPGZXrPR31cTWmOc4jWVJU7xA1kuGaJ1Uh/hTPNFfWynQiUsfoc+k9skfJPlvKfTOpF+Ztdyj+1wpzivczWWMy5/SmzaUZJ9VTHcXhNMxzndWcdimSPd9T34rMSe5ljZd/V5zVDAi5BUub9SZFKbGy4uzJbjnm9wYfvlBxvW57q45Qo42dMlzynkXqTZ4pLnvV+HSfLua2rmqUeozuJHEu4pLjEhirq6qtqHcfpNqnmr4/AgEDHMb+jpL8OFzWuGOpx9Ns/4+A7HNv1e7vOTRHNfm5o309lqHs3vxvv+2s9thdHsW8+jM3scL5lroJIKdOhpD5K3LC9TEzXvXtlkuuW8/zdDnM7B8tc/DkSH8xU1uPv1qRZymA582Wl3uOBPVXzdfB/mroSM2fUfu6dx692nYNeznHF7JI6flqWcUozOT7dKV8S7zcq5VE9o6XsG2VT9sUWL2zeA/FCjTEbNeJ8WvHFvy/+pxHn04gLasU1//1xwcOuUT7v90fNo9nzblty89NnVV4687jL9kxcMMYg9yZyz5K4l+pZeHmOyrpeiqx3gJv1YlXrZch6oR62l0EqlvUGy3paY2HGYx4OxOMxGfPROhZBs2xnsmxHPRZBmmznKNwfh2NPHIFRmI4pOBIz8Rgcjxk4CUfhyTjaNoeu/D8QgyQ/9Ry62ZLfWMkvR1XOFPm76W4=
*/