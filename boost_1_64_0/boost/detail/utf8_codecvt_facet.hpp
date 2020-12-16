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
Mo9L5iuDoia7iYCUWZMTYI9zYOeQ0qzXAaJk8eUE2OMc2AQZu8f0PTxsZxXsxgjdGlhltl7PjL5Ed09FAQR191To7qnQ3ZeK7p4K3X3W89TdU/XuXs/V0PIJ6NzU9cTVjAnocwrocQboCCrDKYIZThHMcIpghhUqdo+IZTQqdMyTFzk0Z7lVdJCiM0R0gKJ7QrR1jaiwrhEqIAmHjh6QjEMGA+gUWz4YcQyRv1xGML/eg4DiFtjW9MaVA12RG9C7tBIvBVs3SWVKz/wrIABBg8ko0llNqZBIgv+Fe/ZjBDpZqy08ClpjB93CiMcP2MhKWUo0PqPQW/cihJfu+aLmxR4kFQoSHPhfjKzUp0EFtoM+/CuoQX75BRw/xh2idfX+3h1ZV0tQo4MmWgm6ttbW1RKYaG88QxNtUee6mhD4m19X/2smXmj5IZp4ZZaJV9bBiXcodqgZKC6miTMDajlD26Fm4P3H9TRxHujcoQ7DDkXramzynj1FxPNLlieRih3vixv/X+FULWyVSIbjOFXLlGsOa3iwRHKFjySSeKzD+7i7BNNcvzsL7LPhuRWey+HJgScZnrfPTHM156e5NsFzNzwz4QnBcwI8/4B0L8NzxZg016nwpMDzxwKQVcKzFJ7L4DkdnppQmmsyPCPg8cHz13PTXI3wrIbnunM7ZZKdv87ff8uvMKZ/6ln/OoD8IbUwhYggSHGbGLJaYAbvIim5uIl54SdXK33/pnVxf4q+14ttNJe2FlgvZTIdhpP59Jy4tCQqLRd+sUtLaluah0tztcYpzWMtbbdBhU2AX6zCdu/X87E03XhYyI9xq6aTgRkQiK5VkG6iMKMc/MFG/ZaGObAYAgVYiEMugJD29Y5WA2kYaalBNtcgdmtxKgtMNrVW7L6JVRj2TeyRELM0y0iwjrvYpaV0rHf+zd6ZwEVVxHF8QZDl3OVeBGSxLTdDJaGiT1RYVFtRUVnRbfdlRYlFl6VoYgupXR+77/u+TO0yK1nPgJI8SjE1F/HCsrto5s2+x2Pf25nfVHy6dj6f9+G9mf+8ebzv/Gbem3nzXzkP3v+uYDr/Xavo/ydF/4HvOtkPjLC5cI/6JlcfOHD3esh7xeDJczYbuVwa08tNWjlnMLWcvodxbOyAjUNo87f6aqMvX8wzmqczXneg/OiprWFa71nO0tDzicwNG8fGDtg4hDbsoTM4wWwM3vwiABtHSBuyX06vsChwhfRVlhoXBYw1MVMj8opcpX+rLqERFYFXlArlfZ8N0swMDNJU+RMievsKqNKP90QEIsroVWiP9G72SO8OXKKbJpK2UpBuF6Q7eOll3ERB4WWCwst4hXeczvymeYjftE7m09OjOfJy6iZA2Vfk2kR+acDQdKZgkG6mIOpZ5cX8l3PVF3NG3xdcQ3Q1wwfUMB9QU3vbCA3YRZSqaYDWfIBme9voDfq66if/1hWu+uaFC/s2euGhxwDYXRGk27npggGMMm4it3B2V7jpvMI7fujdmVdy+tFKWpU5NnbAxiG0odPNnIuooJk5NnbAxqG3kenMXw535jobbYqD9RFj/mwLdvRisAWrpE+ERYEnQnJcQR/O6PH/u4WjU02Bj+7G0JrdcUBPZ/9zuOb2Yc2d4fuLam7Pw5i7p3tyBxJM5+1TdPP2Ux5WHr5yzlMfvljt8Alqjz7dLki3ctNDJzLdCNLtgnQrN12fGCwFQedfyes/K0nBgnQ7N13Q+VdwEwWFVwgKr+AV3kTSAw/5FaoDHVoR9b92RLWjvgToZzuqgmc7qgK+Z2s/7DqFzD+Q7VmyNZJtDNk8ZHORzUq2c89JshxCtkFkiyTbxtFknRXZniTb5NHheYdwCIdwkAs=
*/