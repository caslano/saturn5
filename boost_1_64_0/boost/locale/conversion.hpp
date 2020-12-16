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
SHsd6uiZjEgdnSW+z8J15N1hyo7bTy6d4C3drcy70+6G4ruu0msYfTqbY68z5ulSaKtA26ezuXY6U2jz0ecfAc7bUVhygYHvkWGjBw9OG+w2DFt9zpO0yaY+5wfzcjQfoU7pBw+yWn3jUQa13XWPNOSVx4xyARXQf5epU9nsDDHmHlAkdajTF9O7lHRV+viLMdrTA5b29ETs9hScl1J2lC1kl79Tzd9V/CZh35lp+rs08c1IFwjK3DrLay5vTZ0kpmz8Nr1aytU6y7Cz0yavSh/ib7H5FmFadZ4QRcbCsHfmaimT5IP1y36F5amyVmRFynoL0vZoZW2qPYTreJWS/2osKWLV0kbeHosMOzuQIfS9IPLPUvJX3/Py7EiebxPfjFqefc0+r+jGndWRzINzhWaZVtDWtTVV23wzWmQc7UDGiHpSvqubxT2lTLWuxufo26UxUyt3W+tMZzIbM523S6ZVvidXTN5Y7bI4N1LWu5DWo5X14MqGtlrJ/x3RZSW9Oi+pr5mtk1VJa87n45D1jkhZOQdBeard5gD634nXPnPCJi5x/65nf0/dxvfoUSmPjf78yru+GTgfpBttJfKfXXSC5+VPPps7+ayb25ftP3Xff4/d5t9lnxmvHeaPb4j73rMPnl8TaHpg7CrPnbhw8Uub//k+SL/jmi0u+f07W8YwxKX8jTUo82+Xcn+Q8reY+ywBPhmQxL/PAnwFSHVxH4J7TUu4hvMLwGBMxNG0X5wCvC/wTNq5HU37ttOAK2j/WQk8H/hY4Ntob3cXcC3wvcB1wIuAZwC/Rvu692lf9wHtAr+iXeA3wEfSDvQo4PWAjwYuAhb5b8MYi7sDNwJPBm5irMVmYB/THQ18MPCZwIcAnw88G/gmxly8XaRjuTND68VcN1/C9aT9qI/7ad/XzSNMD9GH6yPAecCLaGf6KPD6wE8Cbwf8NHAJf5eL3yyvy1yDxBotyxvJdSxxXcryLmdMxSuAC4CvBC4EvgZ4S+DrgbcFvhF4gswXH6HANwi9AC8A3pvPhVw3AVczXTPwLbRjvQv4EuCFwJ3AdwNfDnw78DXiN/keZ3Btj+1lCfv/0eT7S/L9Fe01vwZmLE/a8XKdibJa7Xifp7wvAmcAvwQsnn8MnAv8MvBqgo7t8zXgLYBfpx7eoPxvsd2+DewD7gH2A78HfATw+8DHAC8FPgX4A+AzgT8EPh/4I+CLgZdRHx8r7SRA/jfXtJPvKf9PbCc/M1bnIFfQHvk32pX+zno0cH89gYDHALuBN2N6UV6h+R2P15/l0VZWXmepdrRMl6OxT11Ovj5ju/1ciRHqI10W6dQYoSeR7mTgNNobpzOGa6Zib1zI7y/mo+eT5XUxXZ5ansa+2AM8h+3gAtb/XLM8zuVJP9tS3g5Kuh6H6XodpjNmOkvniZGuAxVU8zjsDB9PcWQnbGcbXH5scoRf5rnIM2QXXHNPSr9tg3V2wccj3yi2wTF9Mx9xbHK/bIJVe2DVFrgT+cIeeMD9MtvY/Zr2vvPvSRkwm1+NT2ZH/pjnnJTsyL7X6pM5cE/Kn+qXeSBsep3Y8y5Auw8AegGZT6QYYwFlgAbA6YAFgEWA5YCkJ1OM9QCTAH7A3CcTNr6JK3ElrsSVuBJX4kpciStx/Z3XX2T/31Bf1X/7f2HLn1JgmL6OyhnnbyhlGQI4dF2sM+xj2t+U7lI2YcfJ2Gsp91bBMcssb2v9YbUhXzKHrBsjRtw+zvZoQ3snyE+NW0c+5Y8wv3wpgAeKhABaPtvqvE3N1c1NrVhPo+18VD6RT3x8qvbVqt+Q+W6TPzN+4myxd6XlM2jj6FSXntg8TnSiy9PpSzCdRMMBDwr7ID2PaJM=
*/