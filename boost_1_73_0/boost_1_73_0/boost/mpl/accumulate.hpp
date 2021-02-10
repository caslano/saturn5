
#ifndef BOOST_MPL_ACCUMULATE_HPP_INCLUDED
#define BOOST_MPL_ACCUMULATE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
// Copyright David Abrahams 2001-2002
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/fold.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(State)
    , typename BOOST_MPL_AUX_NA_PARAM(ForwardOp)
    >
struct accumulate
    : fold<Sequence,State,ForwardOp>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(3,accumulate,(Sequence,State,ForwardOp))
};

BOOST_MPL_AUX_NA_SPEC(3, accumulate)

}}

#endif // BOOST_MPL_ACCUMULATE_HPP_INCLUDED

/* accumulate.hpp
JGBtkk1v2zAMhu8C/B+IFLsUdWWnabcIQoAty9pu6RIkbq+DYtOxUUfyLDqd//1kOx9A0YstUuTDl6QkoaVYWZwwmevUuN8rNm+mSuyEPUTRsvvA/Sxiu7qgnE2fV/PFMvqzmq0X85cZk/wcL3mPYLLCsmicI1Gkeg4Pr0MYBgEsfnnsuyIUENV4BcEYfpu9uwkDCEdiNBYu5v4p8tgaqz1WAlqFvu0MnqpX9NhcOc+TSfI0x+TACW/gZ63bCo4zFGFw4switRUwGIbB8NZP4s/+zXh0NxyNvww89jWOsSR/pfQWrYBN44p5bGo0oSZ/jnpLmYC7zqUxptxoAXFhLJ6joqbEVuU/4hntCo/9qLVu/AyV09agbVqkx/zUGN+NqB+J5IcRsQt2AdMib0k2T5DJuDNcSN/zhGVEpUs4mpKMKSasyDfhbTByF70NUqsd9sOGblfwllMG7xZ25eSj0nUJFv/WqGOE528umffZIGOz2ymd9GUF51tjtgVeO7f41LKXi1XE28pwMt1psY4el07LKdsdD310Hb5glacNtM2DSgkroAy71UKmLGwQNQxsZmjA5L6LdYiyMmTitjn3/qAvenxLHnswlgR8JO+4VwGX/LKdveRnlOQnPj8//v9QSwMECgAAAAgALWdK
*/