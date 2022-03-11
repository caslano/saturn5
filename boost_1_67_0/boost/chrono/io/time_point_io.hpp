//  (C) Copyright Howard Hinnant
//  (C) Copyright 2010-2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

//===-------------------------- locale ------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// This code was adapted by Vicente from Howard Hinnant's experimental work
// on chrono i/o to Boost and some functions from libc++/locale to emulate the missing time_get::get()

#ifndef BOOST_CHRONO_IO_TIME_POINT_IO_HPP
#define BOOST_CHRONO_IO_TIME_POINT_IO_HPP

#include <boost/chrono/io/time_point_put.hpp>
#include <boost/chrono/io/time_point_get.hpp>
#include <boost/chrono/io/duration_io.hpp>
#include <boost/chrono/io/ios_base_state.hpp>
#include <boost/chrono/io/utility/manip_base.hpp>
#include <boost/chrono/time_point.hpp>
#include <boost/chrono/clock_string.hpp>
#include <boost/chrono/round.hpp>
#include <boost/chrono/detail/scan_keyword.hpp>
#include <boost/static_assert.hpp>
#include <boost/detail/no_exceptions_support.hpp>
#include <cstring>
#include <locale>
#include <ctime>

#if  ( defined BOOST_WINDOWS && ! defined(__CYGWIN__) )  \
  || (defined(sun) || defined(__sun)) \
  || (defined __IBMCPP__) \
  || defined __ANDROID__ \
  || defined __QNXNTO__ \
  || (defined(_AIX) && defined __GNUC__)
#define  BOOST_CHRONO_INTERNAL_TIMEGM
#endif

#if (defined BOOST_WINDOWS && ! defined(__CYGWIN__)) \
  || ( (defined(sun) || defined(__sun)) && defined __GNUC__) \
  || (defined __IBMCPP__) \
  || defined __ANDROID__ \
  || (defined(_AIX) && defined __GNUC__)
#define  BOOST_CHRONO_INTERNAL_GMTIME
#endif

#define  BOOST_CHRONO_USES_INTERNAL_TIME_GET

namespace boost
{
  namespace chrono
  {
    typedef double fractional_seconds;
    namespace detail
    {


      template <class CharT, class InputIterator = std::istreambuf_iterator<CharT> >
      struct time_get
      {
        std::time_get<CharT> const &that_;
        time_get(std::time_get<CharT> const& that) : that_(that) {}

        typedef std::time_get<CharT> facet;
        typedef typename facet::iter_type iter_type;
        typedef typename facet::char_type char_type;
        typedef std::basic_string<char_type> string_type;

        static int
        get_up_to_n_digits(
            InputIterator& b, InputIterator e,
            std::ios_base::iostate& err,
            const std::ctype<CharT>& ct,
            int n)
        {
            // Precondition:  n >= 1
            if (b == e)
            {
                err |= std::ios_base::eofbit | std::ios_base::failbit;
                return 0;
            }
            // get first digit
            CharT c = *b;
            if (!ct.is(std::ctype_base::digit, c))
            {
                err |= std::ios_base::failbit;
                return 0;
            }
            int r = ct.narrow(c, 0) - '0';
            for (++b, --n; b != e && n > 0; ++b, --n)
            {
                // get next digit
                c = *b;
                if (!ct.is(std::ctype_base::digit, c))
                    return r;
                r = r * 10 + ct.narrow(c, 0) - '0';
            }
            if (b == e)
                err |= std::ios_base::eofbit;
            return r;
        }


        void get_day(
            int& d,
            iter_type& b, iter_type e,
            std::ios_base::iostate& err,
            const std::ctype<char_type>& ct) const
        {
            int t = get_up_to_n_digits(b, e, err, ct, 2);
            if (!(err & std::ios_base::failbit) && 1 <= t && t <= 31)
                d = t;
            else
                err |= std::ios_base::failbit;
        }

        void get_month(
            int& m,
            iter_type& b, iter_type e,
            std::ios_base::iostate& err,
            const std::ctype<char_type>& ct) const
        {
            int t = get_up_to_n_digits(b, e, err, ct, 2);
            if (!(err & std::ios_base::failbit) && 1 <= t && t <= 12)
                m = --t;
            else
                err |= std::ios_base::failbit;
        }


        void get_year4(int& y,
                                                      iter_type& b, iter_type e,
                                                      std::ios_base::iostate& err,
                                                      const std::ctype<char_type>& ct) const
        {
            int t = get_up_to_n_digits(b, e, err, ct, 4);
            if (!(err & std::ios_base::failbit))
                y = t - 1900;
        }

        void
        get_hour(int& h,
                                                     iter_type& b, iter_type e,
                                                     std::ios_base::iostate& err,
                                                     const std::ctype<char_type>& ct) const
        {
            int t = get_up_to_n_digits(b, e, err, ct, 2);
            if (!(err & std::ios_base::failbit) && t <= 23)
                h = t;
            else
                err |= std::ios_base::failbit;
        }

        void
        get_minute(int& m,
                                                       iter_type& b, iter_type e,
                                                       std::ios_base::iostate& err,
                                                       const std::ctype<char_type>& ct) const
        {
            int t = get_up_to_n_digits(b, e, err, ct, 2);
            if (!(err & std::ios_base::failbit) && t <= 59)
                m = t;
            else
                err |= std::ios_base::failbit;
        }

        void  get_second(int& s,
                                                       iter_type& b, iter_type e,
                                                       std::ios_base::iostate& err,
                                                       const std::ctype<char_type>& ct) const
        {
            int t = get_up_to_n_digits(b, e, err, ct, 2);
            if (!(err & std::ios_base::failbit) && t <= 60)
                s = t;
            else
                err |= std::ios_base::failbit;
        }

        void get_white_space(iter_type& b, iter_type e,
                                                            std::ios_base::iostate& err,
                                                            const std::ctype<char_type>& ct) const
        {
            for (; b != e && ct.is(std::ctype_base::space, *b); ++b)
                ;
            if (b == e)
                err |= std::ios_base::eofbit;
        }

        void get_12_hour(int& h,
                                                        iter_type& b, iter_type e,
                                                        std::ios_base::iostate& err,
                                                        const std::ctype<char_type>& ct) const
        {
            int t = get_up_to_n_digits(b, e, err, ct, 2);
            if (!(err & std::ios_base::failbit) && 1 <= t && t <= 12)
                h = t;
            else
                err |= std::ios_base::failbit;
        }

        void get_percent(iter_type& b, iter_type e,
                                                        std::ios_base::iostate& err,
                                                        const std::ctype<char_type>& ct) const
        {
            if (b == e)
            {
                err |= std::ios_base::eofbit | std::ios_base::failbit;
                return;
            }
            if (ct.narrow(*b, 0) != '%')
                err |= std::ios_base::failbit;
            else if(++b == e)
                err |= std::ios_base::eofbit;
        }

        void get_day_year_num(int& d,
                                                             iter_type& b, iter_type e,
                                                             std::ios_base::iostate& err,
                                                             const std::ctype<char_type>& ct) const
        {
            int t = get_up_to_n_digits(b, e, err, ct, 3);
            if (!(err & std::ios_base::failbit) && 1 <= t && t <= 366)
                d = --t;
            else
                err |= std::ios_base::failbit;
        }

        void
        get_weekday(int& w,
                                                        iter_type& b, iter_type e,
                                                        std::ios_base::iostate& err,
                                                        const std::ctype<char_type>& ct) const
        {
            int t = get_up_to_n_digits(b, e, err, ct, 1);
            if (!(err & std::ios_base::failbit) && t <= 6)
                w = t;
            else
                err |= std::ios_base::failbit;
        }
#if 0

        void
        get_am_pm(int& h,
                                                      iter_type& b, iter_type e,
                                                      std::ios_base::iostate& err,
                                                      const std::ctype<char_type>& ct) const
        {
            const string_type* ap = am_pm();
            if (ap[0].size() + ap[1].size() == 0)
            {
                err |= ios_base::failbit;
                return;
            }
            ptrdiff_t i = detail::scan_keyword(b, e, ap, ap+2, ct, err, false) - ap;
            if (i == 0 && h == 12)
                h = 0;
            else if (i == 1 && h < 12)
                h += 12;
        }

#endif

        InputIterator get(
            iter_type b, iter_type e,
            std::ios_base& iob,
            std::ios_base::iostate& err,
            std::tm* tm,
            char fmt, char) const
        {
            err = std::ios_base::goodbit;
            const std::ctype<char_type>& ct = std::use_facet<std::ctype<char_type> >(iob.getloc());

            switch (fmt)
            {
            case 'a':
            case 'A':
              {
                std::tm tm2;
                std::memset(&tm2, 0, sizeof(std::tm));
                that_.get_weekday(b, e, iob, err, &tm2);
                //tm->tm_wday = tm2.tm_wday;
              }
              break;
            case 'b':
            case 'B':
            case 'h':
              {
                std::tm tm2;
                std::memset(&tm2, 0, sizeof(std::tm));
                that_.get_monthname(b, e, iob, err, &tm2);
                //tm->tm_mon = tm2.tm_mon;
              }
              break;
//            case 'c':
//              {
//                const string_type& fm = c();
//                b = get(b, e, iob, err, tm, fm.data(), fm.data() + fm.size());
//              }
//              break;
            case 'd':
            case 'e':
              get_day(tm->tm_mday, b, e, err, ct);
              break;
            case 'D':
              {
                const char_type fm[] = {'%', 'm', '/', '%', 'd', '/', '%', 'y'};
                b = get(b, e, iob, err, tm, fm, fm + sizeof(fm)/sizeof(fm[0]));
              }
              break;
            case 'F':
              {
                const char_type fm[] = {'%', 'Y', '-', '%', 'm', '-', '%', 'd'};
                b = get(b, e, iob, err, tm, fm, fm + sizeof(fm)/sizeof(fm[0]));
              }
              break;
            case 'H':
              get_hour(tm->tm_hour, b, e, err, ct);
              break;
            case 'I':
              get_12_hour(tm->tm_hour, b, e, err, ct);
              break;
            case 'j':
              get_day_year_num(tm->tm_yday, b, e, err, ct);
              break;
            case 'm':
              get_month(tm->tm_mon, b, e, err, ct);
              break;
            case 'M':
              get_minute(tm->tm_min, b, e, err, ct);
              break;
            case 'n':
            case 't':
              get_white_space(b, e, err, ct);
              break;
//            case 'p':
//              get_am_pm(tm->tm_hour, b, e, err, ct);
//              break;
            case 'r':
              {
                const char_type fm[] = {'%', 'I', ':', '%', 'M', ':', '%', 'S', ' ', '%', 'p'};
                b = get(b, e, iob, err, tm, fm, fm + sizeof(fm)/sizeof(fm[0]));
              }
              break;
            case 'R':
              {
                const char_type fm[] = {'%', 'H', ':', '%', 'M'};
                b = get(b, e, iob, err, tm, fm, fm + sizeof(fm)/sizeof(fm[0]));
              }
              break;
            case 'S':
              get_second(tm->tm_sec, b, e, err, ct);
              break;
            case 'T':
              {
                const char_type fm[] = {'%', 'H', ':', '%', 'M', ':', '%', 'S'};
                b = get(b, e, iob, err, tm, fm, fm + sizeof(fm)/sizeof(fm[0]));
              }
              break;
            case 'w':
              {
                get_weekday(tm->tm_wday, b, e, err, ct);
              }
              break;
            case 'x':
              return that_.get_date(b, e, iob, err, tm);
//            case 'X':
//              return that_.get_time(b, e, iob, err, tm);
//              {
//                const string_type& fm = X();
//                b = that_.get(b, e, iob, err, tm, fm.data(), fm.data() + fm.size());
//              }
//              break;
//            case 'y':
//              get_year(tm->tm_year, b, e, err, ct);
                break;
            case 'Y':
              get_year4(tm->tm_year, b, e, err, ct);
              break;
            case '%':
              get_percent(b, e, err, ct);
              break;
            default:
                err |= std::ios_base::failbit;
            }
            return b;
        }


        InputIterator get(
          iter_type b, iter_type e,
          std::ios_base& iob,
          std::ios_base::iostate& err, std::tm* tm,
          const char_type* fmtb, const char_type* fmte) const
        {
          const std::ctype<char_type>& ct = std::use_facet<std::ctype<char_type> >(iob.getloc());
          err = std::ios_base::goodbit;
          while (fmtb != fmte && err == std::ios_base::goodbit)
          {
              if (b == e)
              {
                  err = std::ios_base::failbit;
                  break;
              }
              if (ct.narrow(*fmtb, 0) == '%')
              {
                  if (++fmtb == fmte)
                  {
                      err = std::ios_base::failbit;
                      break;
                  }
                  char cmd = ct.narrow(*fmtb, 0);
                  char opt = '\0';
                  if (cmd == 'E' || cmd == '0')
                  {
                      if (++fmtb == fmte)
                      {
                          err = std::ios_base::failbit;
                          break;
                      }
                      opt = cmd;
                      cmd = ct.narrow(*fmtb, 0);
                  }
                  b = get(b, e, iob, err, tm, cmd, opt);
                  ++fmtb;
              }
              else if (ct.is(std::ctype_base::space, *fmtb))
              {
                  for (++fmtb; fmtb != fmte && ct.is(std::ctype_base::space, *fmtb); ++fmtb)
                      ;
                  for (        ;    b != e    && ct.is(std::ctype_base::space, *b);    ++b)
                      ;
              }
              else if (ct.toupper(*b) == ct.toupper(*fmtb))
              {
                  ++b;
                  ++fmtb;
              }
              else
                  err = std::ios_base::failbit;
          }
          if (b == e)
              err |= std::ios_base::eofbit;
          return b;
        }

      };


      template <class CharT>
      class time_manip: public manip<time_manip<CharT> >
      {
        std::basic_string<CharT> fmt_;
        timezone tz_;
      public:

        time_manip(timezone tz, std::basic_string<CharT> fmt)
        // todo move semantics
        :
          fmt_(fmt), tz_(tz)
        {
        }

        /**
         * Change the timezone and time format ios state;
         */
        void operator()(std::ios_base &ios) const
        {
          set_time_fmt<CharT> (ios, fmt_);
          set_timezone(ios, tz_);
        }
      };

      class time_man: public manip<time_man>
      {
        timezone tz_;
      public:

        time_man(timezone tz)
        // todo move semantics
        :
          tz_(tz)
        {
        }

        /**
         * Change the timezone and time format ios state;
         */
        void operator()(std::ios_base &ios) const
        {
          //set_time_fmt<typename out_stream::char_type>(ios, "");
          set_timezone(ios, tz_);
        }
      };

    }

    template <class CharT>
    inline detail::time_manip<CharT> time_fmt(timezone tz, const CharT* fmt)
    {
      return detail::time_manip<CharT>(tz, fmt);
    }

    template <class CharT>
    inline detail::time_manip<CharT> time_fmt(timezone tz, std::basic_string<CharT> fmt)
    {
      // todo move semantics
      return detail::time_manip<CharT>(tz, fmt);
    }

    inline detail::time_man time_fmt(timezone f)
    {
      return detail::time_man(f);
    }

    /**
     * time_fmt_io_saver i/o saver.
     *
     * See Boost.IO i/o state savers for a motivating compression.
     */
    template <typename CharT = char, typename Traits = std::char_traits<CharT> >
    struct time_fmt_io_saver
    {

      //! the type of the state to restore
      //typedef std::basic_ostream<CharT, Traits> state_type;
      typedef std::ios_base state_type;

      //! the type of aspect to save
      typedef std::basic_string<CharT, Traits> aspect_type;

      /**
       * Explicit construction from an i/o stream.
       *
       * Store a reference to the i/o stream and the value of the associated @c time format .
       */
      explicit time_fmt_io_saver(state_type &s) :
        s_save_(s), a_save_(get_time_fmt<CharT>(s_save_))
      {
      }

      /**
       * Construction from an i/o stream and a @c time format  to restore.
       *
       * Stores a reference to the i/o stream and the value @c new_value to restore given as parameter.
       */
      time_fmt_io_saver(state_type &s, aspect_type new_value) :
        s_save_(s), a_save_(get_time_fmt<CharT>(s_save_))
      {
        set_time_fmt(s_save_, new_value);
      }

      /**
       * Destructor.
       *
       * Restores the i/o stream with the format to be restored.
       */
      ~time_fmt_io_saver()
      {
        this->restore();
      }

      /**
       * Restores the i/o stream with the time format to be restored.
       */
      void restore()
      {
        set_time_fmt(s_save_, a_save_);
      }
    private:
      state_type& s_save_;
      aspect_type a_save_;
    };

    /**
     * timezone_io_saver i/o saver.
     *
     * See Boost.IO i/o state savers for a motivating compression.
     */
    struct timezone_io_saver
    {

      //! the type of the state to restore
      typedef std::ios_base state_type;
      //! the type of aspect to save
      typedef timezone aspect_type;

      /**
       * Explicit construction from an i/o stream.
       *
       * Store a reference to the i/o stream and the value of the associated @c timezone.
       */
      explicit timezone_io_saver(state_type &s) :
        s_save_(s), a_save_(get_timezone(s_save_))
      {
      }

      /**
       * Construction from an i/o stream and a @c timezone to restore.
       *
       * Stores a reference to the i/o stream and the value @c new_value to restore given as parameter.
       */
      timezone_io_saver(state_type &s, aspect_type new_value) :
        s_save_(s), a_save_(get_timezone(s_save_))
      {
        set_timezone(s_save_, new_value);
      }

      /**
       * Destructor.
       *
       * Restores the i/o stream with the format to be restored.
       */
      ~timezone_io_saver()
      {
        this->restore();
      }

      /**
       * Restores the i/o stream with the timezone to be restored.
       */
      void restore()
      {
        set_timezone(s_save_, a_save_);
      }
    private:
      timezone_io_saver& operator=(timezone_io_saver const& rhs) ;

      state_type& s_save_;
      aspect_type a_save_;
    };

    /**
     *
     * @param os
     * @param tp
     * @Effects Behaves as a formatted output function. After constructing a @c sentry object, if the @ sentry
     * converts to true, calls to @c facet.put(os,os,os.fill(),tp) where @c facet is the @c time_point_put<CharT>
     * facet associated to @c os or a new created instance of the default @c time_point_put<CharT> facet.
     * @return @c os.
     */
    template <class CharT, class Traits, class Clock, class Duration>
    std::basic_ostream<CharT, Traits>&
    operator<<(std::basic_ostream<CharT, Traits>& os, const time_point<Clock, Duration>& tp)
    {

      bool failed = false;
      BOOST_TRY
      {
        std::ios_base::iostate err = std::ios_base::goodbit;
        BOOST_TRY
        {
          typename std::basic_ostream<CharT, Traits>::sentry opfx(os);
          if (bool(opfx))
          {
            if (!std::has_facet<time_point_put<CharT> >(os.getloc()))
            {
              if (time_point_put<CharT> ().put(os, os, os.fill(), tp) .failed())
              {
                err = std::ios_base::badbit;
              }
            }
            else
            {
              if (std::use_facet<time_point_put<CharT> >(os.getloc()) .put(os, os, os.fill(), tp).failed())
              {
                err = std::ios_base::badbit;
              }
            }
            os.width(0);
          }
        }
        BOOST_CATCH (...)
        {
          bool flag = false;
          BOOST_TRY
          {
            os.setstate(std::ios_base::failbit);
          }
          BOOST_CATCH (std::ios_base::failure )
          {
            flag = true;
          }
          BOOST_CATCH_END
          if (flag) throw;
        }
        BOOST_CATCH_END
        if (err) os.setstate(err);
        return os;
      }
      BOOST_CATCH (...)
      {
        failed = true;
      }
      BOOST_CATCH_END
      if (failed) os.setstate(std::ios_base::failbit | std::ios_base::badbit);
      return os;
    }

    template <class CharT, class Traits, class Clock, class Duration>
    std::basic_istream<CharT, Traits>&
    operator>>(std::basic_istream<CharT, Traits>& is, time_point<Clock, Duration>& tp)
    {
      std::ios_base::iostate err = std::ios_base::goodbit;

      BOOST_TRY
      {
        typename std::basic_istream<CharT, Traits>::sentry ipfx(is);
        if (bool(ipfx))
        {
          if (!std::has_facet<time_point_get<CharT> >(is.getloc()))
          {
            time_point_get<CharT> ().get(is, std::istreambuf_iterator<CharT, Traits>(), is, err, tp);
          }
          else
          {
            std::use_facet<time_point_get<CharT> >(is.getloc()).get(is, std::istreambuf_iterator<CharT, Traits>(), is,
                err, tp);
          }
        }
      }
      BOOST_CATCH (...)
      {
        bool flag = false;
        BOOST_TRY
        {
          is.setstate(std::ios_base::failbit);
        }
        BOOST_CATCH (std::ios_base::failure )
        {
          flag = true;
        }
        BOOST_CATCH_END
        if (flag) throw;
      }
      BOOST_CATCH_END
      if (err) is.setstate(err);
      return is;
    }


    namespace detail
    {

//#if defined BOOST_CHRONO_INTERNAL_TIMEGM

    inline int32_t is_leap(int32_t year)
    {
      if(year % 400 == 0)
      return 1;
      if(year % 100 == 0)
      return 0;
      if(year % 4 == 0)
      return 1;
      return 0;
    }
    inline int32_t days_from_0(int32_t year)
    {
      year--;
      return 365 * year + (year / 400) - (year/100) + (year / 4);
    }
    inline int32_t days_from_1970(int32_t year)
    {
      static const int32_t days_from_0_to_1970 = days_from_0(1970);
      return days_from_0(year) - days_from_0_to_1970;
    }
    inline int32_t days_from_1jan(int32_t year,int32_t month,int32_t day)
    {
      static const int32_t days[2][12] =
      {
        { 0,31,59,90,120,151,181,212,243,273,304,334},
        { 0,31,60,91,121,152,182,213,244,274,305,335}
      };

      return days[is_leap(year)][month-1] + day - 1;
    }

    inline time_t internal_timegm(std::tm const *t)
    {
      int year = t->tm_year + 1900;
      int month = t->tm_mon;
      if(month > 11)
      {
        year += month/12;
        month %= 12;
      }
      else if(month < 0)
      {
        int years_diff = (-month + 11)/12;
        year -= years_diff;
        month+=12 * years_diff;
      }
      month++;
      int day = t->tm_mday;
      int day_of_year = days_from_1jan(year,month,day);
      int days_since_epoch = days_from_1970(year) + day_of_year ;

      time_t seconds_in_day = 3600 * 24;
      time_t result = seconds_in_day * days_since_epoch + 3600 * t->tm_hour + 60 * t->tm_min + t->tm_sec;

      return result;
    }
//#endif

    /**
    * from_ymd could be made more efficient by using a table
    * day_count_table indexed by the y%400.
    * This table could contain the day_count
    * by*365 + by/4 - by/100 + by/400
    *
    * from_ymd = (by/400)*days_by_400_years+day_count_table[by%400] +
    * days_in_year_before[is_leap_table[by%400]][m-1] + d;
    */
    inline unsigned days_before_years(int32_t y)
   {
     return y * 365 + y / 4 - y / 100 + y / 400;
   }

    // Returns year/month/day triple in civil calendar
    // Preconditions:  z is number of days since 1970-01-01 and is in the range:
    //                   [numeric_limits<Int>::min(), numeric_limits<Int>::max()-719468].
    template <class Int>
    //constexpr
    void
    inline civil_from_days(Int z, Int& y, unsigned& m, unsigned& d) BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT_MSG(std::numeric_limits<unsigned>::digits >= 18,
                 "This algorithm has not been ported to a 16 bit unsigned integer");
        BOOST_STATIC_ASSERT_MSG(std::numeric_limits<Int>::digits >= 20,
                 "This algorithm has not been ported to a 16 bit signed integer");
        z += 719468;
        const Int era = (z >= 0 ? z : z - 146096) / 146097;
        const unsigned doe = static_cast<unsigned>(z - era * 146097);          // [0, 146096]
        const unsigned yoe = (doe - doe/1460 + doe/36524 - doe/146096) / 365;  // [0, 399]
        y = static_cast<Int>(yoe) + era * 400;
        const unsigned doy = doe - (365*yoe + yoe/4 - yoe/100);                // [0, 365]
        const unsigned mp = (5*doy + 2)/153;                                   // [0, 11]
        d = doy - (153*mp+2)/5 + 1;                             // [1, 31]
        m = mp + (mp < 10 ? 3 : -9);                            // [1, 12]
        y += (m <= 2);
        --m;
    }
   inline std::tm * internal_gmtime(std::time_t const* t, std::tm *tm)
   {
      if (t==0) return 0;
      if (tm==0) return 0;

#if 0
      static  const unsigned char
        day_of_year_month[2][366] =
           {
           { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12 },

           { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12

           } };

      static const int32_t days_in_year_before[2][13] =
     {
       { -1, 30, 58, 89, 119, 150, 180, 211, 242, 272, 303, 333, 364 },
       { -1, 30, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 }
     };
#endif

     const time_t seconds_in_day = 3600 * 24;
     int32_t days_since_epoch = static_cast<int32_t>(*t / seconds_in_day);
     int32_t hms = static_cast<int32_t>(*t - seconds_in_day*days_since_epoch);
     if (hms < 0) {
       days_since_epoch-=1;
       hms = seconds_in_day+hms;
     }

#if 0
     int32_t x = days_since_epoch;
     int32_t y = static_cast<int32_t> (static_cast<long long> (x + 2) * 400
           / 146097);
       const int32_t ym1 = y - 1;
       int32_t doy = x - days_before_years(y);
       const int32_t doy1 = x - days_before_years(ym1);
       const int32_t N = std::numeric_limits<int>::digits - 1;
       const int32_t mask1 = doy >> N; // arithmetic rshift - not portable - but nearly universal
       const int32_t mask0 = ~mask1;
       doy = (doy & mask0) | (doy1 & mask1);
       y = (y & mask0) | (ym1 & mask1);
       //y -= 32767 + 2;
       y += 70;
       tm->tm_year=y;
       const int32_t leap = is_leap(y);
       tm->tm_mon = day_of_year_month[leap][doy]-1;
       tm->tm_mday = doy - days_in_year_before[leap][tm->tm_mon] ;
#else
       int32_t y;
       unsigned m, d;
       civil_from_days(days_since_epoch, y, m, d);
       tm->tm_year=y-1900; tm->tm_mon=m; tm->tm_mday=d;
#endif

     tm->tm_hour = hms / 3600;
     const int ms = hms % 3600;
     tm->tm_min = ms / 60;
     tm->tm_sec = ms % 60;

     tm->tm_isdst = -1;
     (void)mktime(tm);
     return tm;
   }

    } // detail
#ifndef BOOST_CHRONO_NO_UTC_TIMEPOINT

#if defined BOOST_CHRONO_PROVIDES_DATE_IO_FOR_SYSTEM_CLOCK_TIME_POINT

    template <class CharT, class Traits, class Duration>
    std::basic_ostream<CharT, Traits>&
    operator<<(std::basic_ostream<CharT, Traits>& os, const time_point<system_clock, Duration>& tp)
    {
      typename std::basic_ostream<CharT, Traits>::sentry ok(os);
      if (bool(ok))
      {
        bool failed = false;
        BOOST_TRY
        {
          const CharT* pb = 0; //nullptr;
          const CharT* pe = pb;
          std::basic_string<CharT> fmt = get_time_fmt<CharT> (os);
          pb = fmt.data();
          pe = pb + fmt.size();

          timezone tz = get_timezone(os);
          std::locale loc = os.getloc();
          time_t t = system_clock::to_time_t(time_point_cast<system_clock::duration>(tp));
          std::tm tm;
          std::memset(&tm, 0, sizeof(std::tm));
          if (tz == timezone::local)
          {
#if defined BOOST_WINDOWS && ! defined(__CYGWIN__)
#if BOOST_MSVC < 1400  // localtime_s doesn't exist in vc7.1
            std::tm *tmp = 0;
            if ((tmp=localtime(&t)) == 0)
              failed = true;
            else
              tm =*tmp;
# else
            if (localtime_s(&tm, &t) != 0) failed = true;
# endif
#else
            if (localtime_r(&t, &tm) == 0) failed = true;
#endif
          }
          else
          {
#if defined BOOST_CHRONO_INTERNAL_GMTIME
            if (detail::internal_gmtime(&t, &tm) == 0) failed = true;

#elif defined BOOST_WINDOWS && ! defined(__CYGWIN__)
            std::tm *tmp = 0;
            if((tmp = gmtime(&t)) == 0)
              failed = true;
            else
              tm = *tmp;
#else
            if (gmtime_r(&t, &tm) == 0) failed = true;
            tm.tm_isdst = -1;
            (void)mktime(&tm);

#endif

          }
          if (!failed)
          {
            const std::time_put<CharT>& tpf = std::use_facet<std::time_put<CharT> >(loc);
            if (pb == pe)
            {
              CharT pattern[] =
              { '%', 'Y', '-', '%', 'm', '-', '%', 'd', ' ', '%', 'H', ':', '%', 'M', ':' };
              pb = pattern;
              pe = pb + sizeof (pattern) / sizeof(CharT);
              failed = tpf.put(os, os, os.fill(), &tm, pb, pe).failed();
              if (!failed)
              {
                duration<fractional_seconds> d = tp - system_clock::from_time_t(t) + seconds(tm.tm_sec);
                if (d.count() < 10) os << CharT('0');
                //if (! os.good()) {
                //  throw "exception";
                //}
                std::ios::fmtflags flgs = os.flags();
                os.setf(std::ios::fixed, std::ios::floatfield);
                //if (! os.good()) {
                //throw "exception";
                //}
                os.precision(9);
                os << d.count();
                //if (! os.good()) {
                //throw "exception";
                //}
                os.flags(flgs);
                if (tz == timezone::local)
                {
                  CharT sub_pattern[] =
                  { ' ', '%', 'z' };
                  pb = sub_pattern;
                  pe = pb + +sizeof (sub_pattern) / sizeof(CharT);
                  failed = tpf.put(os, os, os.fill(), &tm, pb, pe).failed();
                }
                else
                {
                  CharT sub_pattern[] =
                  { ' ', '+', '0', '0', '0', '0', 0 };
                  os << sub_pattern;
                }
              }
            }
            else
            {
              failed = tpf.put(os, os, os.fill(), &tm, pb, pe).failed();
            }
          }
        }
        BOOST_CATCH (...)
        {
          failed = true;
        }
        BOOST_CATCH_END
        if (failed)
        {
          os.setstate(std::ios_base::failbit | std::ios_base::badbit);
        }
      }
      return os;
    }
#endif

    namespace detail
    {

      template <class CharT, class InputIterator>
      minutes extract_z(InputIterator& b, InputIterator e, std::ios_base::iostate& err, const std::ctype<CharT>& ct)
      {
        int min = 0;
        if (b != e)
        {
          char cn = ct.narrow(*b, 0);
          if (cn != '+' && cn != '-')
          {
            err |= std::ios_base::failbit;
            return minutes(0);
          }
          int sn = cn == '-' ? -1 : 1;
          int hr = 0;
          for (int i = 0; i < 2; ++i)
          {
            if (++b == e)
            {
              err |= std::ios_base::eofbit | std::ios_base::failbit;
              return minutes(0);
            }
            cn = ct.narrow(*b, 0);
            if (! ('0' <= cn && cn <= '9'))
            {
              err |= std::ios_base::failbit;
              return minutes(0);
            }
            hr = hr * 10 + cn - '0';
          }
          for (int i = 0; i < 2; ++i)
          {
            if (++b == e)
            {
              err |= std::ios_base::eofbit | std::ios_base::failbit;
              return minutes(0);
            }
            cn = ct.narrow(*b, 0);
            if (! ('0' <= cn && cn <= '9'))
            {
              err |= std::ios_base::failbit;
              return minutes(0);
            }
            min = min * 10 + cn - '0';
          }
          if (++b == e) {
            err |= std::ios_base::eofbit;
          }
          min += hr * 60;
          min *= sn;
        }
        else
        {
          err |= std::ios_base::eofbit | std::ios_base::failbit;
        }
        return minutes(min);
      }

    } // detail

#if defined BOOST_CHRONO_PROVIDES_DATE_IO_FOR_SYSTEM_CLOCK_TIME_POINT

    template <class CharT, class Traits, class Duration>
    std::basic_istream<CharT, Traits>&
    operator>>(std::basic_istream<CharT, Traits>& is, time_point<system_clock, Duration>& tp)
    {
      typename std::basic_istream<CharT, Traits>::sentry ok(is);
      if (bool(ok))
      {
        std::ios_base::iostate err = std::ios_base::goodbit;
        BOOST_TRY
        {
          const CharT* pb = 0; //nullptr;
          const CharT* pe = pb;
          std::basic_string<CharT> fmt = get_time_fmt<CharT> (is);
          pb = fmt.data();
          pe = pb + fmt.size();

          timezone tz = get_timezone(is);
          std::locale loc = is.getloc();
          const std::time_get<CharT>& tg = std::use_facet<std::time_get<CharT> >(loc);
          const std::ctype<CharT>& ct = std::use_facet<std::ctype<CharT> >(loc);
          tm tm; // {0}
          std::memset(&tm, 0, sizeof(std::tm));

          typedef std::istreambuf_iterator<CharT, Traits> It;
          if (pb == pe)
          {
            CharT pattern[] =
            { '%', 'Y', '-', '%', 'm', '-', '%', 'd', ' ', '%', 'H', ':', '%', 'M', ':' };
            pb = pattern;
            pe = pb + sizeof (pattern) / sizeof(CharT);

#if defined BOOST_CHRONO_USES_INTERNAL_TIME_GET
            const detail::time_get<CharT>& dtg(tg);
            dtg.get(is, 0, is, err, &tm, pb, pe);
#else
            tg.get(is, 0, is, err, &tm, pb, pe);
#endif
            if (err & std::ios_base::failbit) goto exit;
            fractional_seconds sec;
            CharT c = CharT();
            std::ios::fmtflags flgs = is.flags();
            is.setf(std::ios::fixed, std::ios::floatfield);
            is.precision(9);
            is >> sec;
            is.flags(flgs);
            if (is.fail())
            {
              err |= std::ios_base::failbit;
              goto exit;
            }
            It i(is);
            It eof;
            c = *i;
            if (++i == eof || c != ' ')
            {
              err |= std::ios_base::failbit;
              goto exit;
            }
            minutes min = detail::extract_z(i, eof, err, ct);

            if (err & std::ios_base::failbit) goto exit;
            time_t t;

#if defined BOOST_CHRONO_INTERNAL_TIMEGM
            t = detail::internal_timegm(&tm);
#else
            t = timegm(&tm);
#endif
            tp = time_point_cast<Duration>(
                system_clock::from_time_t(t) - min + round<system_clock::duration> (duration<fractional_seconds> (sec))
                );
          }
          else
          {
            const CharT z[2] =
            { '%', 'z' };
            const CharT* fz = std::search(pb, pe, z, z + 2);
#if defined BOOST_CHRONO_USES_INTERNAL_TIME_GET
            const detail::time_get<CharT>& dtg(tg);
            dtg.get(is, 0, is, err, &tm, pb, fz);
#else
            tg.get(is, 0, is, err, &tm, pb, fz);
#endif
            minutes minu(0);
            if (fz != pe)
            {
              if (err != std::ios_base::goodbit)
              {
                err |= std::ios_base::failbit;
                goto exit;
              }
              It i(is);
              It eof;
              minu = detail::extract_z(i, eof, err, ct);
              if (err & std::ios_base::failbit) goto exit;
              if (fz + 2 != pe)
              {
                if (err != std::ios_base::goodbit)
                {
                  err |= std::ios_base::failbit;
                  goto exit;
                }
#if defined BOOST_CHRONO_USES_INTERNAL_TIME_GET
                const detail::time_get<CharT>& dtg(tg);
                dtg.get(is, 0, is, err, &tm, fz + 2, pe);
#else
                tg.get(is, 0, is, err, &tm, fz + 2, pe);
#endif
                if (err & std::ios_base::failbit) goto exit;
              }
            }
            tm.tm_isdst = -1;
            time_t t;
            if (tz == timezone::utc || fz != pe)
            {
#if defined BOOST_CHRONO_INTERNAL_TIMEGM
              t = detail::internal_timegm(&tm);
#else
              t = timegm(&tm);
#endif
            }
            else
            {
              t = mktime(&tm);
            }
            tp = time_point_cast<Duration>(
                system_clock::from_time_t(t) - minu
                );
          }
        }
        BOOST_CATCH (...)
        {
          err |= std::ios_base::badbit | std::ios_base::failbit;
        }
        BOOST_CATCH_END
        exit: is.setstate(err);
      }
      return is;
    }

#endif
#endif //UTC
  } // chrono

}

#endif  // header

/* time_point_io.hpp
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
*/