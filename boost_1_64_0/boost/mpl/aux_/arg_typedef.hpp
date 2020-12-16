
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
1+D6qw03g7KVF3rqHMlXvmwoRxluA1HVEKLKqnqELxQYqYN1LF9lIHl8qA28Zwu/q4wWOxHbkv0KlV1AmdqY8UqkSz/ItBIiNPDPyZyM6aEntUVlZ3r55ZV4Q22lqs1DbG6nVW1oVk8IV1SfAbZ7LcXMVT69RTRNJup+aoNz6/6/SOp3HEtcc77LpJzhFvrL9DRxdd7c52Yux7iWNJ+1sQhILylaw5aOyXFxx6LhvUiUz3O6QvvbHzsYLak6u/Cc8XPPDaLpx3Qf2vUFmrtB95FV9SGvMUcyuwUZkubn2GfzmLJSsoNLpA7Hs3iZC7fCPlgm0vlpdiHOD7Px+fyU8kO/pIY4O3AFVbPJ6WU3PWO0AKNGVM66XIko8ETzCZn4BwQNxuTDE82nWdldhZwC80qSj78DZqU/n1HdsuHf5EpS+7voNUH6Z+KbX3nPOEZ7S9Dnh6058ordZTdRGjxwnKb8gatwo+ZCRKNXAxzDCukz9znE4udQP1Z4+VvTFTkG9QgdwXhEM0nDsSP4dDrfNFHXHuFEifGOxv7/paB/d9pC9GOXLfkWu6zcZOmvD8H2wIfcIopagey3VOZvIeKci7i4yObIIpsr8zeTHTMXcXORjZFFNlbmbyS/Y9oLEsuSgBSqx6RB1AzWaj1OHKACoi8drLd/xrdy+28IOEQA5w1kJjREMq43FJsXDqXv2if6jy7q/aV4rWbNewIw7HdMp8oHibGYNedeStFHelmd7Ou1ysLXis1ho+S6r6ssWUeL66ExeoT5wn0Qtb1WZP5piOLRoz1n0Kck7kIDzyV7m9a7Mn9d+Z7cEKHk/XBfsh/FiIPqxzveS2btZc1gACteRMCgoqKocJDYaRWFgi4v3+cMwUddtiDuHndICi+QbTa72G4njpmodVL2alWGBf7Em6V4ThfJsmsEsi9ZI6w11zhCHYznVWG4mus7AsWopafYix14JCYx/Skb+onks1/gOvMLlHSL2/rB8bLtneVlO8XFNBEPKBPhTnfydfLqRHUjk7x+5xjz/hNQvfpn7I6XVwteMjBTcuEynLZl+uYfcpl2VBbuKDbvL5CLsK2yZAcxSQfrNcnfUWQOY/Cob5x8cYQpvcIFv8nw7F9Ls45IsVSGZCXCLp+YDSXbyvflBpuA7DgGeNELB/5QxxzlDdOabpNrugeQ7sGaenhNYWW+R64pW/vvIjcuYId6SUDqhrC4oki0U7itfK9op2QXdu0uBMTwUTtgUlA89l1lzdAkgb+r+rMfpQsXk33qtYD7vUsG/eveZP9NH0v/+1ymh00fbYxYvljqQArVf61v+gFAQTJ9ZC22HFwN+ODpQZPh7WhPWMa0/cJPy30QpLCfMvw73PRx6V9fKLd/CsY7KXz0/VZYYo2vXnI84lOCrb/WlOB4OyV44dd6mMzDpU3KtmZ34mgjfEvAETH+6gn2EQ1VxGslcP1Jihw+jmoxQaz9S62ecFSnopH+57jY/FXmTOd/qZe5D25kmX7tl3ZaC8N74Ec7KdM0/OIhwanX55mxan1w8daAXACH00tPHX71OEND6DuY5EyrwqKdGTs+4FA55Wu/EjD55aX3uCi5BPeYTzBrvbTQ0DnuVCPVFHwDh3sUnXZbNP0JxyRf/U1PyVix4mjhByRiP2Aj+PhVVXme2gyu8Ct4bzU+FH6GUM/aPYc0a6l/LPvvMcqfGXC8VzGQg9M5Wj1PBd8uGDpwLRMbE6SkiqiJGrX+NHwmpdOCefSd7eEJz/N3encaC5zyvgT578rDlFDDODPm6Txz4XuFe+tqwtxeACWISPR0D/LjAHS+BmgLikmAINPIY84/vf+oAn8nKYqxVEGDdQsOAjS6mZc=
*/