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
KWiN9JlMfHuNfDjy6ewT2iAoJqu6u5WsixijOybEcW8EwgbS2lEKGY4VI49qsU2WpoQG/f5mPInfL8YbsdSFfsJEWHz1Gs3HgofTDnCZfb6/FrmTPZePSvLXdEAvG9bb9HPbXWkmURVLNUa1xNCL61B4X4PC21K9lJ98z/Xf49Knn46LJWPacSGe2cG/1zejwiG3hTA7l0vyaqnHl4WW5Sb2l5xa1GO1u5XkaYiBUCrNEK6A9dOv+7EFekNzMWa32Z+EhO6kGceHhwQ3+1umwsmaxXz4WqpfMqEj1K2wNjOTbwhAn0NctWz7ig9jweQ6vwnXeyPKlJIsWhwlmzlejft24QDkf0CXsyErNB+Fygty2mBSDUNMiKf1y9QdJ2NTrok9oMC9d2vO1y1FbB44UnWO6olwoEj/WaJi3QAPWnop1oYi8f3VPMe31CdC+ViiPmkru0J4uqxXPV0uaEO9byn1vjL96bMTFeSnV6HD8tAhQSc2aIMV8Tt2oTICKkm+Sd2n7lzEO2ASvcg7ggCx0GY0e9vZ9O0bWCl5CkyuDP+FU5HDdg542tTSiQ3UTcetJnIqnsQ0Jvun6CQiJ4E8YrrYlkJw6uifZD+yPsZ1rt3z82lttaT8f7R9CVxU1ff4ALKpOAPjCFkqJSWlKUULRiVToEMxSqVGuVEqUWmRMV8x94Byek5ii9mq7bbbJmimuCSYC2ilmBu2+YhU
*/