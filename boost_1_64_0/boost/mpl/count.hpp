
#ifndef BOOST_MPL_COUNT_HPP_INCLUDED
#define BOOST_MPL_COUNT_HPP_INCLUDED

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
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/count_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct count
    : count_impl< typename sequence_tag<Sequence>::type >
        ::template apply<Sequence,T>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,count,(Sequence,T))
};

BOOST_MPL_AUX_NA_SPEC(2, count)

}}

#endif // BOOST_MPL_COUNT_HPP_INCLUDED

/* count.hpp
Fv6BuG4jKfnFY15V/+32WEIEphMvw2p4wbLczH06ELEe6j/n0DOOf6n2/FzPaxtf4HEjLL71Lxxd3fPrWHz3swlZ3CzU8Sqz3vHM8eNS91E+LY3S+rrdOchViZrUmal7xCUKTg171VeQFEViFA/rRLAHrtipR5t5km3DjBxmHJPhN8cwMO2O7vkebmzPz37tjKFLGKf0ytJ4DSf+Lk7xgCKnQdZRSWpPbZBvCpq0j3aeb86XlGdrbVh1+qw4gx/BxURwzQm4dxDvxRevwyydgNsRVnUA7Ccdj4fN9ZJnWMWimYp9rVXJsVQbgFX5AGUODAYfT7j1UhbWAelBwU1Pe+cpyXBe9EFf4LVnaXZD42I1caVvINdNQ/ccdq6oX+KF/5bHtoRKv7Vv+qtJxNE0yja1XIG1fF1PFEU3t3e2c4/3ctFQhnELfEZ2yBHVmBPhCQqu2sR65OnR/eOTrRI0JojGy9h84yHsgfuGssKwYDxB7WVDD871rmIyIyCpHaNh/CMCXr7qM68U9MUmfKM8853NSv+J9JR01XoQAl+2kflk2MsLckIN5/qyDw==
*/