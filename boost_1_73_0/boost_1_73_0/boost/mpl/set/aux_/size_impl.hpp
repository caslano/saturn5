
#ifndef BOOST_MPL_SET_AUX_SIZE_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_SIZE_IMPL_HPP_INCLUDED

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
#include <boost/mpl/set/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct size_impl< aux::set_tag >
{
    template< typename Set > struct apply
        : Set::size
    {
    };
};

}}

#endif // BOOST_MPL_SET_AUX_SIZE_IMPL_HPP_INCLUDED

/* size_impl.hpp
YlBkgqjjinzqKCAg+M0ojqKAA4iCigqDOurzPaLgU17g6UNEHBh455yqW7fu7SUNhE/GSX809/bps1SdOnVquV1/9IQjd7fs07rlZs3F1hAL9fAhZJss+9phY8kCHzGlzPHuvWNOr23d6kW1jxe2bVnVVJ7CgiI1EVVD7RTP7fliwU0pPERzkZnCZT0oE8w153/UM2lmMNK5BaRMU781d8owr5J0oVkSzMBMeJl74WCrG9IsgTes7OsDK/NzMkw=
*/