//
//  Copyright (c) 2009-2011 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_LOCALE_CONVERTER_HPP_INCLUDED
#define BOOST_LOCALE_CONVERTER_HPP_INCLUDED

#include <boost/locale/config.hpp>
#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4275 4251 4231 4660)
#endif
#include <locale>


namespace boost {
    namespace locale {
        
        ///
        /// \defgroup convert Text Conversions 
        ///
        ///  This module provides various function for string manipulation like Unicode normalization, case conversion etc.
        /// @{
        ///

        
        ///
        /// \brief This class provides base flags for text manipulation. It is used as base for converter facet.
        ///
        class converter_base {
        public:
            ///
            /// The flag used for facet - the type of operation to perform
            ///
            typedef enum {
                normalization,  ///< Apply Unicode normalization on the text
                upper_case,     ///< Convert text to upper case
                lower_case,     ///< Convert text to lower case
                case_folding,   ///< Fold case in the text
                title_case      ///< Convert text to title case
            } conversion_type;
        };

        template<typename CharType>
        class converter;

        #ifdef BOOST_LOCALE_DOXYGEN
        ///
        /// \brief The facet that implements text manipulation
        ///
        /// It is used to performs text conversion operations defined by \ref conversion_type. It is specialized
        /// for four types of characters \c char, \c wchar_t, \c char16_t, \c char32_t
        ///
        template<typename Char>
        class BOOST_LOCALE_DECL converter: public converter_base, public std::locale::facet {
        public:
            /// Locale identification
            static std::locale::id id;

            /// Standard constructor
            converter(size_t refs = 0) : std::locale::facet(refs)
            {
            }
            ///
            /// Convert text in range [\a begin, \a end) according to conversion method \a how. Parameter
            /// \a flags is used for specification of normalization method like nfd, nfc etc.
            ///
            virtual std::basic_string<Char> convert(conversion_type how,Char const *begin,Char const *end,int flags = 0) const = 0;
#if defined (__SUNPRO_CC) && defined (_RWSTD_VER)
            std::locale::id& __get_id (void) const { return id; }
#endif
        };
        #else

        template<>
        class BOOST_LOCALE_DECL converter<char> : public converter_base, public std::locale::facet {
        public:
            static std::locale::id id;

            converter(size_t refs = 0) : std::locale::facet(refs)
            {
            }
            virtual std::string convert(conversion_type how,char const *begin,char const *end,int flags = 0) const = 0;
#if defined (__SUNPRO_CC) && defined (_RWSTD_VER)
            std::locale::id& __get_id (void) const { return id; }
#endif
        };

        template<>
        class BOOST_LOCALE_DECL converter<wchar_t> : public converter_base, public std::locale::facet {
        public:
            static std::locale::id id;
            converter(size_t refs = 0) : std::locale::facet(refs)
            {
            }
             virtual std::wstring convert(conversion_type how,wchar_t const *begin,wchar_t const *end,int flags = 0) const = 0;
#if defined (__SUNPRO_CC) && defined (_RWSTD_VER)
            std::locale::id& __get_id (void) const { return id; }
#endif
        };

        #ifdef BOOST_LOCALE_ENABLE_CHAR16_T
        template<>
        class BOOST_LOCALE_DECL converter<char16_t> : public converter_base, public std::locale::facet {
        public:
            static std::locale::id id;
            converter(size_t refs = 0) : std::locale::facet(refs)
            {
            }
            virtual std::u16string convert(conversion_type how,char16_t const *begin,char16_t const *end,int flags = 0) const = 0; 
#if defined (__SUNPRO_CC) && defined (_RWSTD_VER)
            std::locale::id& __get_id (void) const { return id; }
#endif
        };
        #endif

        #ifdef BOOST_LOCALE_ENABLE_CHAR32_T
        template<>
        class BOOST_LOCALE_DECL converter<char32_t> : public converter_base, public std::locale::facet {
        public:
            static std::locale::id id;
            converter(size_t refs = 0) : std::locale::facet(refs)
            {
            }
            virtual std::u32string convert(conversion_type how,char32_t const *begin,char32_t const *end,int flags = 0) const = 0;
#if defined (__SUNPRO_CC) && defined (_RWSTD_VER)
            std::locale::id& __get_id (void) const { return id; }
#endif
        };
        #endif

        #endif

        ///
        /// The type that defined <a href="http://unicode.org/reports/tr15/#Norm_Forms">normalization form</a>
        ///

        typedef enum {
            norm_nfd,   ///< Canonical decomposition
            norm_nfc,   ///< Canonical decomposition followed by canonical composition
            norm_nfkd,  ///< Compatibility decomposition
            norm_nfkc,  ///< Compatibility decomposition followed by canonical composition.
            norm_default = norm_nfc, ///< Default normalization - canonical decomposition followed by canonical composition
        } norm_type;
       
        ///
        /// Normalize Unicode string \a str according to \ref norm_type "normalization form" \a n
        ///
        /// Note: This function receives only Unicode strings, i.e.: UTF-8, UTF-16 or UTF-32. It does not take
        /// in account the locale encoding, because Unicode decomposition and composition are meaningless outside 
        /// of a Unicode character set.
        ///
        /// \note throws std::bad_cast if loc does not have \ref converter facet installed
        /// 
        template<typename CharType>
        std::basic_string<CharType> normalize(std::basic_string<CharType> const &str,norm_type n=norm_default,std::locale const &loc=std::locale())
        {
            return std::use_facet<converter<CharType> >(loc).convert(converter_base::normalization,str.data(),str.data() + str.size(),n);
        }

        ///
        /// Normalize NUL terminated Unicode string \a str according to \ref norm_type "normalization form" \a n
        ///
        /// Note: This function receives only Unicode strings, i.e.: UTF-8, UTF-16 or UTF-32. It does not take
        /// in account the locale encoding, because Unicode decomposition and composition are meaningless outside 
        /// of a Unicode character set.
        /// 
        /// \note throws std::bad_cast if loc does not have \ref converter facet installed
        /// 
        template<typename CharType>
        std::basic_string<CharType> normalize(CharType const *str,norm_type n=norm_default,std::locale const &loc=std::locale())
        {
            CharType const *end=str;
            while(*end)
                end++;
            return std::use_facet<converter<CharType> >(loc).convert(converter_base::normalization,str,end,n);
        }
        
        ///
        /// Normalize Unicode string in range [begin,end) according to \ref norm_type "normalization form" \a n
        ///
        /// Note: This function receives only Unicode strings, i.e.: UTF-8, UTF-16 or UTF-32. It does not take
        /// in account the locale encoding, because Unicode decomposition and composition are meaningless outside 
        /// of a Unicode character set.
        /// 
        /// \note throws std::bad_cast if loc does not have \ref converter facet installed
        /// 
        template<typename CharType>
        std::basic_string<CharType> normalize(  CharType const *begin,
                                                CharType const *end,
                                                norm_type n=norm_default,
                                                std::locale const &loc=std::locale())
        {
            return std::use_facet<converter<CharType> >(loc).convert(converter_base::normalization,begin,end,n);
        }

        ///////////////////////////////////////////////////
        
        ///
        /// Convert a string \a str to upper case according to locale \a loc
        ///
        /// \note throws std::bad_cast if loc does not have \ref converter facet installed
        /// 

        template<typename CharType>
        std::basic_string<CharType> to_upper(std::basic_string<CharType> const &str,std::locale const &loc=std::locale())
        {
            return std::use_facet<converter<CharType> >(loc).convert(converter_base::upper_case,str.data(),str.data()+str.size());
        }
        
        ///
        /// Convert a NUL terminated string \a str to upper case according to locale \a loc
        ///
        /// \note throws std::bad_cast if loc does not have \ref converter facet installed
        /// 
        template<typename CharType>
        std::basic_string<CharType> to_upper(CharType const *str,std::locale const &loc=std::locale())
        {
            CharType const *end=str;
            while(*end)
                end++;
            return std::use_facet<converter<CharType> >(loc).convert(converter_base::upper_case,str,end);
        }
        
        ///
        /// Convert a string in range [begin,end) to upper case according to locale \a loc
        ///
        /// \note throws std::bad_cast if loc does not have \ref converter facet installed
        /// 
        template<typename CharType>
        std::basic_string<CharType> to_upper(CharType const *begin,CharType const *end,std::locale const &loc=std::locale())
        {
            return std::use_facet<converter<CharType> >(loc).convert(converter_base::upper_case,begin,end);
        }

        ///////////////////////////////////////////////////
        
        ///
        /// Convert a string \a str to lower case according to locale \a loc
        ///
        /// \note throws std::bad_cast if loc does not have \ref converter facet installed
        /// 

        template<typename CharType>
        std::basic_string<CharType> to_lower(std::basic_string<CharType> const &str,std::locale const &loc=std::locale())
        {
            return std::use_facet<converter<CharType> >(loc).convert(converter_base::lower_case,str.data(),str.data()+str.size());
        }
        
        ///
        /// Convert a NUL terminated string \a str to lower case according to locale \a loc
        ///
        /// \note throws std::bad_cast if loc does not have \ref converter facet installed
        /// 
        template<typename CharType>
        std::basic_string<CharType> to_lower(CharType const *str,std::locale const &loc=std::locale())
        {
            CharType const *end=str;
            while(*end)
                end++;
            return std::use_facet<converter<CharType> >(loc).convert(converter_base::lower_case,str,end);
        }
        
        ///
        /// Convert a string in range [begin,end) to lower case according to locale \a loc
        ///
        /// \note throws std::bad_cast if loc does not have \ref converter facet installed
        /// 
        template<typename CharType>
        std::basic_string<CharType> to_lower(CharType const *begin,CharType const *end,std::locale const &loc=std::locale())
        {
            return std::use_facet<converter<CharType> >(loc).convert(converter_base::lower_case,begin,end);
        }
        ///////////////////////////////////////////////////
        
        ///
        /// Convert a string \a str to title case according to locale \a loc
        ///
        /// \note throws std::bad_cast if loc does not have \ref converter facet installed
        /// 

        template<typename CharType>
        std::basic_string<CharType> to_title(std::basic_string<CharType> const &str,std::locale const &loc=std::locale())
        {
            return std::use_facet<converter<CharType> >(loc).convert(converter_base::title_case,str.data(),str.data()+str.size());
        }
        
        ///
        /// Convert a NUL terminated string \a str to title case according to locale \a loc
        ///
        /// \note throws std::bad_cast if loc does not have \ref converter facet installed
        /// 
        template<typename CharType>
        std::basic_string<CharType> to_title(CharType const *str,std::locale const &loc=std::locale())
        {
            CharType const *end=str;
            while(*end)
                end++;
            return std::use_facet<converter<CharType> >(loc).convert(converter_base::title_case,str,end);
        }
        
        ///
        /// Convert a string in range [begin,end) to title case according to locale \a loc
        ///
        /// \note throws std::bad_cast if loc does not have \ref converter facet installed
        /// 
        template<typename CharType>
        std::basic_string<CharType> to_title(CharType const *begin,CharType const *end,std::locale const &loc=std::locale())
        {
            return std::use_facet<converter<CharType> >(loc).convert(converter_base::title_case,begin,end);
        }

        ///////////////////////////////////////////////////
        
        ///
        /// Fold case of a string \a str according to locale \a loc
        ///
        /// \note throws std::bad_cast if loc does not have \ref converter facet installed
        /// 

        template<typename CharType>
        std::basic_string<CharType> fold_case(std::basic_string<CharType> const &str,std::locale const &loc=std::locale())
        {
            return std::use_facet<converter<CharType> >(loc).convert(converter_base::case_folding,str.data(),str.data()+str.size());
        }
        
        ///
        /// Fold case of a NUL terminated string \a str according to locale \a loc
        ///
        /// \note throws std::bad_cast if loc does not have \ref converter facet installed
        /// 
        template<typename CharType>
        std::basic_string<CharType> fold_case(CharType const *str,std::locale const &loc=std::locale())
        {
            CharType const *end=str;
            while(*end)
                end++;
            return std::use_facet<converter<CharType> >(loc).convert(converter_base::case_folding,str,end);
        }
        
        ///
        /// Fold case of a string in range [begin,end) according to locale \a loc
        ///
        /// \note throws std::bad_cast if loc does not have \ref converter facet installed
        /// 
        template<typename CharType>
        std::basic_string<CharType> fold_case(CharType const *begin,CharType const *end,std::locale const &loc=std::locale())
        {
            return std::use_facet<converter<CharType> >(loc).convert(converter_base::case_folding,begin,end);
        }

        ///
        ///@}
        ///
    } // locale

} // boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif


#endif

///
/// \example conversions.cpp
///
/// Example of using various text conversion functions.
///
/// \example wconversions.cpp
///
/// Example of using various text conversion functions with wide strings.
///

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4


/* conversion.hpp
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
*/