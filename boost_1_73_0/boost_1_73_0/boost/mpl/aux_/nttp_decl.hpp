
#ifndef BOOST_MPL_AUX_NTTP_DECL_HPP_INCLUDED
#define BOOST_MPL_AUX_NTTP_DECL_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/nttp.hpp>

#if defined(BOOST_MPL_CFG_NTTP_BUG)

typedef bool        _mpl_nttp_bool;
typedef int         _mpl_nttp_int;
typedef unsigned    _mpl_nttp_unsigned;
typedef long        _mpl_nttp_long;

#   include <boost/preprocessor/cat.hpp>
#   define BOOST_MPL_AUX_NTTP_DECL(T, x) BOOST_PP_CAT(_mpl_nttp_,T) x /**/

#else

#   define BOOST_MPL_AUX_NTTP_DECL(T, x) T x /**/

#endif

#endif // BOOST_MPL_AUX_NTTP_DECL_HPP_INCLUDED

/* nttp_decl.hpp
3+P3N3zQYyCwIrDC61Erhfx41vMRLBu3N34ySylbMYVp5qaKZiRbiY2VK4b8HhyAS5PZ/Mk9NV95YwX4qCjnurzFzFen6OXWsclqltVntwFmcpKWFQtF684fUrYpx+0Wq+XN9Lq8Obep4jLC6vGx19ClTdX8uAilRpOZhJkZSBnBsDlZGJft8CqWzbDLxyqFqdw4/iS9UzIBRrPbZR+gedntTvkUTE5ByZzLrmAU8Xcq7SvWzY25rKsNpWremkg=
*/