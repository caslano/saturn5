//
//  Copyright (c) 2009-2011 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_LOCALE_DATE_TIME_FACET_HPP_INCLUDED
#define BOOST_LOCALE_DATE_TIME_FACET_HPP_INCLUDED

#include <boost/locale/config.hpp>
#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4275 4251 4231 4660)
#endif

#include <boost/cstdint.hpp>
#include <locale>

namespace boost {
    namespace locale {
        ///
        /// \brief Namespace that contains various types for manipulation with dates
        ///
        namespace period {
            ///
            /// \brief This namespace holds a enum of various period types like era, year, month, etc..
            ///
            namespace marks {
                /// \brief the type that defines a flag that holds a period identifier
                enum period_mark {
                    invalid,                    ///< Special invalid value, should not be used directly
                    era,                        ///< Era i.e. AC, BC in Gregorian and Julian calendar, range [0,1]
                    year,                       ///< Year, it is calendar specific, for example 2011 in Gregorian calendar.
                    extended_year,              ///< Extended year for Gregorian/Julian calendars, where 1 BC == 0, 2 BC == -1.
                    month,                      ///< The month of year, calendar specific, in Gregorian [0..11]
                    day,                        ///< The day of month, calendar specific, in Gregorian [1..31]
                    day_of_year,                ///< The number of day in year, starting from 1, in Gregorian  [1..366]
                    day_of_week,                ///< Day of week, Sunday=1, Monday=2,..., Saturday=7.
                                                ///< Note that updating this value respects local day of week, so for example,
                                                ///< If first day of week is Monday and the current day is Tuesday then setting
                                                ///< the value to Sunday (1) would forward the date by 5 days forward and not backward
                                                ///< by two days as it could be expected if the numbers were taken as is.
                    day_of_week_in_month,       ///< Original number of the day of the week in month. For example 1st Sunday, 
                                                ///< 2nd Sunday, etc. in Gregorian [1..5]
                    day_of_week_local,          ///< Local day of week, for example in France Monday is 1, in US Sunday is 1, [1..7]
                    hour,                       ///< 24 clock hour [0..23]
                    hour_12,                    ///< 12 clock hour [0..11]
                    am_pm,                      ///< am or pm marker [0..1]
                    minute,                     ///< minute [0..59]
                    second,                     ///< second [0..59]
                    week_of_year,               ///< The week number in the year
                    week_of_month,              ///< The week number within current month
                    first_day_of_week,          ///< First day of week, constant, for example Sunday in US = 1, Monday in France = 2
                };

            } // marks

            ///
            /// \brief This class holds a type that represents certain period of time like
            /// year, hour, second and so on.
            ///
            /// It can be created from either marks::period_mark type or by using shortcuts in period
            /// namespace - calling functions like period::year(), period::hour() and so on.
            ///
            /// Basically it represents the same object as enum marks::period_mark but allows to
            /// provide save operator overloading that would not collide with casing of enum to
            /// numeric values.
            ///
            class period_type {
            public:
                ///
                /// Create a period of specific type, default is invalid.
                ///
                period_type(marks::period_mark m = marks::invalid) : mark_(m) 
                {
                }
               
                ///
                /// Get the value of marks::period_mark it was created with.
                /// 
                marks::period_mark mark() const
                {
                    return mark_;
                }

                ///
                /// Check if two periods are the same
                ///
                bool operator==(period_type const &other) const
                {
                    return mark()==other.mark();
                }
                ///
                /// Check if two periods are different
                ///
                bool operator!=(period_type const &other) const
                {
                    return mark()!=other.mark();
                }
            private:
                marks::period_mark mark_;
            };

        } // namespace period

        ///
        /// Structure that define POSIX time, seconds and milliseconds
        /// since Jan 1, 1970, 00:00 not including leap seconds.
        ///
        struct posix_time {
            int64_t seconds; ///< Seconds since epoch
            uint32_t nanoseconds;  ///< Nanoseconds resolution
        };

        ///
        /// This class defines generic calendar class, it is used by date_time and calendar
        /// objects internally. It is less useful for end users, but it is build for localization
        /// backend implementation
        ///

        class abstract_calendar {
        public:

            ///
            /// Type that defines how to fetch the value
            ///
            typedef enum {
                absolute_minimum,   ///< Absolute possible minimum for the value, for example for day is 1
                actual_minimum,     ///< Actual minimal value for this period.
                greatest_minimum,   ///< Maximal minimum value that can be for this period
                current,            ///< Current value of this period
                least_maximum,      ///< The last maximal value for this period, For example for Gregorian calendar
                                    ///< day it is 28
                actual_maximum,     ///< Actual maximum, for it can be 28, 29, 30, 31 for day according to current month
                absolute_maximum,   ///< Maximal value, for Gregorian day it would be 31.
            } value_type;

            ///
            /// A way to update the value
            ///
            typedef enum {
                move,   ///< Change the value up or down effecting others for example 1990-12-31 + 1 day = 1991-01-01
                roll,   ///< Change the value up or down not effecting others for example 1990-12-31 + 1 day = 1990-12-01
            } update_type;

            ///
            /// Information about calendar
            ///
            typedef enum {
                is_gregorian,   ///< Check if the calendar is Gregorian
                is_dst          ///< Check if the current time is in daylight time savings
            } calendar_option_type;

            ///
            /// Make a polymorphic copy of the calendar
            ///
            virtual abstract_calendar *clone() const = 0;

            ///
            /// Set specific \a value for period \a p, note not all values are settable.
            ///
            /// After call of set_value you may want to call normalize() function to make sure
            /// vall periods are updated, if you set sereral fields that are part of single
            /// date/time representation you should call set_value several times and then
            /// call normalize().
            ///
            /// If normalize() is not called after set_value, the behavior is undefined
            ///
            virtual void set_value(period::marks::period_mark p,int value) = 0;

            ///
            /// Recalculate all periods after setting them, should be called after use of set_value() function.
            ///
            virtual void normalize() = 0;

            ///
            /// Get specific value for period \a p according to a value_type \a v
            ///
            virtual int get_value(period::marks::period_mark p,value_type v) const = 0;

            ///
            /// Set current time point
            ///
            virtual void set_time(posix_time const &p)  = 0;
            ///
            /// Get current time point
            ///
            virtual posix_time get_time() const  = 0;

            ///
            /// Set option for calendar, for future use
            ///
            virtual void set_option(calendar_option_type opt,int v) = 0;
            ///
            /// Get option for calendar, currently only check if it is Gregorian calendar
            ///
            virtual int get_option(calendar_option_type opt) const = 0;

            ///
            /// Adjust period's \a p value by \a difference items using a update_type \a u.
            /// Note: not all values are adjustable
            ///
            virtual void adjust_value(period::marks::period_mark p,update_type u,int difference) = 0;

            ///
            /// Calculate the difference between this calendar  and \a other in \a p units
            ///
            virtual int difference(abstract_calendar const *other,period::marks::period_mark p) const = 0;

            ///
            /// Set time zone, empty - use system
            ///
            virtual void set_timezone(std::string const &tz) = 0;
            ///
            /// Get current time zone, empty - system one
            ///
            virtual std::string get_timezone() const = 0;

            ///
            /// Check of two calendars have same rules
            ///
            virtual bool same(abstract_calendar const *other) const = 0;

            virtual ~abstract_calendar()
            {
            }

        };

        ///
        /// \brief the facet that generates calendar for specific locale
        ///
        class BOOST_LOCALE_DECL calendar_facet : public std::locale::facet {
        public:
            ///
            /// Basic constructor
            ///
            calendar_facet(size_t refs = 0) : std::locale::facet(refs) 
            {
            }
            ///
            /// Create a new calendar that points to current point of time.
            ///
            virtual abstract_calendar *create_calendar() const = 0;

            ///
            /// Locale id (needed to work with std::locale)
            ///
            static std::locale::id id;
        };

    } // locale
} // boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif


#endif
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4


/* date_time_facet.hpp
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
*/