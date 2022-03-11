// Copyright (c) 2001 Ronald Garcia, Indiana University (garcia@osl.iu.edu)
// Andrew Lumsdaine, Indiana University (lums@osl.iu.edu).
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_UTF8_CODECVT_FACET_HPP
#define BOOST_UTF8_CODECVT_FACET_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// utf8_codecvt_facet.hpp

// This header defines class utf8_codecvt_facet, derived from 
// std::codecvt<wchar_t, char>, which can be used to convert utf8 data in
// files into wchar_t strings in the application.
//
// The header is NOT STANDALONE, and is not to be included by the USER.
// There are at least two libraries which want to use this functionality, and
// we want to avoid code duplication. It would be possible to create utf8
// library, but:
// - this requires review process first
// - in the case, when linking the a library which uses utf8 
//   (say 'program_options'), user should also link to the utf8 library.
//   This seems inconvenient, and asking a user to link to an unrevieved 
//   library is strange. 
// Until the above points are fixed, a library which wants to use utf8 must:
// - include this header in one of it's headers or sources
// - include the corresponding boost/detail/utf8_codecvt_facet.ipp file in one
//   of its sources
// - before including either file, the library must define
//   - BOOST_UTF8_BEGIN_NAMESPACE to the namespace declaration that must be used
//   - BOOST_UTF8_END_NAMESPACE to the code to close the previous namespace
//     declaration.
//   - BOOST_UTF8_DECL -- to the code which must be used for all 'exportable'
//     symbols.
//
// For example, program_options library might contain:
//    #define BOOST_UTF8_BEGIN_NAMESPACE <backslash character> 
//             namespace boost { namespace program_options {
//    #define BOOST_UTF8_END_NAMESPACE }}
//    #define BOOST_UTF8_DECL BOOST_PROGRAM_OPTIONS_DECL
//    #include <boost/detail/utf8_codecvt_facet.ipp>
//
// Essentially, each library will have its own copy of utf8 code, in
// different namespaces. 

// Note:(Robert Ramey).  I have made the following alterations in the original
// code.
// a) Rendered utf8_codecvt<wchar_t, char>  with using templates
// b) Move longer functions outside class definition to prevent inlining
// and make code smaller
// c) added on a derived class to permit translation to/from current
// locale to utf8

//  See http://www.boost.org for updates, documentation, and revision history.

// archives stored as text - note these ar templated on the basic
// stream templates to accommodate wide (and other?) kind of characters
//
// note the fact that on libraries without wide characters, ostream is
// is not a specialization of basic_ostream which in fact is not defined
// in such cases.   So we can't use basic_ostream<OStream::char_type> but rather
// use two template parameters
//
// utf8_codecvt_facet
//   This is an implementation of a std::codecvt facet for translating 
//   from UTF-8 externally to UCS-4.  Note that this is not tied to
//   any specific types in order to allow customization on platforms
//   where wchar_t is not big enough.
//
// NOTES:  The current implementation jumps through some unpleasant hoops in
// order to deal with signed character types.  As a std::codecvt_base::result,
// it is necessary  for the ExternType to be convertible to unsigned  char.
// I chose not to tie the extern_type explicitly to char. But if any combination
// of types other than <wchar_t,char_t> is used, then std::codecvt must be
// specialized on those types for this to work.

#include <locale>
#include <cwchar>   // for mbstate_t
#include <cstddef>  // for std::size_t

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std {
    using ::mbstate_t;
    using ::size_t;
}
#endif

// maximum lenght of a multibyte string
#define MB_LENGTH_MAX 8

BOOST_UTF8_BEGIN_NAMESPACE

//----------------------------------------------------------------------------//
//                                                                            //
//                          utf8_codecvt_facet                                //
//                                                                            //
//            See utf8_codecvt_facet.ipp for the implementation.              //
//----------------------------------------------------------------------------//

#ifndef BOOST_UTF8_DECL
#define BOOST_UTF8_DECL
#endif

struct BOOST_UTF8_DECL utf8_codecvt_facet :
    public std::codecvt<wchar_t, char, std::mbstate_t>  
{
public:
    explicit utf8_codecvt_facet(std::size_t no_locale_manage=0);
    virtual ~utf8_codecvt_facet();
protected:
    virtual std::codecvt_base::result do_in(
        std::mbstate_t& state, 
        const char * from,
        const char * from_end, 
        const char * & from_next,
        wchar_t * to, 
        wchar_t * to_end, 
        wchar_t*& to_next
    ) const;

    virtual std::codecvt_base::result do_out(
        std::mbstate_t & state,
        const wchar_t * from,
        const wchar_t * from_end,
        const wchar_t*  & from_next,
        char * to,
        char * to_end,
        char * & to_next
    ) const;

    bool invalid_continuing_octet(unsigned char octet_1) const {
        return (octet_1 < 0x80|| 0xbf< octet_1);
    }

    bool invalid_leading_octet(unsigned char octet_1)   const {
        return (0x7f < octet_1 && octet_1 < 0xc0) ||
            (octet_1 > 0xfd);
    }

    // continuing octets = octets except for the leading octet
    static unsigned int get_cont_octet_count(unsigned char lead_octet) {
        return get_octet_count(lead_octet) - 1;
    }

    static unsigned int get_octet_count(unsigned char lead_octet);

    // How many "continuing octets" will be needed for this word
    // ==   total octets - 1.
    int get_cont_octet_out_count(wchar_t word) const ;

    virtual bool do_always_noconv() const BOOST_NOEXCEPT_OR_NOTHROW {
        return false;
    }

    // UTF-8 isn't really stateful since we rewind on partial conversions
    virtual std::codecvt_base::result do_unshift(
        std::mbstate_t&,
        char * from,
        char * /*to*/,
        char * & next
    ) const {
        next = from;
        return ok;
    }

    virtual int do_encoding() const BOOST_NOEXCEPT_OR_NOTHROW {
        const int variable_byte_external_encoding=0;
        return variable_byte_external_encoding;
    }

    // How many char objects can I process to get <= max_limit
    // wchar_t objects?
    virtual int do_length(
        std::mbstate_t &,
        const char * from,
        const char * from_end, 
        std::size_t max_limit
    ) const
#if BOOST_WORKAROUND(__IBMCPP__, BOOST_TESTED_AT(600))
    throw()
#endif
    ;

    // Nonstandard override
    virtual int do_length(
        const std::mbstate_t & s,
        const char * from,
        const char * from_end, 
        std::size_t max_limit
    ) const
#if BOOST_WORKAROUND(__IBMCPP__, BOOST_TESTED_AT(600))
    throw()
#endif
    {
        return do_length(
            const_cast<std::mbstate_t &>(s),
            from,
            from_end,
            max_limit
        );
    }

    // Largest possible value do_length(state,from,from_end,1) could return.
    virtual int do_max_length() const BOOST_NOEXCEPT_OR_NOTHROW {
        return 6; // largest UTF-8 encoding of a UCS-4 character
    }
};

BOOST_UTF8_END_NAMESPACE

#endif // BOOST_UTF8_CODECVT_FACET_HPP

/* utf8_codecvt_facet.hpp
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
*/