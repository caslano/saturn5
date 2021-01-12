
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
wtq8gVfwJk7mzZzOaXyQt/IZ3sbFfICvczbf5YP8iA9xMx/m15zDn/gIo36rR9maj7EbHw/l9a/sx3k8m09wAJ/hID7L8VzIyXyO9/J5PsQl/CszQ/ldGsrvsrBfPF8Zfven7IX7O3WEJmG/vB72yxthv6xmHa5hY77JlnybHbmWXfhOKF/reQbfY3++z2R+xGXcFMrPp3yLm/kJ/86d/JxRe3QLK/NLHsOv2JXfsBe/5bn8
*/