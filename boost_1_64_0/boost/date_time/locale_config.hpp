#ifndef DATE_TIME_LOCALE_CONFIG_HPP___
#define DATE_TIME_LOCALE_CONFIG_HPP___

/* Copyright (c) 2002-2020 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland
 * $Date$
 */

// This file configures whether the library will support locales and hence
// iostream based i/o.  Even if a compiler has some support for locales,
// any failure to be compatible gets the compiler on the exclusion list.
//
// At the moment this is defined for MSVC 6 and any compiler that
// defines BOOST_NO_STD_LOCALE (gcc 2.95.x)

#include "boost/config.hpp" //sets BOOST_NO_STD_LOCALE
#include "boost/config/workaround.hpp"

//This file basically becomes a noop if locales are not properly supported
#if (defined(BOOST_NO_STD_LOCALE)  \
 || (BOOST_WORKAROUND( BOOST_MSVC, < 1300)) \
 || (BOOST_WORKAROUND( __BORLANDC__, BOOST_TESTED_AT( 0x581 )) ) \
 || (BOOST_WORKAROUND( BOOST_XLCPP_ZOS, BOOST_TESTED_AT( 0x42010000 )) ) /* <cctype> "shadows" the locale enabled overloads from <locale> */ \
 )
#define BOOST_DATE_TIME_NO_LOCALE
#endif


#endif


/* locale_config.hpp
iWI3lAuRwxM3VaRlPIff7cYj4wjn2A3q2X+9OPsHWJSFCbUww/ARG9Lk4QRWSnvfJklYru+oDcBVlZsB1BNnrPNKSXGW5Iw3fN2IWr077QbBuEYzZiLpeguhuYKhqdKj+T2hOVc2Vtmb2Ur49koaIVXJ6yyfAUCMEL+Niskwq+1b+1gxe9VzOVUoAGrIk/+x4lj4ZFhZx5IY0P0tTQx4i8q5tweJAbpyJkE5YaY060kGVN0R4gOCmMwgrtZDnAQQkfMifl3rla72SCJg5yrrsiTFe1hcOzmS1KUOjYN/43d44ttL7XPK+VYv51tQ2DCJ+VaOynOab9jvemsRmoL4j8R0BbSbzc22IB58heBSv7qAf/MtLeKfubsZTtklTvHoAsiOehupKs1ofUqk28vw3yahHagcQ71tKxHUpMrNaxNSp/9ubfpP4RE6qgxGP9gcndZQNfghBzuh73dEZZwNPtmzybxjW66cPjO1+Ld72PRpm8In+1g52VPglaQQ7j1bh7q8h7qQ+Zxo9shwmY4UJ+2wtLHo2QypPO1E+aIEXpAAq/UGBK3nVin4NrS4NQhVz6ml0sTMoxY0Zy0o0rfgza9gYp7jZHur7XQw8yjyHLXzYWJtl54wC7ezrdVYzsmohH5UwpqutLXSlTAZS/gGMqhHDRXarmO7eoyBD1tw6xnOsytme7Ftns+7vyTuPY4GZAtUa9wGCAdSG79g/KoYM55Clf6mi0nHPot6Kz2VhVe8+s3Qnq5JtEcevcrudoXWwfAQ9Tid6jGxi0n3FMavhw/rcQfu0or4Lm2UPPAmjO0Yxnl6jJ9EAGwsggXsclbiJH2gCSJnbZxPcwzuDHALAdVJVc3pKciNYqkujY78nyuzihalMm7/mGNC/EFYxU02w5xiW9zFFquZcEiIyt37mVo5L+YfTZV712NSuXvAyCPSI9KSapbGakarTIMYC+oqc8RG6r/0MY1XvBONgsgVRqkteFWAXY63ieDCeCNGhDfaTgYtfcighYZFKt3jeLGTnKjz5bCoCeFKEDmZjhfGACbyneY8w4XeGMirkTu04vgcG8tCnouddvrmJ+XJ+qSPF//i50YtvvzIVxrJ+0P8/PVq/h6vNFqKR1+DQLr4hDfuarQej17x31hEmKTfADzys+v4pT9bueInUqSpTBuuZcAVj4Sdc1DYoYPw9iL2dzYP5T1KoPMrWIT3RDirPQphx2B3wXq2lh3UVpwrD2oJgnuB4OxE9XUscuCtVeT7taqvALwTGkb9hwlgCQc0AI3NAKBZeqCiOuQ6cUF6IchQAOFOIHqgTkjJvEG4F4vCFSJ+uaFLCqXVq4jOqG/UrtVOqaTGCWVbwdSxZCFHZ2mYIs/SqkihL/Ac+KCRO0kwbQbmxzao9mcLWkEbFjibbkOavg0Y1D0MfRUzclCGSIrmwlYObRibOyVoN/Tcy43WfQ6Ex1ZzPBskHhKUCkN9spQ7yVOxfs8DEHualo7WTuF1DmGTqbjr7sR9cbttWsGDgExMmEiqS88i9AXqjJG3rEmlGhAq1YB2mTmml7MW3KdTqQZkry76Z6POxSSWuctOucplLvv71PcL4/V9OTmKw/TQ0ixMpUiS0WAWLq7X59Hl6tJpXAqoIrGlVNwmnIekPAGNu/kaDMUXMlOzCw+w4TsMd0LYLzZmTz4sWonkHxY+wW4cFbSppnB28hBzPdjKHDohp15lRsQS2EGogQqRiEuE9lrmevY9IuKyeESskGNP7hdawmQYTSezPkdlC9mat2Gl4qMoN8GkwqtMmUirSDP4RdIMsmy00Rv7J6ftymFO29FnO20XwqTLhN8fw7sRw47oZH8NnxJT/8/fsKUWuz0=
*/