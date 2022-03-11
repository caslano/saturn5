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