//
//  Copyright (c) 2009-2011 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_LOCALE_FORMATTING_HPP_INCLUDED
#define BOOST_LOCALE_FORMATTING_HPP_INCLUDED

#include <boost/locale/config.hpp>
#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4275 4251 4231 4660)
#endif
#include <boost/cstdint.hpp>
#include <boost/locale/time_zone.hpp>
#include <ostream>
#include <istream>
#include <string>
#include <string.h>
#include <typeinfo>

namespace boost {
    namespace locale {
        ///
        /// \brief This namespace holds additional formatting
        /// flags that can be set using ios_info.
        ///
        namespace flags {
            ///
            /// Formatting flags, each one of them has corresponding manipulation
            /// in namespace \a as
            ///
            typedef enum {
                posix               = 0,
                number              = 1,
                currency            = 2,
                percent             = 3,
                date                = 4,
                time                = 5,
                datetime            = 6,
                strftime            = 7,
                spellout            = 8,
                ordinal             = 9,

                display_flags_mask  = 31,

                currency_default    = 0 << 5,
                currency_iso        = 1 << 5,
                currency_national   = 2 << 5,

                currency_flags_mask = 3 << 5,

                time_default        = 0 << 7,
                time_short          = 1 << 7,
                time_medium         = 2 << 7,
                time_long           = 3 << 7,
                time_full           = 4 << 7,
                time_flags_mask     = 7 << 7,

                date_default        = 0 << 10,
                date_short          = 1 << 10,
                date_medium         = 2 << 10,
                date_long           = 3 << 10,
                date_full           = 4 << 10,
                date_flags_mask     = 7 << 10,

                datetime_flags_mask = date_flags_mask | time_flags_mask

            } display_flags_type;

            ///
            /// Special string patters that can be used
            /// for text formatting
            ///
            typedef enum {
                datetime_pattern,   ///< strftime like formatting
                time_zone_id        ///< time zone name
            } pattern_type;

            ///
            /// Special integer values that can be used for formatting
            ///
            typedef enum {
                domain_id           ///< Domain code - for message formatting
            } value_type;

            
        } // flags

        ///
        /// \brief This class holds an external data - beyond existing fmtflags that std::ios_base holds
        ///
        /// You should almost never create this object directly. Instead, you should access it via ios_info::get(stream_object)
        /// static member function. It automatically creates default formatting data for that stream
        ///
        class BOOST_LOCALE_DECL ios_info {
        public:

            /// \cond INTERNAL

            ios_info();
            ios_info(ios_info const &);
            ios_info const &operator=(ios_info const &);
            ~ios_info();

            /// \endcond

            ///
            /// Get ios_info instance for specific stream object
            ///
            static ios_info &get(std::ios_base &ios);

            ///
            /// Set a flags that define a way for format data like number, spell, currency etc.
            ///
            void display_flags(uint64_t flags);
            
            ///
            /// Set a flags that define how to format currency
            ///
            void currency_flags(uint64_t flags);
            
            ///
            /// Set a flags that define how to format date
            ///
            void date_flags(uint64_t flags);
            
            ///
            /// Set a flags that define how to format time
            ///
            void time_flags(uint64_t flags);
            
            ///
            /// Set a flags that define how to format both date and time
            ///
            void datetime_flags(uint64_t flags);
            
            ///
            /// Set special message domain identification
            ///
            void domain_id(int);
            
            ///
            /// Set time zone for formatting dates and time
            ///
            void time_zone(std::string const &);
            

            ///
            /// Set date/time pattern (strftime like)
            ///
            template<typename CharType>
            void date_time_pattern(std::basic_string<CharType> const &str)
            {
                string_set &s = date_time_pattern_set();
                s.set<CharType>(str.c_str());
            }


            ///
            /// Get a flags that define a way for format data like number, spell, currency etc.
            ///
            uint64_t display_flags() const;
            
            ///
            /// Get a flags that define how to format currency
            ///
            uint64_t currency_flags() const;

            
            ///
            /// Get a flags that define how to format date
            ///
            uint64_t date_flags() const;
            
            ///
            /// Get a flags that define how to format time
            ///
            uint64_t time_flags() const;

            ///
            /// Get a flags that define how to format both date and time
            ///
            uint64_t datetime_flags() const;
            
            ///
            /// Get special message domain identification
            ///
            int domain_id() const;
            
            ///
            /// Get time zone for formatting dates and time
            ///
            std::string time_zone() const;
            
            ///
            /// Get date/time pattern (strftime like)
            ///
            template<typename CharType>
            std::basic_string<CharType> date_time_pattern() const
            {
                string_set const &s = date_time_pattern_set();
                return s.get<CharType>();
            }
            
            /// \cond INTERNAL
            void on_imbue();
            /// \endcond
            
        private:

            class string_set;

            string_set const &date_time_pattern_set() const;
            string_set &date_time_pattern_set();
            
            class BOOST_LOCALE_DECL string_set {
            public:
                string_set(); 
                ~string_set();
                string_set(string_set const &other);
                string_set const &operator=(string_set const &other);
                void swap(string_set &other);
                
                template<typename Char>
                void set(Char const *s)
                {
                    delete [] ptr;
                    ptr = 0;
                    type=&typeid(Char);
                    Char const *end = s;
                    while(*end!=0) end++;
                    // if ptr = 0 it does not matter what is value of size
                    size = sizeof(Char)*(end - s+1);
                    ptr = new char[size];
                    memcpy(ptr,s,size);
                }

                template<typename Char>
                std::basic_string<Char> get() const
                {
                    if(type==0 || *type!=typeid(Char))
                        throw std::bad_cast();
                    std::basic_string<Char> result = reinterpret_cast<Char const *>(ptr);
                    return result;
                }

            private:
                std::type_info const *type;
                size_t size;
                char *ptr;
            };

            uint64_t flags_;
            int domain_id_;
            std::string time_zone_;
            string_set datetime_;

            struct data;
            data *d;

        };


        ///
        /// \brief This namespace includes all manipulators that can be used on IO streams
        ///
        namespace as {
            ///
            /// \defgroup manipulators I/O Stream manipulators
            ///
            /// @{
            ///

            ///
            /// Format values with "POSIX" or "C"  locale. Note, if locale was created with additional non-classic locale then
            /// These numbers may be localized
            ///
            
            inline std::ios_base & posix(std::ios_base & ios)
            {
                ios_info::get(ios).display_flags(flags::posix);
                return ios;
            }

            ///
            /// Format a number. Note, unlike standard number formatting, integers would be treated like real numbers when std::fixed or
            /// std::scientific manipulators were applied
            ///
            inline std::ios_base & number(std::ios_base & ios)
            {
                ios_info::get(ios).display_flags(flags::number);
                return ios;
            }
            
            ///
            /// Format currency, number is treated like amount of money
            ///
            inline std::ios_base & currency(std::ios_base & ios)
            {
                ios_info::get(ios).display_flags(flags::currency);
                return ios;
            }
            
            ///
            /// Format percent, value 0.3 is treated as 30%.
            ///
            inline std::ios_base & percent(std::ios_base & ios)
            {
                ios_info::get(ios).display_flags(flags::percent);
                return ios;
            }
            
            ///
            /// Format a date, number is treated as POSIX time
            ///
            inline std::ios_base & date(std::ios_base & ios)
            {
                ios_info::get(ios).display_flags(flags::date);
                return ios;
            }

            ///
            /// Format a time, number is treated as POSIX time
            ///
            inline std::ios_base & time(std::ios_base & ios)
            {
                ios_info::get(ios).display_flags(flags::time);
                return ios;
            }

            ///
            /// Format a date and time, number is treated as POSIX time
            ///
            inline std::ios_base & datetime(std::ios_base & ios)
            {
                ios_info::get(ios).display_flags(flags::datetime);
                return ios;
            }

            ///
            /// Create formatted date time, Please note, this manipulator only changes formatting mode,
            /// and not format itself, so you are probably looking for ftime manipulator
            ///
            inline std::ios_base & strftime(std::ios_base & ios)
            {
                ios_info::get(ios).display_flags(flags::strftime);
                return ios;
            }
            
            ///
            /// Spell the number, like "one hundred and ten"
            ///
            inline std::ios_base & spellout(std::ios_base & ios)
            {
                ios_info::get(ios).display_flags(flags::spellout);
                return ios;
            }
            
            ///
            /// Write an order of the number like 4th.
            ///
            inline std::ios_base & ordinal(std::ios_base & ios)
            {
                ios_info::get(ios).display_flags(flags::ordinal);
                return ios;
            }

            ///
            /// Set default currency formatting style -- national, like "$"
            ///
            inline std::ios_base & currency_default(std::ios_base & ios)
            {
                ios_info::get(ios).currency_flags(flags::currency_default);
                return ios;
            }

            ///
            /// Set ISO currency formatting style, like "USD", (requires ICU >= 4.2)
            ///
            inline std::ios_base & currency_iso(std::ios_base & ios)
            {
                ios_info::get(ios).currency_flags(flags::currency_iso);
                return ios;
            }

            ///
            /// Set national currency formatting style, like "$"
            ///
            inline std::ios_base & currency_national(std::ios_base & ios)
            {
                ios_info::get(ios).currency_flags(flags::currency_national);
                return ios;
            }

            ///
            /// set default (medium) time formatting style
            ///
            inline std::ios_base & time_default(std::ios_base & ios)
            {
                ios_info::get(ios).time_flags(flags::time_default);
                return ios;
            }

            ///
            /// set short time formatting style
            ///
            inline std::ios_base & time_short(std::ios_base & ios)
            {
                ios_info::get(ios).time_flags(flags::time_short);
                return ios;
            }

            ///
            /// set medium time formatting style
            ///
            inline std::ios_base & time_medium(std::ios_base & ios)
            {
                ios_info::get(ios).time_flags(flags::time_medium);
                return ios;
            }

            ///
            /// set long time formatting style
            ///
            inline std::ios_base & time_long(std::ios_base & ios)
            {
                ios_info::get(ios).time_flags(flags::time_long);
                return ios;
            }

            ///
            /// set full time formatting style
            ///
            inline std::ios_base & time_full(std::ios_base & ios)
            {
                ios_info::get(ios).time_flags(flags::time_full);
                return ios;
            }

            ///
            /// set default (medium) date formatting style
            ///
            inline std::ios_base & date_default(std::ios_base & ios)
            {
                ios_info::get(ios).date_flags(flags::date_default);
                return ios;
            }

            ///
            /// set short date formatting style
            ///
            inline std::ios_base & date_short(std::ios_base & ios)
            {
                ios_info::get(ios).date_flags(flags::date_short);
                return ios;
            }

            ///
            /// set medium date formatting style
            ///
            inline std::ios_base & date_medium(std::ios_base & ios)
            {
                ios_info::get(ios).date_flags(flags::date_medium);
                return ios;
            }

            ///
            /// set long date formatting style
            ///
            inline std::ios_base & date_long(std::ios_base & ios)
            {
                ios_info::get(ios).date_flags(flags::date_long);
                return ios;
            }

            ///
            /// set full date formatting style
            ///
            inline std::ios_base & date_full(std::ios_base & ios)
            {
                ios_info::get(ios).date_flags(flags::date_full);
                return ios;
            }            
            
            
            /// \cond INTERNAL 
            namespace details {
                template<typename CharType>
                struct add_ftime {

                    std::basic_string<CharType> ftime;

                    void apply(std::basic_ios<CharType> &ios) const
                    {
                        ios_info::get(ios).date_time_pattern(ftime);
                        as::strftime(ios);
                    }

                };

                template<typename CharType>
                std::basic_ostream<CharType> &operator<<(std::basic_ostream<CharType> &out,add_ftime<CharType> const &fmt)
                {
                    fmt.apply(out);
                    return out;
                }
                
                template<typename CharType>
                std::basic_istream<CharType> &operator>>(std::basic_istream<CharType> &in,add_ftime<CharType> const &fmt)
                {
                    fmt.apply(in);
                    return in;
                }

            }
            /// \endcond 

            ///
            /// Set strftime like formatting string
            ///
            /// Please note, formatting flags are very similar but not exactly the same as flags for C function strftime.
            /// Differences: some flags as "%e" do not add blanks to fill text up to two spaces, not all flags supported.
            ///
            /// Flags:
            /// -   "%a" -- Abbreviated  weekday (Sun.)
            /// -   "%A" -- Full weekday (Sunday)
            /// -   "%b" -- Abbreviated month (Jan.)
            /// -   "%B" -- Full month (January)
            /// -   "%c" -- Locale date-time format. **Note:** prefer using "as::datetime"
            /// -   "%d" -- Day of Month [01,31]
            /// -   "%e" -- Day of Month [1,31]
            /// -   "%h" -- Same as "%b"
            /// -   "%H" -- 24 clock hour [00,23]
            /// -   "%I" -- 12 clock hour [01,12]
            /// -   "%j" -- Day of year [1,366]
            /// -   "%m" -- Month [01,12]
            /// -   "%M" -- Minute [00,59]
            /// -   "%n" -- New Line
            /// -   "%p" -- AM/PM in locale representation
            /// -   "%r" -- Time with AM/PM, same as "%I:%M:%S %p"
            /// -   "%R" -- Same as "%H:%M"
            /// -   "%S" -- Second [00,61]
            /// -   "%t" -- Tab character
            /// -   "%T" -- Same as "%H:%M:%S"
            /// -   "%x" -- Local date representation. **Note:** prefer using "as::date"
            /// -   "%X" -- Local time representation. **Note:** prefer using "as::time"
            /// -   "%y" -- Year [00,99]
            /// -   "%Y" -- 4 digits year. (2009)
            /// -   "%Z" -- Time Zone
            /// -   "%%" -- Percent symbol
            ///


            template<typename CharType>
            #ifdef BOOST_LOCALE_DOXYGEN
            unspecified_type
            #else
            details::add_ftime<CharType> 
            #endif
            ftime(std::basic_string<CharType> const &format)
            {
                details::add_ftime<CharType> fmt;
                fmt.ftime=format;
                return fmt;
            }

            ///
            /// See ftime(std::basic_string<CharType> const &format)
            ///
            template<typename CharType>
            #ifdef BOOST_LOCALE_DOXYGEN
            unspecified_type
            #else
            details::add_ftime<CharType> 
            #endif
            ftime(CharType const *format)
            {
                details::add_ftime<CharType> fmt;
                fmt.ftime=format;
                return fmt;
            }

            /// \cond INTERNAL
            namespace details {
                struct set_timezone {
                    std::string id;
                };
                template<typename CharType>
                std::basic_ostream<CharType> &operator<<(std::basic_ostream<CharType> &out,set_timezone const &fmt)
                {
                    ios_info::get(out).time_zone(fmt.id);
                    return out;
                }
                
                template<typename CharType>
                std::basic_istream<CharType> &operator>>(std::basic_istream<CharType> &in,set_timezone const &fmt)
                {
                    ios_info::get(in).time_zone(fmt.id);
                    return in;
                }
            }
            /// \endcond
            
            ///
            /// Set GMT time zone to stream
            /// 
            inline std::ios_base &gmt(std::ios_base &ios)
            {
                ios_info::get(ios).time_zone("GMT");
                return ios;
            }

            ///
            /// Set local time zone to stream
            ///
            inline std::ios_base &local_time(std::ios_base &ios)
            {
                ios_info::get(ios).time_zone(time_zone::global());
                return ios;
            }

            ///
            /// Set time zone using \a id
            ///
            inline 
            #ifdef BOOST_LOCALE_DOXYGEN
            unspecified_type
            #else
            details::set_timezone 
            #endif
            time_zone(char const *id) 
            {
                details::set_timezone tz;
                tz.id=id;
                return tz;
            }

            ///
            /// Set time zone using \a id
            ///
            inline 
            #ifdef BOOST_LOCALE_DOXYGEN
            unspecified_type
            #else
            details::set_timezone 
            #endif            
            time_zone(std::string const &id) 
            {
                details::set_timezone tz;
                tz.id=id;
                return tz;
            }


        ///
        /// @}
        ///

        } // as manipulators
        
    } // locale
} // boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif


#endif
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

/* formatting.hpp
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
*/