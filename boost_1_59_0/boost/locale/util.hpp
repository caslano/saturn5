//
//  Copyright (c) 2009-2011 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_LOCALE_UTIL_HPP
#define BOOST_LOCALE_UTIL_HPP
#include <locale>
#include <typeinfo>
#include <boost/cstdint.hpp>
#include <boost/locale/utf.hpp>
#include <boost/locale/generator.hpp>
#include <boost/assert.hpp>

#include <vector>
namespace boost {
namespace locale {
///
/// \brief This namespace provides various utility function useful for Boost.Locale backends
/// implementations
///
namespace util {
    
    ///
    /// \brief Return default system locale name in POSIX format.
    ///
    /// This function tries to detect the locale using, LC_CTYPE, LC_ALL and LANG environment
    /// variables in this order and if all of them unset, in POSIX platforms it returns "C"
    /// 
    /// On Windows additionally to check the above environment variables, this function
    /// tries to creates locale name from ISO-339 and ISO-3199 country codes defined
    /// for user default locale.
    /// If \a use_utf8_on_windows is true it sets the encoding to UTF-8, otherwise, if system
    /// locale supports ANSI code-page it defines the ANSI encoding like windows-1252, otherwise it fall-backs
    /// to UTF-8 encoding if ANSI code-page is not available.
    ///
    BOOST_LOCALE_DECL
    std::string get_system_locale(bool use_utf8_on_windows = false);

    ///
    /// \brief Installs information facet to locale in based on locale name \a name
    ///
    /// This function installs boost::locale::info facet into the locale \a in and returns
    /// newly created locale.
    ///
    /// Note: all information is based only on parsing of string \a name;
    ///
    /// The name has following format: language[_COUNTRY][.encoding][\@variant]
    /// Where language is ISO-639 language code like "en" or "ru", COUNTRY is ISO-3166
    /// country identifier like "US" or "RU". the Encoding is a charracter set name
    /// like UTF-8 or ISO-8859-1. Variant is backend specific variant like \c euro or
    /// calendar=hebrew.
    ///
    /// If some parameters are missing they are specified as blanks, default encoding
    /// is assumed to be US-ASCII and missing language is assumed to be "C"
    ///
    BOOST_LOCALE_DECL
    std::locale create_info(std::locale const &in,std::string const &name); 


    ///
    /// \brief This class represent a simple stateless converter from UCS-4 and to UCS-4 for
    ///  each single code point
    ///
    /// This class is used for creation of std::codecvt facet for converting utf-16/utf-32 encoding
    /// to encoding supported by this converter
    ///
    /// Please note, this converter should be fully stateless. Fully stateless means it should
    /// never assume that it is called in any specific order on the text. Even if the
    /// encoding itself seems to be stateless like windows-1255 or shift-jis, some
    /// encoders (most notably iconv) can actually compose several code-point into one or
    /// decompose them in case composite characters are found. So be very careful when implementing
    /// these converters for certain character set.
    ///
    class base_converter {
    public:

        ///
        /// This value should be returned when an illegal input sequence or code-point is observed:
        /// For example if a UCS-32 code-point is in the range reserved for UTF-16 surrogates
        /// or an invalid UTF-8 sequence is found
        ///
        static const uint32_t illegal=utf::illegal;

        ///
        /// This value is returned in following cases: The of incomplete input sequence was found or 
        /// insufficient output buffer was provided so complete output could not be written.
        ///
        static const uint32_t incomplete=utf::incomplete;
        
        virtual ~base_converter() 
        {
        }
        ///
        /// Return the maximal length that one Unicode code-point can be converted to, for example
        /// for UTF-8 it is 4, for Shift-JIS it is 2 and ISO-8859-1 is 1
        ///
        virtual int max_len() const 
        {
            return 1;
        }
        ///
        /// Returns true if calling the functions from_unicode, to_unicode, and max_len is thread safe.
        ///
        /// Rule of thumb: if this class' implementation uses simple tables that are unchanged
        /// or is purely algorithmic like UTF-8 - so it does not share any mutable bit for
        /// independent to_unicode, from_unicode calls, you may set it to true, otherwise,
        /// for example if you use iconv_t descriptor or UConverter as conversion object return false,
        /// and this object will be cloned for each use.
        ///
        virtual bool is_thread_safe() const 
        {
            return false;
        }
        ///
        /// Create a polymorphic copy of this object, usually called only if is_thread_safe() return false
        ///
        virtual base_converter *clone() const 
        {
            BOOST_ASSERT(typeid(*this)==typeid(base_converter));
            return new base_converter();
        }

        ///
        /// Convert a single character starting at begin and ending at most at end to Unicode code-point.
        ///
        /// if valid input sequence found in [\a begin,\a code_point_end) such as \a begin < \a code_point_end && \a code_point_end <= \a end
        /// it is converted to its Unicode code point equivalent, \a begin is set to \a code_point_end
        ///
        /// if incomplete input sequence found in [\a begin,\a end), i.e. there my be such \a code_point_end that \a code_point_end > \a end
        /// and [\a begin, \a code_point_end) would be valid input sequence, then \a incomplete is returned begin stays unchanged, for example
        /// for UTF-8 conversion a *begin = 0xc2, \a begin +1 = \a end is such situation.
        ///
        /// if invalid input sequence found, i.e. there is a sequence [\a begin, \a code_point_end) such as \a code_point_end <= \a end
        /// that is illegal for this encoding, \a illegal is returned and begin stays unchanged. For example if *begin = 0xFF and begin < end
        /// for UTF-8, then \a illegal is returned.
        /// 
        ///
        virtual uint32_t to_unicode(char const *&begin,char const *end) 
        {
            if(begin == end)
                return incomplete;
            unsigned char cp = *begin;
            if(cp <= 0x7F) {
                begin++;
                return cp;
            }
            return illegal;
        }
        ///
        /// Convert a single code-point \a u into encoding and store it in [begin,end) range.
        ///
        /// If u is invalid Unicode code-point, or it can not be mapped correctly to represented character set,
        /// \a illegal should be returned
        ///
        /// If u can be converted to a sequence of bytes c1, ... , cN (1<= N <= max_len() ) then
        /// 
        /// -# If end - begin >= N, c1, ... cN are written starting at begin and N is returned
        /// -# If end - begin < N, incomplete is returned, it is unspecified what would be
        ///    stored in bytes in range [begin,end)

        virtual uint32_t from_unicode(uint32_t u,char *begin,char const *end) 
        {
            if(begin==end)
                return incomplete;
            if(u >= 0x80)
                return illegal;
            *begin = static_cast<char>(u);
            return 1;
        }
    };

    #if !defined(BOOST_LOCALE_HIDE_AUTO_PTR) && !defined(BOOST_NO_AUTO_PTR)
    ///
    /// This function creates a \a base_converter that can be used for conversion between UTF-8 and
    /// unicode code points
    ///
    BOOST_LOCALE_DECL std::auto_ptr<base_converter> create_utf8_converter();
    ///
    /// This function creates a \a base_converter that can be used for conversion between single byte
    /// character encodings like ISO-8859-1, koi8-r, windows-1255 and Unicode code points,
    /// 
    /// If \a encoding is not supported, empty pointer is returned. You should check if
    /// std::auto_ptr<base_converter>::get() != 0
    ///
    BOOST_LOCALE_DECL std::auto_ptr<base_converter> create_simple_converter(std::string const &encoding);


    ///
    /// Install codecvt facet into locale \a in and return new locale that is based on \a in and uses new
    /// facet.
    ///
    /// codecvt facet would convert between narrow and wide/char16_t/char32_t encodings using \a cvt converter.
    /// If \a cvt is null pointer, always failure conversion would be used that fails on every first input or output.
    /// 
    /// Note: the codecvt facet handles both UTF-16 and UTF-32 wide encodings, it knows to break and join
    /// Unicode code-points above 0xFFFF to and from surrogate pairs correctly. \a cvt should be unaware
    /// of wide encoding type
    ///
    BOOST_LOCALE_DECL
    std::locale create_codecvt(std::locale const &in,std::auto_ptr<base_converter> cvt,character_facet_type type);
    #endif

    #ifndef BOOST_NO_CXX11_SMART_PTR
    ///
    /// This function creates a \a base_converter that can be used for conversion between UTF-8 and
    /// unicode code points
    ///
    BOOST_LOCALE_DECL std::unique_ptr<base_converter> create_utf8_converter_unique_ptr();
    ///
    /// This function creates a \a base_converter that can be used for conversion between single byte
    /// character encodings like ISO-8859-1, koi8-r, windows-1255 and Unicode code points,
    /// 
    /// If \a encoding is not supported, empty pointer is returned. You should check if
    /// std::unique_ptr<base_converter>::get() != 0
    ///
    BOOST_LOCALE_DECL std::unique_ptr<base_converter> create_simple_converter_unique_ptr(std::string const &encoding);

    ///
    /// Install codecvt facet into locale \a in and return new locale that is based on \a in and uses new
    /// facet.
    ///
    /// codecvt facet would convert between narrow and wide/char16_t/char32_t encodings using \a cvt converter.
    /// If \a cvt is null pointer, always failure conversion would be used that fails on every first input or output.
    /// 
    /// Note: the codecvt facet handles both UTF-16 and UTF-32 wide encodings, it knows to break and join
    /// Unicode code-points above 0xFFFF to and from surrogate pairs correctly. \a cvt should be unaware
    /// of wide encoding type
    ///
    BOOST_LOCALE_DECL
    std::locale create_codecvt(std::locale const &in,std::unique_ptr<base_converter> cvt,character_facet_type type);
    #endif

    ///
    /// This function creates a \a base_converter that can be used for conversion between UTF-8 and
    /// unicode code points
    ///
    BOOST_LOCALE_DECL base_converter *create_utf8_converter_new_ptr();
    ///
    /// This function creates a \a base_converter that can be used for conversion between single byte
    /// character encodings like ISO-8859-1, koi8-r, windows-1255 and Unicode code points,
    /// 
    /// If \a encoding is not supported, empty pointer is returned. You should check if
    /// std::unique_ptr<base_converter>::get() != 0
    ///
    BOOST_LOCALE_DECL base_converter *create_simple_converter_new_ptr(std::string const &encoding);

    ///
    /// Install codecvt facet into locale \a in and return new locale that is based on \a in and uses new
    /// facet.
    ///
    /// codecvt facet would convert between narrow and wide/char16_t/char32_t encodings using \a cvt converter.
    /// If \a cvt is null pointer, always failure conversion would be used that fails on every first input or output.
    /// 
    /// Note: the codecvt facet handles both UTF-16 and UTF-32 wide encodings, it knows to break and join
    /// Unicode code-points above 0xFFFF to and from surrogate pairs correctly. \a cvt should be unaware
    /// of wide encoding type
    ///
    /// ownership of cvt is transfered 
    ///
    BOOST_LOCALE_DECL
    std::locale create_codecvt_from_pointer(std::locale const &in,base_converter *cvt,character_facet_type type);

    /// 
    /// Install utf8 codecvt to UTF-16 or UTF-32 into locale \a in and return
    /// new locale that is based on \a in and uses new facet. 
    /// 
    BOOST_LOCALE_DECL
    std::locale create_utf8_codecvt(std::locale const &in,character_facet_type type);

    ///
    /// This function installs codecvt that can be used for conversion between single byte
    /// character encodings like ISO-8859-1, koi8-r, windows-1255 and Unicode code points,
    /// 
    /// Throws boost::locale::conv::invalid_charset_error if the chacater set is not supported or isn't single byte character
    /// set
    BOOST_LOCALE_DECL
    std::locale create_simple_codecvt(std::locale const &in,std::string const &encoding,character_facet_type type);
} // util
} // locale 
} // boost

#endif
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

/* util.hpp
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
*/