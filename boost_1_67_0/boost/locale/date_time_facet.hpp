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