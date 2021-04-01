
#ifndef BOOST_MPL_AUX_ARG_TYPEDEF_HPP_INCLUDED
#define BOOST_MPL_AUX_ARG_TYPEDEF_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/lambda.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#if defined(BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT) \
    || BOOST_WORKAROUND(__DMC__, BOOST_TESTED_AT(0x840))
    
#   define BOOST_MPL_AUX_ARG_TYPEDEF(T, name) typedef T name;

#else

#   define BOOST_MPL_AUX_ARG_TYPEDEF(T, name) /**/

#endif

#endif // BOOST_MPL_AUX_ARG_TYPEDEF_HPP_INCLUDED

/* arg_typedef.hpp
DFJy8mz/IihAQmP+aKYaSkZDCMs+mrrppeQzJ5124R0nGa6d/wK/p1SYN+Ld0dELe+Gw3Sly3PORDvTZpwh5iV1GsuipeSBdM8m1fY29GNMFAHDqsn/9CkXqiZN96zJm38h+vVulEnT41TuzcdCt6Go1z94hg+ABScIrKorIPErNHACceC20Pj9ByujfSmeZ4SUAN3KNB4JxpEdE/ByqyOZCM9KonpfmVMuqYgcj9tkxzkHKds/uyOgVWucr0wLh8wXsRzeykOACSPcvHHHS7/Dv24Dlxkph+4a28f7b9w3XQDHTVhjg+d/ykL7nq4jZrHN8vtj2eivS/7Vxrbx3/CdHwMDGxUzcZD/b4+njC/dr9ueYD4mDypi70hUhtNpA+dyG+bVVSNJnSnRGo9tV1bDSOkLnZyYhzvA1FbLDb18UzX3If5pBOchNl+Oj0sHGsEa7OqWSQFD++z2d5RBI//Ku18hY71VpxF55dJfuRO20qDl6t2juFP2w3DV7kq1EnosiKud9R01X/Muu/aHTh+s4ZmJEuoN+y6HPSWuIoC2DPDT7GRkPRVvKeg==
*/