#ifndef BOOST_SERIALIZATION_CONFIG_HPP
#define BOOST_SERIALIZATION_CONFIG_HPP

//  config.hpp  ---------------------------------------------//

//  (c) Copyright Robert Ramey 2004
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/serialization

//----------------------------------------------------------------------------//

// This header implements separate compilation features as described in
// http://www.boost.org/more/separate_compilation.html

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

// note: this version incorporates the related code into the the
// the same library as BOOST_ARCHIVE.  This could change some day in the
// future

// if BOOST_SERIALIZATION_DECL is defined undefine it now:
#ifdef BOOST_SERIALIZATION_DECL
    #undef BOOST_SERIALIZATION_DECL
#endif

// we need to import/export our code only if the user has specifically
// asked for it by defining either BOOST_ALL_DYN_LINK if they want all boost
// libraries to be dynamically linked, or BOOST_SERIALIZATION_DYN_LINK
// if they want just this one to be dynamically liked:
#if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_SERIALIZATION_DYN_LINK)
    #if !defined(BOOST_DYN_LINK)
        #define BOOST_DYN_LINK
    #endif
    // export if this is our own source, otherwise import:
    #if defined(BOOST_SERIALIZATION_SOURCE)
        #define BOOST_SERIALIZATION_DECL BOOST_SYMBOL_EXPORT
    #else
        #define BOOST_SERIALIZATION_DECL BOOST_SYMBOL_IMPORT
    #endif // defined(BOOST_SERIALIZATION_SOURCE)
#endif // defined(BOOST_ALL_DYN_LINK) || defined(BOOST_SERIALIZATION_DYN_LINK)

// if BOOST_SERIALIZATION_DECL isn't defined yet define it now:
#ifndef BOOST_SERIALIZATION_DECL
    #define BOOST_SERIALIZATION_DECL
#endif

//  enable automatic library variant selection  ------------------------------//

#if !defined(BOOST_ALL_NO_LIB) && !defined(BOOST_SERIALIZATION_NO_LIB) \
&&  !defined(BOOST_ARCHIVE_SOURCE) && !defined(BOOST_WARCHIVE_SOURCE)  \
&&  !defined(BOOST_SERIALIZATION_SOURCE)
    //
    // Set the name of our library, this will get undef'ed by auto_link.hpp
    // once it's done with it:
    //
    #define BOOST_LIB_NAME boost_serialization
    //
    // If we're importing code from a dll, then tell auto_link.hpp about it:
    //
    #if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_SERIALIZATION_DYN_LINK)
    #  define BOOST_DYN_LINK
    #endif
    //
    // And include the header that does the work:
    //
    #include <boost/config/auto_link.hpp>

#endif

#endif // BOOST_SERIALIZATION_CONFIG_HPP

/* config.hpp
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
*/