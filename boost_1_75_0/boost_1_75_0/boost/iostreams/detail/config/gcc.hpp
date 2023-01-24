// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Adapted from <boost/config/auto_link.hpp> and from
// http://www.boost.org/more/separate_compilation.html, by John Maddock.

#ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_GCC_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_CONFIG_GCC_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <boost/config.hpp> // BOOST_INTEL.

#if defined(__GNUC__) && !defined(BOOST_INTEL)
# define BOOST_IOSTREAMS_GCC (__GNUC__ * 100 + __GNUC_MINOR__)
# define BOOST_IOSTREAMS_GCC_WORKAROUND_GUARD 1
#else
# define BOOST_IOSTREAMS_GCC_WORKAROUND_GUARD 0
#endif

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_GCC_HPP_INCLUDED

/* gcc.hpp
qkbrkW/r7NkMYweh9kdWxDtdaUTzLGcFsVD/tGRh6tJR1PXWtcThPqTggr905sy4Djt8s39iMZUTSvMu0T9lwUNrQiwlFrCbV8JqGNqFsaatnEua2Mbaf5Bow50FLOenHpYa3fH9E8H61ddD0qjgyUa36nWh57FDUkDKLXWr3rMUdQZpSzGjlLSKPJ2K8u00FWv/XwKsyrjIDorkJ0jGByhCDvTY7DDFWh23WQ4j2eiV4dJ6YbPQXxynPR/zQkXapzNUO/NrXDoUz57ZEcZg21I9XsUmnD0q/GVA01/VyVi84DbWyQNqSyjVetUqNPL+sjoT8l8YlH+FeIVchRKECocIo+FWY1eNo+Gtdcvv64pMfH9jLN8eIU56qNom/0uKMGAWkYF2EvJDzSLy68URhEB5niThJS/NXweYmuUeAzIxOQXb0DOMV1au0qNocgQoY36GXik2t6nyRujUknzaVe2XsJwsMXgww3u0QYmHsP/ipyw2pXp9hLNe058fus31glmTs102UbML0B3EdnGo5XrCD9j/wlxtghhofejZFi6E893L7BF/2HCQUjwm2rPU8WM2f+XDdElbKZmMXwiXP47seDx/4YOqV6gAJBlHdHCucM4/j2DK/5Hlnw8e+/bRjzsJz6f2MuWjH7Et8TTX4y+/fJKVh8HsjI2ev9rXCTgvMf6gYfFx+3XH0hm0E73k5tbIAu4p2HC5RYQ/
*/