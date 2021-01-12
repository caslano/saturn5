
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
zcbHRdvyK7gAz1tGndTUNWvG22nGW9jHi5S7dsLyt3INua8ypmNfd7bzIs/hdzgxKW6y/MBJXmmfo2qfkTo/tyQv7M9nWjq3oaf2BzgxRtrRd1EWl3wPqi3XHkIVwnNyfBhP/j7fqQm0v1tR6m7HqeTblZP3zjdXz99vabbnrs8pJP3ZtZ3bodxJGKi0Q3HKkn6l6MjZq+R4wduf7O1nLXM67t9aBClX2tPENGt5X6bdcSiv
*/