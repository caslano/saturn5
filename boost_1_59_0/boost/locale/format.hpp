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
Q55H9Om/OWP+4lTg+QAiSxUujHV/GkStAd7Nu45jIMx0DrZXqbEVT1QS5LhXvsv4umcSBh6yy3e18z4MBCh0bCs+EcLx1ScOe5sZwjER6i6oKSmOpGhs1e8OpiW9xhqXs/sKboBvWB9FSlh/lrrA7NtK5sLpSiq4JN1AQ1qwBveANonjnOMWSR0T9tlr2V1H3bF0w8FF7BAdIovXd7SaDfaq5/WF6GltdL/QmYvmZyxYNDbWbfa2Xq9zp8KjB6e9KI7ldMaqaxB3zyiF1N4EEPsNOGyKNhNXwA/6p3xhAg/VNv/oIxs79exeG7haC99qFyLUIa8on6nb9TQVQCrdYzEY6N2AKRG/Q2yL6IvsOsHlNrhXLxPdgPV9GyoQbBHmovJXiLulUUp+fwsIHmi2Omf3GN9tl/i3fPZjXC0v/s3yAz8J29Y6LsxIloZkh9Xy7X+AOVZDdWukHmF3K347DzSHA3CZCYSSForo55mVFIw1cdPxCY41IWicZFH1F1ZyqHBy8m8nj8MTtMrVuWl2siHrrakMilMvyM/5iVu2DcrEo/7cRPXjIAx8Ayv6gqaKfgGUzrgTeiCeRIVVX72DTMw2FkGCIQSWzjNyuIXshURjVAx44sodecHRndPrs7jHo5u/PL4SQR/eW7ZmKnxJR8fsQ1WQwjXoA2xr0t5bQLXJOKEI6fdirf1pe8t28x8FR6n1eVTHm0Iwl5TbWRisCVgkDjtiWwiNuQAF/clj0u+V7WQEMQo7/myYYsv3T0ShabIc8kpWoPayVJRIqMIysT4h+TlW86VR3pW/5FKNDMOFvvGulsAhIA0D3v///1E6H3SOQDc16ESapJZpyTEUp7R5XKCXAOsiIu3sgK8xfmaLT7UiHtBOCSMYWdLGTylOAlNxW0wR9pFMGF31djkaByvCW2WDT/ycV05eCBxhFPGCCdzuLjvElPXpF+RbmSGCGOFFFF1u2MKWVt4ggFKtCRkrpBPDwRyf3RnAirUJWRMV2nJRaL3QLZpUbj3ILr1aRcS8kZMvGNfnUt8NydAZ8lQoFFY5qpsIE3khR9CsWzfYDk1IxhWP/KE+sReC/LHYwA8sluM2sufIMz4F6wH0NiYyknSjQr9wOyhA3HJdLNQXaIzPo2cs+um212J4DOLyLzeKGl6nODKfH9xcoxi9g7g6ZP/yT/iZXGk+ccUlbZ9TzvcneXMmUr0uAmifd/ifAgy8ggM5wPiAFRNhe3gwsg9P0uC0ZbSre8hy+SLbM8bcqLS8gdFkT3eDE0oAtj2efBAR9HUTmlkiKjQiO+dUdpayIHYJPAZqTfLWZE3pePmPwNtLMnHQ1OOv7ibZaIMtorpGyRfHKd3BMrr/5fgZgmjpkEDqAPazTjs8A8GlKdEzLSVtditAw11BJhq+OaJZBdGjERdFxw5FVcTHSCc0v2cngNVdNcy5+lSq+OIswnlEC89uiMfx0h6ccUrAxMXpc4NVHqiEqjqzBq8LwLVZOvVCQiXElL//N/1fTc5AyO3LWcSLBosOXGEctFsPYi7s5vSXimE6zlgYoo9cdGNzYtEkWV5Ughr4hIrpCQuF54Z3XuSuu8c/pq8Tsihz+acV1HH+lo8Ypv7kbmwX/Th22krAtN82NvTEkFjbXCDghfRAiYBdJDqnNoZqV2BEZCzGOuL3ysW+saHkkayR+1VnKs5gIpL+o9yoakcxmnjW2JjGm4JmEGuj7JtE1gtUq3Af/6z/jxxZsGQZ+fy85II+IYH9I2yekYowM1DAnc0qi8Ydpt/PfPVIaT6syayXjSzVRunF2ia7dL8ZY9UgI4GBNgoKsPQmMeYx4adP2g1+StMDTRhin5te4zq2rrQ9Ivtz2GlDtacgadHy55jfpJbBRxJ/iLbJ2i8FjCt1+dDCCCzuPs/4j7NbzK+HXQ5qpmCPX/n6gCLL8XGXA5N/NHRBcu/eeARcrcr1RL3WYT7XBzm8opwN/YZ+gBZxnYWG7XB+czsCLbJdw0s+2jT8a+i5zgx1jjbu2BcOFT2q/BR1zY8zWjLyXVk87XKYwgqhotjdL/9IgTXYtkIeN+QmNSvzQ+n1cV2FhGGXSCYtFAxfj6A4dHMz94SEMPDmMfGRYDuXSGNnS1HePxBi54/RM5Z4+Rsq95BdF918Qu3EmE7xJwpV+qJRBW3TXFD7ztPUMJrp7kqI5pQ1C0+tH4Pehis/9C3f/apN/o76Sc3OC9MiAlLS60gkav0S0WQKpp28L9DigOyvYH+1sB+1wOATeUVcxzNlnd/Eq6EESSlWn+1+HX9IrVtzVQOMWgdY8EZjwDOpbTYdy9rjIo97C/L7Od7AVFP2w1djdEM6w1tH+NF51I2EBfOd06ZC3TgXsb1xAK7K8Rj+MGcHmArjrMliPTSFcj9TyNsSbeWa6Wydf2itcRSPrNZ5f+vpEfj5H+h4a8ISVGgFEz8dbwk40a7hj/gZwPa68J0BnPtTVEH/YCELb7iGClsoos2AKS3J5H1/nkFuuhNJ8qvoFzFCq7uiC3qV12DW7iAPouoH0ndIBrrod5v6fNZF2EnT9c4Nzt/O2i0vYMDq2Uv/wJrMrkHNvbTZngouvIAQxE1XLRaSBV+eu/CbCG8FPyPSeBzZNpvKRHJN0Dpi79h1iOUpaLux4+iVlhyl5dv2FpNiffWy10EkabB/Tb/qLcVqc3qPn9We7Rju2XMHF/VFI0N/i46Yul2Rvk/OgxOWsQZ2kTo2vyTw8uAbO5xmuBTv3QkwcEPjSvGI+6rm9rYvULkVm/9LlKkAMCkwGdDg6EjZ32HXyjkFSE759P8r238typSow3ypd5NIdg4Nadg/yJY+TznM+dx/LYfGaSOb2Z2u9OTQJK2Ds3yrpGFKZU6hvKQLCdDz76b1NldVBy9EkP1fHzbImSKPGpcuqtWIJR8UwvgjAtbj9J9mGYhQO8SM5x2fT2rGD9fsWPn+JME6I+FKE8bC7I/TRPP0HXIADOTANfh4T/ytp9hEllar/Ry/Gr/0uscSnbNDPvZIsv7gM41KC+ubgPzTA3c2f24LvzhO2J4tdkJzSgF3SuDNnX+wMFgE94J1sIRQN4RhiTlUotqfDyraH/K/6K//Is2XS26fBgQIvj0s2/y11wrEDUVufLGWzrryAioOGQ2B9Fl39Qe0pyzmpEznrvBE4mlaunB6vHz84kYBU60qS79HDbUkMsFdPAU3JMrjP0wtQcB4TaSd2V8wd202STqfBbsqFPPsDfyJr/tAxkpd0klAvvEaX2NXeGlA9hO9SqGniuR7qcnK0FZOTtGsgNWOWYYuEJbw5Ih3zs+8nnJwqtlIEe6Mj824eHnw8Gc2GlB9FR77fxkQs3fk2XgIY6KtKUCkb8Fq3ecI34MOssj/nyrv4ozYkByWrUPp/9g+D0YtJB7tvlVf3J2VLY/Bt0hd+JUpgBAp8PLlGfOfpaMdI20ABIwmHD0x+RLrjvCdxnvRDBTbDUXfqe9P6r9mTnKxZa10jpCcU+csb7hZROvXQm4cqlvd3CaOFKpII6hit+dmyLOYIN8WLa6F3Vjgv6vWhRHkZ/Z41Thvnm1RK9wOQhhtbmzq1JpaYtgKgECbo9lSNFHIHtv+48nqEoEg+RpGYtbAgjs/+x8p+w5wJVaMtC1Wb5HpvIUqDKyyxvj2uXaPxABUO6ZBVnmBjMB9LKgj0bPoQtRI8QRY5vdyUmX4HXb0x304jJx/2q+EPIue6i3+5xcf4fOuo4AAyiVCD7uL6kityJIiDz7eTYAiFFv8b+t+IyMHnG/28Jv9SOvHPyORq7UelTj0oTbt119+Mx49T9S+5jr3x8Sxt36f14YLNs4xvpiXIcJOgYRkLYBETMY+FYJclJFxg8/VKU5xlBzh9QhOj1S9Yyhxi/r6P1UAb5vkliQxpg/Fs+Tayyv3a/XlOvqPCuiB7FzEpOhKxI3t4rZEA2hnXOonmKVQht+rcqagb5jGtabyJqc+TF7nxvHefbnwj3mWlHq2tfVTN4Ezzu7YmCOV7KRd3FngUM8qnd/GeAqU02cDYsYXmALgr0x+o8Dm7ai0Rl5HeJSPnJ8ukbe8IzpPo54FwLS97wl3r2Y7Qlyem5h+PRo8KUnxP3ITCTL0XNC/+sSCa6DGAFtrgrexYspc1/Va/OxFvxW/s4mSx+jsff6xruf7MLcFAyAB5v0HDRv56KB94MLFW+ekqgNUqrCalFPUwytgBdxeNY52klnzNGjq4U3xobHL4Bq3jdaoGUfX/Yhr3Ry6ZX5Oa/Wugqjcef3o+sQGVEBpia+5L/3ibFgi8Y0KEhTtn7Jsut8c/5F3fkuyghoKaqFcU1yj+yoSeQc+NJt6bwM9a/JYX7dJ8+DXxySOWhpitzwVbmN0OcH/uv8m4hsPd8Bg+yFY0Vgh2l23MqHv77BbCerCKBFkOeldP2X/6f0YgbjirrmOqmHniCDhj1lLVYQHldbH/WoKYN38GIljrg9n+YuUVAIpmc2bkNs3prHqx1pB3F3/DHpWn2YWW+yQWm8TxYNMskGbYT9d1BuPKAPjZ1vuibsb9s8jC1MrD0lDyVTSRjNHV3p/s8EWcBrhAtVzB7mKptBRt6+es6apdLP7SbrtOOLCuMbvwgkdtWyN+oqio/JuwDHWyh6XXNShD1cfwCm4sMDqA/QCA8R9J4L2IfbZZBH19l+9AGE5Tex1vpvs////J+JEcddwqQiuMqnh4t5UPFr8S8n+r8StVVlKWNHsWcw7Oa3fNhiBNeFesEMoAuV57Z1d9RUW2pct0aKR1/UG2w7OQ5qFjAH30mXIEriRhkrNtd/+PQ2Z4F76tpk5JMES5YHLCUOct1zmsDJncbmQJX+vHQCciBSm4HpEHuwp1jYKimyqVa0zNsZ1Eqf2A7qQgIIxnmtw/mKeYVTuBBBYmnzhmfzs7jjkktKa2Yt7GCXZgpyv8EZGbOa9TTK7H6d+yc4PwbphEsZsrsO82kj93tqJKtw3jMCi09wk7WHu++6KBYhlET00f4ib8LHNOePmPLp4C2dfz78yEgugNRaOgK8F6wCXM1dwaUJtf9mYiiahqGZiO/7ptcE+8HvIktTLJG5YnomIBuozHapdVvky36nZPv+s4h///ouqOedgrYFXLMfVrjJk2glaz6/evig6xBFrihirq2IuPDD6UyC8+PtddxTkjgPpUL4a+eR5cW8WYgzRLKGrQto9llYRsvkPw5s/ZcZKqKHEkh9DEjMHcodviR2g6fVntVQoAAoyliRBC2ROrKgTyeSqPOPHKtqwOk/R5dt5vABuoTDouJC3t2Zr6vx/+N1Ctl5R/Bq7VsZBo0rIEZSscNFak7Vqk6X4XD1imo+xVAtCfW/tnnz14KNjw9dAZmcd0045Hms+1AKDXvdaT6rePpPrTFa6KWso9oYGtxQV9tR5/yrS97dvC7UeIzViF1pxSFfvibY41XbhZgSPodf7v/rSxx0yrxKwf8ReyI14ssP3U1Cti2zxrZX7UlBJ+0tpOr2b61i7vRm2vxScKPvAgW315PY16w9xWEXiu6mw3gdZeDl35OhRBHV4N/cTul5Wk9+uqy8srephxTxttbnkN/2FNXZ+Z4ba8gSrNCFE00goItkIG8f/3UfDe5jRA//Yd0u3HLCsHVMn7Ay+XhyWY2T95tX44cAxqRswfeHxnp7DCySmJTyS1re8vMzv/erMbw+JGDvrj7oAdvy3A0AhZOhoDOxAB+2toTlv+Oba10uKV9h7Sp3jpMtEDN0GxW0VV+vZK/zLSogG1DVfZSa1SZ2otVJJF6vF7ZM72q/FM+fmZ2ysTrZnXGqCQBkYSVG/MNzXjAAFXSAQfR1aguuASRZ36IT5CI8hznp7X4ab/YkKSNGEELPG1xCLVJ7A4weTfH/US0/0e7uC3k6O4nRcyuDxqR3x0uCjiOFLmg7Wyaxfs1PyHpEiJ47StrJM2HOc9ix5We9yEe3RUItsStODiccL9X0RnpKnIHpLzSHSmEXBamubOdVMtZVfxvB3jZm+BxAdikez2sWGkZ5ILQn19xDdHvIcna1GXbZHT2z0PquiFWKHegyAbkqlCA82n2eI2Vpml5vpaUFN4pJohKVVF12G074NBmJajJuPtjqkbihKgt0uRqGr1OgMF6ce+yA7BRfqFSB5gWiT9IwZlUdPQChUed7EjNjYka7wo+E8tX/SLuvOwzCDjZ/ZyU1+mCnMz5cJnw6ujdm9Zcrt/d8l1BcAZ1PEZf1g/b8XY8Sl6cGSoUm9NXsAYiT7ig1lG3i5cMvmr4D1JtqRdFUq2NrCpMwGoqdYd3xhEtdUiW50sUl2i7O95dqqNjHVbf2z9VH0XPkVpP87pVotuLoxk9tMdFFJ+TuCcd+trv8RXyrhZxZqFB6rS90FxjV10X31XV6CuqHZ2GPzvcEAZOw2772EDLVZige93eT0qbwtVbF88gYeoUwHrbgt98cExmXUUf205EYSKiuiA8QSGwxbLhddKgNAbst1F2i+iNurffZv0X/IDoedv/9J5VYA7eNCYQIhMgQALbVpETgPYw1GA7o8JX32jAYo/xzJxuDGuc5fBlMwWfStVDSi7RlFnWQsZbZ1ftQ3M7qa+eIqNcQTa20VOgpGEYLi2QFJyQSF5Qn+v+AkRiqYnbRhJeyepDLAQXUL9fSgZ5OY/qir0ProWuj48adF3e32TVb+LJ9IUZs3MeyzWk70tgZev3Sf274/WAsoT8NDU1YXrQuEIPm7Yr7Y3PKhMzugz6bqImN+iTQmFlUGMRzYc9KezbIUGdrb42nsMPz3bixlEi6qk+9ihvgjZg5P+okggxqRnhK3RCvtxPWuRoijeiduq8RY2zuGhzbwviRQxfWC3JKjcRp+gLHPSUT4XN4ZWDpz/ZO/ol8nCxYCJNPzfj+UbugURX3bLsb6OZceOdHtPYc+zDeRWJQx9I5Y0k5qjyfVBygksiZ5CiIBABWor0zj1VTlLVOSNq9Dtkyh/ZAtzwvEdFjQIgX1Nq/PYHJibSHFQxrtFOaSqJbdz0YEa4eE5N9S0TdXwMDtr8Z8cMhZ0lrSyvszXoQRKR9z6/aD2kuzee9Tthcko6Gd9cR4tEjGCqajJhtDZu5RAOsYMPeJKl3GUqM3YpYHEerLBzjGHY7zrMK5cnSmV4LhqsUvFyaxnk0Wp6/g4bwH9A1Nynx6qoykK9nh5VkNyliHLerlwfm3SOsD9bqOx0KfhHmlOVOaYa6aVGLNrziI+1GMRSvrys2cnchOXhCqzpgYp1PQhMtskq10kjARUFRRJMJTySBMHfCPliWVm/7+H2xEQtWUgB09OJgtobiZPG4Y1tHkL1b6ZMjJI9a/wuSc9fP5OJuL+rNfj5HOSnT1J0cR8PUf4/aDQ3ufJwecYXmNN1nkPEFYEyGDU/irmnwDLwZpmU/998r2yn+RUnP9d+sanBuZF7V4V11ImhC1eE7BfVnE6v7avkE6Bxy0SSNU/avJYUCMSh4P0FVftdiyp3iKYX4eEGKxYTnttGKMqZtdderDYf4ThnX/6my/5E/kw8wk/UVyoDFcZ3OyO+xsmL7oz2tSOZ3c6bjYl3sA6yYDVg0ho8hcVdEPQ4ZoODufbgoG0DW0ecPeJTI3CZG7fc9gh9bYjID9AW0FAYk7Nwwc
*/