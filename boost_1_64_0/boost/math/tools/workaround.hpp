//  Copyright (c) 2006-7 John Maddock
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_TOOLS_WORHAROUND_HPP
#define BOOST_MATH_TOOLS_WORHAROUND_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/tools/config.hpp>

namespace boost{ namespace math{ namespace tools{
//
// We call this short forwarding function so that we can work around a bug
// on Darwin that causes std::fmod to return a NaN.  The test case is:
// std::fmod(1185.0L, 1.5L);
//
template <class T>
inline T fmod_workaround(T a, T b) BOOST_MATH_NOEXCEPT(T)
{
   BOOST_MATH_STD_USING
   return fmod(a, b);
}
#if (defined(macintosh) || defined(__APPLE__) || defined(__APPLE_CC__)) && ((LDBL_MANT_DIG == 106) || (__LDBL_MANT_DIG__ == 106))
template <>
inline long double fmod_workaround(long double a, long double b) BOOST_NOEXCEPT
{
   return ::fmodl(a, b);
}
#endif

}}} // namespaces

#endif // BOOST_MATH_TOOLS_WORHAROUND_HPP


/* workaround.hpp
Gy2jk7dC65hHeVmVbcXiMirEkVNHQzs8F8iD9S7L4rTaRp7tKZR3B5XX1FmUN3nCTq3M37Lk5OHY/DjFV00tZFxIX4dd3y53Mr5GeTgv8iQqWtumwZGjQfy5n5I25SwTdVoWMkMhrz4Lry3gmduiOXzBAYb58y9TmaKBBSytYtuuvsy7A5kqa3iUq2JbmajKdffG7UF+GQ2DRTAVUVHTfRn8WV/T2c2S9ZWVpQWXfAnfN95IysmYaNs0zmtPyfNDOGM7dXa4ZOtC63EyqIeqkyppm149tBELSDe3Aqe9i+gMx1xsL1JOwbRpNFx4Ohl2R17GwobrC+srwff3nX4Z01kWlXFuNaKrsLW6EtiXj6+YiJKibH370g92DAt+lx6+FMwdPKvzQiGPOTii/oHM52lZVTVRVKWc2PGRw4e7MFDrzpfX52tY1SrVRrLSKQNXl6BTFlSXwg3zRi1SWUVacAGTPYstD7xYRC5P1hbwER/wqi7Lir16QXulLq3ajFv0feJ5KitRjWzzDCbeBd3f8EBJrA3x2TDKujOUJQRMA8rwQeq3m5d0+jZrH13fXrhEx3WZxXWcCzY/n4CFb66vBO+hvwV48u4WJkadLJQNTt0MFrS8ES0ubsbggngLnePuInwZa3Ihc15Elg/MeH1tfXX97GDmdQPrRUlyfv4h4M+TPI+rSFn+zfWzQ+0TC/rU43uztxfe9RvSTlnWdQtVYEN4ulrjmQHmhv4Nta0C5uOohc/gjcHSglhbhGpC99FzmUPAQ/y9dSpvlcDgbWeWwECETtXpM3o+q+w31P6rSqapVCN5s2fX1pZWenlBW5+nZqLgqslKJ87jwruIV/6GjOVG5kWTpiMxLxhYxXnr7QrVGxg9h+Uw7WRYFhrX65zPM5XnKsnLGHhfmMz0sLcRbKpPK/OMMxztgO30+06iX8GyPEpUW3P7dQXjfb6FGUysLfTf23zY8mLO2ARWpDhyvPogHN4KtPPLm/oofBDsCS4S/oylhQJt89LxQxq+Pjvy/yqQn6dx0/JEOv4NuLeGp6tLYFmrq/BmKpB/dyC/gWVXtmXitR3EjzzXvYkocvlBfhuMW1nEWZ5myH8WhK/pO5B+vl3Li3GCy0J/5jte701po/ggjJvMCX8BgylL4I9C3Z89NYAYKuYFDr7aIWUskjJKJuNWxmnZjC2D3MRgO24L2lFmOc+iFnVwy6gDTe4fqEfYh+8P+AtYONK4lNvwb4R98C3CL1jaNE3SVsgPLy5ayK25cWZzfhDE9/h5ILsquEzyIrW8uJGHafv08uZqWPc/h3VPYllXqsD+H/G9aH55iJ7pyL/7d/RbIilhAs5S7MN1OP9sC1XZV8nhvv2gz1+ylGdFFtVGPDT75mS4udJ7r3ac8sSZrHLZtB2Pv94OOh1LUk/Bcl4VMEkIIkj/YxbetqzR/eMrCW/O0rgoyrJoCa/ZcellxnOy93ID30rKaGCOKtq2bEtaBnx8jTInmeM8ryEs7eYrUk7NmrqQVdS0vXKi0X1hYwwf9xLuezPotyzN2zpXGS0HHqDrKdO9e8K7lEuEv2SZjKE5svL5ceMIU69+TxnshScv0zqkMs1kJIXfkTCJDE8f16Nn0MstvZ/wcyZE1MZ1nhN+s4l2g5Y5G/J5a1aovKnjOnKHWtOLS4Opw3Qdl4G8MoryJpYKmdbWg2eCzNkQ4VUgsOF1nFSewDN6sYF/nFnVG7PBmfln2DLc+y+/DO3FkLVtnEW0iI11O7946+N/Obtu4LyWKmxyzjknw1BQgG09LIbBm3MCmzTDDAhZ2AJZEpJMGgoKCgoKCgoKCgoKCgoKCgoKCgpmCENBQUFBQUHOOe/e/94=
*/