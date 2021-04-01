
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
bUNDhTIKjAgc/OBa5vR3r+nhpWdkHQ8mrYrRhkiar9YyahBx8LtO5qwdWAyONa1F6h4X4VbxfJgPzZxDMUx3c5iZmxjXx6YQJ1zkC9cOYWn0tSqdLYEMLMPiaHBnmHO+Ob0mNLyOa00oxYGs/6vtj7C6crYBZia+GDNNYJVNn73eGMNgU1BGTUzszxg6ETR4oLX3IszfIC8IkVGqlPq62LoMCG5fkGfDVIAUxUOfNMW0UxXjEkMAcFIt21bbOyokMC3TO1Ij2/dwFMyumGYi/boJ072i99w2V33B28m3BCWtsb3Jszj2uHlnOvDJun3AVdT0hLXE0xuDNr1+pVemiDTmrhK5DpYIDCCjySrZo22HcnfRnss564CD93+k4fvob+o/4ey0MXDC8BMx6YHC3eefZR4orYOzmHLGPFnAOBXRBlDMdDKCIdoHfHkAAAdEmvxyIHlxiHdNI7dYZgh2fvhtFahjwLEJJ4iICjt1X7PJWl8d4XrTRisNd8cKfd1p0WmmGYmXiH3d4nypTq4+tAXbva5woIqeq9i5WWiXBPSujed5UxlMstdRgA==
*/