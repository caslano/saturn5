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
EYCe9ICHJR1CjV+1D8cuaqnOES2mZ15FBiHzIAKVFQSAIFJBWFWGT6xbqxsAjzPlpX4uB14Pkt6ihnCN2mxXxMJRtGiyjzAzbOJwSpjwY0MtKtg+Wj0juvpeIj34Ayy+4kpFRCw400mivIDwQLX5ZKTsY2NBP6z2SYYSsEEbyYKjL0MwzV3VKKzvz3BDAzXTevyb1HWlak4r0/1ItMLsCCQftmsZKSBvGpiqoLO4yV+mcLptCrort06JyXdUhIKBOQvn9Xcy17nXYyChv4Uro2WLixY1W3MWnAVtmCkcJYGG4O8Figg9YIp7xuaMYKJzl7dySbOh2RSsw84JBgNAU7gFQZ+I/a8O+58tP7XSqoKRXosmKjz0/VUBHufV3wmshdIjLoiiwHiSJ2P4ik3V+9AdSKj1vnLWs6AXK3PWaFUgBpWGnT/+kWlgTQIhCnyOz/uMLwRZynqC8U2I+GIOrwfO6r/qXyyTJ0drwK4nkbQVD4chwtZno8AV56Hj4jyPHiU99bZL/KtozjRrH8cNN8ZAUuiWuvNPoWuB6+dfPDagJbq883AS0VqjqBSuhM1KSCxjp1fEUGYYvWNtwiHiwXtKdnd+3WrFQPO9GtkvWFvBFIgkCQTRvSqCbF9RTYYryTJgXJKhBiW0iQNSOP397QFJ2bz9QcxFI1pcA0RWkDdMoX4Zh0bgEjaZMwtuf+gRGFw/OHnjdLlgDkPp9kCZp/PFiLtCtYegHJK8/bzJUV77KPZnoPYILlhLPNz0XBM3MsTH3K20Cz9CG96Sd1wGu/5WRmM3DY5R+wh/Gog/KxONMZxR/akUPSoO2rQ5W/nDWAqmtporxNebt8ByOjr74obgeIWH3WnNRS38FFRmRFdx5dlLagOk1Ds6Bct8iFiipz9CggKJUCXu2L+jSVhcDlFrga7GvREYQAPMGw9HZEmbCPXSrS+EHG6PbVYK7DLX4T+jfAEaIw4l6hGuX9HuFKPdi3KmZGm+nExh9Qw3s6lwLRFp3avI/htkHxe/OSgDfmwKJ+kZg6bY5eTer/2kNWyTdNkIItgxLr74N4yDLCgBtAidYDgVYi1kwPYkqFIdOIRUDOeKMO1RVZYn4mS8NWssFhPuvw+2pQQicU7emqmG6+9Lz2rJOlFrCx0hQj08szUnn64XYTj0UZB9BhntvaJDTGNk8vavhRJ7pL1PnPmXt+AMxskO7GrSJqcDU/DtWKDtZUah/vBMtrSmPcsHxHSwBVNkO/Fw4msL4VVxj7sapOzGZQQ7Bj+aCWf5h+qd2eVeixFo18FNDMfGIaLy1PNQmV8vqa9GhZnL1uqdS9nghc9Eg0qBXwpgI4EmvWt54LbexU322Uo+xEF1T7s6w5KGrPNzor0D42Gwk+sd6bD/5yjJyODn8kSGngK5YadhfW0qCgbF0cmXtyt6s980AE6Nx5nLIzg/VF8pOKBpCC9fhTYpHWAeE//dWuJB8jiz2Q2Ix/cHyuMdeKkCz+5qYhbJ/7fPPskCJC0tDzB/d8SmT+yeuakbWURIwj8+4Xto6Lx5DzME6EZhsgTkwhYWsH/WAvuPONAPwAfmb0LCjJn/ikDLbwE/gsbKKGLKXb5ssZAZqEscQO3RjB3elsQJlZSJzHT8J3763IObEm7yRVdpmR5RMxa7MmU4Ih/4RJ0pkxbCb/uCQEu1GDnH+wntsVfAK8V4DgO6kfwv/dCjJ1ofpWVlNj+Asfzngl8o1yH7UznuKzsnAcKiBbXCT3TJ4F6OLQDAXQn/AU6QTgr/QQif9X6ghPdHoKaggP1/FysX/P9gEcOtnyDmL7zZy/8/h3n0TalXKlUTH5gV1gsw/ESdSUIIrB+3DvZoT9YN4xniMyRTKgGShIkwnzBfX0ULnio9hgwWilTgKi4hQXpzKvOgJXig2je5hxmDqkHHDJAKBREad6PPMcX96KOVXRdsPyYH/ZHyQmxzbTeUCTzS6KoTCANUV5wl7BACbQ0LrzcRcqY9/JF3fQt0wvtqFxGG1BJOp6BwZ99xXeNkuXlPhgXmROnFGtOX6ly5zYUU/Z5ic1FzX9S6CAyA4JKHqCYJcmqTRiUoqri46onqtgnkFKi4IOJ6t21A5I14bX35ej/AbgJKRcS48OeN6wNWytxmwF1pkJemCKIgDZf4qK8TOlDai1lrNxyEceb1x+SojFcqCFHGdisz2GF3xbjifseWo4PpGYHxTkm5oPJz5nskcrpowV14F7pKFLgpHF6fiPIMOcgMDvW8apBtDYdDVcePkCqKranrUlYQXsNF70yTOr65qjQTPC4U4PDJ9Nrtv4pUFIlE/IHn/gSq8a1iXBVw1XgUlKYlwSKYmE6QUFtTdSHETBVkiYeZ5DzULgJZWAIAZ88QiSr6YfO1TjlGxOIpsIg3vrIuXa8+GNNcqthDv9M/4LVs41FSpdURop9ldu5n/0eUaIE9gwRcPKOVgpy+6WYY24AO4yvC12VCGgzNYtVR7wNZc6pqULwotVy8/LNq1HxDveE1Jgq/fOlgFR5Q/BUVLsV5ZylfX3VipF+0YIMhPwRbDlO7l+mf0GyX0itKzeF1SPTphqaHFT+IcOd8uUlMMUW9oR1xgEEacdBMAStB4fBopNNxfznBXW/3aaTh1PmwEylvZgpa269HvfFBVyK3iTZpv8MMigGlpcj4mKcnATP2b1FIJck4l73PUTbnKc0MQlOjfh6Ua9OdxB1Xvv8lBzIood//2HkuqzWjF6tiqdFAfg65wG9nIXfqtn0Tat0LPlOtd3l8pb84V6TGg1IN7p0x/k4vrDWc4kYzPYkbkqSiOsmzBQkVhOvu/6zdK1g8z4ZAkNiHKKyyJju+OFkyLBllyIWr0ND52YBI1Jhf6/Fg02U8RIe3znRplkV/2LLIoEnEYiDr0WaIWlnY4/undYh20IKV+04B69aoSLNX0U4+fpmPWENgSmUEeA6zQgcHUdJ+6ygtGSTecdduCCuJXuEE7QOHicuWKy2dDa5V0HhIrYFmGEGbfu82o4Yvn8XfOx00oKGmKx8pDGMIaWO9WxkI0Ft/YaPDQWuOEKZ8hdx9lJ9HR/L1WtPV29UABiz50/Yfha6lKT6yRKlXHSD8uz4jClF7UtO3jJwo92neEMdpB4N+uEHVc1QqvV9drSLlfrpHQUe0Az1HV1uFe1mx0mpZF+UZjGLkqAVa5sNp0OI7XWcz/VVffSm1/tro5RApnc1jpba7nN3838bu6V+/UiOYvhu2o+BIuv/RTq5X1al1sW2JPz2IiCShKqVjZc3jO8Ri7C9aaSD5Eh8TIhKSOx1LGCvfiECKY7KYbPYa+Jonluws05auSmbQ5laSy2gkvqfgCj3vZdfVaL+ELPLcka2J74oqwjn4XvynshoyQqzGqp88qCkSARhkLe2VAzpY8tsSViyRuSAyiiVYCLJfwZ9TwyqzQY9GVHbGMIH0SqmvVtaQ+9Rdtz7DKYdC9w5sbws68DrawbMVm8NsjagtgemLDYwt6bZGaEdg7nnSemSL5cGzh3MbFgc8pvfQNX5q8NACbquuzAzCMItYR/jT5LryFlA0b7zjhhF2UGOz1FTZYHtdGN0+sM8CIRJNmQYWsJ6qEZDZUQMJiN3vWCRYaS34fDQmTp1HvUy8G/ehD3bIol+0U2tWQeqYOU/7x5TX0IH/o6sxC/iZtnkLKZ3GGtX85zRgzy83ikGhT4fJxEkAEmCNjIY+tG6SMIhbW7JHmsdz0ableKPZ4QkEUg8HD91stpn2LKASVpDfgaJVlw4j8nqpQxsGem/kCGCph+TmY9zJK/VBVkS2KOmGjoaWf357cV1MwuHbPYIWF1Zj0SQ0qHatpc1rmSOYXFZbo6MonV+yKA1jDvfMvARE9qotZ8FZpmvYhJID2B++QlASHWLeIckYS+0tU+l3GK4I3LZb+PfNr7jMaUk7h/FjJZn14syA1TSpWTC1/kEmHM62z3/eUtwH04EFLCIikg5gYHqao00IG7GjWj8IhUWTw/SD0F7KRvhoBDY8WmQh0Q7pySgvVuZNR4m/+G8t57kc9u9S9TTfQxu+D4O02Dn1FEWTM/0NCJZRKXzbYXxYieeKujfwBOTCi3CJ9FJygyeFx7NQpyuRpMkhH5Z1zVezxwDUJPauKvMe6tqhhPDjRGcv9X2wALGrObI5U4hx4vitLAcUovOoB2Ae5s5LvY44JSmRC0SIdUieXqYdPhsQISpyfAkfTgKHI1+vzrEyQn+5bpDDEqEKyQDclAlhNSf7IZgoibPDJAq5fW6KOdxhVSbGlBHtCnbAehcBV3BB8UUGk1+R2G1vwxGZTgQkmDO3udrsrxOD7R56nAKOe81R5y8UUtJeswjBktCP1FceJtaQHWmLcjgPNABAiiv4KinjqW9LL2XCNoldI/SpZtwCl0LIvH57owPS9Oxo+5ICJpThoVAmJYkyEkNqVn7wJcGw/zrciOyl6VuMn+HPSYq4uwROSzxHutQi9Vz/iG0+Ww+fB5mpSM6/Gnl5EDagGqcDdkzOL7x2hZH7EU/6SVtQGwMP2WjcaP9PsgkuUqg6uQ9TVm9zcanxFqi/PHl1gZZBWWQxEqjXPKYV52TMn5s2l8XMGmWeBIKyjwZMjaUGDGEXKudXgFm9DPcr6zCwpAKpCBBIumiyrp0RYEqTfvEA75sKk0AGB37cU6khftBsvy1VZ76ZSWeErLQAoyh/3jSbVHaGXuVGlfMIWLdTfKY0je8nzO1wDcnxIwBPQIcw7ZmBc+t57xAr8I2xUulpLu9L59Pm3CkePx9l2kzLmN0K2JGGJokZD26vOQvPPGg2QcMd5bHfQVhZhGmqf9xJA36uh3OHd5eXVLspeizcr0ypvWvj66IDJN5F3K72+4iRJ8gURC3Ebo2LH+a9W2NX6vGITG/CSJEIxjEuFQHpVpOJOD8DhMrdUACxSzsAgfVbcsj8uB3xPJPdIMXD1rSQ9SJ5YszDWmapluP6jTxJWKippJrWaYZo6BxbSis8W0SBEo4peHsGqHklg51XvTPqUmec0AgKCyDpzGIHR9AxStxOxloLJnH8NNMERA+/l5I8LwS9OhxCUbxYsAmiLF0elf24AgxaGMh5WRw+tfqBktHOIYKnBGHE7AyTNoTmO5LD4EyJlYr270hylttSB3KqKtGStYobJceC+acwd2UuYHup/KR89s9JMov2yY9Qk+ujOQJeaNqrn0tXCJTjOVTCBPFygfSb5qbfp0uvdtW15Lm9Lr2Q5EEAJWxklCgIEIZGSeVtPtbgss20jUzjxT41TnVXwnuGbAgAYcyyFEWUJ/BIRDTT/Xg/My8f5KQKMeKCT1P0v0Tq3kD/fYPgLtLbA50YJENwMrkmi1b1296C9ZCwePjN61yGqIxhX3rHSpmu/6e4ia69byqdX00XQI2lPAb6yep+jBFHxLq43j+0UCIrNkLH4gCGhYNMJD6LWO4qTKoGSmKRlb0o5f2yHcNdPFWlfMUXcotV+9gX0UKAntEkooxZF7JA40voNprpnWNfPtAgEseCwMIOho/waIhGlPA9izbIl7aTTzo/c+8nVI4G0IkcFX5PUkwioi2AAViIDL4om3QSP9F6ygOolNjKgl251l+W9DMsuL6xZzwGCUwYLvoE7JP78lxRukuzgtMlCP6NtcUZMBeZlFNRoB2zCeHDiBENAFvRjg1xHDWe+3l5IMen4rOMFt569UZ7B0IwhYlLtAUFoNbATqcYqVyQFcN0obagjKGYrD1DIWZRDhR6O1IzT1PcYJwbxabCFbphVtJ9/+r3mzQL6elS4cKPESSjv2SgYVZLDgKOUUS9gPlxEXlSB+8+Icq4dgANqZ0FBexuHllF9ACier39CouoOUyE4P0BSY8YmsFSSikrmZl4rZzW46H0ioJ4A+xeFPwHX2G+B4IpXuAgsJ9yxwF26TfQoGyldgpayQz/oJJVEggHqObjMklETO8afq3vyg5FcuRgWM1nNkrieQ2wgQQfvYgMTp6v4GKYaCQIqVSAgFZF9peejkqNYPxVuJm1QGoW2hSU3IjfTRdO+Bdi0rNRABLlIEsOWK2mNvCDX+xb1uQbGg0v5b5PLLjpyjh/lF/2j6uNDy4PdW/haWZ+W2yPrfRyBBZy4on5b1UL0rMvTx6RuPIHPk/T1nkmUd7WIbvy36jQ7T7znI+xSYwt+AAZOGF+xz3FHe8uB8nlHjqYE+A4MBnV6Fu+kFX7/lp8eS+b9d3BmMohVjSs2Q3yHVsqX8Kn9U0UKCF0SALluMKhgJoVt7yiEeJJUmWB3swnRKj5TQqtXmO9ClxUDbUZu5hSPNgpA2N+NAmG3RqVuxcIJ0M55vnoWEsjQKfTZWCvtY/otVO+gQHeE9LQHp8VFKWGDkGd/67sCUD3a75yT+JrM/oaFsLV2or3+0+L7evdOAIsnu7aT6hvtF1bNmE1gtA6ZNtkysiR/eD+zHNVPJCBiS4HyhJWKcqXIyh0L03v5wQzlH2YjUZRSiulfefa+VrNzIz39hrI5bPaAA1DzEAyImDmQJi8t5PLsP/LB1gHR3lLO0eCKSmhBSULeN2jymQpqO/KQlZ0CQgHDSpxF1iig0X36u1NFzc9MaVSREzSoVJTWnaLyFJ+7LvH7rQ9MxehBERDLqZcauZVOgAJbFCt8ZzBFHife5jdvVRuCveY6WnIL0OlEohqcB9lxfRcLZV74SruwMd3mAwMgo86Zi4lwo4EprFNOSxF4WbDEsNS00G0pj5xpMYMQuQlfQI0t8QuN6+SbG64EF70nXG/dTnZeuVd8/wuWSAssfmkSIXQM2VLhLLuv9LnEDe0DWNsukXBiOTiS4XNnWKuMOd/SoyPgw+DVhwBsp681fMpuXlpUfbZAzBD2IPbW6Dv95L2RJTxLxI9K2r7Zn1f+4Op5VFBmkIsYSh9Zw+yQLtzJQMwJbKVj9S55/kXqLiao0W+UQr4qjoyQmVCS+ydcgp7/SoHkcQ1PoiwQhZgbgKVGt6ZHYna3h0X8c6CC2ZdshvrezdSmUcUx1aBdir0SXPShxKW1Wf+eimEFZJcAstAVDuNglWWXfQGiyz0hBb98mwHHDGON2OowARwUOba42vCOHefu+E+KmZBx6Q5nNaYDLxDx/j0yDjliaOBosjU+9F41bpNse5+Tb4aXEXQ+Z3GB0hhmpEG0WOvfOoUl9IItbI3xeqYOxETmQLbkNAnUZFem1UVxuZ0HP/2R7Gg0WpAtrs/0Nh66FeE12CHaHUQD1UgQGac+3agx6EmDtsrRbcGGSugLneFlxei+HY30OGin8aQ8sBbu992hN8UbURhKvk4/MvNvrIBlCuIscD+IBw0XAOSHAh6ahlYHWkfYv56MOMzjY/J9Zhkd2al+uo4SMT4o/ed0MCcFiPBkqzJUfZUPDcIWWerig42ayyW3O/MUGv68Kme/yLal0pgc3dYzJq9Sjk+Gbzv6Bmtpf2xe4QDEiX5ApejSO64jJSkW3X0wlG0oOzzcZOPevmj3Lnd2vQFWXLv+B8VTq7fk0VLqMhSzkrDWRpu9fgbF/jxf8Bfk3Fn/7H+f/9O+P5Cgbxw/6FQvRxinv4C8n/hh5v+gTAoJ5guxS9LQQzng0LVpk4s0qOzXdoKCU6XQTfoufHngzndzVQWHeOvKu/cGX6eH1V6lcsBBAUE/8sDrspYD9bMOjpyUJASbyhbMSU5tJWJFuYyiIyBREYzauFJuTCQzLid87Py9MzLtqw0sdO9K3XPBLQfvf1MEwI/OMPLSDAzY+txxSe/j1kDhs05RSF2yEcyYmMDvrJJYrWHbx6o7qaHheCI10yudR8+7QWBs+n06ungaC4pPTiH98Rg+XMA7D8LtMe3wtdD01cJyfQUsR6Pp8LOO6zKITd93K4jA3dsyVr9CUw75yeKGYqlerWeLx49pEtlcrIPdKyavyLqILqAfjVbiyO6NLpe4p2c3ts10vKqivnzHnt8mYiUEcoQS3sfbj90FBb/tvrSOZuMPiPPl7IEiCh5LzxFLkQS2167sKQhtFCQmAIHLNtTbDBaswbg2rZt27bd7tq2v9q2bdu2bdu2jb8nOZM8ydyvZL0zFwO6q/AgKxyOn4fS4R6JhjcX8lE/s4Hi/g8ubg4vmnviGLViizQTyygO6fLVUaYdToQZyvrk8zGm9NUWRT7vW14YU+oNKjTuWzOFDdGdLdwHtMqnskAocmon7u2GcIt5s+G6jeYlaYmPcH0MCdXoVzBaZdnlGI8eFkH6DHLSAlyPOc4YBv+kIBQmcAB6h79MU95apuCm/K5PHfUD/yxg2UnirG83gyF7Ip0ZlrNbTQ5QWrdqVk1bn+j++ZsfZbA1cztLLn+GiGYShTuU+fWDI4ooUkRsWbb26dyx9K3QNiFiwVubjEoZQOm/YkMEmOB6WfA8+W9QSg/WcNjQIljSZ+67QbhBWO4iI7xOvWHKHwyRSK65nfFzQGjkHkvPGei3rG0RJCoxCiNbG1ibdHvpAJAxX5s2FKFzB70ZXhjwVHiToTIseDQhpDht7N9ia0tSd0skNKOIQtR4q8RlwmV11/7B8mStloUlaLgsf7c9dF0XGCAtFnodMCuIFITQrzifoRVPuwEU/k5pfxEajdHH55AYVTsUbrwe7jwPem5dwuguMp04PbsV+Dq98+ETjl0ATdXYYlbu328pECKNZjIBjTe01i7V/ebFdlj5NYx6KCpZ4LGB5Bpyl1BSgJmZNjC4xNdi5HYwBN2LNHStgcBRmEgSSpIwMc2wmpaP9mjl85txRbgSiIcPyZNKSzTXdyR2ZZ+of4e6KEtpQQh1/8J5zeLcdyeS7aww8AwmRSgznI8xdG9j7PBayf5DwWPuC/V20TeOL4gi+w+rGhYhChT9Kbm7EtVfr0h3yyNti2CBreLhFK4NzgGVGOMVOsCEqLTOzcEOvoRzzC4kY6lKlldXJqkzFzxXhDl6yc7fVG1HuoGL2vdVi//GZiLlK/Jse2B6EAvyZxSC6786BSc2Ccuim5EwN3pk0wgMWUkE+bQjvdKTs88qMKGDOsJTwLOtC/Cj+PT422nogd3t3w6ix9/ZuNos3+fF595jC72T4Y/caIWvK/6d18IDFvNM+hQizy19g5+22zvrn8P9lyk8aP4meZorCsJgOH8UPXUPY9x8qpVEzQvWPo1OgvAvlL210kPzkXgSnFX5l0drkz4=
*/