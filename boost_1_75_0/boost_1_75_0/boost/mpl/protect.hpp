
#ifndef BOOST_MPL_PROTECT_HPP_INCLUDED
#define BOOST_MPL_PROTECT_HPP_INCLUDED

// Copyright Peter Dimov 2001
// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/arity.hpp>
#include <boost/mpl/aux_/config/dtp.hpp>
#include <boost/mpl/aux_/nttp_decl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(T)
    , int not_le_ = 0
    >
struct protect : T
{
#if BOOST_WORKAROUND(__EDG_VERSION__, == 238)
    typedef mpl::protect type;
#else
    typedef protect type;
#endif
};

#if defined(BOOST_MPL_CFG_BROKEN_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES)
namespace aux { 
template< BOOST_MPL_AUX_NTTP_DECL(int, N), typename T >
struct arity< protect<T>, N > 
    : arity<T,N>
{ 
};
} // namespace aux
#endif

BOOST_MPL_AUX_NA_SPEC_MAIN(1, protect)
#if !defined(BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT)
BOOST_MPL_AUX_NA_SPEC_TEMPLATE_ARITY(1, 1, protect)
#endif

}}

#endif // BOOST_MPL_PROTECT_HPP_INCLUDED

/* protect.hpp
mVyYRwh4wFEfNKemHGUc6529QQd7DbQtG4HNQHkoSWdBptFH3caQ9UBSIDQcM3ZQbTacXwRns+43xJyiAXGE6LvbE5Byi5vtAGaP170nVp0AlvilT88ihJsbXVRvXk9tx5fX7TMtVHp4nwcZjqfrEs32Ym+xcJ5fbRJgayMSs7Z1d3WhzrQ2uiFQz7RrECTTIBDsYpiGHgmTgbdCqk3YgATvwyYHuCl0MfQRO5G8GK+5Xfz8SZ2EnBBVkBw+e06vhLxe9Aj8YO6ZHLDNtGK8Vtox6LH/c98bE3+Be4/gieAJ/4fC9zLz2AHit2K1knvBeWGvHHZZvk9ZIBT5cvb8JecKfgtdEEEQTRBZEPP8xkp5JwfuEeEK0R/by2WJt/t3r3ts9pJXi8hqL6ocGYonqhLyGRJd+4WAAQVz6TlVIQ4rwsJmkxKJYN/Y9JOi3hSycZJFZp9OHre9Sx1Ho/vrSALDLM7ERyd9nrCwi5/2ekOiS0scXS/eHXrL55XFYPKWxHbzovA+Kd2GoddGDbwsKanJxpzmV4klFY93uLIHPORKL4u/MzkJbraOBW9XxIOtHr8M1DFzHEZtBuzez0oGiMtbvuAYuzR3dxd2XySoz3/MuRnxo+4E+V+RCaCQ3e5hEsTnMQxe3Nl2hWXPRUPaMRjN8MkLXr4xZ96SU+kCVJS9Aa9E31/cGBGnpBvvVbSI5+IJCAXscjyrRBQP
*/