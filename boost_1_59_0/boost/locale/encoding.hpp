//
//  Copyright (c) 2009-2011 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_LOCALE_ENCODING_HPP_INCLUDED
#define BOOST_LOCALE_ENCODING_HPP_INCLUDED

#include <boost/locale/config.hpp>
#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4275 4251 4231 4660)
#endif
#include <boost/locale/info.hpp>
#include <boost/locale/encoding_errors.hpp>
#include <boost/locale/encoding_utf.hpp>



namespace boost {
    namespace locale {

        ///
        /// \brief Namespace that contains all functions related to character set conversion
        ///
        namespace conv {
            ///
            /// \defgroup codepage Character conversion functions
            ///
            /// @{

            ///
            /// convert string to UTF string from text in range [begin,end) encoded with \a charset according to policy \a how
            ///
            template<typename CharType>
            std::basic_string<CharType> to_utf(char const *begin,char const *end,std::string const &charset,method_type how=default_method);

            ///
            /// convert UTF text in range [begin,end) to a text encoded with \a charset according to policy \a how
            ///
            template<typename CharType>
            std::string from_utf(CharType const *begin,CharType const *end,std::string const &charset,method_type how=default_method);

            ///
            /// convert string to UTF string from text in range [begin,end) encoded according to locale \a loc according to policy \a how
            ///
            /// \note throws std::bad_cast if the loc does not have \ref info facet installed
            /// 
            template<typename CharType>
            std::basic_string<CharType> to_utf(char const *begin,char const *end,std::locale const &loc,method_type how=default_method)
            {
                return to_utf<CharType>(begin,end,std::use_facet<info>(loc).encoding(),how);
            }

            ///
            /// convert UTF text in range [begin,end) to a text encoded according to locale \a loc according to policy \a how
            ///
            /// \note throws std::bad_cast if the loc does not have \ref info facet installed
            /// 
            template<typename CharType>
            std::string from_utf(CharType const *begin,CharType const *end,std::locale const &loc,method_type how=default_method)
            {
                return from_utf(begin,end,std::use_facet<info>(loc).encoding(),how);
            }

            ///
            /// convert a string \a text encoded with \a charset to UTF string
            ///
            
            template<typename CharType>
            std::basic_string<CharType> to_utf(std::string const &text,std::string const &charset,method_type how=default_method)
            {
                return to_utf<CharType>(text.c_str(),text.c_str()+text.size(),charset,how);
            }

            ///
            /// Convert a \a text from \a charset to UTF string
            ///
            template<typename CharType>
            std::string from_utf(std::basic_string<CharType> const &text,std::string const &charset,method_type how=default_method)
            {
                return from_utf(text.c_str(),text.c_str()+text.size(),charset,how);
            }

            ///
            /// Convert a \a text from \a charset to UTF string
            ///
            template<typename CharType>
            std::basic_string<CharType> to_utf(char const *text,std::string const &charset,method_type how=default_method)
            {
                char const *text_end = text;
                while(*text_end) 
                    text_end++;
                return to_utf<CharType>(text,text_end,charset,how);
            }

            ///
            /// Convert a \a text from UTF to \a charset
            ///
            template<typename CharType>
            std::string from_utf(CharType const *text,std::string const &charset,method_type how=default_method)
            {
                CharType const *text_end = text;
                while(*text_end) 
                    text_end++;
                return from_utf(text,text_end,charset,how);
            }

            ///
            /// Convert a \a text in locale encoding given by \a loc to UTF
            ///
            /// \note throws std::bad_cast if the loc does not have \ref info facet installed
            /// 
            template<typename CharType>
            std::basic_string<CharType> to_utf(std::string const &text,std::locale const &loc,method_type how=default_method)
            {
                return to_utf<CharType>(text.c_str(),text.c_str()+text.size(),loc,how);
            }

            ///
            /// Convert a \a text in UTF to locale encoding given by \a loc
            ///
            /// \note throws std::bad_cast if the loc does not have \ref info facet installed
            /// 
            template<typename CharType>
            std::string from_utf(std::basic_string<CharType> const &text,std::locale const &loc,method_type how=default_method)
            {
                return from_utf(text.c_str(),text.c_str()+text.size(),loc,how);
            }

            ///
            /// Convert a \a text in locale encoding given by \a loc to UTF
            ///
            /// \note throws std::bad_cast if the loc does not have \ref info facet installed
            /// 
            template<typename CharType>
            std::basic_string<CharType> to_utf(char const *text,std::locale const &loc,method_type how=default_method)
            {
                char const *text_end = text;
                while(*text_end) 
                    text_end++;
                return to_utf<CharType>(text,text_end,loc,how);
            }

            ///
            /// Convert a \a text in UTF to locale encoding given by \a loc
            ///
            /// \note throws std::bad_cast if the loc does not have \ref info facet installed
            /// 
            template<typename CharType>
            std::string from_utf(CharType const *text,std::locale const &loc,method_type how=default_method)
            {
                CharType const *text_end = text;
                while(*text_end) 
                    text_end++;
                return from_utf(text,text_end,loc,how);
            }


            ///
            /// Convert a text in range [begin,end) to \a to_encoding from \a from_encoding
            ///
            
            BOOST_LOCALE_DECL
            std::string between(char const *begin,
                                char const *end,
                                std::string const &to_encoding,
                                std::string const &from_encoding,
                                method_type how=default_method);

            ///
            /// Convert a \a text to \a to_encoding from \a from_encoding
            ///
            
            inline
            std::string between(char const *text,
                                std::string const &to_encoding,
                                std::string const &from_encoding,
                                method_type how=default_method)
            {
                char const *end=text;
                while(*end)
                    end++;
                return boost::locale::conv::between(text,end,to_encoding,from_encoding,how);
            }

            ///
            /// Convert a \a text to \a to_encoding from \a from_encoding
            ///
            inline
            std::string between(std::string const &text,
                                std::string const &to_encoding,
                                std::string const &from_encoding,
                                method_type how=default_method)
            {
                return boost::locale::conv::between(text.c_str(),text.c_str()+text.size(),to_encoding,from_encoding,how);
            }
          
            /// \cond INTERNAL

            template<>
            BOOST_LOCALE_DECL std::basic_string<char> to_utf(char const *begin,char const *end,std::string const &charset,method_type how);

            template<>
            BOOST_LOCALE_DECL std::string from_utf(char const *begin,char const *end,std::string const &charset,method_type how);

            template<>
            BOOST_LOCALE_DECL std::basic_string<wchar_t> to_utf(char const *begin,char const *end,std::string const &charset,method_type how);

            template<>
            BOOST_LOCALE_DECL std::string from_utf(wchar_t const *begin,wchar_t const *end,std::string const &charset,method_type how);

            #ifdef BOOST_LOCALE_ENABLE_CHAR16_T
            template<>
            BOOST_LOCALE_DECL std::basic_string<char16_t> to_utf(char const *begin,char const *end,std::string const &charset,method_type how);

            template<>
            BOOST_LOCALE_DECL std::string from_utf(char16_t const *begin,char16_t const *end,std::string const &charset,method_type how);
            #endif

            #ifdef BOOST_LOCALE_ENABLE_CHAR32_T
            template<>
            BOOST_LOCALE_DECL std::basic_string<char32_t> to_utf(char const *begin,char const *end,std::string const &charset,method_type how);

            template<>
            BOOST_LOCALE_DECL std::string from_utf(char32_t const *begin,char32_t const *end,std::string const &charset,method_type how);
            #endif


            /// \endcond

            /// @}

        } // conv

    } // locale
} // boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4


/* encoding.hpp
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
*/