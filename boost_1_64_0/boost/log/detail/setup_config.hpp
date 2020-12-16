/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   setup_config.hpp
 * \author Andrey Semashev
 * \date   14.09.2009
 *
 * \brief  This header is the Boost.Log library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html. In this file
 *         internal configuration macros are defined.
 */

#ifndef BOOST_LOG_DETAIL_SETUP_CONFIG_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_SETUP_CONFIG_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if !defined(BOOST_LOG_SETUP_BUILDING_THE_LIB)

// Detect if we're dealing with dll
#   if defined(BOOST_LOG_SETUP_DYN_LINK) || defined(BOOST_ALL_DYN_LINK)
#        define BOOST_LOG_SETUP_DLL
#   endif

#   if defined(BOOST_LOG_SETUP_DLL)
#       define BOOST_LOG_SETUP_API BOOST_SYMBOL_IMPORT
#   else
#       define BOOST_LOG_SETUP_API
#   endif

//
// Automatically link to the correct build variant where possible.
//
#   if !defined(BOOST_ALL_NO_LIB) && !defined(BOOST_LOG_SETUP_NO_LIB)
#       define BOOST_LIB_NAME boost_log_setup
#       if defined(BOOST_LOG_SETUP_DLL)
#           define BOOST_DYN_LINK
#       endif
#       include <boost/config/auto_link.hpp>
#   endif  // auto-linking disabled

#else // !defined(BOOST_LOG_SETUP_BUILDING_THE_LIB)

#   if defined(BOOST_LOG_SETUP_DLL)
#       define BOOST_LOG_SETUP_API BOOST_SYMBOL_EXPORT
#   else
#       define BOOST_LOG_SETUP_API BOOST_SYMBOL_VISIBLE
#   endif

#endif // !defined(BOOST_LOG_SETUP_BUILDING_THE_LIB)

#endif // BOOST_LOG_DETAIL_SETUP_CONFIG_HPP_INCLUDED_

/* setup_config.hpp
0J4d2xpZrTVep0JtYOgIHaEjdISO0BE6QkfoCB2h4zs8vo/n/1mLsvwz2N/K/v/7HPv/0UfKwTkier6sd/Zv2u8O/PfOW8jd3e8NCrKLnO/rxX6K0cn7faH6Z9rP3M8mBN7hfVTtd3jc1/GsnIg0v8v/rPzBc42Td6W13vn7tE87vlDycpLOWdv3ljhy6JyyY71qDRgD42EsbFHuWbUbjIepsD5M0/NoaD2Hxtwfeu4MHaEjdISO0BE6QkfoCB2hI3SEjv/143t4/r98cVbGnAWFC7+V5//N+vxvBz6ga91oBmPhBP/3Dt+wn/8vXzxLbr6YdVYu/X/5i4s8nvXVLf9inXresOz9/Xq1760nz55feFLsvMk+1LEe6wHcfhQZek++0Lh4UZGsuY2x7Uyz3alZuX3jhdnZWcH1kD+W69niR5xtv9ClH0/9cKwhvSKFP/Z61pfl+ouyanQ4MbD2tDeSeYkZ7GFtYIfxA7H7qNOvbvyxwzNc3DSxda2dFPs/w+9axnjMda+6aw31N2Jnk3GecaGasVJW/YnGnRW3MDG7z3DpuNO1t/Xl2pWBcIXLtXznt4t/KfcoQy/LDMd65Dm2nVhYT/xoxRxKHdXTZeo9NxKO+qwVrsmawR7OtbgpzvXMLcVuv3N+g9ylX0nLaYJr37uWxyroWCoSc7ssuXUsSVn513QiXSpzV6/WOVy24YWPD52efbj+62l9ln4/6zZ2WGVX638KbIBs0cRspjqR2sNGsCNEjC5wOewKr4Yp8BrYDZbC7vAO2ANugmlwM+wLt8KB8GE4GL4Ph8CP4EhYBkfBL/U+9UziBmPhGFnnyeGxFsS9DgSz0Hxc6AgdoSN0hI7QETpCR+j4jo7v4fk//9vU/7/V8fz/VS1DjswwxvvKNAb26a/Zz//53vr/9blK9rNa9pPDxvA1uO6+dxzzAXqNf7FOXf045pK4j3C4Lzb6mZN8v7Xd67XK5wfU/T6xc9zXz8w2Y/V5dsRh0eNttjeTbb1tA/1muErQZ9Knxd1+38s8pQwyF5rWvs+nxN79ts7o0iMSPn2mR2OzXM9E43akmYz/HnMShLt6uvux76W7336OnyPX7zcbG9dpHC03n5sz2W1l+aXmXnry5b6Jjvsmil23XvyIgK5f7Awh7oHj7tf9djqIWQPN101iNtBTf77h2E9+mfg/POxWsyaTDDUdz/eFoh/bSvMMSdNLjSSdUzgq7nb4elHSx3HH5ublZoLqKT8g1476YtjNNZYvDms5sPKFPKmgE9/WDX6fuP21rz651Jyv0G0yo01LN/4jcu010Y3/FqtHxlAmrL3OD0l8HzPPp6bcyvX72PUcq+VhvpSPkaRdspglOMzCVJd6uB2+ZLM7Xx218vAhuacvbAJl19aXrjqgLR3gBWJnYNgNZi2+y13LS5e9+LVb/L9Lz4PltjJ98r8R+z+oUM4r09u+UMLxtjmKlNG4W3GSulBOH7td77ZI2kXb910u/rSx549qih+zzUessNvpF26n3T3ipkHYXNLJVYYceuiniT8T7f3ph8XNTl8/vox/BX69ZDyFW6454mr5f6247Wz+2eihehvcOtMjqqAzXfx0nOdzbulMH3nE1o/e3VCzwUEzW0957yMVdaunHKmoW73zkYq61VsfqahbvemRirrV449U1K2+6HXbzA7fP9g7E/AoiiwAV/dMJichhCMREgi3cuaCAAICIobIBuUWUEAORbkvQRHwBuVGV1YFdBURQcFjQS5BBQRFxfXCFRUQFV1WAVFBUfefl5qamUxPDCvLt8c0X/GnXtfVVdU9/V5VVw3yy0z5evtlpnxd/DJTvks+DF1Hva1fZsqX55eZ8jU=
*/