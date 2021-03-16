//  Boost string_algo library config.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_CONFIG_HPP
#define BOOST_STRING_CONFIG_HPP

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

#ifdef BOOST_STRING_DEDUCED_TYPENAME
#   error "macro already defined!"
#endif

#define BOOST_STRING_TYPENAME BOOST_DEDUCED_TYPENAME

// Metrowerks workaround
#if BOOST_WORKAROUND(__MWERKS__, <= 0x3003) // 8.x
#pragma parse_func_templ off
#endif

#endif  // BOOST_STRING_CONFIG_HPP

/* config.hpp
aiu4YSc+68xf0LBpgX6pIWd6IOVnc+agpCVVPIVB6UDDzmZbQQmovADT3+1u9+MKTl+sVa6iO0MsxTvEi2yysSpGiABkic6CDOeLL0ClFynCbzaKyRqF9CAfmSLKp5Z869wCPWewiKebcbE8SndWEC1ZahGNRoAW5HsPBCCG+jyNx6SUtwDmzaGaMK/e+YInUPEmWQBzDbOA/QMeypvKqBKNVD07A3v/Uao4IYShQY64N3/U8boIOG4gsfUWAcc=
*/