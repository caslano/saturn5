#ifndef GREGORIAN_HPP__
#define GREGORIAN_HPP__

/* Copyright (c) 2002-2004 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst 
 * $Date$
 */

/*! @file gregorian.hpp
  Single file header that provides overall include for all elements of 
  the gregorian date-time system.  This includes the various types 
  defined, but also other functions for formatting and parsing.
*/


#include "boost/date_time/compiler_config.hpp"
#include "boost/date_time/gregorian/gregorian_types.hpp"
#include "boost/date_time/gregorian/conversion.hpp"
#if defined(BOOST_DATE_TIME_INCLUDE_LIMITED_HEADERS)
#include "boost/date_time/gregorian/formatters_limited.hpp"
#else
#include "boost/date_time/gregorian/formatters.hpp"
#endif

#if defined(USE_DATE_TIME_PRE_1_33_FACET_IO)
#include "boost/date_time/gregorian/greg_facet.hpp"
#else
#include "boost/date_time/gregorian/gregorian_io.hpp"
#endif // USE_DATE_TIME_PRE_1_33_FACET_IO

#include "boost/date_time/gregorian/parsers.hpp"



#endif

/* gregorian.hpp
CEejZW81G2asrGPj53XaOJ7u76QhuqQHf5xHuY3B19I2mDL3i01ojvZIhqTRgdF3VU12hGZMSkKshN6WBQP5uwpsiXQzr6P08jGDYl+fG6w7TikDK6Yy9SpjCHm/czkV6OFdslpdn33p0ihmEvoTlZwLe3d7FyV4Xud6EoKIV8ZwKXE6DWtx/h5aNIHNEqSrEdwPFB4fFBBLZBGoIJARp4+Tx/t6v+Qboj90DF8ydV9Y/To0KNvLBhz7YH3pTiSvA2e1FNImtxdBFSgQNJrudNKdN+wmtwne6EBvBGCjZgEeaIkyYbBPCmh5HiLJ+xeGEZ45yBsx4nQ+DTgmkpiJ1fZdiIWNl9ZGi5hpCKcCkS0iSg/xckP0SC9Z9Im1rQYOXh36Dw3sXBP9bSx5A3mArFaZLL2FV1dcH1onXaOaM2tcQ9GStq5s8ZxInnlMWnjROeXFeojtCjym2m/GSX+ElYWIKAn1BGJVDcz9bQXbKdjlD5lT1Bj/QLu5FV3uW1QxYXrnYaqinGJ+W4r5nfvWpS2rbpektg4G/wfe9AaC9d9E2JhXDOLOJy2u9alOHUn8KdC20S5XsQJR0lOdCwsQqyX2OH8CbJcbur3CKL8729JA2umMaOSYucznd6kG7dDxiTg2sS3KspM/cTNbQJu3K1o9m9q30mfmrHlkopxeBfj/FYaBDSRnDwgAO0XhYYMtOp9xngF8j/N8ry0j
*/