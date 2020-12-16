
#ifndef BOOST_MPL_AUX_COUNT_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_COUNT_IMPL_HPP_INCLUDED

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

#include <boost/mpl/count_fwd.hpp>
#include <boost/mpl/count_if.hpp>
#include <boost/mpl/same_as.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>

namespace boost { namespace mpl {

template< typename Tag > struct count_impl
{
    template< typename Sequence, typename T > struct apply
#if BOOST_WORKAROUND(__BORLANDC__,BOOST_TESTED_AT(0x561))
    {
        typedef typename count_if< Sequence,same_as<T> >::type type;
        BOOST_STATIC_CONSTANT(int, value = BOOST_MPL_AUX_VALUE_WKND(type)::value);
#else
        : count_if< Sequence,same_as<T> >
    {
#endif
    };
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(2,count_impl)

}}

#endif // BOOST_MPL_AUX_COUNT_IMPL_HPP_INCLUDED

/* count_impl.hpp
8L7NPDATzTZLKomI3Nz2wDM/ofV6vzRHe2E+q+7iNKTYchbnU/6asv/AjkmlDnYkZkDKPRMh92Se6nqb5OG14crdtzPx1DZUF0g8ucDe6Uhjt1e5mB8FViBTA8O9RYriUuSLZGv64tLPzPRZ67MuMdTBFrhkJF2E/nsE+bZbEZ9D3RT0G7P70D+AZ2XdmJ7QF2mTslNSCH9zW2qd+N9R3zLr0uHO3VfhfxhCbA8d0HxEbRsVFOG6te8mG5F6jolUxVQQKZH9GlGhw8N6a1xCC4kasWhAB1MdCzWUsgM4idi5oqtI/yuMKQd6ZqiR21zKbYNvSjiI+rsUvHMGKNxD+M2uQM19d3Ijl9sa+UtuZCAHYLACGBIclkg9nlMvs6W+QKa+0Rw7lCgGMVkOwWNdIc7EbnApSYG9uGq4W8G/BhrhBwP1AguVI6CycrUtwp/hynheLBpstL5S0uhFeECTcDYErqf50etz3GOV7cWxSh7jO6bdSeQL7r+QCcb5dwcxR5llcAsuA/uZbEPtEL59GhO8q+RIeghENi4p22t6x9F00MXCidmD9iE8ObgMejoJszA7VbNLPgfTCUwVOQWPwRIFu9SM4Dlfk0gN9DPRfwPxPxK0F+cp2jY1Bm07aw4oGv/l8ejy21cLIstv++SHfG8+Ma+qvHh0NerrFaW+6Q9Efr9pTnh5/Rf50et/6/HI5VfcH/n9JRHqH12N+ntFqf/3Sn4f0v8nV/pT3nMjaooCFdKG3RO6ObNTfJ0M43XLnCBvNjs61A+8q2s+NKK6kWos/w9SEpuvkMDHwkOhkKVb4Sdxl/D/nij5T9xvwgSKPGVDz3qV6bjEQ4lVIhElz0iAxEIcJ9iuDEvpg6TLXNQ3SHF/s3HBKEkrr2SNmm84N208mpb3YA2kp11Hg3OAH3tmCQvK4rlU/0UVZxy6RIzvSPg/zQiOn0yTW7i3z2olaVoNSdPq/MxC0DsexdU5l+f3WU1TWkjxCJXJ17L8zGWDfOTUuibD3I/zM1GAmBRkrhEmQDMNXg1rdWTZ+EeLa3COQJ6zNViecutDGv9/Wqj7cjd6Tzt2QTh5SLOHKt+fuj4S6b4VmBzE/y+Mxv8fnlOVfq2YFX3/5kbRd705LvL7b2eGpx+tq1H/ptD5t5S8ESzfOrY1+Hdq8Hvz7cfU/Dw4NdT8rBLvzV5PhpufhH4q/6VV8qO+bcH1fXQt5F9PRLQPT5+G+wftKBZj1QesYiJVA+DDbslZ4DJ3W/52gmOgMOJrmW5QDPGig008bAugQ3Yc6q2uzoj+YV3NINEYcK2+WPsYtE8H51lxs351Y6UyixboV10qFTj9Fv2qSaUCt+SoVxLb5c75N1B7x8q/jvT3KP7n30vpb+vBMx+7Wa434/GWMR7jxmExHjNvXLT9kn6Nln89FGK+JTcM0HdMWl3usxi2OnluNtblwRP3gwxXXjJ4WquUkP6ftLRQWh0qB+xwnscGm+meeAXRb5r0YYfFpAtmL3C+SHaNK9CKKws0lc/ry+d15HMnC6Hmd6Csl8i/tvR3Jf7n333oL/1wzcdfjFfzHmK9x84Pt95Z/01CZfO53koQqCI/4Mqd58bp7WG9CkMdUzyyHpioyHdGXf6PDyn9OkarPxVU0aZg2ZEm4gLKZQtfWbeMEXI+NppH3ENaWgm8VoLaOgFeJ+Y5MYYjqMCx8m8w/WXhf/49nf7mHKnZGFrz/1AwPagFWIo4ogEi7lWixYPfRgltYOPAWEqttC/f7VFp80Wcvy1XqvV+08RQ9HGReG+2nhuOPt45o4r8b0qk8+urK6vg30VMn9+zcvqUiOnN7pXTmw9FSr/qYft5eqogGn3ocKU9/fs=
*/