
#ifndef BOOST_MPL_AUX_HAS_APPLY_HPP_INCLUDED
#define BOOST_MPL_AUX_HAS_APPLY_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/aux_/config/has_apply.hpp>

namespace boost { namespace mpl { namespace aux {
#if !defined(BOOST_MPL_CFG_NO_HAS_APPLY)
BOOST_MPL_HAS_XXX_TRAIT_NAMED_DEF(has_apply, apply, false)
#else
template< typename T, typename fallback_ = false_ >
struct has_apply
    : fallback_
{
};
#endif
}}}

#endif // BOOST_MPL_AUX_HAS_APPLY_HPP_INCLUDED

/* has_apply.hpp
sVnLJfbYpArV++A9xwgnWnok7LYMLGk6oe+UDmlgJI5jsHCrEii+7ycMLSgKjFV4AuO4p4Wo+uQv04r8ajWYgCqSPyasMg6Yb7TCCWoPsnMRnUQgxAmx7yxjB1yRZ7Osozw5fCJf0WzChCmQE136SoGSw4XYt8/RLPcH+TnkoCvk16HDhKwIDF5rOAC3gfMhyAfog1LmMKRf5jyNeVVDFbiw4RgnI+9nXDqHK8ox71BemO3At6OhipVnjplPNv1yISZCkyg9dRHQ6IA9fi5tgTtW6h7uPFZF+LKi0UT4kpaxpPshsn6ORNTc2Sfu8FKOwcf5fiR5FaX3IIArdBWlM9IwEMHwdx7BBWnWnlKJEHAIIvxpBv43DkOONeYumx6505CVXgtONtZJQERwGXzCXsBTRXukpwNzDDelWagga0uloqeDl0OSraeDH7OzEcA2PGhctr5el5nSDNu6kbuUMlQcULvPAEWrjP4Smp5Dak7rZbB0g79uP/MPwJAK7yLyLn+i1+CPVgmvf1AXlhlCcH76Q9i+5HW1vzmdijLwA6tFVzrnK6KbCrS6RJYyxzdPDbCHb36x1DV3mHKMHu80rNUklfp31vUkO4COtAWDd+/6Y9IewHoE+aj42HXv7Oy+dZs1661QuBVJxZ7hqBCTkLXLFcXNPbbIa5U/DdLwp+gYke6If0Ro/VyHG88UJ7Hh42msj4I6BrcGwUUD
*/