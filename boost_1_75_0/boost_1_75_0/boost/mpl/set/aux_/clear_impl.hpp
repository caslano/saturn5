
#ifndef BOOST_MPL_SET_AUX_CLEAR_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_CLEAR_IMPL_HPP_INCLUDED

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

#include <boost/mpl/clear_fwd.hpp>
#include <boost/mpl/set/aux_/set0.hpp>
#include <boost/mpl/set/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct clear_impl< aux::set_tag >
{
    template< typename Set > struct apply
    {
        typedef set0<> type;
    };
};

}}

#endif // BOOST_MPL_SET_AUX_CLEAR_IMPL_HPP_INCLUDED

/* clear_impl.hpp
Du3Pvowal20RQZSPw0vEbM+SFtaR9lsE2/uArMGCcEnicaHU2xh1ycenGgeHKvUb8DmCEyb0xwze6CUSx/E/Q/L/CGzxivxXyxrh9Hdgq5NdsZBhOfFEwEHzWw1XFxf+z+elVo97RdexCx/mvDSVXGVr3bskzk6+Fr5ZlJeP2p6rZhdyJaBDE32XXKiAXTHTzP2x7dUUIP+p5BU6FE3sYwhyC9kAoNhl++5hfex4/VIh11vmITRkrN/Ky+qZ1uJzWu9a7lwOut/3oA5AnBZRNzU2583Xc0XFVk/8IVm3/CFZc0UNFhoZwswfnn1MumfJmvxZsr5QdQPGW7/jp83EHY8kGiAbkI5s6UNZEh3wXW7FOsMB7wNKueRFRzH/0LVGNZ51LWUf5vJ0Qd6/SdZtreeXedGH6Vm3T6DMlYuqMdB7DgsqYgtgqomeYFix61roUjTGEl1Smq7y8P4nlKfVdCupMb0PeUy40lQXv6iDapz8TbysnfwHpYEJ+ulo1g5T+roVcHBkWUYNqO521tlrx9F9/qGKCkGz9dIKFhAwO/15ZwueJ+dZ14daUzUFIndprVUOOus+mK2axXnTOVKmXZk3kzXeCveiMzDvlD7786nczZ+pyO/iz1srfRvwrjWr7Sveg0bTm+pWHtr+zCV3KlsnUzU7obvKehz0oyTvxskVZeXZ16qKRZB7G8vANiKX/rwU4/2nC+YttkiO
*/