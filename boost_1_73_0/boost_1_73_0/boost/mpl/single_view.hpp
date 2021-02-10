
#ifndef BOOST_MPL_SINGLE_VIEW_HPP_INCLUDED
#define BOOST_MPL_SINGLE_VIEW_HPP_INCLUDED

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

#include <boost/mpl/aux_/single_element_iter.hpp>
#include <boost/mpl/iterator_range.hpp>
#include <boost/mpl/aux_/na_spec.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct single_view
    : iterator_range<
          aux::sel_iter<T,0>
        , aux::sel_iter<T,1>
        >
{
};

BOOST_MPL_AUX_NA_SPEC_NO_ETI(1, single_view)

}}

#endif // BOOST_MPL_SINGLE_VIEW_HPP_INCLUDED

/* single_view.hpp
7/E9BBNY6QNEQRhAOI7HkzgI4OY+J13xGBr5I9sGdMO2SBZaOVRulNcVNtu/HRVuV57WU1QvTsQQkFRz5qRWMdBwEgb+iYjX3yjshUb/aIs88VtpGxMi8FevJWpM7e3zri5K2UA7V3kbeEDHMiPCucrDX0OSKLbD7hTADRYeLVlp4SidAIXHUioEpgrwe9Igdz65S0mc1uWMlPK5Mccvd7Hn1Ludz5iRi2X2mN+u44um+jp7yGmPPCH8by/QC/+KRm5qaAeAbRwacAJbj0AwC8+ICoZWaDckyaHF+gKV0U7zhvjmU971CV5bMiBLbV0M/+kYkPneCW3kn76/7fRC8W1V8pdq//0pLDN1LfjV/V0RTeof8+nUp3COla92SS8HZHCma8bibSgTej5tQk8W0PMN/QtQSwMECgAAAAgALWdKUrtpb8PIAAAATgEAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxOTExVVQFAAG2SCRgRZDBDsIwCIbvfQqiFz2YZUeTZhcfwcSrqRtz1QpLQc3eXmY1O/HDT+ErXlG0DYKN85F6tnDH6c25k8a1z5zOGGQ686iRyflqMX1V+t0ajphfmHcSO3Q+45im2f4J8w8pIunPb7+JNcj3VeOIycrVP/UU
*/