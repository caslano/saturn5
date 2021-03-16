//  (c) Copyright Fernando Luis Cacciola Carballal 2000-2004
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/numeric/conversion
//
// Contact the author at: fernando_cacciola@hotmail.com
//
//
//  Revision History
//
//    19 Nov 2001 Syntatic changes as suggested by Darin Adler (Fernando Cacciola)
//    08 Nov 2001 Fixes to accommodate MSVC (Fernando Cacciola)
//    04 Nov 2001 Fixes to accommodate gcc2.92 (Fernando Cacciola)
//    30 Oct 2001 Some fixes suggested by Daryle Walker (Fernando Cacciola)
//    25 Oct 2001 Initial boostification (Fernando Cacciola)
//    23 Jan 2004 Inital add to cvs (post review)s
//    22 Jun 2011 Added support for specializing cast policies via numeric_cast_traits (Brandon Kohn).
//
#ifndef BOOST_NUMERIC_CONVERSION_CAST_25OCT2001_HPP
#define BOOST_NUMERIC_CONVERSION_CAST_25OCT2001_HPP

#include <boost/detail/workaround.hpp>

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x582))

#  include<boost/numeric/conversion/detail/old_numeric_cast.hpp>

#else

#include <boost/type.hpp>
#include <boost/numeric/conversion/converter.hpp>
#include <boost/numeric/conversion/numeric_cast_traits.hpp>

namespace boost
{
    template <typename Target, typename Source> 
    inline Target numeric_cast( Source arg )
    {
        typedef numeric::conversion_traits<Target, Source>   conv_traits;
        typedef numeric::numeric_cast_traits<Target, Source> cast_traits;
        typedef boost::numeric::converter
            <
                Target,
                Source, 
                conv_traits,
                typename cast_traits::overflow_policy, 
                typename cast_traits::rounding_policy, 
                boost::numeric::raw_converter< conv_traits >,
                typename cast_traits::range_checking_policy
            > converter;
        return converter::convert(arg);
    }
    
    using numeric::bad_numeric_cast;
} // namespace boost

#endif

#endif

/* cast.hpp
oziVK/d6TchEuiG6gPlpV4pnkoXew9rjBa0Gz9FM/1Lo7acu1zvE+945WGtPpp8YI2arsFA3F1+g0slitr4K9YrMmMfFg9NUutFJcU09iL+2TE2xt64X08t+J11Tq5ed734fq78hXb162ZJurbp26fNA1VVLRZz+6GVr1sDT6urm4cORJ4qcFCzpXqdME5hj6slw2wIyjY6he5BpcAyfZ6FL0CMiLzueOz2Cft1tuV2BRLyeHuDRwIeAs0Sfmog=
*/