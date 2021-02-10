
#ifndef BOOST_MPL_EMPTY_HPP_INCLUDED
#define BOOST_MPL_EMPTY_HPP_INCLUDED

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
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/empty_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct empty
    : empty_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,empty,(Sequence))
};

BOOST_MPL_AUX_NA_SPEC(1, empty)

}}

#endif // BOOST_MPL_EMPTY_HPP_INCLUDED

/* empty.hpp
aJwNVnf4PMcYDfDcwgTm1ocMP3Ek8Kg1Nbx1L+77QbjqSHERF9c/6ANQSwMECgAAAAgALWdKUjM0ZIzxBAAAgg4AAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxNTVVVAUAAbZIJGDtV+1v2jgY/x6J/8HrqdK2WwgvrbbjApIDrDBBy0vaivsyGcckLkmc2U4Z/ev3OKHQbtVuL3c66bSoamzHz9vvecXVTGlKFOtYLk9XAl5rtt0IGaiONfD9SfEPTS79cnHuj8aI5DqyXOdw0XVKWus3NGfylklb8YBZrmRZvIXPqjikSdCxDO17yT7kXLIACB98cgOiSSnVqVfr6KRWL+VhoBGS3xHNRYpmO2KkNorGQrGKVQptIZwRGjEgblYbr9HzHpEbnr5Ak8HEOanWq42KdX19bRt2LNWcEs1ayIsJXSck5BRJRuKkfRTyJGGIxDHaMolUk8qmVkdP0hL1I2TGqIrVFamGM9vfZnCm2UftRDqJ/0Q0IlIx3eZK2G/enP5h14vLKaPG/hbaGV2xEiEAwRI1gN6PuELwp/IsgxsB0gItGainc5nCdgMqINADlZijkGmFCFpxqTSQP0K5VBLFPGUoIwq42TxFKymSggONOaheeqxeq9U/85oxya6D
*/