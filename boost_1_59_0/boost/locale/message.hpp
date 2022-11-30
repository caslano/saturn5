//
//  Copyright (c) 2009-2011 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_LOCALE_MESSAGE_HPP_INCLUDED
#define BOOST_LOCALE_MESSAGE_HPP_INCLUDED

#include <boost/locale/config.hpp>
#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4275 4251 4231 4660)
#endif
#include <locale>
#include <string>
#include <vector>
#include <set>
#include <memory>
#include <boost/locale/formatting.hpp>

// glibc < 2.3.4 declares those as macros if compiled with optimization turned on
#ifdef gettext
#  undef gettext
#  undef ngettext
#  undef dgettext
#  undef dngettext
#endif

namespace boost {
    namespace locale {
        ///
        /// \defgroup message Message Formatting (translation) 
        ///
        ///This module provides message translation functionality, i.e. allow your application to speak native language
        ///
        /// @{
        /// 

        /// \cond INTERNAL 

        template<typename CharType>
        struct base_message_format: public std::locale::facet
        {
        };
       
        /// \endcond
       
        ///
        /// \brief This facet provides message formatting abilities
        ///
        template<typename CharType>
        class message_format : public base_message_format<CharType>
        {
        public:

            ///
            /// Character type
            ///
            typedef CharType char_type;
            ///
            /// String type
            ///
            typedef std::basic_string<CharType> string_type;

            ///
            /// Default constructor
            ///
            message_format(size_t refs = 0) : 
                base_message_format<CharType>(refs)
            {
            }

            ///
            /// This function returns a pointer to the string for a message defined by a \a context
            /// and identification string \a id. Both create a single key for message lookup in
            /// a domain defined by \a domain_id.
            ///
            /// If \a context is NULL it is not considered to be a part of the key
            ///
            /// If a translated string is found, it is returned, otherwise NULL is returned
            /// 
            ///
            virtual char_type const *get(int domain_id,char_type const *context,char_type const *id) const = 0;
            ///
            /// This function returns a pointer to the string for a plural message defined by a \a context
            /// and identification string \a single_id. 
            ///
            /// If \a context is NULL it is not considered to be a part of the key
            ///
            /// Both create a single key for message lookup in
            /// a domain defined \a domain_id. \a n is used to pick the correct translation string for a specific
            /// number.
            ///
            /// If a translated string is found, it is returned, otherwise NULL is returned
            /// 
            ///
            virtual char_type const *get(int domain_id,char_type const *context,char_type const *single_id,int n) const = 0;

            ///
            /// Convert a string that defines \a domain to the integer id used by \a get functions
            ///
            virtual int domain(std::string const &domain) const = 0;

            ///
            /// Convert the string \a msg to target locale's encoding. If \a msg is already
            /// in target encoding it would be returned otherwise the converted
            /// string is stored in temporary \a buffer and buffer.c_str() is returned.
            ///
            /// Note: for char_type that is char16_t, char32_t and wchar_t it is no-op, returns
            /// msg
            ///
            virtual char_type const *convert(char_type const *msg,string_type &buffer) const = 0;

#if defined (__SUNPRO_CC) && defined (_RWSTD_VER)
            std::locale::id& __get_id (void) const { return id; }
#endif
        protected:
            virtual ~message_format()
            {
            }

        };
        
        /// \cond INTERNAL

        namespace details {
            inline bool is_us_ascii_char(char c)
            {
                // works for null terminated strings regardless char "signness"
                return 0<c && c<0x7F; 
            }
            inline bool is_us_ascii_string(char const *msg)
            {
                while(*msg) {
                    if(!is_us_ascii_char(*msg++))
                        return false;
                }
                return true;
            }

            template<typename CharType>
            struct string_cast_traits {
                static CharType const *cast(CharType const *msg,std::basic_string<CharType> &/*unused*/)
                {
                    return msg;
                }
            };

            template<>
            struct string_cast_traits<char> {
                static char const *cast(char const *msg,std::string &buffer)
                {
                    if(is_us_ascii_string(msg))
                        return msg;
                    buffer.reserve(strlen(msg));
                    char c;
                    while((c=*msg++)!=0) {
                        if(is_us_ascii_char(c))
                            buffer+=c;
                    }
                    return buffer.c_str();
                }
            };
        } // details

        /// \endcond

        ///
        /// \brief This class represents a message that can be converted to a specific locale message
        ///
        /// It holds the original ASCII string that is queried in the dictionary when converting to the output string.
        /// The created string may be UTF-8, UTF-16, UTF-32 or other 8-bit encoded string according to the target 
        /// character type and locale encoding.
        ///
        template<typename CharType>
        class basic_message {
        public:

            typedef CharType char_type; ///< The character this message object is used with
            typedef std::basic_string<char_type> string_type;   ///< The string type this object can be used with
            typedef message_format<char_type> facet_type;   ///< The type of the facet the messages are fetched with

            ///
            /// Create default empty message
            /// 
            basic_message() :
                n_(0),
                c_id_(0),
                c_context_(0),
                c_plural_(0)
            {
            }

            ///
            /// Create a simple message from 0 terminated string. The string should exist
            /// until the message is destroyed. Generally useful with static constant strings
            /// 
            explicit basic_message(char_type const *id) :
                n_(0),
                c_id_(id),
                c_context_(0),
                c_plural_(0)
            {
            }

            ///
            /// Create a simple plural form message from 0 terminated strings. The strings should exist
            /// until the message is destroyed. Generally useful with static constant strings.
            ///
            /// \a n is the number, \a single and \a plural are singular and plural forms of the message
            /// 
            explicit basic_message(char_type const *single,char_type const *plural,int n) :
                n_(n),
                c_id_(single),
                c_context_(0),
                c_plural_(plural)
            {
            }

            ///
            /// Create a simple message from 0 terminated strings, with context
            /// information. The string should exist
            /// until the message is destroyed. Generally useful with static constant strings
            /// 
            explicit basic_message(char_type const *context,char_type const *id) :
                n_(0),
                c_id_(id),
                c_context_(context),
                c_plural_(0)
            {
            }

            ///
            /// Create a simple plural form message from 0 terminated strings, with context. The strings should exist
            /// until the message is destroyed. Generally useful with static constant strings.
            ///
            /// \a n is the number, \a single and \a plural are singular and plural forms of the message
            /// 
            explicit basic_message(char_type const *context,char_type const *single,char_type const *plural,int n) :
                n_(n),
                c_id_(single),
                c_context_(context),
                c_plural_(plural)
            {
            }


            ///
            /// Create a simple message from a string.
            ///
            explicit basic_message(string_type const &id) :
                n_(0),
                c_id_(0),
                c_context_(0),
                c_plural_(0),
                id_(id)
            {
            }

            ///
            /// Create a simple plural form message from strings.
            ///
            /// \a n is the number, \a single and \a plural are single and plural forms of the message
            /// 
            explicit basic_message(string_type const &single,string_type const &plural,int number) :
                n_(number),
                c_id_(0),
                c_context_(0),
                c_plural_(0),
                id_(single),
                plural_(plural)
            {
            }

            ///
            /// Create a simple message from a string with context.
            ///
            explicit basic_message(string_type const &context,string_type const &id) :
                n_(0),
                c_id_(0),
                c_context_(0),
                c_plural_(0),
                id_(id),
                context_(context)
            {
            }

            ///
            /// Create a simple plural form message from strings.
            ///
            /// \a n is the number, \a single and \a plural are single and plural forms of the message
            /// 
            explicit basic_message(string_type const &context,string_type const &single,string_type const &plural,int number) :
                n_(number),
                c_id_(0),
                c_context_(0),
                c_plural_(0),
                id_(single),
                context_(context),
                plural_(plural)
            {
            }

            ///
            /// Copy an object
            ///
            basic_message(basic_message const &other) :
                n_(other.n_),
                c_id_(other.c_id_),
                c_context_(other.c_context_),
                c_plural_(other.c_plural_),
                id_(other.id_),
                context_(other.context_),
                plural_(other.plural_)
            {
            }

            ///
            /// Assign other message object to this one
            ///
            basic_message const &operator=(basic_message const &other)
            {
                if(this==&other) {
                    return *this;
                }
                basic_message tmp(other);
                swap(tmp);
                return *this;
            }

            ///
            /// Swap two message objects
            ///
            void swap(basic_message &other)
            {
                std::swap(n_,other.n_);
                std::swap(c_id_,other.c_id_);
                std::swap(c_context_,other.c_context_);
                std::swap(c_plural_,other.c_plural_);

                id_.swap(other.id_);
                context_.swap(other.context_);
                plural_.swap(other.plural_);
            }

            ///
            /// Message class can be explicitly converted to string class
            ///

            operator string_type () const
            {
                return str();
            }

            ///
            /// Translate message to a string in the default global locale, using default domain
            ///
            string_type str() const
            {
                std::locale loc;
                return str(loc,0);
            }
            
            ///
            /// Translate message to a string in the locale \a locale, using default domain
            ///
            string_type str(std::locale const &locale) const
            {
                return str(locale,0);
            }
           
            ///
            /// Translate message to a string using locale \a locale and message domain  \a domain_id
            /// 
            string_type str(std::locale const &locale,std::string const &domain_id) const
            {
                int id=0;
                if(std::has_facet<facet_type>(locale))
                    id=std::use_facet<facet_type>(locale).domain(domain_id);
                return str(locale,id);
            }

            ///
            /// Translate message to a string using the default locale and message domain  \a domain_id
            /// 
            string_type str(std::string const &domain_id) const
            {
                int id=0;
                std::locale loc;
                if(std::has_facet<facet_type>(loc))
                    id=std::use_facet<facet_type>(loc).domain(domain_id);
                return str(loc,id);
            }

            
            ///
            /// Translate message to a string using locale \a loc and message domain index  \a id
            /// 
            string_type str(std::locale const &loc,int id) const
            {
                string_type buffer;                
                char_type const *ptr = write(loc,id,buffer);
                if(ptr == buffer.c_str())
                    return buffer;
                else
                    buffer = ptr;
                return buffer;
            }


            ///
            /// Translate message and write to stream \a out, using imbued locale and domain set to the 
            /// stream
            ///
            void write(std::basic_ostream<char_type> &out) const
            {
                std::locale const &loc = out.getloc();
                int id = ios_info::get(out).domain_id();
                string_type buffer;
                out << write(loc,id,buffer);
            }

        private:
            char_type const *plural() const
            {
                if(c_plural_)
                    return c_plural_;
                if(plural_.empty())
                    return 0;
                return plural_.c_str();
            }
            char_type const *context() const
            {
                if(c_context_)
                    return c_context_;
                if(context_.empty())
                    return 0;
                return context_.c_str();
            }

            char_type const *id() const
            {
                return c_id_ ? c_id_ : id_.c_str();
            }
            
            char_type const *write(std::locale const &loc,int domain_id,string_type &buffer) const
            {
                char_type const *translated = 0;
                static const char_type empty_string[1] = {0};

                char_type const *id = this->id();
                char_type const *context = this->context();
                char_type const *plural = this->plural();
                
                if(*id == 0)
                    return empty_string;
                
                facet_type const *facet = 0;
                if(std::has_facet<facet_type>(loc))
                    facet = &std::use_facet<facet_type>(loc);

                if(facet) { 
                    if(!plural) {
                        translated = facet->get(domain_id,context,id);
                    }
                    else {
                        translated = facet->get(domain_id,context,id,n_);
                    }
                }

                if(!translated) {
                    char_type const *msg = plural ? ( n_ == 1 ? id : plural) : id;

                    if(facet) {
                        translated = facet->convert(msg,buffer);
                    }
                    else {
                        translated = details::string_cast_traits<char_type>::cast(msg,buffer);
                    }
                }
                return translated;
            }

            /// members

            int n_;
            char_type const *c_id_;
            char_type const *c_context_;
            char_type const *c_plural_;
            string_type id_;
            string_type context_;
            string_type plural_;
        };


        ///
        /// Convenience typedef for char
        ///
        typedef basic_message<char> message;
        ///
        /// Convenience typedef for wchar_t
        ///
        typedef basic_message<wchar_t> wmessage;
        #ifdef BOOST_LOCALE_ENABLE_CHAR16_T
        ///
        /// Convenience typedef for char16_t
        ///
        typedef basic_message<char16_t> u16message;
        #endif
        #ifdef BOOST_LOCALE_ENABLE_CHAR32_T
        ///
        /// Convenience typedef for char32_t
        ///
        typedef basic_message<char32_t> u32message;
        #endif

        ///
        /// Translate message \a msg and write it to stream
        ///
        template<typename CharType>
        std::basic_ostream<CharType> &operator<<(std::basic_ostream<CharType> &out,basic_message<CharType> const &msg)
        {
            msg.write(out);
            return out;
        }

        ///
        /// \anchor boost_locale_translate_family \name Indirect message translation function family
        /// @{

        ///
        /// \brief Translate a message, \a msg is not copied 
        ///
        template<typename CharType>
        inline basic_message<CharType> translate(CharType const *msg)
        {
            return basic_message<CharType>(msg);
        }
        ///
        /// \brief Translate a message in context, \a msg and \a context are not copied 
        ///
        template<typename CharType>
        inline basic_message<CharType> translate(   CharType const *context,
                                                    CharType const *msg)
        {
            return basic_message<CharType>(context,msg);
        }
        ///
        /// \brief Translate a plural message form, \a single and \a plural are not copied 
        ///
        template<typename CharType>
        inline basic_message<CharType> translate(   CharType const *single,
                                                    CharType const *plural,
                                                    int n)
        {
            return basic_message<CharType>(single,plural,n);
        }
        ///
        /// \brief Translate a plural message from in constext, \a context, \a single and \a plural are not copied 
        ///
        template<typename CharType>
        inline basic_message<CharType> translate(   CharType const *context,
                                                    CharType const *single,
                                                    CharType const *plural,
                                                    int n)
        {
            return basic_message<CharType>(context,single,plural,n);
        }
        
        ///
        /// \brief Translate a message, \a msg is copied 
        ///
        template<typename CharType>
        inline basic_message<CharType> translate(std::basic_string<CharType> const &msg)
        {
            return basic_message<CharType>(msg);
        }
        
        ///
        /// \brief Translate a message in context,\a context and \a msg is copied 
        ///
        template<typename CharType>
        inline basic_message<CharType> translate(   std::basic_string<CharType> const &context,
                                                    std::basic_string<CharType> const &msg)
        {
            return basic_message<CharType>(context,msg);
        }
        ///
        /// \brief Translate a plural message form in constext, \a context, \a single and \a plural are copied 
        ///
        template<typename CharType>
        inline basic_message<CharType> translate(   std::basic_string<CharType> const &context,
                                                    std::basic_string<CharType> const &single,
                                                    std::basic_string<CharType> const &plural,
                                                    int n)
        {
            return basic_message<CharType>(context,single,plural,n);
        }

        ///
        /// \brief Translate a plural message form, \a single and \a plural are copied 
        ///

        template<typename CharType>
        inline basic_message<CharType> translate(   std::basic_string<CharType> const &single,
                                                    std::basic_string<CharType> const &plural,
                                                    int n)
        {
            return basic_message<CharType>(single,plural,n);
        }

        /// @}

        /// 
        /// \anchor boost_locale_gettext_family \name Direct message translation functions family 
        ///

        ///
        /// Translate message \a id according to locale \a loc
        ///
        template<typename CharType>
        std::basic_string<CharType> gettext(CharType const *id,
                                            std::locale const &loc=std::locale())
        {
            return basic_message<CharType>(id).str(loc);
        }
        ///
        /// Translate plural form according to locale \a loc
        ///
        template<typename CharType>
        std::basic_string<CharType> ngettext(   CharType const *s,
                                                CharType const *p,
                                                int n,
                                                std::locale const &loc=std::locale())
        {
            return basic_message<CharType>(s,p,n).str(loc);
        }
        ///
        /// Translate message \a id according to locale \a loc in domain \a domain
        ///
        template<typename CharType>
        std::basic_string<CharType>  dgettext(  char const *domain,
                                                CharType const *id,
                                                std::locale const &loc=std::locale())
        {
            return basic_message<CharType>(id).str(loc,domain);
        }

        ///
        /// Translate plural form according to locale \a loc in domain \a domain
        ///
        template<typename CharType>
        std::basic_string<CharType>  dngettext( char const *domain,
                                                CharType const *s,
                                                CharType const *p,
                                                int n,
                                                std::locale const &loc=std::locale())
        {
            return basic_message<CharType>(s,p,n).str(loc,domain);
        }
        ///
        /// Translate message \a id according to locale \a loc in context \a context
        ///
        template<typename CharType>
        std::basic_string<CharType>  pgettext(  CharType const *context,
                                                CharType const *id,
                                                std::locale const &loc=std::locale())
        {
            return basic_message<CharType>(context,id).str(loc);
        }
        ///
        /// Translate plural form according to locale \a loc in context \a context
        ///
        template<typename CharType>
        std::basic_string<CharType>  npgettext( CharType const *context,
                                                CharType const *s,
                                                CharType const *p,
                                                int n,
                                                std::locale const &loc=std::locale())
        {
            return basic_message<CharType>(context,s,p,n).str(loc);
        }
        ///
        /// Translate message \a id according to locale \a loc in domain \a domain in context \a context
        ///
        template<typename CharType>
        std::basic_string<CharType>  dpgettext( char const *domain,
                                                CharType const *context,
                                                CharType const *id,
                                                std::locale const &loc=std::locale())
        {
            return basic_message<CharType>(context,id).str(loc,domain);
        }
        ///
        /// Translate plural form according to locale \a loc in domain \a domain in context \a context
        ///
        template<typename CharType>
        std::basic_string<CharType>  dnpgettext(char const *domain,
                                                CharType const *context,
                                                CharType const *s,
                                                CharType const *p,
                                                int n,
                                                std::locale const &loc=std::locale())
        {
            return basic_message<CharType>(context,s,p,n).str(loc,domain);
        }

        ///
        /// \cond INTERNAL
        ///
        
        template<>
        struct BOOST_LOCALE_DECL base_message_format<char> : public std::locale::facet 
        {
            base_message_format(size_t refs = 0) : std::locale::facet(refs)
            {
            }
            static std::locale::id id;
        };
        
        template<>
        struct BOOST_LOCALE_DECL base_message_format<wchar_t> : public std::locale::facet 
        {
            base_message_format(size_t refs = 0) : std::locale::facet(refs)
            {
            }
            static std::locale::id id;
        };
        
        #ifdef BOOST_LOCALE_ENABLE_CHAR16_T

        template<>
        struct BOOST_LOCALE_DECL base_message_format<char16_t> : public std::locale::facet 
        {
            base_message_format(size_t refs = 0) : std::locale::facet(refs)
            {
            }
            static std::locale::id id;
        };

        #endif

        #ifdef BOOST_LOCALE_ENABLE_CHAR32_T

        template<>
        struct BOOST_LOCALE_DECL base_message_format<char32_t> : public std::locale::facet 
        {
            base_message_format(size_t refs = 0) : std::locale::facet(refs)
            {
            }
            static std::locale::id id;
        };
        
        #endif

        /// \endcond

        ///
        /// @}
        ///

        namespace as {
            /// \cond INTERNAL
            namespace details {
                struct set_domain {
                    std::string domain_id;
                };
                template<typename CharType>
                std::basic_ostream<CharType> &operator<<(std::basic_ostream<CharType> &out, set_domain const &dom)
                {
                    int id = std::use_facet<message_format<CharType> >(out.getloc()).domain(dom.domain_id);
                    ios_info::get(out).domain_id(id);
                    return out;
                }
            } // details
            /// \endcond

            ///
            /// \addtogroup manipulators
            ///
            /// @{
            
            ///
            /// Manipulator for switching message domain in ostream,
            ///
            /// \note The returned object throws std::bad_cast if the I/O stream does not have \ref message_format facet installed
            /// 
            inline 
            #ifdef BOOST_LOCALE_DOXYGEN
            unspecified_type
            #else
            details::set_domain 
            #endif
            domain(std::string const &id)
            {
                details::set_domain tmp = { id };
                return tmp;
            }
            /// @}
        } // as
    } // locale 
} // boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif


#endif

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4


/* message.hpp
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
*/