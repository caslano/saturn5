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
WwrRUGmH1q9rK6eE+qdhI5FrHn1E06s3Z4cbQNJPZCnm9+zGiDos7SM6P76YfL3d4N50EAeCUJiH9zPxzRjkqLLwojxjj12tiYmrZtP/Q+BK+CYPaARaFQNq19S9B4Xo7Ng6XrPEhNq61W7931PeVhZvhmJXkemMDlR1VNRxyHQjR8SRYFGakrX7HOkY1Whdn2qgxvxcrYc+yk/hda4vE8tC3bUCEsNk1dJuS9P1tfa2nt80jU0sLmwYOfKUQ/OD6m3/g6nGyi59/kztFdRn/wldZ0n3y1Au8lV9HZuTWinJ5qj1PPT5/jR1NZ20t89HF2dN1oKN6smMI6eDWmymmyLk0YojLJ0Jr6v08s3FhQ2d/yNzc7hbkjJNH8eKQEGo3C19vSnVHRp7S9Qh/yOW6CY2cG4TkQ2SoZte8Ce2c8b2/Qd2Ivb9bl92mmkTlxsW14BRNJHclMOPNfr3Bx+YKVBxdNEXDPj/tWi9aaZNDuM6obNA9oEQQPHXiicssCyeLtTBqN1DhrPt6Bm51QlPWb7o8Zh5scBzb1Pukan3uJPihNcqH48vLsYnx9OzU9MrzyoeSfAIee8Pzyj1lMxs8dD+sH4qmp839U9ky5wLsu71ftfOg7gWLsC0/rtEOVjnN27toqrwbGHF6Nla
*/