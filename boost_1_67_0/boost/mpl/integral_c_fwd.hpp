
#ifndef BOOST_MPL_INTEGRAL_C_FWD_HPP_INCLUDED
#define BOOST_MPL_INTEGRAL_C_FWD_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2006
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/workaround.hpp>
#include <boost/mpl/aux_/adl_barrier.hpp>

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_OPEN

#if BOOST_WORKAROUND(__HP_aCC, <= 53800)
// the type of non-type template arguments may not depend on template arguments
template< typename T, long N > struct integral_c;
#else
template< typename T, T N > struct integral_c;
#endif

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_CLOSE
BOOST_MPL_AUX_ADL_BARRIER_DECL(integral_c)

#endif // BOOST_MPL_INTEGRAL_C_FWD_HPP_INCLUDED

/* integral_c_fwd.hpp
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
*/