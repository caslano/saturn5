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
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
*/