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

struct BOOST_SYMBOL_VISIBLE utf8_codecvt_facet :
    public std::codecvt<wchar_t, char, std::mbstate_t>
{
public:
    BOOST_UTF8_DECL explicit utf8_codecvt_facet(std::size_t no_locale_manage = 0);
    BOOST_UTF8_DECL virtual ~utf8_codecvt_facet();

protected:
    BOOST_UTF8_DECL virtual std::codecvt_base::result do_in(
        std::mbstate_t& state,
        const char * from,
        const char * from_end,
        const char * & from_next,
        wchar_t * to,
        wchar_t * to_end,
        wchar_t * & to_next
    ) const;

    BOOST_UTF8_DECL virtual std::codecvt_base::result do_out(
        std::mbstate_t & state,
        const wchar_t * from,
        const wchar_t * from_end,
        const wchar_t * & from_next,
        char * to,
        char * to_end,
        char * & to_next
    ) const;

    bool invalid_continuing_octet(unsigned char octet_1) const {
        return (octet_1 < 0x80|| 0xbf< octet_1);
    }

    bool invalid_leading_octet(unsigned char octet_1) const {
        return (0x7f < octet_1 && octet_1 < 0xc0) ||
            (octet_1 > 0xfd);
    }

    // continuing octets = octets except for the leading octet
    static unsigned int get_cont_octet_count(unsigned char lead_octet) {
        return get_octet_count(lead_octet) - 1;
    }

    BOOST_UTF8_DECL static unsigned int get_octet_count(unsigned char lead_octet);

    // How many "continuing octets" will be needed for this word
    // ==   total octets - 1.
    BOOST_UTF8_DECL static int get_cont_octet_out_count(wchar_t word);

    virtual bool do_always_noconv() const BOOST_NOEXCEPT_OR_NOTHROW {
        return false;
    }

    // UTF-8 isn't really stateful since we rewind on partial conversions
    virtual std::codecvt_base::result do_unshift(
        std::mbstate_t &,
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
    BOOST_UTF8_DECL virtual int do_length(
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