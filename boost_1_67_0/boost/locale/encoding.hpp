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