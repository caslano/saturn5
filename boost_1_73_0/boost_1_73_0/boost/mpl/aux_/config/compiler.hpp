
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
UZ9FRdEbDPgI+Htq2bbjwXjZO9t6/oC1zg/Q9kGWE9ZABULTgVBkDh4RDXiusMQg+zaXIaraklW2HAluQuiYX7tmIKat+28EDsQ9351/vWHyCNSuLuXwYbJY3iazgbhWCisOn8vzgRj8Z7CxPBnC/Upru6N/8ozCZgi6gV9GT8zL403J07/kL1BLAwQKAAAACAAtZ0pS6zvp2fMBAABOBAAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDIwNTJVVAUAAbZIJGC9VE1v2kAQva/Efxg54hLVLND0EMtFighKoiYYgZNTJbRdhtiKvWt5Bwyq+t87tgnkUKRe2st6dvfNmzcf65DQkVYORyJMzdry5w33lS1XbiTu43jWLHA3icX4ef4YzeLlOJpOJ+N4GUfC90t0NtuiCOXJLZQtk7gQF7DAcoul79IVg0ossj0DVooUGKsT1G9fvT06rw0mB70BDPt9iL6JW0UYQLzBT9C/hqnd8sWgD4Or4Oo6YMjdE0uyhtCQ/4jmlZIAPh9P4n3B3oQ7kkWmUiMEU4ayDlwLPAhpFI6ztPZoFepmwxDX6B6JhKhgh/cthEblXCyOY1ATkAVXoE7XqYbEOgrg1nJmBHm6A92CUmscVCkloMyqMeyGQIGn
*/