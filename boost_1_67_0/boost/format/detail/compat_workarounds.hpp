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