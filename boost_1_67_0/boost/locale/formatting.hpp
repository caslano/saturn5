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