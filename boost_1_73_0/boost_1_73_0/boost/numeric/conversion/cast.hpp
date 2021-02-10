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
+9D6fTBkb1udUpvXEc0FEj5TNds5AtHtXwxYf/KB+Om77fHIgZ/KHfhu2Hmq74G9FfZZclYQdAbP8N22hLEJ3NMpD7cWMGVZBWVx7KTbgfXKbellprEFO3WStWOzsotWtzcZupuqL9ZHk3bbHY2s+En19BaSzTXs9M55lE+c1RZAhvuTXq+5IVXI6SIUbod1+91xURPRNA/VlIcM57w2G4q96w3etnqs1evVDye7HOV7uM4qWAnHRmqugMK5LfAA0T2AogzUCwWP0mXtW/ZQ/gb2k33lyvYzrhFfeOpp/J1T2lP0Io03B4jD5qNml4PR2IHTQ8wuum6vM+r+6bJea/jO3ZxvllM1mzFdJ5jHG2f4ngx/uMO3g5F7AJb8rB53B31n/ZXvAM9Oa9zCEWOO28etPw67Y3eVaP3wP8R3PVUxDR8/WUwc09rqhYyT4ueH+a2jUv34L6Uq9m9jZG5u9lzFc0U/SKiCTJEHCe4bSxgJXPD/gxoepmZnzkx2T1v8Nn//e/L2FnDyFAXAth/iL1uf5ZPbjt18pq5KfWDirs7AGo7wunmh+lr5F1BLAwQKAAAACAAtZ0pSh3fZrfoDAACNDwAAIwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2xpYnRlc3QvbGliMTUzNC5j
*/