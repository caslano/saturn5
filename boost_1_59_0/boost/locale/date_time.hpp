//
//  Copyright (c) 2009-2011 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_LOCALE_DATE_TIME_HPP_INCLUDED
#define BOOST_LOCALE_DATE_TIME_HPP_INCLUDED

#include <boost/locale/config.hpp>
#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4275 4251 4231 4660)
#endif

#include <boost/locale/hold_ptr.hpp>
#include <boost/locale/date_time_facet.hpp>
#include <boost/locale/formatting.hpp>
#include <boost/locale/time_zone.hpp>
#include <locale>
#include <vector>
#include <stdexcept>


namespace boost {
    namespace locale {
        ///
        /// \defgroup date_time Date, Time, Timezone and Calendar manipulations 
        ///
        /// This module provides various calendar, timezone and date time services
        ///
        /// @{


        ///
        /// \brief This error is thrown in case of invalid state that occurred
        ///
        class BOOST_SYMBOL_VISIBLE date_time_error : public std::runtime_error {
        public:
            ///
            /// Constructor of date_time_error class
            /// 
            date_time_error(std::string const &e) : std::runtime_error(e) {}
        };


        ///
        /// \brief This class represents a pair of period_type and the integer
        /// values that describes its amount. For example 3 days or 4 years.
        ///
        /// Usually obtained as product of period_type and integer or
        /// my calling a representative functions
        /// For example day()*3 == date_time_period(day(),3) == day(3)
        /// 
        struct date_time_period 
        {
            period::period_type type;   ///< The type of period, i.e. era, year, day etc.
            int value;                  ///< The value the actual number of \a periods
            ///
            /// Operator + returns copy of itself
            ///
            date_time_period operator+() const { return *this; }
            ///
            /// Operator -, switches the sign of period
            ///
            date_time_period operator-() const { return date_time_period(type,-value); }
            
            ///
            /// Constructor that creates date_time_period from period_type \a f and a value \a v -- default 1.
            ///
            date_time_period(period::period_type f=period::period_type(),int v=1) : type(f), value(v) {}
        };

        namespace period {
            ///
            ///  Get period_type for: special invalid value, should not be used directly
            ///
            inline period_type invalid(){ return period_type(marks::invalid); }
            ///
            ///  Get period_type for: Era i.e. AC, BC in Gregorian and Julian calendar, range [0,1]
            ///
            inline period_type era(){ return period_type(marks::era); }
            ///
            ///  Get period_type for: Year, it is calendar specific, for example 2011 in Gregorian calendar.
            ///
            inline period_type year(){ return period_type(marks::year); }
            ///
            ///  Get period_type for: Extended year for Gregorian/Julian calendars, where 1 BC == 0, 2 BC == -1.
            ///
            inline period_type extended_year(){ return period_type(marks::extended_year); }
            ///
            ///  Get period_type for: The month of year, calendar specific, in Gregorian [0..11]
            ///
            inline period_type month(){ return period_type(marks::month); }
            ///
            ///  Get period_type for: The day of month, calendar specific, in Gregorian [1..31]
            ///
            inline period_type day(){ return period_type(marks::day); }
            ///
            ///  Get period_type for: The number of day in year, starting from 1, in Gregorian  [1..366]
            ///
            inline period_type day_of_year(){ return period_type(marks::day_of_year); }
            ///
            ///  Get period_type for: Day of week, Sunday=1, Monday=2,..., Saturday=7.
            ///
            /// Note that updating this value respects local day of week, so for example,
            /// If first day of week is Monday and the current day is Tuesday then setting
            /// the value to Sunday (1) would forward the date by 5 days forward and not backward
            /// by two days as it could be expected if the numbers were taken as is.
            ///
            inline period_type day_of_week(){ return period_type(marks::day_of_week); }
            ///
            ///  Get period_type for: Original number of the day of the week in month. For example 1st Sunday, 
            /// 2nd Sunday, etc. in Gregorian [1..5]
            ///
            inline period_type day_of_week_in_month(){ return period_type(marks::day_of_week_in_month); }
            ///
            ///  Get period_type for: Local day of week, for example in France Monday is 1, in US Sunday is 1, [1..7]
            ///
            inline period_type day_of_week_local(){ return period_type(marks::day_of_week_local); }
            ///
            ///  Get period_type for: 24 clock hour [0..23]
            ///
            inline period_type hour(){ return period_type(marks::hour); }
            ///
            ///  Get period_type for: 12 clock hour [0..11]
            ///
            inline period_type hour_12(){ return period_type(marks::hour_12); }
            ///
            ///  Get period_type for: am or pm marker [0..1]
            ///
            inline period_type am_pm(){ return period_type(marks::am_pm); }
            ///
            ///  Get period_type for: minute [0..59]
            ///
            inline period_type minute(){ return period_type(marks::minute); }
            ///
            ///  Get period_type for: second [0..59]
            ///
            inline period_type second(){ return period_type(marks::second); }
            ///
            ///  Get period_type for: The week number in the year
            ///
            inline period_type week_of_year(){ return period_type(marks::week_of_year); }
            ///
            ///  Get period_type for: The week number within current month
            ///
            inline period_type week_of_month(){ return period_type(marks::week_of_month); }
            ///
            ///  Get period_type for: First day of week, constant, for example Sunday in US = 1, Monday in France = 2
            ///
            inline period_type first_day_of_week(){ return period_type(marks::first_day_of_week); }

            ///
            ///  Get date_time_period for: Era i.e. AC, BC in Gregorian and Julian calendar, range [0,1]
            ///
            inline date_time_period era(int v) { return date_time_period(era(),v); } 
            ///
            ///  Get date_time_period for: Year, it is calendar specific, for example 2011 in Gregorian calendar.
            ///
            inline date_time_period year(int v) { return date_time_period(year(),v); } 
            ///
            ///  Get date_time_period for: Extended year for Gregorian/Julian calendars, where 1 BC == 0, 2 BC == -1.
            ///
            inline date_time_period extended_year(int v) { return date_time_period(extended_year(),v); } 
            ///
            ///  Get date_time_period for: The month of year, calendar specific, in Gregorian [0..11]
            ///
            inline date_time_period month(int v) { return date_time_period(month(),v); } 
            ///
            ///  Get date_time_period for: The day of month, calendar specific, in Gregorian [1..31]
            ///
            inline date_time_period day(int v) { return date_time_period(day(),v); } 
            ///
            ///  Get date_time_period for: The number of day in year, starting from 1, in Gregorian  [1..366]
            ///
            inline date_time_period day_of_year(int v) { return date_time_period(day_of_year(),v); } 
            ///
            ///  Get date_time_period for: Day of week, Sunday=1, Monday=2,..., Saturday=7.
            ///
            /// Note that updating this value respects local day of week, so for example,
            /// If first day of week is Monday and the current day is Tuesday then setting
            /// the value to Sunday (1) would forward the date by 5 days forward and not backward
            /// by two days as it could be expected if the numbers were taken as is.
            ///
            inline date_time_period day_of_week(int v) { return date_time_period(day_of_week(),v); } 
            ///
            ///  Get date_time_period for: Original number of the day of the week in month. For example 1st Sunday, 
            /// 2nd Sunday, etc. in Gregorian [1..5]
            ///
            inline date_time_period day_of_week_in_month(int v) { return date_time_period(day_of_week_in_month(),v); } 
            ///
            ///  Get date_time_period for: Local day of week, for example in France Monday is 1, in US Sunday is 1, [1..7]
            ///
            inline date_time_period day_of_week_local(int v) { return date_time_period(day_of_week_local(),v); } 
            ///
            ///  Get date_time_period for: 24 clock hour [0..23]
            ///
            inline date_time_period hour(int v) { return date_time_period(hour(),v); } 
            ///
            ///  Get date_time_period for: 12 clock hour [0..11]
            ///
            inline date_time_period hour_12(int v) { return date_time_period(hour_12(),v); } 
            ///
            ///  Get date_time_period for: am or pm marker [0..1]
            ///
            inline date_time_period am_pm(int v) { return date_time_period(am_pm(),v); } 
            ///
            ///  Get date_time_period for: minute [0..59]
            ///
            inline date_time_period minute(int v) { return date_time_period(minute(),v); } 
            ///
            ///  Get date_time_period for: second [0..59]
            ///
            inline date_time_period second(int v) { return date_time_period(second(),v); } 
            ///
            ///  Get date_time_period for: The week number in the year
            ///
            inline date_time_period week_of_year(int v) { return date_time_period(week_of_year(),v); } 
            ///
            ///  Get date_time_period for: The week number within current month
            ///
            inline date_time_period week_of_month(int v) { return date_time_period(week_of_month(),v); } 
            ///
            ///  Get date_time_period for: First day of week, constant, for example Sunday in US = 1, Monday in France = 2
            ///
            inline date_time_period first_day_of_week(int v) { return date_time_period(first_day_of_week(),v); } 

            ///
            /// Get predefined constant for January
            ///
            inline date_time_period january() { return date_time_period(month(),0); }
            ///
            /// Get predefined constant for February
            ///
            inline date_time_period february() { return date_time_period(month(),1); }
            ///
            /// Get predefined constant for March
            ///
            inline date_time_period march() { return date_time_period(month(),2); }
            ///
            /// Get predefined constant for April
            ///
            inline date_time_period april() { return date_time_period(month(),3); }
            ///
            /// Get predefined constant for May
            ///
            inline date_time_period may() { return date_time_period(month(),4); }
            ///
            /// Get predefined constant for June
            ///
            inline date_time_period june() { return date_time_period(month(),5); }
            ///
            /// Get predefined constant for July
            ///
            inline date_time_period july() { return date_time_period(month(),6); }
            ///
            /// Get predefined constant for August
            ///
            inline date_time_period august() { return date_time_period(month(),7); }
            ///
            /// Get predefined constant for September
            ///
            inline date_time_period september() { return date_time_period(month(),8); }
            ///
            /// Get predefined constant for October 
            ///
            inline date_time_period october() { return date_time_period(month(),9); }
            ///
            /// Get predefined constant for November
            ///
            inline date_time_period november() { return date_time_period(month(),10); }
            ///
            /// Get predefined constant for December
            ///
            inline date_time_period december() { return date_time_period(month(),11); }

            ///
            /// Get predefined constant for Sunday
            ///
            inline date_time_period sunday() { return date_time_period(day_of_week(),1); }
            ///
            /// Get predefined constant for Monday 
            ///
            inline date_time_period monday() { return date_time_period(day_of_week(),2); }
            ///
            /// Get predefined constant for Tuesday
            ///
            inline date_time_period tuesday() { return date_time_period(day_of_week(),3); }
            ///
            /// Get predefined constant for Wednesday
            ///
            inline date_time_period wednesday() { return date_time_period(day_of_week(),4); }
            ///
            /// Get predefined constant for Thursday
            ///
            inline date_time_period thursday() { return date_time_period(day_of_week(),5); }
            ///
            /// Get predefined constant for Friday
            ///
            inline date_time_period friday() { return date_time_period(day_of_week(),6); }
            ///
            /// Get predefined constant for Saturday
            ///
            inline date_time_period saturday() { return date_time_period(day_of_week(),7); }
            ///
            /// Get predefined constant for AM (Ante Meridiem)
            ///
            inline date_time_period am() { return date_time_period(am_pm(),0); }
            ///
            /// Get predefined constant for PM (Post Meridiem)
            ///
            inline date_time_period pm() { return date_time_period(am_pm(),1); }

            ///
            /// convert period_type to date_time_period(f,1)
            ///
            inline date_time_period operator+(period::period_type f) 
            {
                return date_time_period(f);
            }
            ///
            /// convert period_type to date_time_period(f,-1)
            ///
            inline date_time_period operator-(period::period_type f)
            {
                return date_time_period(f,-1);
            }

            ///
            /// Create date_time_period of type \a f with value \a v. 
            ///
            template<typename T>
            date_time_period operator*(period::period_type f,T v)
            {
                return date_time_period(f,v);
            }

            ///
            /// Create date_time_period of type \a f with value \a v. 
            ///
            template<typename T>
            date_time_period operator*(T v,period::period_type f)
            {
                return date_time_period(f,v);
            }
            ///
            /// Create date_time_period of type \a f with value \a v. 
            ///
            template<typename T>
            date_time_period operator*(T v,date_time_period f)
            {
                return date_time_period(f.type,f.value*v);
            }

            ///
            /// Create date_time_period of type \a f with value \a v. 
            ///
            template<typename T>
            date_time_period operator*(date_time_period f,T v)
            {
                return date_time_period(f.type,f.value*v);
            }


        } // period


        ///
        /// \brief this class that represents a set of periods, 
        ///
        /// It is generally created by operations on periods:
        /// 1995*year + 3*month + 1*day. Note: operations are not commutative.
        ///
        class date_time_period_set {
        public:
            
            ///
            /// Default constructor - empty set
            ///
            date_time_period_set()
            {
            }
            ///
            /// Create a set of single period with value 1
            ///
            date_time_period_set(period::period_type f)
            {
                basic_[0]=date_time_period(f);
            }
            ///
            /// Create a set of single period \a fl
            ///
            date_time_period_set(date_time_period const &fl)
            {
                basic_[0]=fl;
            }
            ///
            /// Append date_time_period \a f to the set
            ///
            void add(date_time_period f)
            {
                size_t n=size();
                if(n < 4)
                    basic_[n]=f;
                else
                    periods_.push_back(f);
            }
            ///
            /// Get number if items in list
            ///
            size_t size() const
            {
                if(basic_[0].type == period::period_type())
                    return 0;
                if(basic_[1].type == period::period_type())
                    return 1;
                if(basic_[2].type == period::period_type())
                    return 2;
                if(basic_[3].type == period::period_type())
                    return 3;
                return 4+periods_.size();
            }
            ///
            /// Get item at position \a n the set, n should be in range [0,size)
            ///
            date_time_period const &operator[](size_t n) const 
            {
                if(n >= size())
                    throw std::out_of_range("Invalid index to date_time_period");
                if(n < 4)
                    return basic_[n];
                else
                    return periods_[n-4];
            }
        private:
            date_time_period basic_[4];
            std::vector<date_time_period> periods_;
        };

        
        ///
        /// Append two periods sets. Note this operator is not commutative 
        ///
        inline date_time_period_set operator+(date_time_period_set const &a,date_time_period_set const &b)
        {
            date_time_period_set s(a);
            for(unsigned i=0;i<b.size();i++)
                s.add(b[i]);
            return s;
        }
        
        ///
        /// Append two period sets when all periods of set \b change their sign
        ///
        inline date_time_period_set operator-(date_time_period_set const &a,date_time_period_set const &b)
        {
            date_time_period_set s(a);
            for(unsigned i=0;i<b.size();i++)
                s.add(-b[i]);
            return s;
        }


        ///
        /// \brief this class provides an access to general calendar information. 
        ///
        /// This information is not connected to specific date but generic to locale, and timezone.
        /// It is used in obtaining general information about calendar and is essential for creation of
        /// date_time objects.
        ///
        class BOOST_LOCALE_DECL calendar {
        public:

            ///
            /// Create calendar taking locale and timezone information from ios_base instance.
            /// 
            /// \note throws std::bad_cast if ios does not have a locale with installed \ref calendar_facet
            /// facet installed
            /// 
            calendar(std::ios_base &ios);
            ///
            /// Create calendar with locale \a l and time_zone \a zone
            ///
            /// \note throws std::bad_cast if loc does not have \ref calendar_facet facet installed
            /// 
            calendar(std::locale const &l,std::string const &zone);
            ///
            /// Create calendar with locale \a l and default timezone
            ///
            /// \note throws std::bad_cast if loc does not have \ref calendar_facet facet installed
            /// 
            calendar(std::locale const &l);
            ///
            /// Create calendar with default locale and timezone \a zone
            ///
            /// \note throws std::bad_cast if global locale does not have \ref calendar_facet facet installed
            /// 
            calendar(std::string const &zone);
            ///
            /// Create calendar with default locale and timezone 
            ///
            /// \note throws std::bad_cast if global locale does not have \ref calendar_facet facet installed
            /// 
            calendar();
            ~calendar();

            ///
            /// copy calendar
            ///
            calendar(calendar const &other);
            ///
            /// assign calendar
            ///
            calendar const &operator=(calendar const &other);

            ///
            /// Get minimum value for period f, For example for period::day it is 1.
            ///
            int minimum(period::period_type f) const;
            ///
            /// Get greatest possible minimum value for period f, For example for period::day it is 1, but may be different for other calendars.
            ///
            int greatest_minimum(period::period_type f) const;
            ///
            /// Get maximum value for period f, For example for Gregorian calendar's maximum period::day it is 31.
            ///
            int maximum(period::period_type f) const;
            ///
            /// Get least maximum value for period f, For example for Gregorian calendar's maximum period::day it is 28.
            ///
            int least_maximum(period::period_type f) const;

            ///
            /// Get first day of week for specific calendar, for example for US it is 1 - Sunday for France it is 2 - Monday
            int first_day_of_week() const;

            ///
            /// get calendar's locale
            ///
            std::locale get_locale() const;
            ///
            /// get calendar's time zone
            ///
            std::string get_time_zone() const;

            ///
            /// Check if the calendar is Gregorian
            ///
            bool is_gregorian() const;

            ///
            /// Compare calendars for equivalence: i.e. calendar types, time zones etc.
            ///
            bool operator==(calendar const &other) const;
            ///
            /// Opposite of ==
            ///
            bool operator!=(calendar const &other) const;

        private:
            friend class date_time;
            std::locale locale_;
            std::string tz_;
            hold_ptr<abstract_calendar> impl_;
        };

        ///
        /// \brief this class represents a date time and allows to perform various operation according to the
        /// locale settings.
        ///
        /// This class allows to manipulate various aspects of dates and times easily using arithmetic operations with
        /// periods.
        ///
        /// General arithmetic functions:
        ///
        /// - date_time + date_time_period_set = date_time: move time point forward by specific periods like date_time + month;
        /// - date_time - date_time_period_set = date_time: move time point backward by specific periods like date_time - month;
        /// - date_time << date_time_period_set  = date_time: roll time point forward by specific periods with rolling to begin if overflows: like "2010-01-31" << 2* day == "2010-01-02" instead of "2010-02-02"
        /// - date_time >> date_time_period_set  = date_time: roll time point backward by specific periods with rolling to end if overflows: like "2010-01-02" >> 2* day == "2010-01-31" instead of "2009-12-30"
        /// - date_time / period_type = int - current period value: like "2010-12-21" / month == 12. "2010-12-21" / year = 2010
        /// - (date_time - date_time) / period_type = int: distance between dates in period_type. Like ("2010-12-01" - "2008-12-01") / month = 24.
        ///
        /// You can also assign specific periods using assignment operator like:
        /// some_time = year * 1995 that sets the year to 1995.
        ///
        ///
        
        class BOOST_LOCALE_DECL date_time {
        public:

            ///
            /// Dafault constructor, uses default calendar initialized date_time object to current time.
            ///
            /// \note throws std::bad_cast if the global locale does not have \ref calendar_facet facet installed
            /// 
            date_time();
            ///
            /// copy date_time
            ///
            date_time(date_time const &other);
            ///
            /// copy date_time and change some fields according to the \a set
            ///
            date_time(date_time const &other,date_time_period_set const &set);
            ///
            /// assign the date_time
            ///
            date_time const &operator=(date_time const &other);
            ~date_time();

            ///
            /// Create a date_time object using POSIX time \a time and default calendar
            ///
            /// \note throws std::bad_cast if the global locale does not have \ref calendar_facet facet installed
            /// 
            date_time(double time);
            ///
            /// Create a date_time object using POSIX time \a time and calendar \a cal
            ///
            date_time(double time,calendar const &cal);
            ///
            /// Create a date_time object using calendar \a cal and initializes it to current time.
            ///
            date_time(calendar const &cal);
            
            ///
            /// Create a date_time object using default calendar and define values given in \a set
            ///
            /// \note throws std::bad_cast if the global locale does not have \ref calendar_facet facet installed
            /// 
            date_time(date_time_period_set const &set);
            ///
            /// Create a date_time object using calendar \a cal and define values given in \a set
            ///
            date_time(date_time_period_set const &set,calendar const &cal);

           
            ///
            /// assign values to various periods in set \a f  
            ///
            date_time const &operator=(date_time_period_set const &f);

            ///
            /// set specific period \a f value to \a v
            ///
            void set(period::period_type f,int v);
            ///
            /// get specific period \a f value
            ///
            int get(period::period_type f) const;

            ///
            /// syntactic sugar for get(f)
            ///
            int operator/(period::period_type f) const
            {
                return get(f);
            }

            ///
            /// add single period f to the current date_time
            ///
            date_time operator+(period::period_type f) const
            {
                return *this+date_time_period(f);
            }

            ///
            /// subtract single period f from the current date_time
            ///
            date_time operator-(period::period_type f) const
            {
                return *this-date_time_period(f);
            }

            ///
            /// add single period f to the current date_time
            ///
            date_time const &operator+=(period::period_type f)
            {
                return *this+=date_time_period(f);
            }
            ///
            /// subtract single period f from the current date_time
            ///
            date_time const &operator-=(period::period_type f)
            {
                return *this-=date_time_period(f);
            }

            ///
            /// roll forward a date by single period f.
            ///
            date_time operator<<(period::period_type f) const
            {
                return *this<<date_time_period(f);
            }

            ///
            /// roll backward a date by single period f.
            ///
            date_time operator>>(period::period_type f) const
            {
                return *this>>date_time_period(f);
            }

            ///
            /// roll forward a date by single period f.
            ///
            date_time const &operator<<=(period::period_type f)
            {
                return *this<<=date_time_period(f);
            }
            ///
            /// roll backward a date by single period f.
            ///
            date_time const &operator>>=(period::period_type f)
            {
                return *this>>=date_time_period(f);
            }

            ///
            /// add date_time_period to the current date_time
            ///
            date_time operator+(date_time_period const &v) const;
            ///
            /// subtract date_time_period from the current date_time
            ///
            date_time operator-(date_time_period const &v) const;
            ///
            /// add date_time_period to the current date_time
            ///
            date_time const &operator+=(date_time_period const &v);
            ///
            /// subtract date_time_period from the current date_time
            ///
            date_time const &operator-=(date_time_period const &v);

            ///
            /// roll current date_time forward by date_time_period v
            ///
            date_time operator<<(date_time_period const &v) const;
            ///
            /// roll current date_time backward by date_time_period v
            ///
            date_time operator>>(date_time_period const &v) const ;
            ///
            /// roll current date_time forward by date_time_period v
            ///
            date_time const &operator<<=(date_time_period const &v);
            ///
            /// roll current date_time backward by date_time_period v
            ///
            date_time const &operator>>=(date_time_period const &v);

            ///
            /// add date_time_period_set v to the current date_time
            ///
            date_time operator+(date_time_period_set const &v) const;
            ///
            /// subtract date_time_period_set v from the current date_time
            ///
            date_time operator-(date_time_period_set const &v) const;
            ///
            /// add date_time_period_set v to the current date_time
            ///
            date_time const &operator+=(date_time_period_set const &v);
            ///
            /// subtract date_time_period_set v from the current date_time
            ///
            date_time const &operator-=(date_time_period_set const &v);

            ///
            /// roll current date_time forward by date_time_period_set v
            ///
            date_time operator<<(date_time_period_set const &v) const;
            ///
            /// roll current date_time backward by date_time_period_set v
            ///
            date_time operator>>(date_time_period_set const &v) const ;
            ///
            /// roll current date_time forward by date_time_period_set v
            ///
            date_time const &operator<<=(date_time_period_set const &v);
            ///
            /// roll current date_time backward by date_time_period_set v
            ///
            date_time const &operator>>=(date_time_period_set const &v);

            ///
            /// Get POSIX time
            ///
            /// The POSIX time is number of seconds since January 1st, 1970 00:00 UTC, ignoring leap seconds.
            ///
            double time() const;
            ///
            /// set POSIX time
            ///
            /// The POSIX time is number of seconds since January 1st, 1970 00:00 UTC, ignoring leap seconds.
            /// This time can be fetched from Operating system clock using C function time, gettimeofday and others.
            ///
            void time(double v);

            ///
            /// compare date_time in the timeline (ignores difference in calendar, timezone etc)
            ///
            bool operator==(date_time const &other) const;
            ///
            /// compare date_time in the timeline (ignores difference in calendar, timezone etc)
            ///
            bool operator!=(date_time const &other) const;
            ///
            /// compare date_time in the timeline (ignores difference in calendar, timezone etc)
            ///
            bool operator<(date_time const &other) const;
            ///
            /// compare date_time in the timeline (ignores difference in calendar, timezone etc)
            ///
            bool operator>(date_time const &other) const;
            ///
            /// compare date_time in the timeline (ignores difference in calendar, timezone etc)
            ///
            bool operator<=(date_time const &other) const;
            ///
            /// compare date_time in the timeline (ignores difference in calendar, timezone etc)
            ///
            bool operator>=(date_time const &other) const;

            ///
            /// swaps two dates - efficient, does not throw
            ///
            void swap(date_time &other);

            ///
            /// calculate the distance from this date_time to \a other in terms of perios \a f
            ///
            int difference(date_time const &other,period::period_type f) const;

            ///
            /// Get minimal possible value for *this time point for a period \a f.
            ///
            int minimum(period::period_type f) const;
            ///
            /// Get minimal possible value for *this time point for a period \a f. For example
            /// in February maximum(day) may be 28 or 29, in January maximum(day)==31
            ///
            int maximum(period::period_type f) const;

            ///
            /// Check if *this time point is in daylight saving time 
            ///
            bool is_in_daylight_saving_time() const;

        private:
            hold_ptr<abstract_calendar> impl_;
        };

        ///
        /// Writes date_time \a t to output stream \a out.
        ///
        /// This function uses locale, calendar and time zone of the target stream \a in.
        ///
        /// For example:
        /// \code
        ///  date_time now(time(0),hebrew_calendar)
        ///  cout << "Year: " << period::year(now) <<" Full Date:"<< now;
        /// \endcode
        ///
        /// The output may be Year:5770 Full Date:Jan 1, 2010
        /// 
        template<typename CharType>
        std::basic_ostream<CharType> &operator<<(std::basic_ostream<CharType> &out,date_time const &t)
        {
            double time_point = t.time();
            uint64_t display_flags = ios_info::get(out).display_flags();
            if  (
                    display_flags == flags::date 
                    || display_flags == flags::time 
                    || display_flags == flags::datetime 
                    || display_flags == flags::strftime
                ) 
            {
                out << time_point;
            }
            else {
                ios_info::get(out).display_flags(flags::datetime);
                out << time_point;
                ios_info::get(out).display_flags(display_flags);
            }
            return out;
        }

        ///
        /// Reads date_time \a t from output stream \a in
        ///
        /// This function uses locale, calendar and time zone of the source stream \a in.
        ///
        template<typename CharType>
        std::basic_istream<CharType> &operator>>(std::basic_istream<CharType> &in,date_time &t)
        {
            double v;
            uint64_t display_flags = ios_info::get(in).display_flags();
            if  (
                    display_flags == flags::date 
                    || display_flags == flags::time 
                    || display_flags == flags::datetime 
                    || display_flags == flags::strftime
                ) 
            {
                in >> v;
            }
            else {
                ios_info::get(in).display_flags(flags::datetime);
                in >> v;
                ios_info::get(in).display_flags(display_flags);
            }
            if(!in.fail())
                t.time(v);
            return in;
        }

        ///
        /// \brief This class represents a period: a pair of two date_time objects.
        /// 
        /// It is generally used as syntactic sugar to calculate difference between two dates.
        ///
        /// Note: it stores references to the original objects, so it is not recommended to be used
        /// outside of the equation you calculate the difference in.
        ///
        class date_time_duration {
        public:

            ///
            /// Create an object were \a first represents earlier point on time line and \a second is later
            /// point.
            /// 
            date_time_duration(date_time const &first,date_time const &second) :
                s_(first),
                e_(second)
            {
            }
            
            ///
            /// find a difference in terms of period_type \a f
            ///
            int get(period::period_type f) const
            {
                return start().difference(end(),f);
            }

            ///
            /// Syntactic sugar for get(f)
            ///
            int operator / (period::period_type f) const
            {
                return start().difference(end(),f);
            }

            ///
            /// Get starting point
            ///
            date_time const &start() const { return s_; }
            ///
            /// Get ending point
            ///
            date_time const &end() const { return e_; }
        private:
            date_time const &s_;
            date_time const &e_;
        };

        ///
        /// Calculates the difference between two dates, the left operand is a later point on time line.
        /// Returns date_time_duration object.
        ///
        inline date_time_duration operator-(date_time const &later,date_time const &earlier)
        {
            return date_time_duration(earlier,later);
        }

        
        namespace period {
            ///
            ///  Extract from date_time numerical value of Era i.e. AC, BC in Gregorian and Julian calendar, range [0,1]
            ///
            inline int era(date_time const &dt) { return dt.get(era()); } 
            ///
            ///  Extract from date_time numerical value of Year, it is calendar specific, for example 2011 in Gregorian calendar.
            ///
            inline int year(date_time const &dt) { return dt.get(year()); } 
            ///
            ///  Extract from date_time numerical value of Extended year for Gregorian/Julian calendars, where 1 BC == 0, 2 BC == -1.
            ///
            inline int extended_year(date_time const &dt) { return dt.get(extended_year()); } 
            ///
            ///  Extract from date_time numerical value of The month of year, calendar specific, in Gregorian [0..11]
            ///
            inline int month(date_time const &dt) { return dt.get(month()); } 
            ///
            ///  Extract from date_time numerical value of The day of month, calendar specific, in Gregorian [1..31]
            ///
            inline int day(date_time const &dt) { return dt.get(day()); } 
            ///
            ///  Extract from date_time numerical value of The number of day in year, starting from 1, in Gregorian  [1..366]
            ///
            inline int day_of_year(date_time const &dt) { return dt.get(day_of_year()); } 
            ///
            ///  Extract from date_time numerical value of Day of week, Sunday=1, Monday=2,..., Saturday=7.
            ///
            /// Note that updating this value respects local day of week, so for example,
            /// If first day of week is Monday and the current day is Tuesday then setting
            /// the value to Sunday (1) would forward the date by 5 days forward and not backward
            /// by two days as it could be expected if the numbers were taken as is.
            ///
            inline int day_of_week(date_time const &dt) { return dt.get(day_of_week()); } 
            ///
            ///  Extract from date_time numerical value of Original number of the day of the week in month. For example 1st Sunday, 
            /// 2nd Sunday, etc. in Gregorian [1..5]
            ///
            inline int day_of_week_in_month(date_time const &dt) { return dt.get(day_of_week_in_month()); } 
            ///
            ///  Extract from date_time numerical value of Local day of week, for example in France Monday is 1, in US Sunday is 1, [1..7]
            ///
            inline int day_of_week_local(date_time const &dt) { return dt.get(day_of_week_local()); } 
            ///
            ///  Extract from date_time numerical value of 24 clock hour [0..23]
            ///
            inline int hour(date_time const &dt) { return dt.get(hour()); } 
            ///
            ///  Extract from date_time numerical value of 12 clock hour [0..11]
            ///
            inline int hour_12(date_time const &dt) { return dt.get(hour_12()); } 
            ///
            ///  Extract from date_time numerical value of am or pm marker [0..1]
            ///
            inline int am_pm(date_time const &dt) { return dt.get(am_pm()); } 
            ///
            ///  Extract from date_time numerical value of minute [0..59]
            ///
            inline int minute(date_time const &dt) { return dt.get(minute()); } 
            ///
            ///  Extract from date_time numerical value of second [0..59]
            ///
            inline int second(date_time const &dt) { return dt.get(second()); } 
            ///
            ///  Extract from date_time numerical value of The week number in the year
            ///
            inline int week_of_year(date_time const &dt) { return dt.get(week_of_year()); } 
            ///
            ///  Extract from date_time numerical value of The week number within current month
            ///
            inline int week_of_month(date_time const &dt) { return dt.get(week_of_month()); } 
            ///
            ///  Extract from date_time numerical value of First day of week, constant, for example Sunday in US = 1, Monday in France = 2
            ///
            inline int first_day_of_week(date_time const &dt) { return dt.get(first_day_of_week()); } 
            
            ///
            ///  Extract from date_time_duration numerical value of duration in  Era i.e. AC, BC in Gregorian and Julian calendar, range [0,1]
            ///
            inline int era(date_time_duration const &dt) { return dt.get(era()); } 
            ///
            ///  Extract from date_time_duration numerical value of duration in years
            ///
            inline int year(date_time_duration const &dt) { return dt.get(year()); } 
            ///
            ///  Extract from date_time_duration numerical value of duration in extended years (for Gregorian/Julian calendars, where 1 BC == 0, 2 BC == -1).
            ///
            inline int extended_year(date_time_duration const &dt) { return dt.get(extended_year()); } 
            ///
            ///  Extract from date_time_duration numerical value of duration in months
            ///
            inline int month(date_time_duration const &dt) { return dt.get(month()); } 
            ///
            ///  Extract from date_time_duration numerical value of duration in days of month
            ///
            inline int day(date_time_duration const &dt) { return dt.get(day()); } 
            ///
            ///  Extract from date_time_duration numerical value of duration in days of year
            ///
            inline int day_of_year(date_time_duration const &dt) { return dt.get(day_of_year()); } 
            ///
            ///  Extract from date_time_duration numerical value of duration in days of week
            ///
            inline int day_of_week(date_time_duration const &dt) { return dt.get(day_of_week()); } 
            ///
            ///  Extract from date_time_duration numerical value of duration in original number of the day of the week in month
            ///
            inline int day_of_week_in_month(date_time_duration const &dt) { return dt.get(day_of_week_in_month()); } 
            ///
            ///  Extract from date_time_duration numerical value of duration in local day of week
            ///
            inline int day_of_week_local(date_time_duration const &dt) { return dt.get(day_of_week_local()); } 
            ///
            ///  Extract from date_time_duration numerical value of duration in hours
            ///
            inline int hour(date_time_duration const &dt) { return dt.get(hour()); } 
            ///
            ///  Extract from date_time_duration numerical value of duration in  12 clock hours
            ///
            inline int hour_12(date_time_duration const &dt) { return dt.get(hour_12()); } 
            ///
            ///  Extract from date_time_duration numerical value of duration in  am or pm markers
            ///
            inline int am_pm(date_time_duration const &dt) { return dt.get(am_pm()); } 
            ///
            ///  Extract from date_time_duration numerical value of duration in  minutes
            ///
            inline int minute(date_time_duration const &dt) { return dt.get(minute()); } 
            ///
            ///  Extract from date_time_duration numerical value of duration in  seconds
            ///
            inline int second(date_time_duration const &dt) { return dt.get(second()); } 
            ///
            ///  Extract from date_time_duration numerical value of duration in the week number in the year
            ///
            inline int week_of_year(date_time_duration const &dt) { return dt.get(week_of_year()); } 
            ///
            ///  Extract from date_time_duration numerical value of duration in  The week number within current month
            ///
            inline int week_of_month(date_time_duration const &dt) { return dt.get(week_of_month()); } 
            ///
            ///  Extract from date_time_duration numerical value of duration in the first day of week
            ///
            inline int first_day_of_week(date_time_duration const &dt) { return dt.get(first_day_of_week()); } 


        }
        
        /// @}


    } // locale
} // boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif


#endif
///
/// \example calendar.cpp
///
/// Example of using date_time functions for generating calendar for current year.
///

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

/* date_time.hpp
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
*/