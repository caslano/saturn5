//
//  Copyright (c) 2009-2011 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_LOCALE_FORMAT_HPP_INCLUDED
#define BOOST_LOCALE_FORMAT_HPP_INCLUDED

#include <boost/locale/config.hpp>
#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4275 4251 4231 4660)
#endif
#include <boost/locale/message.hpp>
#include <boost/locale/formatting.hpp>
#include <boost/locale/hold_ptr.hpp>

#include <sstream>


namespace boost {
    namespace locale {
        
        ///
        /// \defgroup format Format
        ///
        /// This module provides printf like functionality integrated into iostreams and suitable for localization
        ///
        /// @{
        ///

        /// \cond INTERNAL
        namespace details {

            template<typename CharType>
            struct formattible {
                typedef std::basic_ostream<CharType> stream_type;
                typedef void (*writer_type)(stream_type &output,void const *ptr);

                formattible() :
                    pointer_(0),
                    writer_(&formattible::void_write)
                {
                }
                
                formattible(formattible const &other) :
                    pointer_(other.pointer_),
                    writer_(other.writer_)
                {
                }

                formattible const &operator=(formattible const &other)
                {
                    if(this != &other) {
                        pointer_=other.pointer_;
                        writer_=other.writer_;
                    }
                    return *this;
                }
                
                template<typename Type>
                formattible(Type const &value)
                {
                    pointer_ = static_cast<void const *>(&value);
                    writer_ = &write<Type>;
                }

                template<typename Type>
                formattible const &operator=(Type const &other)
                {
                    *this = formattible(other);
                    return *this;
                }

                friend stream_type &operator<<(stream_type &out,formattible const &fmt)
                {
                    fmt.writer_(out,fmt.pointer_);
                    return out;
                }

            private:
                static void void_write(stream_type &output,void const * /*ptr*/)
                {
                    CharType empty_string[1]={0};
                    output<<empty_string;
                }

                template<typename Type>
                static void write(stream_type &output,void const *ptr)
                {
                    output << *static_cast<Type const *>(ptr);
                }
                
                void const *pointer_;
                writer_type writer_;
            }; // formattible
    
            class BOOST_LOCALE_DECL format_parser  {
            public:
                format_parser(std::ios_base &ios,void *,void (*imbuer)(void *,std::locale const &));
                ~format_parser();
                
                unsigned get_position();
                
                void set_one_flag(std::string const &key,std::string const &value);

                template<typename CharType>
                void set_flag_with_str(std::string const &key,std::basic_string<CharType> const &value)
                {
                    if(key=="ftime" || key=="strftime") {
                        as::strftime(ios_);
                        ios_info::get(ios_).date_time_pattern(value);
                    }
                }
                void restore();
            private:
                void imbue(std::locale const &);
                format_parser(format_parser const &);
                void operator=(format_parser const &);

                std::ios_base &ios_;
                struct data;
                hold_ptr<data> d;
            };

        }

        /// \endcond

        ///
        /// \brief a printf like class that allows type-safe and locale aware message formatting
        ///
        /// This class creates a formatted message similar to printf or boost::format and receives
        /// formatted entries via operator %.
        ///
        /// For example
        /// \code
        ///  cout << format("Hello {1}, you are {2} years old") % name % age << endl;
        /// \endcode
        ///
        /// Formatting is enclosed between curly brackets \c { \c } and defined by a comma separated list of flags in the format key[=value]
        /// value may also be text included between single quotes \c ' that is used for special purposes where inclusion of non-ASCII
        /// text is allowed
        ///
        /// Including of literal \c { and \c } is possible by specifying double brackets \c {{ and \c }} accordingly.
        ///
        ///
        /// For example:
        ///
        /// \code 
        ///   cout << format("The height of water at {1,time} is {2,num=fixed,precision=3}") % time % height;
        /// \endcode
        ///
        /// The special key -- a number without a value defines the position of an input parameter.
        /// List of keys:
        /// -   \c [0-9]+ -- digits, the index of a formatted parameter -- mandatory key.
        /// -   \c num or \c number -- format a number. Optional values are:
        ///     -  \c hex -- display hexadecimal number
        ///     -  \c oct -- display in octal format
        ///     -  \c sci or \c scientific -- display in scientific format
        ///     -  \c fix or \c fixed -- display in fixed format
        ///     .      
        ///     For example \c number=sci
        /// -  \c cur or \c currency -- format currency. Optional values are:
        /// 
        ///     -  \c iso -- display using ISO currency symbol.
        ///     -  \c nat or \c national -- display using national currency symbol.
        ///     .
        /// -  \c per or \c percent -- format percent value.
        /// -  \c date, \c time , \c datetime or \c dt -- format date, time or date and time. Optional values are:
        ///     -  \c s or \c short -- display in short format
        ///     -  \c m or \c medium -- display in medium format.
        ///     -  \c l or \c long -- display in long format.
        ///     -  \c f or \c full -- display in full format.
        ///     .
        /// -  \c ftime with string (quoted) parameter -- display as with \c strftime see, \c as::ftime manipulator
        /// -  \c spell or \c spellout -- spell the number.
        /// -  \c ord or \c ordinal -- format ordinal number (1st, 2nd... etc)
        /// -  \c left or \c < -- align to left.
        /// -  \c right or \c > -- align to right.
        /// -  \c width or \c w -- set field width (requires parameter).
        /// -  \c precision or \c p -- set precision (requires parameter).
        /// -  \c locale -- with parameter -- switch locale for current operation. This command generates locale
        ///     with formatting facets giving more fine grained control of formatting. For example:
        ///    \code
        ///    cout << format("Today {1,date} ({1,date,locale=he_IL.UTF-8@calendar=hebrew,date} Hebrew Date)") % date;
        ///    \endcode
        /// -  \c timezone or \c tz -- the name of the timezone to display the time in. For example:\n
        ///    \code
        ///    cout << format("Time is: Local {1,time}, ({1,time,tz=EET} Eastern European Time)") % date;
        ///    \endcode
        /// -  \c local - display the time in local time
        /// -  \c gmt - display the time in UTC time scale
        ///    \code
        ///    cout << format("Local time is: {1,time,local}, universal time is {1,time,gmt}") % time;
        ///    \endcode
        /// 
        /// 
        /// Invalid formatting strings are slightly ignored. This would prevent from translator
        /// to crash the program in unexpected location.
        /// 
        template<typename CharType>
        class basic_format {
        public:
            typedef CharType char_type; ///< Underlying character type
            typedef basic_message<char_type> message_type; ///< The translation message type
            /// \cond INTERNAL
            typedef details::formattible<CharType> formattible_type; 
            /// \endcond 

            typedef std::basic_string<CharType> string_type; ///< string type for this type of character
            typedef std::basic_ostream<CharType> stream_type; ///< output stream type for this type of character
 

            ///
            /// Create a format class for \a format_string
            ///
            basic_format(string_type format_string) : 
                format_(format_string),
                translate_(false),
                parameters_count_(0)
            {
            }
            ///
            /// Create a format class using message \a trans. The message if translated first according
            /// to the rules of target locale and then interpreted as format string
            ///
            basic_format(message_type const &trans) : 
                message_(trans),
                translate_(true),
                parameters_count_(0)
            {
            }

            ///
            /// Add new parameter to format list. The object should be a type
            /// with defined expression out << object where \c out is \c std::basic_ostream.
            ///
            template<typename Formattible>
            basic_format &operator % (Formattible const &object)
            {
                add(formattible_type(object));
                return *this;
            }

            ///
            /// Format a string using a locale \a loc
            ///
            string_type str(std::locale const &loc = std::locale()) const
            {
                std::basic_ostringstream<CharType> buffer;
                buffer.imbue(loc);
                write(buffer);
                return buffer.str();
            }

            ///
            /// write a formatted string to output stream \a out using out's locale
            ///
            void write(stream_type &out) const
            {
                string_type format;
                if(translate_)
                    format = message_.str(out.getloc(),ios_info::get(out).domain_id());
                else
                    format = format_;
               
                format_output(out,format);

            }
                        
            
        private:

            class format_guard {
            public:
                format_guard(details::format_parser &fmt) : 
                    fmt_(&fmt),
                    restored_(false)
                {
                }
                void restore()
                {
                    if(restored_)
                        return;
                    fmt_->restore();
                    restored_ = true;
                }
                ~format_guard()
                {
                    try {
                        restore();
                    }
                    catch(...) {
                    }
                }
            private:
                details::format_parser *fmt_;
                bool restored_;
            };
            
            void format_output(stream_type &out,string_type const &sformat) const
            {
                char_type obrk='{';
                char_type cbrk='}';
                char_type eq='=';
                char_type comma=',';
                char_type quote='\'';

                size_t pos = 0;
                size_t size=sformat.size();
                CharType const *format=sformat.c_str();
                while(format[pos]!=0) {
                    if(format[pos] != obrk) {
                        if(format[pos]==cbrk && format[pos+1]==cbrk) {
                            out << cbrk;
                            pos+=2;
                        }
                        else {
                            out<<format[pos];
                            pos++;
                        }
                        continue;
                    }

                    if(pos+1 < size && format[pos+1]==obrk) {
                        out << obrk;
                        pos+=2;
                        continue;
                    }
                    pos++;
                  
                    details::format_parser fmt(out,static_cast<void *>(&out),&basic_format::imbue_locale);

                    format_guard guard(fmt);

                    while(pos < size) { 
                        std::string key;
                        std::string svalue;
                        string_type value;
                        bool use_svalue = true;
                        for(;format[pos];pos++) {
                            char_type c=format[pos];
                            if(c==comma || c==eq || c==cbrk)
                                break;
                            else {
                                key+=static_cast<char>(c);
                            }
                        }

                        if(format[pos]==eq) {
                            pos++;
                            if(format[pos]==quote) {
                                pos++;
                                use_svalue = false;
                                while(format[pos]) {
                                    if(format[pos]==quote) {
                                        if(format[pos+1]==quote) {
                                            value+=quote;
                                            pos+=2;
                                        }
                                        else {
                                            pos++;
                                            break;
                                        }
                                    }
                                    else {
                                        value+=format[pos];
                                        pos++;
                                    }
                                }
                            }
                            else {
                                char_type c;
                                while((c=format[pos])!=0 && c!=comma && c!=cbrk) {
                                    svalue+=static_cast<char>(c);
                                    pos++;
                                }
                            }
                        }

                        if(use_svalue) {
                            fmt.set_one_flag(key,svalue);
                        }
                        else 
                            fmt.set_flag_with_str(key,value);
                        
                        if(format[pos]==comma) {
                            pos++;
                            continue;
                        }
                        else if(format[pos]==cbrk)  {
                            unsigned position = fmt.get_position();
                            out << get(position);
                            guard.restore();
                            pos++;
                            break;
                        }
                        else {                        
                            guard.restore();
                            break;
                        }
                    }
                }
            }

      
            //
            // Non-copyable 
            //
            basic_format(basic_format const &other);
            void operator=(basic_format const &other);

            void add(formattible_type const &param)
            {
                if(parameters_count_ >= base_params_)
                    ext_params_.push_back(param);
                else 
                    parameters_[parameters_count_] = param;
                parameters_count_++;
            }

            formattible_type get(unsigned id) const
            {
                if(id >= parameters_count_)
                    return formattible_type();
                else if(id >= base_params_)
                    return ext_params_[id - base_params_];
                else
                    return parameters_[id];
            }

            static void imbue_locale(void *ptr,std::locale const &l)
            {
                reinterpret_cast<stream_type *>(ptr)->imbue(l);
            }



            static unsigned const base_params_ = 8;
            
            message_type message_;
            string_type format_;
            bool translate_;


            formattible_type parameters_[base_params_];
            unsigned parameters_count_;
            std::vector<formattible_type> ext_params_;
        };

        ///
        /// Write formatted message to stream.
        ///
        /// This operator actually causes actual text formatting. It uses the locale of \a out stream
        ///
        template<typename CharType>
        std::basic_ostream<CharType> &operator<<(std::basic_ostream<CharType> &out,basic_format<CharType> const &fmt)
        {
            fmt.write(out);
            return out;
        }


        ///
        /// Definition of char based format
        ///
        typedef basic_format<char> format;

        ///
        /// Definition of wchar_t based format
        ///
        typedef basic_format<wchar_t> wformat;

        #ifdef BOOST_LOCALE_ENABLE_CHAR16_T
        ///
        /// Definition of char16_t based format
        ///
        typedef basic_format<char16_t> u16format;
        #endif

        #ifdef BOOST_LOCALE_ENABLE_CHAR32_T
        ///
        /// Definition of char32_t based format
        ///
        typedef basic_format<char32_t> u32format;
        #endif

        ///
        /// @}
        ///

    }
}

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif

///
/// \example hello.cpp
///
/// Basic example of using various functions provided by this library
///
/// \example whello.cpp
///
/// Basic example of using various functions with wide strings provided by this library
///
///

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4


/* format.hpp
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
*/