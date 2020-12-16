#ifndef POSIXTIME_FORMATTERS_LIMITED_HPP___
#define POSIXTIME_FORMATTERS_LIMITED_HPP___

/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/compiler_config.hpp>
#include <boost/date_time/iso_format.hpp>
#include <boost/date_time/date_format_simple.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/date_time/time_formatting_streams.hpp>
#include <boost/date_time/time_resolution_traits.hpp> // absolute_value

namespace boost {

namespace posix_time {

  //! Time duration to string -hh::mm::ss.fffffff. Example: 10:09:03.0123456
  /*!\ingroup time_format
   */
  inline std::string to_simple_string(time_duration td) {
    std::ostringstream ss;
    if(td.is_special()) {
      /* simply using 'ss << td.get_rep()' won't work on compilers
       * that don't support locales. This way does. */
      // switch copied from date_names_put.hpp
      switch(td.get_rep().as_special())
      {
      case not_a_date_time:
        //ss << "not-a-number";
        ss << "not-a-date-time";
        break;
      case pos_infin:
        ss << "+infinity";
        break;
      case neg_infin:
        ss << "-infinity";
        break;
      default:
        ss << "";
      }
    }
    else {
      if(td.is_negative()) {
        ss << '-';
      }
      ss  << std::setw(2) << std::setfill('0')
          << date_time::absolute_value(td.hours()) << ":";
      ss  << std::setw(2) << std::setfill('0')
          << date_time::absolute_value(td.minutes()) << ":";
      ss  << std::setw(2) << std::setfill('0')
          << date_time::absolute_value(td.seconds());
      //TODO the following is totally non-generic, yelling FIXME
#if (defined(BOOST_MSVC) && (_MSC_VER < 1300))
      boost::int64_t frac_sec =
        date_time::absolute_value(td.fractional_seconds());
      // JDG [7/6/02 VC++ compatibility]
      char buff[32];
      _i64toa(frac_sec, buff, 10);
#else
      time_duration::fractional_seconds_type frac_sec =
        date_time::absolute_value(td.fractional_seconds());
#endif
      if (frac_sec != 0) {
        ss  << "." << std::setw(time_duration::num_fractional_digits())
            << std::setfill('0')

          // JDG [7/6/02 VC++ compatibility]
#if (defined(BOOST_MSVC) && (_MSC_VER < 1300))
            << buff;
#else
        << frac_sec;
#endif
      }
    }// else
    return ss.str();
  }

  //! Time duration in iso format -hhmmss,fffffff Example: 10:09:03,0123456
  /*!\ingroup time_format
   */
  inline
  std::string
  to_iso_string(time_duration td)
  {
    std::ostringstream ss;
    if(td.is_special()) {
      /* simply using 'ss << td.get_rep()' won't work on compilers
       * that don't support locales. This way does. */
      // switch copied from date_names_put.hpp
      switch(td.get_rep().as_special()) {
      case not_a_date_time:
        //ss << "not-a-number";
        ss << "not-a-date-time";
        break;
      case pos_infin:
        ss << "+infinity";
        break;
      case neg_infin:
        ss << "-infinity";
        break;
      default:
        ss << "";
      }
    }
    else {
      if(td.is_negative()) {
        ss << '-';
      }
      ss  << std::setw(2) << std::setfill('0')
          << date_time::absolute_value(td.hours());
      ss  << std::setw(2) << std::setfill('0')
          << date_time::absolute_value(td.minutes());
      ss  << std::setw(2) << std::setfill('0')
          << date_time::absolute_value(td.seconds());
      //TODO the following is totally non-generic, yelling FIXME
#if (defined(BOOST_MSVC) && (_MSC_VER < 1300))
      boost::int64_t frac_sec =
        date_time::absolute_value(td.fractional_seconds());
      // JDG [7/6/02 VC++ compatibility]
      char buff[32];
      _i64toa(frac_sec, buff, 10);
#else
      time_duration::fractional_seconds_type frac_sec =
        date_time::absolute_value(td.fractional_seconds());
#endif
      if (frac_sec != 0) {
        ss  << "." << std::setw(time_duration::num_fractional_digits())
            << std::setfill('0')

          // JDG [7/6/02 VC++ compatibility]
#if (defined(BOOST_MSVC) && (_MSC_VER < 1300))
            << buff;
#else
        << frac_sec;
#endif
      }
    }// else
    return ss.str();
  }

  //! Time to simple format CCYY-mmm-dd hh:mm:ss.fffffff
  /*!\ingroup time_format
   */
  inline
  std::string
  to_simple_string(ptime t)
  {
    std::string ts = gregorian::to_simple_string(t.date());// + " ";
    if(!t.time_of_day().is_special()) {
      return ts + " " + to_simple_string(t.time_of_day());
    }
    else {
      return ts;
    }
  }

  //! Convert to string of form [YYYY-mmm-DD HH:MM::SS.ffffff/YYYY-mmm-DD HH:MM::SS.fffffff]
  /*!\ingroup time_format
   */
  inline
  std::string
  to_simple_string(time_period tp)
  {
    std::string d1(to_simple_string(tp.begin()));
    std::string d2(to_simple_string(tp.last()));
    return std::string("[" + d1 + "/" + d2 +"]");
  }

  //! Convert iso short form YYYYMMDDTHHMMSS where T is the date-time separator
  /*!\ingroup time_format
   */
  inline
  std::string to_iso_string(ptime t)
  {
    std::string ts = gregorian::to_iso_string(t.date());// + "T";
    if(!t.time_of_day().is_special()) {
      return ts + "T" + to_iso_string(t.time_of_day());
    }
    else {
      return ts;
    }
  }

  //! Convert to form YYYY-MM-DDTHH:MM:SS where T is the date-time separator
  /*!\ingroup time_format
   */
  inline
  std::string
  to_iso_extended_string(ptime t)
  {
    std::string ts = gregorian::to_iso_extended_string(t.date());// + "T";
    if(!t.time_of_day().is_special()) {
      return ts + "T" + to_simple_string(t.time_of_day());
    }
    else {
      return ts;
    }
  }


} } //namespace posix_time


#endif


/* time_formatters_limited.hpp
EXQIk82L0YDrqf5faXA9tsElPWCGeixuw6qMfwf6gDZQ/a96uOGc9be3UtYn5KXWGIojLx+IsdpxL1+Pi0RKSBBPRJoE6Q+wbs6hZ4+OR0LCJ+EV7VauGXizWTsnKJbi2CXNG/Gxeqx/X6t6jjmquYASt6hE7qlFV+HKueTUZSQn9+e0ntajty/O6121ek2rP4+ApOGX6+baFfJRXjiZDBxwwfQO3vtoSLz6EeLWV+X19sibcM0NX0YKuzCJkeuFTokaHsWpAaDbr6HMbxCTtXiaRxJHQv7P51H+bcCwI6F6i6y+jrj1GnYmSmVVidoQitrFIGrB+TEwj0Wtrj9AyUjtZWX9cho+ea8ZBaiaBKrJjKoodVvqTvRvyn48UIMMX60UkvqTyO1OQ/3Rq3moK9Gpmvt5tYEGFy2vK+ALvFOn1bRf6EVleO44vFB2lfqT+JmStlCE+78p8clWBQuf3h+x88Z0L5eaS3mhKJsYw9FBmTsatu50Z4cShXNpLF9BqvJVHmy7wbl2w2I8MHdeQWV/CGUN3/11ES4HvhTuAIa0lt5wC5X9ggeRPjAKkBKg+2uwxum66ANKAKvGDhhargr6N5hSTTU0uMtac5tVdeBk6dlVnFSBnHQeemIViO/6rZy09yY7Jw0nTlILihKkqYdhPNIdu/N85JfKk8wv9p+T6j2/SfKPnP6seb/2Qequ9/FRfMfOOpc76/Yc7izabd6kO6sKr1KFzirFJ+81vtS21De5p7B/+uqvsrSnBdpzzZX6S/iosa3s6M7zAMP7NE3qjpNONACMHzy8cS9qfpH1DjsUxbvUw2ZFl+6VmnavNvs3S1nw25XQPaieXa6Q9tpHC7mPrvZxHxk4jRulZtaNAEsVQKxCS62qo4blA1tKa1J3FT+mCLupo3jTjSqdW9F8moH3NSXCejQ3kqohVRdbBP0WK97VpW8oPXiIdD6CcAVAAI2L6nd3IQjtEQGtZ1WBOEPM0sbQdbfspQqABU6tXvtnFffPO7y6f6IzVZVVS2Uf6PQchQ33RJRQm4CFiy5UDpaj/4i27gN1s5K/POxD1jM0V63OTU4Dj8i7utV/18JcbemVpPf0jvs+jw33xmPea3pD/vXXFN5nFQWpT9DWDfXQL2chH/mnd6QqTGKeYq6ZesDiyiBQdZEH1Txp6cM8ebP+nPSXRmj2wx+y6C+gB+ANuy1G5Xxhk9A/H5rB4phTPkcpYZOydYbd8DlEtsoNxqq5YwGtLd+zKUItekH55+WUfzd/klYqQlGj7kSUIlSymspeSwZGBFUkDaiNNaqlAIgmL+tCusj3z6MiM/CL51EWOyhSX4xS5igH4FeiH5K8gCa9KbF4GaX/me0RnX4pY/qRSupNsypugynN2tWDr41kEYZg7qUZHuMCHxMFgK6PUoF6GIFYdzwAf+thPbgYUzyU4mmeRe5duh0Rwd8Rp1VoClpror3rOWdwcg5M6nnqP9bYzPCPCRuNrfF/ZuY4xheEcf+r0TjMmoyMabSyYr0I1/qOFi4F6DlIfs4w0oG3oMIEa80W3tnVOcFVRhxdDQo+zr8G/XHJpQ7YIgLbL87RSyJiS03XiZdrVLSnNUaguvtqgyovdRvm91ERcPnZe+29K0yvRZF6eKoofsyz8djU5oH4Qh8fqQAqOJQdivi9G4+Fmhdxslck18eHOyW3NGvwuAywLvTvkGmq8sbg5qTOqP+gyTgT6SOqRkd133o2tgTAnUNv+yNBQNmPfQU/oUaFPoBdxTt94K7jHb8YP0T5od5iZL5TyRkVQEwfhau9Y3eBSj36Mnrt8D2RA+9gDbTVen18peMdu4dgOZQ5DfiVN/haUU37fO3HL8Y=
*/