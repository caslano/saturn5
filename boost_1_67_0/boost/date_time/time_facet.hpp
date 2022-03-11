
#ifndef _DATE_TIME_FACET__HPP__
#define _DATE_TIME_FACET__HPP__

/* Copyright (c) 2004-2005 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author:  Martin Andrian, Jeff Garland, Bart Garst
 * $Date$
 */

#include <cctype>
#include <locale>
#include <limits>
#include <string>
#include <sstream>
#include <iomanip>
#include <iterator> // i/ostreambuf_iterator
#include <exception>
#include <boost/assert.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include <boost/range/as_literal.hpp>
#include <boost/algorithm/string/erase.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/date_time/compiler_config.hpp>
#include <boost/date_time/date_facet.hpp>
#include <boost/date_time/string_convert.hpp>
#include <boost/date_time/special_defs.hpp>
#include <boost/date_time/time_resolution_traits.hpp> // absolute_value

namespace boost {
namespace date_time {

  template <class CharT>
  struct time_formats {
    public:
      typedef CharT char_type;
      static const char_type fractional_seconds_format[3];               // f
      static const char_type fractional_seconds_or_none_format[3];       // F
      static const char_type seconds_with_fractional_seconds_format[3];  // s
      static const char_type seconds_format[3];                          // S
      static const char_type hours_format[3];                            // H
      static const char_type unrestricted_hours_format[3];               // O
      static const char_type full_24_hour_time_format[3];                // T
      static const char_type full_24_hour_time_expanded_format[9];       // HH:MM:SS
      static const char_type short_24_hour_time_format[3];               // R
      static const char_type short_24_hour_time_expanded_format[6];      // HH:MM
      static const char_type standard_format[9];                         // x X
      static const char_type zone_abbrev_format[3];                      // z
      static const char_type zone_name_format[3];                        // Z
      static const char_type zone_iso_format[3];                         // q
      static const char_type zone_iso_extended_format[3];                // Q
      static const char_type posix_zone_string_format[4];                // ZP
      static const char_type duration_sign_negative_only[3];             // -
      static const char_type duration_sign_always[3];                    // +
      static const char_type duration_seperator[2];
      static const char_type negative_sign[2];                           //-
      static const char_type positive_sign[2];                           //+
      static const char_type iso_time_format_specifier[18];
      static const char_type iso_time_format_extended_specifier[22];
      //default ptime format is YYYY-Mon-DD HH:MM:SS[.fff...][ zzz]
      static const char_type default_time_format[23];
      // default_time_input_format uses a posix_time_zone_string instead of a time zone abbrev
      static const char_type default_time_input_format[24];
      //default time_duration format is HH:MM:SS[.fff...]
      static const char_type default_time_duration_format[11];
  };

  template <class CharT>
  const typename time_formats<CharT>::char_type
  time_formats<CharT>::fractional_seconds_format[3] = {'%','f'};

  template <class CharT>
  const typename time_formats<CharT>::char_type
  time_formats<CharT>::fractional_seconds_or_none_format[3] = {'%','F'};

  template <class CharT>
  const typename time_formats<CharT>::char_type
  time_formats<CharT>::seconds_with_fractional_seconds_format[3] = {'%','s'};

  template <class CharT>
  const typename time_formats<CharT>::char_type
  time_formats<CharT>::seconds_format[3] =  {'%','S'};

  template <class CharT>
  const typename time_formats<CharT>::char_type
  time_formats<CharT>::hours_format[3] =  {'%','H'};

  template <class CharT>
  const typename time_formats<CharT>::char_type
  time_formats<CharT>::unrestricted_hours_format[3] =  {'%','O'};

  template <class CharT>
  const typename time_formats<CharT>::char_type
  time_formats<CharT>::full_24_hour_time_format[3] =  {'%','T'};

  template <class CharT>
  const typename time_formats<CharT>::char_type
  time_formats<CharT>::full_24_hour_time_expanded_format[9] =
  {'%','H',':','%','M',':','%','S'};

  template <class CharT>
  const typename time_formats<CharT>::char_type
  time_formats<CharT>::short_24_hour_time_format[3] =  {'%','R'};

  template <class CharT>
  const typename time_formats<CharT>::char_type
  time_formats<CharT>::short_24_hour_time_expanded_format[6] =
  {'%','H',':','%','M'};

  template <class CharT>
  const typename time_formats<CharT>::char_type
  //time_formats<CharT>::standard_format[5] =  {'%','c',' ','%','z'};
  time_formats<CharT>::standard_format[9] =  {'%','x',' ','%','X',' ','%','z'};

  template <class CharT>
  const typename time_formats<CharT>::char_type
  time_formats<CharT>::zone_abbrev_format[3] =  {'%','z'};

  template <class CharT>
  const typename time_formats<CharT>::char_type
  time_formats<CharT>::zone_name_format[3] =  {'%','Z'};

  template <class CharT>
  const typename time_formats<CharT>::char_type
  time_formats<CharT>::zone_iso_format[3] =  {'%','q'};

  template <class CharT>
  const typename time_formats<CharT>::char_type
  time_formats<CharT>::zone_iso_extended_format[3] ={'%','Q'};

  template <class CharT>
  const typename time_formats<CharT>::char_type
  time_formats<CharT>::posix_zone_string_format[4] ={'%','Z','P'};

  template <class CharT>
  const typename time_formats<CharT>::char_type
  time_formats<CharT>::duration_seperator[2] =  {':'};

  template <class CharT>
  const typename time_formats<CharT>::char_type
  time_formats<CharT>::negative_sign[2] =  {'-'};

  template <class CharT>
  const typename time_formats<CharT>::char_type
  time_formats<CharT>::positive_sign[2] =  {'+'};

  template <class CharT>
  const typename time_formats<CharT>::char_type
  time_formats<CharT>::duration_sign_negative_only[3] ={'%','-'};

  template <class CharT>
  const typename time_formats<CharT>::char_type
  time_formats<CharT>::duration_sign_always[3] ={'%','+'};

  template <class CharT>
  const typename time_formats<CharT>::char_type
  time_formats<CharT>::iso_time_format_specifier[18] =
    {'%', 'Y', '%', 'm', '%', 'd', 'T',
     '%', 'H', '%', 'M', '%', 'S', '%', 'F', '%','q' };

  template <class CharT>
  const typename time_formats<CharT>::char_type
  time_formats<CharT>::iso_time_format_extended_specifier[22] =
    {'%', 'Y', '-', '%', 'm', '-', '%', 'd', ' ',
     '%', 'H', ':', '%', 'M', ':', '%', 'S', '%', 'F','%','Q'};

  template <class CharT>
  const typename time_formats<CharT>::char_type
  time_formats<CharT>::default_time_format[23] =
    {'%','Y','-','%','b','-','%','d',' ',
      '%','H',':','%','M',':','%','S','%','F',' ','%','z'};

  template <class CharT>
  const typename time_formats<CharT>::char_type
  time_formats<CharT>::default_time_input_format[24] =
    {'%','Y','-','%','b','-','%','d',' ',
      '%','H',':','%','M',':','%','S','%','F',' ','%','Z','P'};

  template <class CharT>
  const typename time_formats<CharT>::char_type
  time_formats<CharT>::default_time_duration_format[11] =
    {'%','O',':','%','M',':','%','S','%','F'};



  /*! Facet used for format-based output of time types
   * This class provides for the use of format strings to output times.  In addition
   * to the flags for formatting date elements, the following are the allowed format flags:
   *  - %x %X => default format - enables addition of more flags to default (ie. "%x %X %z")
   *  - %f => fractional seconds ".123456"
   *  - %F => fractional seconds or none: like frac sec but empty if frac sec == 0
   *  - %s => seconds w/ fractional sec "02.123" (this is the same as "%S%f)
   *  - %S => seconds "02"
   *  - %z => abbreviated time zone "EDT"
   *  - %Z => full time zone name "Eastern Daylight Time"
   */
  template <class time_type,
            class CharT,
            class OutItrT = std::ostreambuf_iterator<CharT, std::char_traits<CharT> > >
  class BOOST_SYMBOL_VISIBLE time_facet :
    public boost::date_time::date_facet<typename time_type::date_type , CharT, OutItrT> {
    typedef time_formats< CharT > formats_type;
   public:
    typedef typename time_type::date_type date_type;
    typedef typename time_type::time_duration_type time_duration_type;
    typedef boost::date_time::period<time_type,time_duration_type> period_type;
    typedef boost::date_time::date_facet<typename time_type::date_type, CharT, OutItrT> base_type;
    typedef typename base_type::string_type string_type;
    typedef typename base_type::char_type   char_type;
    typedef typename base_type::period_formatter_type period_formatter_type;
    typedef typename base_type::special_values_formatter_type special_values_formatter_type;
    typedef typename base_type::date_gen_formatter_type date_gen_formatter_type;
    static const char_type* fractional_seconds_format;                // %f
    static const char_type* fractional_seconds_or_none_format;        // %F
    static const char_type* seconds_with_fractional_seconds_format;   // %s
    static const char_type* seconds_format;                           // %S
    static const char_type* hours_format;                             // %H
    static const char_type* unrestricted_hours_format;                // %O
    static const char_type* standard_format;                          // %x X
    static const char_type* zone_abbrev_format;                       // %z
    static const char_type* zone_name_format;                         // %Z
    static const char_type* zone_iso_format;                          // %q
    static const char_type* zone_iso_extended_format;                 // %Q
    static const char_type* posix_zone_string_format;                 // %ZP
    static const char_type* duration_seperator;
    static const char_type* duration_sign_always;                     // %+
    static const char_type* duration_sign_negative_only;              // %-
    static const char_type* negative_sign;                            //-
    static const char_type* positive_sign;                            //+
    static const char_type* iso_time_format_specifier;
    static const char_type* iso_time_format_extended_specifier;

    //default ptime format is YYYY-Mon-DD HH:MM:SS[.fff...][ zzz]
    static const char_type* default_time_format;
    //default time_duration format is HH:MM:SS[.fff...]
    static const char_type* default_time_duration_format;
    static std::locale::id id;

#if defined (__SUNPRO_CC) && defined (_RWSTD_VER)
      std::locale::id& __get_id (void) const { return id; }
#endif

    //! sets default formats for ptime, local_date_time, and time_duration
    explicit time_facet(::size_t ref_arg = 0)
      : base_type(default_time_format, period_formatter_type(), special_values_formatter_type(), date_gen_formatter_type(), ref_arg),
        m_time_duration_format(string_type(duration_sign_negative_only) + default_time_duration_format)
    {}

    //! Construct the facet with an explicitly specified format
    explicit time_facet(const char_type* format_arg,
                        period_formatter_type period_formatter_arg = period_formatter_type(),
                        const special_values_formatter_type& special_value_formatter = special_values_formatter_type(),
                        date_gen_formatter_type dg_formatter = date_gen_formatter_type(),
                         ::size_t ref_arg = 0)
      : base_type(format_arg,
                  period_formatter_arg,
                  special_value_formatter,
                  dg_formatter,
                  ref_arg),
        m_time_duration_format(string_type(duration_sign_negative_only) + default_time_duration_format)
    {}

    //! Changes format for time_duration
    void time_duration_format(const char_type* const format)
    {
      m_time_duration_format = format;
    }

    virtual void set_iso_format()
    {
      this->m_format = iso_time_format_specifier;
    }
    virtual void set_iso_extended_format()
    {
      this->m_format = iso_time_format_extended_specifier;
    }

    OutItrT put(OutItrT next_arg,
                std::ios_base& ios_arg,
                char_type fill_arg,
                const time_type& time_arg) const
    {
      if (time_arg.is_special()) {
        return this->do_put_special(next_arg, ios_arg, fill_arg,
                              time_arg.date().as_special());
      }
      string_type local_format(this->m_format);

      // %T and %R have to be replaced here since they are not standard
      boost::algorithm::replace_all(local_format,
        boost::as_literal(formats_type::full_24_hour_time_format),
        boost::as_literal(formats_type::full_24_hour_time_expanded_format));
      boost::algorithm::replace_all(local_format,
        boost::as_literal(formats_type::short_24_hour_time_format),
        boost::as_literal(formats_type::short_24_hour_time_expanded_format));

      string_type frac_str;
      if (local_format.find(seconds_with_fractional_seconds_format) != string_type::npos) {
        // replace %s with %S.nnn
        frac_str =
          fractional_seconds_as_string(time_arg.time_of_day(), false);
        char_type sep = std::use_facet<std::numpunct<char_type> >(ios_arg.getloc()).decimal_point();

        string_type replace_string(seconds_format);
        replace_string += sep;
        replace_string += frac_str;
        boost::algorithm::replace_all(local_format,
                                      seconds_with_fractional_seconds_format,
                                      replace_string);
      }
      /* NOTE: replacing posix_zone_string_format must be done BEFORE
       * zone_name_format: "%ZP" & "%Z", if Z is checked first it will
       * incorrectly replace a zone_name where a posix_string should go */
      if (local_format.find(posix_zone_string_format) != string_type::npos) {
        if(time_arg.zone_abbrev().empty()) {
          // if zone_abbrev() returns an empty string, we want to
          // erase posix_zone_string_format from format
          boost::algorithm::erase_all(local_format, posix_zone_string_format);
        }
        else{
          boost::algorithm::replace_all(local_format,
                                        posix_zone_string_format,
                                        time_arg.zone_as_posix_string());
        }
      }
      if (local_format.find(zone_name_format) != string_type::npos) {
        if(time_arg.zone_name().empty()) {
          /* TODO: this'll probably create problems if a user places
           * the zone_*_format flag in the format with a ptime. This
           * code removes the flag from the default formats */

          // if zone_name() returns an empty string, we want to
          // erase zone_name_format & one preceeding space
          std::basic_ostringstream<char_type> ss;
          ss << ' ' << zone_name_format;
          boost::algorithm::erase_all(local_format, ss.str());
        }
        else{
          boost::algorithm::replace_all(local_format,
                                        zone_name_format,
                                        time_arg.zone_name());
        }
      }
      if (local_format.find(zone_abbrev_format) != string_type::npos) {
        if(time_arg.zone_abbrev(false).empty()) {
          /* TODO: this'll probably create problems if a user places
           * the zone_*_format flag in the format with a ptime. This
           * code removes the flag from the default formats */

          // if zone_abbrev() returns an empty string, we want to
          // erase zone_abbrev_format & one preceeding space
          std::basic_ostringstream<char_type> ss;
          ss << ' ' << zone_abbrev_format;
          boost::algorithm::erase_all(local_format, ss.str());
        }
        else{
          boost::algorithm::replace_all(local_format,
                                        zone_abbrev_format,
                                        time_arg.zone_abbrev(false));
        }
      }
      if (local_format.find(zone_iso_extended_format) != string_type::npos) {
        if(time_arg.zone_name(true).empty()) {
          /* TODO: this'll probably create problems if a user places
           * the zone_*_format flag in the format with a ptime. This
           * code removes the flag from the default formats */

          // if zone_name() returns an empty string, we want to
          // erase zone_iso_extended_format from format
          boost::algorithm::erase_all(local_format, zone_iso_extended_format);
        }
        else{
          boost::algorithm::replace_all(local_format,
                                        zone_iso_extended_format,
                                        time_arg.zone_name(true));
        }
      }

      if (local_format.find(zone_iso_format) != string_type::npos) {
        if(time_arg.zone_abbrev(true).empty()) {
          /* TODO: this'll probably create problems if a user places
           * the zone_*_format flag in the format with a ptime. This
           * code removes the flag from the default formats */

          // if zone_abbrev() returns an empty string, we want to
          // erase zone_iso_format from format
          boost::algorithm::erase_all(local_format, zone_iso_format);
        }
        else{
          boost::algorithm::replace_all(local_format,
                                        zone_iso_format,
                                        time_arg.zone_abbrev(true));
        }
      }
      if (local_format.find(fractional_seconds_format) != string_type::npos) {
        // replace %f with nnnnnnn
        if (frac_str.empty()) {
          frac_str = fractional_seconds_as_string(time_arg.time_of_day(), false);
        }
        boost::algorithm::replace_all(local_format,
                                      fractional_seconds_format,
                                      frac_str);
      }

      if (local_format.find(fractional_seconds_or_none_format) != string_type::npos) {
        // replace %F with nnnnnnn or nothing if fs == 0
        frac_str =
          fractional_seconds_as_string(time_arg.time_of_day(), true);
        if (frac_str.size()) {
          char_type sep = std::use_facet<std::numpunct<char_type> >(ios_arg.getloc()).decimal_point();
          string_type replace_string;
          replace_string += sep;
          replace_string += frac_str;
          boost::algorithm::replace_all(local_format,
                                        fractional_seconds_or_none_format,
                                        replace_string);
        }
        else {
          boost::algorithm::erase_all(local_format,
                                      fractional_seconds_or_none_format);
        }
      }

      return this->do_put_tm(next_arg, ios_arg, fill_arg,
                       to_tm(time_arg), local_format);
    }

    //! put function for time_duration
    OutItrT put(OutItrT next_arg,
                std::ios_base& ios_arg,
                char_type fill_arg,
                const time_duration_type& time_dur_arg) const
    {
      if (time_dur_arg.is_special()) {
        return this->do_put_special(next_arg, ios_arg, fill_arg,
                              time_dur_arg.get_rep().as_special());
      }

      string_type format(m_time_duration_format);
      if (time_dur_arg.is_negative()) {
        // replace %- with minus sign.  Should we use the numpunct facet?
        boost::algorithm::replace_all(format,
                                      duration_sign_negative_only,
                                      negative_sign);
          // remove all the %+ in the string with '-'
        boost::algorithm::replace_all(format,
                                      duration_sign_always,
                                      negative_sign);
      }
      else { //duration is positive
        // remove all the %- combos from the string
        boost::algorithm::erase_all(format, duration_sign_negative_only);
        // remove all the %+ in the string with '+'
        boost::algorithm::replace_all(format,
                                      duration_sign_always,
                                      positive_sign);
      }

      // %T and %R have to be replaced here since they are not standard
      boost::algorithm::replace_all(format,
        boost::as_literal(formats_type::full_24_hour_time_format),
        boost::as_literal(formats_type::full_24_hour_time_expanded_format));
      boost::algorithm::replace_all(format,
        boost::as_literal(formats_type::short_24_hour_time_format),
        boost::as_literal(formats_type::short_24_hour_time_expanded_format));

      /*
       * It is possible for a time duration to span more then 24 hours.
       * Standard time_put::put is obliged to behave the same as strftime
       * (See ISO 14882-2003 22.2.5.3.1 par. 1) and strftime's behavior is
       * unspecified for the case when tm_hour field is outside 0-23 range
       * (See ISO 9899-1999 7.23.3.5 par. 3). So we must output %H and %O
       * here ourself.
       */
      string_type hours_str;
      if (format.find(unrestricted_hours_format) != string_type::npos) {
        hours_str = hours_as_string(time_dur_arg);
        boost::algorithm::replace_all(format, unrestricted_hours_format, hours_str);
      }
      // We still have to process restricted hours format specifier. In order to
      // support parseability of durations in ISO format (%H%M%S), we'll have to
      // restrict the stringified hours length to 2 characters.
      if (format.find(hours_format) != string_type::npos) {
        if (hours_str.empty())
          hours_str = hours_as_string(time_dur_arg);
        BOOST_ASSERT(hours_str.length() <= 2);
        boost::algorithm::replace_all(format, hours_format, hours_str);
      }

      string_type frac_str;
      if (format.find(seconds_with_fractional_seconds_format) != string_type::npos) {
        // replace %s with %S.nnn
        frac_str =
          fractional_seconds_as_string(time_dur_arg, false);
        char_type sep = std::use_facet<std::numpunct<char_type> >(ios_arg.getloc()).decimal_point();

        string_type replace_string(seconds_format);
        replace_string += sep;
        replace_string += frac_str;
        boost::algorithm::replace_all(format,
                                      seconds_with_fractional_seconds_format,
                                      replace_string);
      }
      if (format.find(fractional_seconds_format) != string_type::npos) {
        // replace %f with nnnnnnn
        if (!frac_str.size()) {
          frac_str = fractional_seconds_as_string(time_dur_arg, false);
        }
        boost::algorithm::replace_all(format,
                                      fractional_seconds_format,
                                      frac_str);
      }

      if (format.find(fractional_seconds_or_none_format) != string_type::npos) {
        // replace %F with nnnnnnn or nothing if fs == 0
        frac_str =
          fractional_seconds_as_string(time_dur_arg, true);
        if (frac_str.size()) {
          char_type sep = std::use_facet<std::numpunct<char_type> >(ios_arg.getloc()).decimal_point();
          string_type replace_string;
          replace_string += sep;
          replace_string += frac_str;
          boost::algorithm::replace_all(format,
                                        fractional_seconds_or_none_format,
                                        replace_string);
        }
        else {
          boost::algorithm::erase_all(format,
                                      fractional_seconds_or_none_format);
        }
      }

      return this->do_put_tm(next_arg, ios_arg, fill_arg,
                       to_tm(time_dur_arg), format);
    }

    OutItrT put(OutItrT next, std::ios_base& ios_arg,
                char_type fill, const period_type& p) const
    {
      return this->m_period_formatter.put_period(next, ios_arg, fill,p,*this);
    }


  protected:

    static
    string_type
    fractional_seconds_as_string(const time_duration_type& time_arg,
                                 bool null_when_zero)
    {
      typename time_duration_type::fractional_seconds_type frac_sec =
        time_arg.fractional_seconds();

      if (null_when_zero && (frac_sec == 0)) {
        return string_type();
      }

      //make sure there is no sign
      return integral_as_string(
        date_time::absolute_value(frac_sec),
        time_duration_type::num_fractional_digits());
    }

    static
    string_type
    hours_as_string(const time_duration_type& time_arg, int width = 2)
    {
      return integral_as_string(date_time::absolute_value(time_arg.hours()), width);
    }

    template< typename IntT >
    static
    string_type
    integral_as_string(IntT val, int width = 2)
    {
      std::basic_ostringstream<char_type> ss;
      ss.imbue(std::locale::classic()); // don't want any formatting
      ss << std::setw(width)
        << std::setfill(static_cast<char_type>('0'));
#if (defined(BOOST_MSVC) && (_MSC_VER < 1300))
      // JDG [7/6/02 VC++ compatibility]
      char_type buff[34];
      ss << _i64toa(static_cast<boost::int64_t>(val), buff, 10);
#else
      ss << val;
#endif
      return ss.str();
    }

  private:
    string_type m_time_duration_format;

  };

  template <class time_type, class CharT, class OutItrT>
  std::locale::id time_facet<time_type, CharT, OutItrT>::id;

  template <class time_type, class CharT, class OutItrT>
  const typename time_facet<time_type, CharT, OutItrT>::char_type*
  time_facet<time_type, CharT, OutItrT>::fractional_seconds_format = time_formats<CharT>::fractional_seconds_format;

  template <class time_type, class CharT, class OutItrT>
  const typename time_facet<time_type, CharT, OutItrT>::char_type*
  time_facet<time_type, CharT, OutItrT>::fractional_seconds_or_none_format = time_formats<CharT>::fractional_seconds_or_none_format;

  template <class time_type, class CharT, class OutItrT>
  const typename time_facet<time_type, CharT, OutItrT>::char_type*
  time_facet<time_type, CharT, OutItrT>::seconds_with_fractional_seconds_format =
    time_formats<CharT>::seconds_with_fractional_seconds_format;


  template <class time_type, class CharT, class OutItrT>
  const typename time_facet<time_type, CharT, OutItrT>::char_type*
  time_facet<time_type, CharT, OutItrT>::zone_name_format =  time_formats<CharT>::zone_name_format;

  template <class time_type, class CharT, class OutItrT>
  const typename time_facet<time_type, CharT, OutItrT>::char_type*
  time_facet<time_type, CharT, OutItrT>::zone_abbrev_format =  time_formats<CharT>::zone_abbrev_format;

  template <class time_type, class CharT, class OutItrT>
  const typename time_facet<time_type, CharT, OutItrT>::char_type*
  time_facet<time_type, CharT, OutItrT>::zone_iso_extended_format =time_formats<CharT>::zone_iso_extended_format;

  template <class time_type, class CharT, class OutItrT>
  const typename time_facet<time_type, CharT, OutItrT>::char_type*
  time_facet<time_type, CharT, OutItrT>::posix_zone_string_format =time_formats<CharT>::posix_zone_string_format;

  template <class time_type, class CharT, class OutItrT>
  const typename time_facet<time_type, CharT, OutItrT>::char_type*
  time_facet<time_type, CharT, OutItrT>::zone_iso_format =  time_formats<CharT>::zone_iso_format;

  template <class time_type, class CharT, class OutItrT>
  const typename time_facet<time_type, CharT, OutItrT>::char_type*
  time_facet<time_type, CharT, OutItrT>::seconds_format =  time_formats<CharT>::seconds_format;

  template <class time_type, class CharT, class OutItrT>
  const typename time_facet<time_type, CharT, OutItrT>::char_type*
  time_facet<time_type, CharT, OutItrT>::hours_format =  time_formats<CharT>::hours_format;

  template <class time_type, class CharT, class OutItrT>
  const typename time_facet<time_type, CharT, OutItrT>::char_type*
  time_facet<time_type, CharT, OutItrT>::unrestricted_hours_format =  time_formats<CharT>::unrestricted_hours_format;

  template <class time_type, class CharT, class OutItrT>
  const typename time_facet<time_type, CharT, OutItrT>::char_type*
  time_facet<time_type, CharT, OutItrT>::standard_format =  time_formats<CharT>::standard_format;

  template <class time_type, class CharT, class OutItrT>
  const typename time_facet<time_type, CharT, OutItrT>::char_type*
  time_facet<time_type, CharT, OutItrT>::duration_seperator =  time_formats<CharT>::duration_seperator;

  template <class time_type, class CharT, class OutItrT>
  const typename time_facet<time_type, CharT, OutItrT>::char_type*
  time_facet<time_type, CharT, OutItrT>::negative_sign =  time_formats<CharT>::negative_sign;

  template <class time_type, class CharT, class OutItrT>
  const typename time_facet<time_type, CharT, OutItrT>::char_type*
  time_facet<time_type, CharT, OutItrT>::positive_sign =  time_formats<CharT>::positive_sign;

  template <class time_type, class CharT, class OutItrT>
  const typename time_facet<time_type, CharT, OutItrT>::char_type*
  time_facet<time_type, CharT, OutItrT>::duration_sign_negative_only =  time_formats<CharT>::duration_sign_negative_only;

  template <class time_type, class CharT, class OutItrT>
  const typename time_facet<time_type, CharT, OutItrT>::char_type*
  time_facet<time_type, CharT, OutItrT>::duration_sign_always =  time_formats<CharT>::duration_sign_always;

  template <class time_type, class CharT, class OutItrT>
  const typename time_facet<time_type,CharT, OutItrT>::char_type*
  time_facet<time_type,CharT, OutItrT>::iso_time_format_specifier = time_formats<CharT>::iso_time_format_specifier;

  template <class time_type, class CharT, class OutItrT>
  const typename time_facet<time_type, CharT, OutItrT>::char_type*
  time_facet<time_type, CharT, OutItrT>::iso_time_format_extended_specifier = time_formats<CharT>::iso_time_format_extended_specifier;

  template <class time_type, class CharT, class OutItrT>
  const typename time_facet<time_type, CharT, OutItrT>::char_type*
  time_facet<time_type, CharT, OutItrT>::default_time_format =
    time_formats<CharT>::default_time_format;

  template <class time_type, class CharT, class OutItrT>
  const typename time_facet<time_type, CharT, OutItrT>::char_type*
  time_facet<time_type, CharT, OutItrT>::default_time_duration_format =
    time_formats<CharT>::default_time_duration_format;


  //! Facet for format-based input.
  /*!
   */
  template <class time_type,
            class CharT,
            class InItrT = std::istreambuf_iterator<CharT, std::char_traits<CharT> > >
  class BOOST_SYMBOL_VISIBLE time_input_facet :
    public boost::date_time::date_input_facet<typename time_type::date_type , CharT, InItrT> {
    public:
      typedef typename time_type::date_type date_type;
      typedef typename time_type::time_duration_type time_duration_type;
      typedef typename time_duration_type::fractional_seconds_type fracional_seconds_type;
      typedef boost::date_time::period<time_type,time_duration_type> period_type;
      typedef boost::date_time::date_input_facet<typename time_type::date_type, CharT, InItrT> base_type;
      typedef typename base_type::duration_type date_duration_type;
      typedef typename base_type::year_type year_type;
      typedef typename base_type::month_type month_type;
      typedef typename base_type::day_type day_type;
      typedef typename base_type::string_type string_type;
      typedef typename string_type::const_iterator const_itr;
      typedef typename base_type::char_type   char_type;
      typedef typename base_type::format_date_parser_type format_date_parser_type;
      typedef typename base_type::period_parser_type period_parser_type;
      typedef typename base_type::special_values_parser_type special_values_parser_type;
      typedef typename base_type::date_gen_parser_type date_gen_parser_type;
      typedef typename base_type::special_values_parser_type::match_results match_results;

      static const char_type* fractional_seconds_format;                // f
      static const char_type* fractional_seconds_or_none_format;        // F
      static const char_type* seconds_with_fractional_seconds_format;   // s
      static const char_type* seconds_format;                           // S
      static const char_type* standard_format;                          // x X
      static const char_type* zone_abbrev_format;                       // z
      static const char_type* zone_name_format;                         // Z
      static const char_type* zone_iso_format;                          // q
      static const char_type* zone_iso_extended_format;                 // Q
      static const char_type* duration_seperator;
      static const char_type* iso_time_format_specifier;
      static const char_type* iso_time_format_extended_specifier;
      static const char_type* default_time_input_format;
      static const char_type* default_time_duration_format;
      static std::locale::id id;

      //! Constructor that takes a format string for a ptime
      explicit time_input_facet(const string_type& format, ::size_t ref_arg = 0)
        : base_type(format, ref_arg),
          m_time_duration_format(default_time_duration_format)
      { }

      explicit time_input_facet(const string_type& format,
                                const format_date_parser_type& date_parser,
                                const special_values_parser_type& sv_parser,
                                const period_parser_type& per_parser,
                                const date_gen_parser_type& date_gen_parser,
                                ::size_t ref_arg = 0)
        : base_type(format,
                    date_parser,
                    sv_parser,
                    per_parser,
                    date_gen_parser,
                    ref_arg),
          m_time_duration_format(default_time_duration_format)
      {}

      //! sets default formats for ptime, local_date_time, and time_duration
      explicit time_input_facet(::size_t ref_arg = 0)
        : base_type(default_time_input_format, ref_arg),
          m_time_duration_format(default_time_duration_format)
      { }

      //! Set the format for time_duration
      void time_duration_format(const char_type* const format) {
        m_time_duration_format = format;
      }
      virtual void set_iso_format()
      {
        this->m_format = iso_time_format_specifier;
      }
      virtual void set_iso_extended_format()
      {
        this->m_format = iso_time_format_extended_specifier;
      }

      InItrT get(InItrT& sitr,
                 InItrT& stream_end,
                 std::ios_base& ios_arg,
                 period_type& p) const
      {
        p = this->m_period_parser.get_period(sitr,
                                             stream_end,
                                             ios_arg,
                                             p,
                                             time_duration_type::unit(),
                                             *this);
        return sitr;
      }

      //default ptime format is YYYY-Mon-DD HH:MM:SS[.fff...][ zzz]
      //default time_duration format is %H:%M:%S%F HH:MM:SS[.fff...]

      InItrT get(InItrT& sitr,
                 InItrT& stream_end,
                 std::ios_base& ios_arg,
                 time_duration_type& td) const
      {
        // skip leading whitespace
        while((sitr != stream_end) && std::isspace(*sitr)) { ++sitr; }

        bool use_current_char = false;

        // num_get will consume the +/-, we may need a copy if special_value
        char_type c = '\0';
        if((sitr != stream_end) && (*sitr == '-' || *sitr == '+')) {
          c = *sitr;
        }

        typedef typename time_duration_type::hour_type hour_type;
        typedef typename time_duration_type::min_type min_type;
        typedef typename time_duration_type::sec_type sec_type;

        hour_type hour = 0;
        min_type min = 0;
        sec_type sec = 0;
        typename time_duration_type::fractional_seconds_type frac(0);

        typedef std::num_get<CharT, InItrT> num_get;
        if(!std::has_facet<num_get>(ios_arg.getloc())) {
          num_get* ng = new num_get();
          std::locale loc = std::locale(ios_arg.getloc(), ng);
          ios_arg.imbue(loc);
        }

        const_itr itr(m_time_duration_format.begin());
        while (itr != m_time_duration_format.end() && (sitr != stream_end)) {
          if (*itr == '%') {
            if (++itr == m_time_duration_format.end()) break;
            if (*itr != '%') {
              switch(*itr) {
              case 'O':
                {
                  // A period may span more than 24 hours. In that case the format
                  // string should be composed with the unrestricted hours specifier.
                  hour = var_string_to_int<hour_type, CharT>(sitr, stream_end,
                                      std::numeric_limits<hour_type>::digits10 + 1);
                  if(hour == -1){
                     return check_special_value(sitr, stream_end, td, c);
                  }
                  break;
                }
              case 'H':
                {
                  match_results mr;
                  hour = fixed_string_to_int<hour_type, CharT>(sitr, stream_end, mr, 2);
                  if(hour == -1){
                     return check_special_value(sitr, stream_end, td, c);
                  }
                  break;
                }
              case 'M':
                {
                  match_results mr;
                  min = fixed_string_to_int<min_type, CharT>(sitr, stream_end, mr, 2);
                  if(min == -1){
                     return check_special_value(sitr, stream_end, td, c);
                  }
                  break;
                }
              case 's':
              case 'S':
                {
                  match_results mr;
                  sec = fixed_string_to_int<sec_type, CharT>(sitr, stream_end, mr, 2);
                  if(sec == -1){
                     return check_special_value(sitr, stream_end, td, c);
                  }
                  if (*itr == 'S')
                    break;
                  // %s is the same as %S%f so we drop through into %f
                }
                /* Falls through. */
              case 'f':
                {
                  // check for decimal, check special_values if missing
                  if(*sitr == '.') {
                    ++sitr;
                    parse_frac_type(sitr, stream_end, frac);
                    // sitr will point to next expected char after this parsing
                    // is complete so no need to advance it
                    use_current_char = true;
                  }
                  else {
                    return check_special_value(sitr, stream_end, td, c);
                  }
                  break;
                }
              case 'F':
                {
                  // check for decimal, skip if missing
                  if(*sitr == '.') {
                    ++sitr;
                    parse_frac_type(sitr, stream_end, frac);
                    // sitr will point to next expected char after this parsing
                    // is complete so no need to advance it
                    use_current_char = true;
                  }
                  else {
                    // nothing was parsed so we don't want to advance sitr
                    use_current_char = true;
                  }
                  break;
                }
              default:
                {} // ignore what we don't understand?
              }// switch
            }
            else { // itr == '%', second consecutive
              ++sitr;
            }

            ++itr; //advance past format specifier
          }
          else {  //skip past chars in format and in buffer
            ++itr;
            // set use_current_char when sitr is already
            // pointing at the next character to process
            if (use_current_char) {
              use_current_char = false;
            }
            else {
              ++sitr;
            }
          }
        }

        td = time_duration_type(hour, min, sec, frac);
        return sitr;
      }


      //! Parses a time object from the input stream
      InItrT get(InItrT& sitr,
                 InItrT& stream_end,
                 std::ios_base& ios_arg,
                 time_type& t) const
      {
        string_type tz_str;
        return get(sitr, stream_end, ios_arg, t, tz_str, false);
      }
      //! Expects a time_zone in the input stream
      InItrT get_local_time(InItrT& sitr,
                            InItrT& stream_end,
                            std::ios_base& ios_arg,
                            time_type& t,
                            string_type& tz_str) const
      {
        return get(sitr, stream_end, ios_arg, t, tz_str, true);
      }

    protected:

      InItrT get(InItrT& sitr,
                 InItrT& stream_end,
                 std::ios_base& ios_arg,
                 time_type& t,
                 string_type& tz_str,
                 bool time_is_local) const
      {
        // skip leading whitespace
        while((sitr != stream_end) && std::isspace(*sitr)) { ++sitr; }

        bool use_current_char = false;
        bool use_current_format_char = false; // used whith two character flags

        // num_get will consume the +/-, we may need a copy if special_value
        char_type c = '\0';
        if((sitr != stream_end) && (*sitr == '-' || *sitr == '+')) {
          c = *sitr;
        }

        typedef typename time_duration_type::hour_type hour_type;
        typedef typename time_duration_type::min_type min_type;
        typedef typename time_duration_type::sec_type sec_type;

        // time elements
        hour_type hour = 0;
        min_type min = 0;
        sec_type sec = 0;
        typename time_duration_type::fractional_seconds_type frac(0);
        // date elements
        short day_of_year(0);
        /* Initialized the following to their minimum values. These intermediate
         * objects are used so we get specific exceptions when part of the input
         * is unparsable.
         * Ex: "205-Jan-15" will throw a bad_year, "2005-Jsn-15"- bad_month, etc.*/
        year_type t_year(1400);
        month_type t_month(1);
        day_type t_day(1);

        typedef std::num_get<CharT, InItrT> num_get;
        if(!std::has_facet<num_get>(ios_arg.getloc())) {
          num_get* ng = new num_get();
          std::locale loc = std::locale(ios_arg.getloc(), ng);
          ios_arg.imbue(loc);
        }

        const_itr itr(this->m_format.begin());
        while (itr != this->m_format.end() && (sitr != stream_end)) {
          if (*itr == '%') {
            if (++itr == this->m_format.end()) break;
            if (*itr != '%') {
              // the cases are grouped by date & time flags - not alphabetical order
              switch(*itr) {
                // date flags
                case 'Y':
                case 'y':
                  {
                    char_type cs[3] = { '%', *itr };
                    string_type s(cs);
                    match_results mr;
                    try {
                      t_year = this->m_parser.parse_year(sitr, stream_end, s, mr);
                    }
                    catch(std::out_of_range&) { // base class for bad_year exception
                      if(this->m_sv_parser.match(sitr, stream_end, mr)) {
                        t = time_type(static_cast<special_values>(mr.current_match));
                        return sitr;
                      }
                      else {
                        throw; // rethrow bad_year
                      }
                    }
                    break;
                  }
                case 'B':
                case 'b':
                case 'm':
                  {
                    char_type cs[3] = { '%', *itr };
                    string_type s(cs);
                    match_results mr;
                    try {
                      t_month = this->m_parser.parse_month(sitr, stream_end, s, mr);
                    }
                    catch(std::out_of_range&) { // base class for bad_month exception
                      if(this->m_sv_parser.match(sitr, stream_end, mr)) {
                        t = time_type(static_cast<special_values>(mr.current_match));
                        return sitr;
                      }
                      else {
                        throw; // rethrow bad_month
                      }
                    }
                    // did m_parser already advance sitr to next char?
                    if(mr.has_remaining()) {
                      use_current_char = true;
                    }
                    break;
                  }
                case 'a':
                case 'A':
                case 'w':
                  {
                    // weekday is not used in construction but we need to get it out of the stream
                    char_type cs[3] = { '%', *itr };
                    string_type s(cs);
                    match_results mr;
                    typename date_type::day_of_week_type wd(0);
                    try {
                      wd = this->m_parser.parse_weekday(sitr, stream_end, s, mr);
                    }
                    catch(std::out_of_range&) { // base class for bad_weekday exception
                      if(this->m_sv_parser.match(sitr, stream_end, mr)) {
                        t = time_type(static_cast<special_values>(mr.current_match));
                        return sitr;
                      }
                      else {
                        throw; // rethrow bad_weekday
                      }
                    }
                    // did m_parser already advance sitr to next char?
                    if(mr.has_remaining()) {
                      use_current_char = true;
                    }
                    break;
                  }
                case 'j':
                  {
                    // code that gets julian day (from format_date_parser)
                    match_results mr;
                    day_of_year = fixed_string_to_int<unsigned short, CharT>(sitr, stream_end, mr, 3);
                    if(day_of_year == -1) {
                      if(this->m_sv_parser.match(sitr, stream_end, mr)) {
                        t = time_type(static_cast<special_values>(mr.current_match));
                        return sitr;
                      }
                    }
                    // these next two lines are so we get an exception with bad input
                    typedef typename time_type::date_type::day_of_year_type day_of_year_type;
                    day_of_year_type t_day_of_year(day_of_year);
                    break;
                  }
                case 'd':
                case 'e':
                  {
                    try {
                      t_day = (*itr == 'd') ?
                          this->m_parser.parse_day_of_month(sitr, stream_end) :
                          this->m_parser.parse_var_day_of_month(sitr, stream_end);
                    }
                    catch(std::out_of_range&) { // base class for exception bad_day_of_month
                      match_results mr;
                      if(this->m_sv_parser.match(sitr, stream_end, mr)) {
                        t = time_type(static_cast<special_values>(mr.current_match));
                        return sitr;
                      }
                      else {
                        throw; // rethrow bad_day_of_month
                      }
                    }
                    break;
                  }
                // time flags
                case 'H':
                  {
                    match_results mr;
                    hour = fixed_string_to_int<hour_type, CharT>(sitr, stream_end, mr, 2);
                    if(hour == -1){
                       return check_special_value(sitr, stream_end, t, c);
                    }
                    break;
                  }
                case 'M':
                  {
                    match_results mr;
                    min = fixed_string_to_int<min_type, CharT>(sitr, stream_end, mr, 2);
                    if(min == -1){
                       return check_special_value(sitr, stream_end, t, c);
                    }
                    break;
                  }
                case 's':
                case 'S':
                  {
                    match_results mr;
                    sec = fixed_string_to_int<sec_type, CharT>(sitr, stream_end, mr, 2);
                    if(sec == -1){
                       return check_special_value(sitr, stream_end, t, c);
                    }
                    if (*itr == 'S' || sitr == stream_end)
                      break;
                    // %s is the same as %S%f so we drop through into %f if we are
                    // not at the end of the stream
                  }
                  /* Falls through. */
                case 'f':
                  {
                    // check for decimal, check SV if missing
                    if(*sitr == '.') {
                      ++sitr;
                      parse_frac_type(sitr, stream_end, frac);
                      // sitr will point to next expected char after this parsing
                      // is complete so no need to advance it
                      use_current_char = true;
                    }
                    else {
                      return check_special_value(sitr, stream_end, t, c);
                    }
                    break;
                  }
                case 'F':
                  {
                    // check for decimal, skip if missing
                    if(*sitr == '.') {
                      ++sitr;
                      parse_frac_type(sitr, stream_end, frac);
                      // sitr will point to next expected char after this parsing
                      // is complete so no need to advance it
                      use_current_char = true;
                    }
                    else {
                      // nothing was parsed so we don't want to advance sitr
                      use_current_char = true;
                    }
                    break;
                  }
                  // time_zone flags
                //case 'q':
                //case 'Q':
                //case 'z':
                case 'Z':
                  {
                    if(time_is_local) { // skip if 't' is a ptime
                      ++itr;
                      if(*itr == 'P') {
                        // skip leading whitespace
                        while((sitr != stream_end) && std::isspace(*sitr)) { ++sitr; }
                        // parse zone
                        while((sitr != stream_end) && (!std::isspace(*sitr))) {
                          tz_str += *sitr;
                          ++sitr;
                        }
                      }
                      else {
                        use_current_format_char = true;
                      }

                    }
                    else {
                      // nothing was parsed so we don't want to advance sitr
                      use_current_char = true;
                    }

                    break;
                  }
                default:
                {} // ignore what we don't understand?
              }// switch
            }
            else { // itr == '%', second consecutive
              ++sitr;
            }

            if(use_current_format_char) {
              use_current_format_char = false;
            }
            else {
              ++itr; //advance past format specifier
            }

          }
          else {  //skip past chars in format and in buffer
            ++itr;
            // set use_current_char when sitr is already
            // pointing at the next character to process
            if (use_current_char) {
              use_current_char = false;
            }
            else {
              ++sitr;
            }
          }
        }

        date_type d(not_a_date_time);
        if (day_of_year > 0) {
          d = date_type(static_cast<unsigned short>(t_year),1,1) + date_duration_type(day_of_year-1);
        }
        else {
          d = date_type(t_year, t_month, t_day);
        }

        time_duration_type td(hour, min, sec, frac);
        t = time_type(d, td);
        return sitr;
      }

      //! Helper function to check for special_value
      /*! First character may have been consumed during original parse
       * attempt. Parameter 'c' should be a copy of that character.
       * Throws ios_base::failure if parse fails. */
      template<class temporal_type>
      inline
      InItrT check_special_value(InItrT& sitr,InItrT& stream_end, temporal_type& tt, char_type c='\0') const
      {
        match_results mr;
        if((c == '-' || c == '+') && (*sitr != c)) { // was the first character consumed?
          mr.cache += c;
        }
        (void)this->m_sv_parser.match(sitr, stream_end, mr);
        if(mr.current_match == match_results::PARSE_ERROR) {
          std::string tmp = convert_string_type<char_type, char>(mr.cache);
          boost::throw_exception(std::ios_base::failure("Parse failed. No match found for '" + tmp + "'"));
          BOOST_DATE_TIME_UNREACHABLE_EXPRESSION(return sitr); // should never reach
        }
        tt = temporal_type(static_cast<special_values>(mr.current_match));
        return sitr;
      }

      //! Helper function for parsing a fractional second type from the stream
      void parse_frac_type(InItrT& sitr,
                           InItrT& stream_end,
                           fracional_seconds_type& frac) const
      {
        string_type cache;
        while((sitr != stream_end) && std::isdigit(*sitr)) {
          cache += *sitr;
          ++sitr;
        }
        if(cache.size() > 0) {
          unsigned short precision = time_duration_type::num_fractional_digits();
          // input may be only the first few decimal places
          if(cache.size() < precision) {
            frac = lexical_cast<fracional_seconds_type>(cache);
            frac = decimal_adjust(frac, static_cast<unsigned short>(precision - cache.size()));
          }
          else {
            // if input has too many decimal places, drop excess digits
            frac = lexical_cast<fracional_seconds_type>(cache.substr(0, precision));
          }
        }
      }

    private:
      string_type m_time_duration_format;

      //! Helper function to adjust trailing zeros when parsing fractional digits
      template<class int_type>
      inline
      int_type decimal_adjust(int_type val, const unsigned short places) const
      {
        unsigned long factor = 1;
        for(int i = 0; i < places; ++i){
          factor *= 10; // shift decimal to the right
        }
        return val * factor;
      }

  };

template <class time_type, class CharT, class InItrT>
  std::locale::id time_input_facet<time_type, CharT, InItrT>::id;

template <class time_type, class CharT, class InItrT>
  const typename time_input_facet<time_type, CharT, InItrT>::char_type*
  time_input_facet<time_type, CharT, InItrT>::fractional_seconds_format = time_formats<CharT>::fractional_seconds_format;

  template <class time_type, class CharT, class InItrT>
  const typename time_input_facet<time_type, CharT, InItrT>::char_type*
  time_input_facet<time_type, CharT, InItrT>::fractional_seconds_or_none_format = time_formats<CharT>::fractional_seconds_or_none_format;

  template <class time_type, class CharT, class InItrT>
  const typename time_input_facet<time_type, CharT, InItrT>::char_type*
  time_input_facet<time_type, CharT, InItrT>::seconds_with_fractional_seconds_format = time_formats<CharT>::seconds_with_fractional_seconds_format;

  template <class time_type, class CharT, class InItrT>
  const typename time_input_facet<time_type, CharT, InItrT>::char_type*
  time_input_facet<time_type, CharT, InItrT>::seconds_format = time_formats<CharT>::seconds_format;

  template <class time_type, class CharT, class InItrT>
  const typename time_input_facet<time_type, CharT, InItrT>::char_type*
  time_input_facet<time_type, CharT, InItrT>::standard_format = time_formats<CharT>::standard_format;

  template <class time_type, class CharT, class InItrT>
  const typename time_input_facet<time_type, CharT, InItrT>::char_type*
  time_input_facet<time_type, CharT, InItrT>::zone_abbrev_format = time_formats<CharT>::zone_abbrev_format;

  template <class time_type, class CharT, class InItrT>
  const typename time_input_facet<time_type, CharT, InItrT>::char_type*
  time_input_facet<time_type, CharT, InItrT>::zone_name_format = time_formats<CharT>::zone_name_format;

  template <class time_type, class CharT, class InItrT>
  const typename time_input_facet<time_type, CharT, InItrT>::char_type*
  time_input_facet<time_type, CharT, InItrT>::zone_iso_format = time_formats<CharT>::zone_iso_format;

  template <class time_type, class CharT, class InItrT>
  const typename time_input_facet<time_type, CharT, InItrT>::char_type*
  time_input_facet<time_type, CharT, InItrT>::zone_iso_extended_format = time_formats<CharT>::zone_iso_extended_format;

  template <class time_type, class CharT, class InItrT>
  const typename time_input_facet<time_type, CharT, InItrT>::char_type*
  time_input_facet<time_type, CharT, InItrT>::duration_seperator = time_formats<CharT>::duration_seperator;

  template <class time_type, class CharT, class InItrT>
  const typename time_input_facet<time_type, CharT, InItrT>::char_type*
  time_input_facet<time_type, CharT, InItrT>::iso_time_format_specifier = time_formats<CharT>::iso_time_format_specifier;

  template <class time_type, class CharT, class InItrT>
  const typename time_input_facet<time_type, CharT, InItrT>::char_type*
  time_input_facet<time_type, CharT, InItrT>::iso_time_format_extended_specifier = time_formats<CharT>::iso_time_format_extended_specifier;

  template <class time_type, class CharT, class InItrT>
  const typename time_input_facet<time_type, CharT, InItrT>::char_type*
  time_input_facet<time_type, CharT, InItrT>::default_time_input_format = time_formats<CharT>::default_time_input_format;

  template <class time_type, class CharT, class InItrT>
  const typename time_input_facet<time_type, CharT, InItrT>::char_type*
  time_input_facet<time_type, CharT, InItrT>::default_time_duration_format = time_formats<CharT>::default_time_duration_format;


} } // namespaces


#endif


/* time_facet.hpp
z/9T8+/rbBOvx9V+cD7tvcM6aHKHzf+zdqs/JvYKDpUHZ3uOn/ItcGPrl3ocSwiC5raueSQnQHfvIPd9uOD2bIV8NhaKY3Xk0O/zrrE9eAKBKhifobCf5R/wyacoQBVLoQLpHIXiWX98gpk5YbSOBkPTNn1UTD7M7TwdWFonOUW4/IlZ+eSLr7Qnh2pqJ84sQHACLpmk/z9eaNC0AS7u7z5njw9q5W/vPkXLLHoavn3/J53Foa61OE+V20b/FuOtqyc1XgwOYa8CEz7NkamKz+mq4Y/kpPyHrm1V7WD22ixtX9eZN/cg8TJ/vuFLuZ0O5r43eK5zOqiNzfSPzhuxgdO2129PKnst2e2P3r3nj880fHQ4zWocbe4OSHxvI+uK5kr+tsOinZQnvo7v8IkBvoUrJ/tmOywuFhzs353LK9s1tZlPKyI/mKcIWOzPW7D4m8OajxXprO2z3F+O5Qbf/suxNX0q7k+7w15OYaTxd749WehlLn9H/0Up0ZsXji3GlKQ8O62O0ssuZXf2lO0e6x+D41jx18ro3kA4ba3WUVU/D4NqD41F+mN1bTC6n8rO56Ceu1PllEC+lxjKWwAkz+0afk0RzXkdpGkAACz/080XWotDZq356cLD2Qm6cGEu7mcbW1jfGZ+cAtQnpvFnWOVM8iRKEyTOhVEUitfna8AlZ32SAZyU46UpXp4q07U+l/KtDpOLmKGyqqdZ0S3PuZY30h3bzwUwd7ODZ6EfL+loRRwaygQsFx8J+sWmDv8mb13+VOAacZXkDMR9Zl4IWJbA6gUBQS+eI4t9EVgatuIUO4OD+jCMoid7sQ/xeGzUo6M75MFMf3duunrwuEr6pja8Tp+vft7F57YIwXhOe/CACXX2IsHCK/nArDgTH7QfwF5qR+3Uj7XYqXgcDsreXmu5JusVd2JhI18zP0XWqYJDt4XXnrdRPWb0Mf5WuSuFPqwjNe69IceOlXFex4xYcDaQXG6sksRlLxTnORv76ck+FusReUUy5RrlUXivfzasRUfbpXlT5hDDB5XYA7UhF+I/dmFita69GQ+fEz2yFfJhObqNT6GGG8BzLTDQyjTesl6deWMTio9zmTqlLKOgflzPhy/7dVDsU/wwNm/vXm3HYlub4dhan3TwFNVLJPgOdQpZpO7JzxMwP9t1hy2mvmp9C2j6nQ6PnbpT+Hffnif8pTh32P7lZHxPthkm29JovmGkMho969479ahwQS1kvWNqdnF6vyX6sHe4DFjdMwOOTr+RfyVg9dh9Bc6KzZ6/eIt6a/elOvyM3geoMk7cdSJ+ZiTcK5nXa5LjT8BebR7Jj2eKhXdi3f5XZzuJjFfTJJhlSuOONEgNe9AmGk3Wrm9vixpvlWwcKsy8YFBA7aWcI+c7xPVj59jOerBxoLoVbjlrZl4stvvVpOJ+1H/A+kxdFpvW70BLmB1DwXv+58nOxos/NFPOxHPJ+r4ITu5dR/GWA+pwnGI54136aXuMPlcf1fCtEy1pQZ8hPtjdHaXNA1a/6MejpTuYaXPRj8L4Irn4DPB5fBY7FAcZ6fRAcy22kb0Lm3x9vuEz89/g9KDcMXq07/dqceNH0cqpxkF+vX6DL6tdTTK9UZs+t9mS52vBuDxS03Z9C/daO61dRUv8tRbrHTzyft77rbhuFbI3mnXdju+3i21tInobtNMx1Dk7ipgeZ8QPltNcBbbqI1/Yi6etEYXipXwuj/zOvhPbiBXqt1oZNXZubfawffWn4+nrK7v0pL04S5/zir1bnsKw4iKrDu85N4LvK/vxAYJ98KrqK1vQGjvV+Q0qNlCWY6sMimef/HAoMmlGh+ZxPH0CfQh9goB+gYJJnRQaooLNbDPXy1J9lm9m751/r6ZPI9OtdsuGrzh7adrU4rzbjqfJKZJTX0/+PT1u/poaG89LhgMXqWPJV8PhcWA4UfrUOc6DTYV9U9uCkcL2x5lvvsI9k+YYv8cjFlVa9qLzL66lbeywuBQdn73PgG/iZTXe+Cxapjr0Tz3MgUtWfgrvksMCZYtPxPUhp12ySX/vtOunJu8LJ1/839O24Uw8p6sxl3tvLD66nyZJ/RdwnHwVu6pa8bRcf6rDH8TU2O8r5vqIrjbZnC0GC/PrtoJTfBnuf8E1KX1UT3WzaWU17WtOXlPi/G26O8RNGB3pX7k/tOGKwniVS85I0LkWIHXuHC3tmjatqD7kKqmyPgzQW+q576lMp8evvB7WNTu+V41NsMQ0Wb0h9CE4vBWQPXs4twrzVow2/L74pxluPfsYZqeP8MzVI88qez8e2xW9kJwdI49EqgcuqmK9PMxF+fkKtHmptOopKOPO0MeJxkcnH/3371IkQuydEVU3gV3stLnPyR9fYyPI8m0BR7X68jw7kHED4nC8OzBx+Ft4gg/4W7venbi48Xw7ERZk/LBia308Pwi4/AVPbYtjxucchOzM4Kn244PtFDDRwJcIYnf+QukMcvqIdMP1RA4NcZvKjV04RXpS8jcciYXOcGG767I9B7m7ysuTgoM6HXi9zDQw4iJKUSFcSuG8bY7Tef3141ccqzDEWZwaTANAZCcKb4OvDvVHPjBJ9P0MY3iZRF4dglmA2cKa2KpK6ApfRul59F7TYENcUBYComD0rYPzrxUVvZU0770E1+Cocg+1YOItfnwK9un0KbDStoXuiQNpuNYOQz41vZVGqD5fFIeo9zGt5byjXallk7maEEx+xAUmARmKb6Cwjz33e9ylf5vx0o8M8JfY4Gg46JZO1Qn3biQcuO+aWXA6IveRGuiOTtXkcuRbJBTyuSiJOAxwS1/XAIRzbDvksVwZWrDwqvXw+dspAQnmN1Mdh5UAUjQqAatoakPt1Gi4IONS+dVQ+jjEdK4IBIEKAXzCHjqMwicdLsVFQPSUQ8CULy6A/r7n9mz98I5vwGoQo9pLX/VKDFKqBt+S90udTwxxz8eSdBOhX+Pl9uLtc7hhxjy1QOc9CragTrPBa5N2T+nuM8B9YzQBQIKaAf0gIGnqEFaoVIK8HGaivs5AxfDgF1DvmigFMMoRhmAS9vK+2oOFSCBCiFUocHl0oYPWcwaKAXIEx+3uCKECbCOiBOng0maPDxk+OuFw2nAxN9+WO6AsfxzffNCfA7U6KrhxUgEPaDLag+WXCggaquEXk2cEnkonc96AIsoOySqZAZJNgpZSGOB9PYA2KaDovXA66xCZMOhVu/0NRISECh5ClhCThsVCgLPOoj7Y/OC9IqOqALwolVoCfKL+DmL5ChIUirytzTI1KG4K8deGSOFoVkDhk0cCF+GhMEfDVIMKiK0Kg0zZVfVhSMWMW5gzZfVGmxYcpmi0HMS+PjYoR4HjgtATnHATIdKNRjjtMvscwU+Syx2wBRjQK6nG3IAypv+MdUupyAKsSVf4/oQ0Zz9NHRneP53xi7UVtol64yVAuSQUHywAfOD0JQCA7BlhdoyNeQMdaCxgducEzMUWAL9RTpwXOZsufHIDZ7MLhcHCwrwePS1L/oBqUgBtIXDQ/4JWAcMa6OImJMZ5QvklkIe9ojB684pgOhqYcsPBudHgiTr9kBbVAg89IAUmAtzeQN1Wwp1HEhXahaC1wZYvojzBAT8BAJkUVtMU+qVN24lNzT+ac1xL+jKAr2npgIxF6Tjgg3y36HArHaIijqbjbwiuDTqIBTh1tlzsg+oiwMt8TvghgVIGFEn63V2FfM0ZPJfSxRoZLHfMl15jg0GD2wMT3C04IWrr4F2NUPtbHgZt57y0lddInd6NtAazCKBw81X3qcACNOBLBDFzZTBzwUw93LTBJpIHRuiAvrBgpgBsCGtnBjDL2lHuixKGbGSCSgKAkxHGwdAsCc8JzIS/+ECw2gvql/uKz5aKv+EKdcS53jMkIDOTzwlOzyXAeZErIGWtFgWnVxLDeJAp48lOXBFQuRb3zQlTFJJLcYd5cA/6zQlRlEMEOlMSGBCQwHihCyKIQBprFhHBFI6AwXm1EITkoxLUIDnz6ZFC6ft1FB10lNP7f5eVd8dnu0GS1rIx5QON8i9R/Z67g4ba4XMsJa5CxM7BnkXOpuZdk06HYgLZwiwFZmoMFnan3/eE8epmOYXYXduVXe8TfDGBbiY0b9FnNc076Barm6L8LFzMnZCh2CtpOO5wqq/ybqvtIK+l9KnEIGxjWFeo6yS4INghIpnocDTgCq6bye/PBP8kXdjigl8/3TcR1XDxvMBE+ojg3UTxyoncePWe9d9ePNwqxpY0eKHceKPOqseqpHn1Ri8VG68Uf01563OAnzfDrqrm7UnsKZdEaJouor2ykWJ1wef1nNflBaaAheV1Et0Q4BDArzlQUDxOBcg3ikga6CRhZCsKtBQYjQCP5fLL0ECYT/uhMSzHjDTZnSLfOxOj94bGR8rC5Gm6C5XFiD7lpabGFc7WH4TP22FSZTK+S57xuf0YedHsVrHzOtZlJ+lbKdxCR0XZ1VuPpyAw8zJppxTOSKIAtYXoQmibjzXv82+QG8WsIAdaI1WKQ8hAxdq1zENyBAXGqLMNDMmYkEHnUQraQLKfA8l5tBvQx8R8RqqDASBDYlJ5xJIaMqUFxQlTQJjxZ1Gx+VYszJKlmJr3IehBLfwEvsIU8JwX2JMp8BMSV8ys+EJzTEeENXkH5oGArGtBMgAvIVgmlPofWWhE0YAyIl5ZA8CiQFN93Brng+iRmSbUBExpIN0aK0AJmU3/3QSE2JIhwE3QKSP348CF6IxgUExzkHQdKpbzvucL+uzvC8c3jzQQaBExhJamAegFygJdA/gqgNcXqtZb219sSsKs6GDmik7YgXntggztss9LY7DDf+cwRIQ/bsP+9rJGhJ+lDezNebUCTkdS/HU7w6BMyHBVB7Y7QieJmZv4Tx4ItmB8+jPOUwqvsUVZrH5I7HCikOw5gKjGMEiwY8SiIiqoByrjl06BH+PUdgUAv3CIlt96ocFEhQsvCCNGBX5/CYIiEmQN0uOAdcUIjcfs0PBzFoLzcwY9JnliAISNDDbAezH2C0GWo6LVAQC2AfNf2UYfijL8mzsAdoc7bpO4bxRbEMKQXUeQYTka6v+4ojjmFslXBeXdCwRgSVgfE2FEZOF3nnD6kBPS+Z32Qlhb+8pYDQnAfQuXKilexUxX5fKoca3LPzubXvLEKF3WzitfrZGvv+BaQr88fSud5gINmARWSKbwTYzTa4NTgmWmsPwU48oJXxVHttwrob/XDYAZAXHQE3rORgfipP8PZSaoKhTv6+oiydT1bHCmqOiQ/zqX/85eRXN1M4XthidkhRiuSMlVm/P0mxeN/ZFy8QfKgnguCXihwtdmwIYNaaVAOlMpxAimCo8Kp4pRHDkhQ8idOCXQHSHNb8W8ZANEiIKcVMSDn+H5ZAH2D8cs1XA2PDdbYR5DXlB+h1yppM6Bh0FStEKKDYdBvICUru3acRyLi8xFV/wWSohQ4yXjFMQG/btuVnzuFhbwn1oJaqXlG/9T3o/hyTh5qiTtPA1/HMt4hQ+fg3Bf+oUUw9CM0mrB9nOxLqv2bNOzK5EDF/A++rzxr6DeBWPbFYPT1i+7mtjBHMwxAbEzlnd4aWBzi06p7IssindHLYPe9WLblaDT7vXcGXevROyPzpPujY4dZ8+simeP2wK9k7bpln++P3UPfhMl9kDnRd8VFbsPChSEp49fA7WnxbaHjo9tK8fuZo7dr/Gm63YVu79l7/eup94Ftelmll33iO4aqGIKcj9wPtC1ALFPjOTTa5FE737a8NiBYNtdtLufZQtqO+24X8UYqCJ4fvBC1r1Xa3jQWxzS3oXdlSL2qMqDtm9B7FaHvde7inLHw76j4sO2F2X3QMca0P7Q8aCO3fdNmZvGx/CHknlOyXlfe+jaz5saxSc3OKq7BPszIn6nzoX2D0X8PgL5fJRDcBnQnh2dYjY9qrkAs09C7HbOhb7DIfYALf30GCnVvU9teMBbHtLegt1dEbuf9aPrbordt2Xt9y6m3kVi02tJiHVXZPdYwxzQ/tTxkI7dz6FdHtMmvA5qS49d0x4e3ZqH3WWP3VflR9f7z+NiCXz7/HLoXU2b7rXne7obsDs2Yg/VuVB1U5C6UYC7m1oP6A2PtcgNj7SroxSh7q7YfVovuu7/5pYt+uXBDkn5yZpuc7EB6PAB0hmR+l/FVxxZCMobkS0JU1xMVTpI2Q6T2a6t2EyX6fMw9jC6wB0RJBG6Yw9vO4uKVeWUqwRY2HLHENrsGnl+C5TI6EqXOny28XSSnvtDwRrEfpaaSXULHf6nHm+of9b6/F4wNLMhRido1LtSQLtqAD06exglpE5EdKg2DMQCamLsOVSeQGH3cOQJ+fkHvNpyj+UxtdLvkFxO9z63mp7YI5Trr3tUVYOyDtxOhHSb34nMlLQhQR1jc3epG3Ud787kFaiW3vTPLcl59ZiQvJ5Mvy4GCCmBHM3mwsBqHhrvj2cJ+7O5o/3lnB9j057wKmX8ugaFj4NC+mLQRfbc5cOXlf19Vzn7h+1Nqn6YLmI5hWD8HrHXd+0FrN+VV9LeEe8j9e3gnSSv39orWB+0d9IeM5dfiY2vm1ypJtt139nzu28N+3vNhawf/et6LwF/YnEfX+nYXefuflsn+0fPZlIPVhUDc7P62n8Ne/5reC3rx8rbWueZ9tpTM3aH3TNgL2r/6F139pqC1Xrn+5+VN7A+5//sivM+WRuO3yHz+mV5B+9t9EzQkxme6rda4HNsvgFztt70h0a4At3ykaR/IfJAZu3B/kdkaf9InfC83ss09Ip69fBlZn9fdSvrV/IfkeV4XQpeH7Z3sL6q/aM1+YXjr43xeF1RnP7+qHGWhV/JH1ffj+s3muvjFdHtbPDlNvA88pzD3isLcG7LrZOk+++SR87fcKi3Uj1tAL12uzJsu0yDBIHDHMP26BXMXTzWtqrpjlKLoEj1ixh7ZG9fLUP7K1s7GWwtMGytMExtOJZOuGT6C+TOrhs2XIujG043+LjpKm7y8w8O8KdF8BVH8JUj2Bok2NoE2FoF2JoybG2Ty2fzI/9XDKAy0VJCp/WO5Jmv0/T6EwSfWK74+XIbTiY/3qpcPPqf5C+HAz/hgWAKpoGdAlFUrQ5gNHZUA8k+r4o+xrIaQAFdI7P52WqAHBjX3C9nh6AmoHSAbaj3a0c2CCYD6DYIpjhFUdqQyfOOOuZ5OhPdFMliVmhtuhDxUhghMXDAuAAmzghD+81UDJJhGazQtZeCOGbTWWDnsTL46i14vzzOSDyrrT4Kzddg0VyBL1TpnS7zw8LzyzvdJ6NyGX60wDdbmDmvHTZ3h+t7vGOViQdrmacr636K/NOlef8V9PMLBbDexZcrl58htr15SwOnXf/r4V+k2K2NMXamvTxw74xFrzDMe1xBHXn9+2pnles3m+KdVlvCA4EaHsYewJYQJu/1xLkrMQUkZp23XwdLn4N0AowLZC1fn06mPt0MPddkO0yfTpT+fwqgk760vQ2v794V5D5Xf3A/6udnT3X5z+77u/y5Fa+brq6y15oP7uY7oZ5X3//Bv/9hop7XnSXlL7Vf3M02xTrft9flXlT/8FfbxSN3ffnv2Q/u+y6p+D13r0P3173APfWXd9uLyL3FPuC+q/+WeRu538p/drJe3n3ryP1U/4PsF++6srx1+WP0a5wZ5v2uiuRr1ytFeubaY23EPXcBLPtbUX5hVMsBd47PrlJtv4tskmk/t1EqO6POGHXaY0oyYVcArZ9fdWWZb934/Ff0i87TL2vWZpnMV+bTX6Acjzn3sPgNrRdS53uYsm3CF1ZFF3AUvq0LLubJegXS6NjFXRJLKQZ+Vjy6cEvoWPdN49v3niA/P++xp2FfgcfRNK5CQEcVnE19vBGafZuiNXceCuTKVQcFVuQ6KA1B8o/pBR7tck3QNUvdoG3oDbneYdbQCN76Wvg2L8+GKZxNveBrlNoXP+J2Fn+JOL2z4HaCXLs/aCTFHLqteBd78n4v9McNE9ma9Hiwi3H5vmS7C8uNFD5WZGwOAIjUjC9uTKjQ88C0PvaMeS8wQQA1MIj3E8zJvO/QzzEKWCHA7GUWOzWnxko1Xe6wMKgULsIFqFAlFMMK7yAnPiGDXxTd4YNbFMv59xxQ8fn1qKHgiumhgxUUMqKGTFDIChxwoY4UMWKGJFBDChwooYQUMCKEkoZiBUChdhTJRfOIoW4UyYUKMUKAUJ7/Q1mM5fh/KOuDCoWQEIoYwEemiydFGN0oXEAMc13+BpxkKjXBpsPNNMLVsojrziTSYnpLPwAp0luHrQRfkR0SrKSHN5ECTzEidBg+I9FMLNrLPMF1WHFWcECaw4s1crf8YGkqYXTo0slHZ6wPjPUANz89jWZME5Sd0UAkOevYDBfDvGEtg0gUDHwjS/0mWWf4EpS2tIiWbUDI2a8OpoJ0AvxYeSrz3LvUqlqt9tmzV+OkwTRlKpYKX50DPo0Z+zNV8sjmTYR1ACz10k9xGFReFIOKFOXvN9VaGOClrThqIUsc8aOF8Ces32wwfFteQzZFiMNpYnp3AoKZWG9dan/+kch4tReILDGcYNHs4EUVSuR/aMIxiUfa144ghGtIQv1LPeWJ6Sv7QMW5FGylwXEqOmWXwI6zJkexfA1456kxI+awgBtw5gEHWmMJegIdyhSMH1gmZqV1qvwnur+O929MFluFiI7w4pSjKDI8NI1nwUQplHRwO19QL4EZ1knsCGwWWGuIZbcfBRfJGHYzErbNUDhAaX+J1TN9VQtKBUQAO5dDzhoXbJZ1SBCoEnifPVg1BqG4hZvo1MbChhQpFjf2phW60jCq1gWrB71yVPRpGFRKWQGfdl7HvUCC75wksKTSP8vpaapMi5ZI3uZdNAl6EV8E0oE1sZwTcCK+VJZzuCgqHGYTOCutEF94njGTlMEf465+9jefJ59FTmkI3+ptOPtoieHiXyP5ZqDnIYksQHxtZF45J0zYI4qCalfKaQwlck7xRmRhfMnQYsutuYI/V+TgEYHNPNlpf5qeZc1bcFVymHekljUjx1b6/HCiHQ540CY4KVnARvMQNA/DDBAyweaYpcD4Uf8GY+6Wowce5KwykNYSHHH10dgYeDMZGWwUUto7PBMn5GZBo/4qmIe1GHWgOuwET/kqrKCTwtyYY35UVptBmVXPRhRzzzWuQ+oKQaAILCUPlbU=
*/