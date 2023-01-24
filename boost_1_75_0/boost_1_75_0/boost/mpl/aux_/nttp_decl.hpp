
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
u53Q61OwGJlM1gvdOFNn3YzTAcgtUzRm2YXMdMljY6H5OYvKekcy26g0Od1JdugC499YggUXQDOmPOMsVWWZL+ICy1TsLIdfaNiTNa/tafW/sNlvjgxgxOtmzMzz6whYEUwT7Q1JuEIwBP7+1PrSAuMcrdulViyeCVqZxGcNYa0WhXMyRteHHQ2CNh9gjzgCcr1LFYMQ8tOJZ6fgP7LyfWsPO9OKISxQLW9XAITwiBL4faK7xJf37VCUO1r2+sUUrGYqOxd7OvyoAIq6NP76UyS443jyKHEpXkQxUDYwlOzwZkm180fHjiAU1/M7PB9efDF9D4Du87+6JOPA/dRKH8JX+V+3+SCmai5TPmq1g76NynC0s8XAVA3SBrlBTkEPoY9zV2PiZBRk8y5xBbu5UQJGQINBeYr5q5l6iZjJzgCKF4t+8X4XWZe027lVdrc/k2IjBNxtc7bj5QVor0kDoKAfTiJUVlH1ttH7A7cDtuZhtQtLJn/ilNhklfYu282kfpBZV27OddRpIBG0iWKXzTJjsGU2z9nmJGd/iibOVLknooteLVXZuWsmRhx4JNIHMGYVNxPBV2/o7uGhKJuWm4kbFWMP6TaUcPAWuBXvFX4ZB+/vUsd4ukArCXuGF6Fepqg9dTQFhlYPAmCjBZsSP7YaB0+cO6H8dw6MefDgDbINQsJLik+vcMzq2xEOiBOi+94Rm/uBZjmyf7G+
*/