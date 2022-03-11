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