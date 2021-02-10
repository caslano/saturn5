
#ifndef BOOST_MPL_AUX_RANGE_C_O1_SIZE_HPP_INCLUDED
#define BOOST_MPL_AUX_RANGE_C_O1_SIZE_HPP_INCLUDED

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

#include <boost/mpl/O1_size_fwd.hpp>
#include <boost/mpl/aux_/range_c/size.hpp>
#include <boost/mpl/aux_/range_c/tag.hpp>

namespace boost { namespace mpl {

template<>
struct O1_size_impl< aux::half_open_range_tag >
    : size_impl< aux::half_open_range_tag >
{
};

}}

#endif // BOOST_MPL_AUX_RANGE_C_O1_SIZE_HPP_INCLUDED

/* O1_size.hpp
zyPHqX0V5SNmIQyGg/Zl9M5RXsC7SvSIR/7d2Db1da4rqXPMZRnCq7zNwnTstWNxbnX+F9auX4O1HTsFtVhG2zEx+rJvtP1T+g1QSwMECgAAAAgALWdKUiSrdOweBAAAdQoAAB0ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q2N1VUBQABtkgkYO1WbW/bNhD+LsD/gWmRL10V2XHSdp5igLIVW4Xt+EVx4H0paJp6iSVRJamozq/fUfJLugUYOmzABowwLFI+3j1399ydbcWkokSyrmHHWcDhsWW7kouN7BpD359WX2jg+vVm4o/GiBQqMmzrJGhb9d23aMHEExOmjDfMsAXLk13XMOwz00QZR/aGKNJFcYZUFEukTSMZZ5ShkqGIPLFafSB4ChIMSUWEMgxfC8NHFnnOJdsgxdGaIcFUITI4lhHLavnKOAqZkoigIBZSGRiwchE/ExXzrFMbSOKMoZxI0GUCmKM9msQsU8g0NWaNtdVstuowWK2LFrpqttCElyiM05TBDQLwGeXZBrB8LbQ3PEBUkLxh1HHooHFMBZc8UKbnLazri2bD6PFMgRnT3+WsA0H4pqxIpckviEZESKZuYsnNT5+ufzZbJ+ERy0IVdVD7qmE8PDyY2i14H1Oi2N4r
*/