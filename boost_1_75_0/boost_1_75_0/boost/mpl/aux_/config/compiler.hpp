
#ifndef BOOST_MPL_AUX_CONFIG_COMPILER_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_COMPILER_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2008
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#if !defined(BOOST_MPL_CFG_COMPILER_DIR)

#   include <boost/mpl/aux_/config/dtp.hpp>
#   include <boost/mpl/aux_/config/ttp.hpp>
#   include <boost/mpl/aux_/config/ctps.hpp>
#   include <boost/mpl/aux_/config/msvc.hpp>
#   include <boost/mpl/aux_/config/gcc.hpp>
#   include <boost/mpl/aux_/config/workaround.hpp>

#   if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
#       define BOOST_MPL_CFG_COMPILER_DIR msvc60

#   elif BOOST_WORKAROUND(BOOST_MSVC, == 1300)
#       define BOOST_MPL_CFG_COMPILER_DIR msvc70

#   elif BOOST_WORKAROUND(BOOST_MPL_CFG_GCC, BOOST_TESTED_AT(0x0304))
#       define BOOST_MPL_CFG_COMPILER_DIR gcc

#   elif BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x610))
#       if !defined(BOOST_MPL_CFG_NO_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES)
#           define BOOST_MPL_CFG_COMPILER_DIR bcc551
#       elif BOOST_WORKAROUND(__BORLANDC__, >= 0x590)
#           define BOOST_MPL_CFG_COMPILER_DIR bcc
#       else
#           define BOOST_MPL_CFG_COMPILER_DIR bcc_pre590
#       endif

#   elif BOOST_WORKAROUND(__DMC__, BOOST_TESTED_AT(0x840))
#       define BOOST_MPL_CFG_COMPILER_DIR dmc

#   elif defined(__MWERKS__)
#       if defined(BOOST_MPL_CFG_BROKEN_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES)
#           define BOOST_MPL_CFG_COMPILER_DIR mwcw
#       else
#           define BOOST_MPL_CFG_COMPILER_DIR plain
#       endif

#   elif defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
#       define BOOST_MPL_CFG_COMPILER_DIR no_ctps

#   elif defined(BOOST_MPL_CFG_NO_TEMPLATE_TEMPLATE_PARAMETERS)
#       define BOOST_MPL_CFG_COMPILER_DIR no_ttp

#   else
#       define BOOST_MPL_CFG_COMPILER_DIR plain
#   endif

#endif // BOOST_MPL_CFG_COMPILER_DIR

#endif // BOOST_MPL_AUX_CONFIG_COMPILER_HPP_INCLUDED

/* compiler.hpp
VbgQMiPXFFYevtncZmm2/a7wrOUcbYKLY6pna0129GhLtKCId+S1HjuDyxlKRMErEdpTpc1290FcSOyskdsUzb1yny1xHAypKjPaRlADXEnsgN8QxoZzXSQlSGux90nu0QtuXuhv7hO3MZvU1J8/WzGF27ItlCY0bnFPqLgKE5Wj9ybq+xVuM63uTdtsWYbqvvnM6udLw1WZ1CaErhphgZMtEUtGE9GVB8JZUzZkkqbhJL22ZnPfGLMRYe1TUFfU2fJtw9rvvWlABBSGGD5oeWN71aqflyDPSfq5pjvkB943i0lJwWWl7XPzaLSvtqncA8SkDgPkuCheGr6117umPmc9B3fJBbD+cbAvHTpOveUYlZ421Fr9x+k9cae8o5n0veMj5SM+3HtcN3jIJFW+32TdnOv5D6bnLadFOBMWoOiPXPDP9C0vfJ3f6gNforQ+NeoNaFDgq7qV3Z8ERvYV/LlI5VbjkFbHrTR+tfDQzv0+63m3QAUHGxOLi3AjTyx5+a5ZnUzKQvQlRxJxkpswbCY6V3RsMOqaqeFhmQr4vUnMoLhyLrXOrCFLeQh6DKL8ENuerQ2qiqic5psVAn6zt2ezdQWW7M1RTOk3YpyoyTYaNJbbFPZ30ze6n86lmwwxkYMAjevuL5wvARx9XtCH0G0qfn8wT8qLyUnRrxfR1WPvMfhc8rPPr1nN55dfL7az45EHzaFGzNmZWV8g
*/