
#ifndef BOOST_MPL_ERASE_HPP_INCLUDED
#define BOOST_MPL_ERASE_HPP_INCLUDED

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

#include <boost/mpl/erase_fwd.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/erase_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/aux_/config/msvc_typename.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(First)
    , typename BOOST_MPL_AUX_NA_PARAM(Last)
    >
struct erase
    : erase_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence,First,Last >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(3,erase,(Sequence,First,Last))
};

BOOST_MPL_AUX_NA_SPEC(3,erase)

}}

#endif // BOOST_MPL_ERASE_HPP_INCLUDED

/* erase.hpp
w3IwF0w/o6urPXRPAlkROiCNfRyClh5WiAZGXlsaMbHruZ3AYXXI+HdQSwMECgAAAAgALWdKUu33eEu9AQAAzQIAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxNTU1VVQFAAG2SCRgVVLLbtswELwTyD8sHAQ9pYxd+1CDFiCrBmLUQARbDdqTQFOriLBMCiQdQ3/f1aNOehKp2dmdGa4I6IOSHiMmtCktfU7YXq0rfMT2m+TX/rB93eRxus2TeLdjgn/Agg8Mdg8HdO/oHr0ukAmHTd0SXMggwVhVoTqtJi36ScSesyzl069TmD3NIY332Tbe3bHfj4k9n9GEJTTSBS1rcOgbazxCsHBCbCBUCKrWVARXqYM2b3ekoJtBoxpLLs5FxDoIpk+E3H4JPgoinUnfYNQ5dKMC36uPWBVCQ+X/riJYW0es1sfpYrEgYLiDMPJMeVGNLluQjQbtoXE2oApYgHyT2vgASta1h9LZc388SnXyROYDm8SEinjDMF6RWrha8yXAEeHiqU9pHaUga+IoSkeaYlC45Pzh+eWQbdPlQxdn+rLP+KjwVkjH0R0Neh2U9u8hy4CuD7N7eaikp4FoYOIrGyZMDK66SMmQVZ1hyvJ2vof5DFYroMXY0Vqsafbm
*/