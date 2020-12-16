// ----------------------------------------------------------------------------
//  compat_workarounds : general framework for non-conformance workarounds
// ----------------------------------------------------------------------------

//  Copyright Samuel Krempp 2003. Use, modification, and distribution are
//  subject to the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// see http://www.boost.org/libs/format for library home page

// ----------------------------------------------------------------------------


//  this file defines  wrapper classes to hide non-conforming 
// std::char_traits<>  and std::allocator<> traits
//  and Includes : config_macros.hpp (defines config macros
//  and compiler-specific switches)

// Non-conformant Std-libs fail to supply conformant traits (std::char_traits,
//  std::allocator) and/or  the std::string doesnt support them.
// We don't want to have hundreds of #ifdef workarounds, so we define 
// replacement traits.
// But both char_traits and allocator traits are visible in the interface, 
// (inside the final string type),  thus we need to keep both 
// the replacement type (typedefed to 'compatible_type') for real use,
// and the original stdlib type (typedef to 'type_for_string') for interface
//  visibility. This is what Compat* classes do (as well as be transparent 
// when good allocator and char traits are present)

#ifndef BOOST_FORMAT_COMPAT_WORKAROUNDS_HPP
#define BOOST_FORMAT_COMPAT_WORKAROUNDS_HPP

namespace boost {
    namespace io {

        // gcc-2.95 char traits (non-conformantly named string_char_traits) 
        // lack several functions so we extend them in a replacement class.
        template<class Tr>
        class CompatTraits; 

        // std::allocator<Ch> in gcc-2.95 is ok, but basic_string only works 
        // with plain 'std::alloc' still, alt_stringbuf requires a functionnal
        // alloc template argument, so we need a replacement allocator
        template<class Alloc>
        class CompatAlloc; 
    } // N.S. io
}// N.S. boost


#include <boost/format/detail/config_macros.hpp>
   // sets-up macros and load compiler-specific workarounds headers.

#if !defined(BOOST_FORMAT_STREAMBUF_DEFINED)
// workarounds-gcc-2.95 might have defined own streambuf
#include <streambuf>
#endif

#if !defined(BOOST_FORMAT_OSTREAM_DEFINED)
// workarounds-gcc-2.95 might already have included <iostream>
#include <ostream>
#endif



namespace boost {
    namespace io {

        // **** CompatTraits general definitions : ----------------------------
        template<class Tr>
        class CompatTraits
        {        // general case : be transparent
        public:
            typedef Tr  compatible_type;
        };

        // **** CompatAlloc general definitions : -----------------------------
        template<class Alloc>
        class CompatAlloc
        {        // general case : be transparent
        public:
            typedef Alloc  compatible_type;
        };

    } //N.S. io
} // N.S. boost
#endif // include guard

/* compat_workarounds.hpp
BCYWDEgTwng5g6vqrJCey1V92BgvZ6iqTrwIVX0M7tRIOkVHaJxtZv6bpha1NFrU0kCQAXVD56GYHi2o5P8OIpQsWNgDTcU43LjQ2qy+r3gXLg1SxJ3FOKvFLjivhCVtRfuWSNIecxXZRcPGLiHeVwbpguEqcwhOSv/vdFLl9SlIEGk5Uy4JJxd8eUTT42mgh31+LL2gQh2edm/COw1wk5kjUdv9nb3lAUdDEGq3ZlbKHxvKm/KzsY6/7oRdoglTXNJxR7IWUVf6ZXTGVlshPVie2us3agYTP2PI/vQi4czrxlC0P2fsbhG0/5WAlogbbBG0Px+Kfo0mCQBT810T2fAzA7b6nu6yq5p4V8HP7rIrCAa3asKv1Crtq33llQ7hzbjvtkHfog9BfpsD3RCWrTiGbxPw79L1APgWXwOGlwEV81NTgKzte6OcB+q89uQI/B9/KZf8ee5/v0kwpK43tn3l0Oke8LIghw0kYIdLA8HC/142f+RsgJos6HhIX1OtBcHZGAaMJi4Ed/OpFKccD+bucjRC9C/aGg7SN971M7VSXGffWx6OfdaVWMZo33Ny9JFw7ZFmG+vL/lvo+jhrS86qfX1Q5AoFz2SEN3VPeVj2Pt84zYX8Ldj/QXn49k1Xng5uf61w2p9D7eeyzKGRbimZ06cnPrIs1kQzLCOIQRRKRoDsvgxycsOs+6sXxpqUsygU4Q/k5ez9RFjOFuFydgsJiF8gbvtfhal1l7vkeubxPZ3IZ4IfXjRSTcRvG8KQViEkt4L0R4LkK6yMK85bScF76NMMRnbNAtqnr3SXjODaOyVKblA70o7M4SobBiLfhau0/ZutIAfXEmSef/5JHtNVti8sgrNm1NGeCe2oI/YUNCr2VJsY0NWMIuKGT0oQuREiPausbqTXGgqThomw5wNpPB2SjIe067EDf54XGxCZCteN3ZARaTEJM9MPM1rCLFsM11paKN24IpsDMkEltQIq0QtsqOSBCadbQwLw227bxIzpYw2ipM/NBYiDmimMw0utA3Eoa61w+FsDgUNvxAFJLx0WRCPPrj0AmB8EYLEfwEsSwG+LYk3sgscFLRgOOXyxgOoAeCBwJXaDJXJXsdXcA4ZjoYVNuaMaK9aYXmby1jVEFFvLaOi67MLW9gJ2nkqcyRt/UULZf9bOfxX7L5FHzEk6/gNPRXmFOS3gEB3shvy9H8t5EsovOEx+Dy+Dt8m6Eo9cgWMU17p+FCiC/qVcF2aJhhXGhr7wHsqV55UMDcks6XLI7K2FfyK8432TtA9xb8KN1+92N36HqfeAkSALc9ErePVIZwYn62IqB0JL0rIzIVdDyakmO8PZcFHO9tCv0SYWxPls2hDrkQtS7tFbvjgX1u2WTeZh6KDQQuGPFP81hR9QuB9Cmf8pCl2Ucw09L6dwNoW5FA6mcD6FeyjcZ4DzJoV/o/AghYcpfIfC9wz1di7A8IgXw08oPErh5xR+6SU8KXRSzoYUxlJ4luI3GPK/4yV8KCzxEv6UczyFEynMo3AyhVMLqF0F1K5CaheFGRD6+3HixPimy018Y/UbR1ZRQkpW0egU+4Au5VkgS0jKantwQHyftydkFTdu6YBMA3q9fSK//kT3ks9Nxwas2mQ6BoyePREUXfB9VjGULobSMJaOE+cezNDyGsCB9y8Qjqcpa9BpWqO/lZ/XlENlUDmsEg8WQU9L/mwuf58cX6ZZ+IJ1a4qAqWw1GJyFR8jU337qQ2ShtWA1Y/YizUdNq9ng3A+ELyiNYWurbnnpW926YOuhroiU+Pjtu6DGVipml2alyCm7HEyLOoMdXQs7dBypdLj6nim/FHeiDfOhV9xlP0SbToAgo6zMMfE=
*/