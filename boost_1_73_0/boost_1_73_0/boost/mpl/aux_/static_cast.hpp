
#ifndef BOOST_MPL_AUX_STATIC_CAST_HPP_INCLUDED
#define BOOST_MPL_AUX_STATIC_CAST_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
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

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x561)) \
 || BOOST_WORKAROUND(__GNUC__, < 3) \
 || BOOST_WORKAROUND(__MWERKS__, <= 0x3001)
#   define BOOST_MPL_AUX_STATIC_CAST(T, expr) (T)(expr)
#else
#   define BOOST_MPL_AUX_STATIC_CAST(T, expr) static_cast<T>(expr)
#endif

#endif // BOOST_MPL_AUX_STATIC_CAST_HPP_INCLUDED

/* static_cast.hpp
Pjdm81uzk3DEltPZQafTnkXcee4kSTicAkODchD3QBeTcGFkZKDCSGzWCcXODoFndGdAQQ/n8Bs1ZwMWnS93ciTHajSO51AIftgEH4a19EAilZFehb0FrH0QlQ444OoyyqL7L7bHXLr/u97uT3bJBXVmnCzMl3w4YcusXAI5Cz05qncYRHbzkw9Lvw6rEwvsVmGwjQMdv/QxNoknGzwuntTguEgS4y+B7yRlummCO2bsXIaSWZ5mM9FXr2bnbPs=
*/