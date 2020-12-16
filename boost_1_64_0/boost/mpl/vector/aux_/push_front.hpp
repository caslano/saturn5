
#ifndef BOOST_MPL_VECTOR_AUX_PUSH_FRONT_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_PUSH_FRONT_HPP_INCLUDED

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

#include <boost/mpl/push_front_fwd.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

#   include <boost/mpl/vector/aux_/item.hpp>
#   include <boost/mpl/vector/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct push_front_impl< aux::vector_tag >
{
    template< typename Vector, typename T > struct apply
    {
        typedef v_item<T,Vector,1> type;
    };
};

}}

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

#endif // BOOST_MPL_VECTOR_AUX_PUSH_FRONT_HPP_INCLUDED

/* push_front.hpp
+06KyJvEo9/2MN5j8Ssmq89c/Irkn/A7y7nfFng0+OYsePtV8JIe2KE4d3jbr+jPeOqG2ccUOsRCPWcL8cMz8DHst66+ijhoNPmns9SFh1FXHsB7KrR88B78hwD00HrmUatH9IB3y4FnbsR/ilS/bzGjl0cwzuPYR3uuP/ae+1WiT+FBvFfCd3lSr9Jmxo/m/shTnAV2cTz7gxPIa8HjRR6F5ztCnI1dzf8Bu+NMfjoQ+7XNwP4c9Fs4ebs3zGp8ksgbvUVd4PfoCeTVaRTrhvZ5k6/r/IJxZTw7p8HrNdPv8SbypwOJd4hzrLFfx8gDF6AH8WOKyFfU5bIvr5b4Ez3hBH/o9y3rB7lw+xf+wyx4hLP4XdfBS5KPMmN3a5zZV+GFP+qLHX2RuGgYdm8SeTHaF/1P9N3vyHEY/lU4PCf5oHAL6hWOcB/2FYfzPiEjfrcXfnfRN/gL5Nca8aOTXNnv8jVx70jksAr/s5Z9HgHwRi79qc/U3rdF/dgf6J0g6nuS2L+nw97OZL38QDw0mXGH78ln/7fZlvXuw7w1Ia9PWqhxOU2dLO/38uY9RH5n1XPtPlGfx5qJ87KZj5/YV3sS+WL8Crbg1waRX/0c//Q33iMAj5Dggv59lDzJAPT6Lehfjccgr2u1hrpd6lv3k48suA9+L4n+UceS8xF+vQ98EvWoBe7Y6bcZx5/x4+Zhtzpo70T4vxw99YDo+x+ot6R+qWgD/oK2j/s56iVr4VvfIF4I1KFvaD/5lzor1u0vzFc0140k3mJevftj52lPix/+HPsSbPDfPW4mvqnA7rxCHqkdv2AO911Bf/T4gbS3+jj+wnE1DiXE040Pk0e/mXoWePboF9Anfib1/T4zdpI8lvZeDfy2I/dxX+v+vBcNfmAtcckj+HE74Gk74dOjsIO15Oft8ds0HqKLemriEPMT1MvhvxqJRx3Wou/Zp9g9hHqAU+y7/5S4Bz7Yg/o9F+TDowr/YRTyCs937BQ8EvVuPvTH528T+W+N3yTO+pF5dMCOwt87/4F/h95Mn0we7GH04e3M8zjsJ+PZjT3J+tjAe7ng213x5wZT5+iPXqPeNtmuvxq317EnrLNI+LeW3fitJu16Nc6BSeh/G9rnSn7rDONEnX2gjyV2lLws+09qGI+Ul7Czp5Av1lUSdWD6eNazfz/ydDwf3rcBfsOmEr97r1nJDd8fqTMr/6SA+I143OsYeg5/vuBX6kuoD7RCT8fBH6S4ktcYgH3cquX98PNMxIlmeIFf8PPw123vII8ZRJ7BkXzeUNb3EnioVPKmy8jbjlH33foD4/GTtv7hRd6mP1HIVRU8xUsaT0scQPzuUMw4D+J6/KLKJegD9KoxhDq6udRhvEjdIONsLqMd5Bv1X7MebscO+rOu8QPyRxvI8xCH/AZfjz2PG07+1XsQ+6/6M27UiWD/GomnllFv5tyInfnIAD/MvJczDi3IJfxtKfuA47T9rk7YQzP3YT9rCvWZpRMs1Sf1PSVfMJ8fwLe9QtwzEbt1gLiE+NgZ/urQGfJKkeTZ2tjntpT1ZYH92E8+4Gni9Gfxn5q4bgLr04L7knetuZv4nDxa5CF4c+xtOvV1cb/w+QRx1VH0fjN2Ixp9/zN2nve46W9ATpjfMvRK9y7y9pXI8STsxwl4R+pJjPgBWZvxm96EX7yOPJoH9/8Dv9geu/y71k94798Yj38wnt3IIfLn8Cn52QT0/DHqQpoHUXdHnKDl5Tqx7zHwGusZB94fWLQFftyG94KQn3R6jveM3UyceyN+BXG0ETtRbI8/24C9/hZ/xoP46jr2TW/BD8hlPnbjt5AX6H4Y/eQAv4K/W/MJ79VdAD9dhVw=
*/