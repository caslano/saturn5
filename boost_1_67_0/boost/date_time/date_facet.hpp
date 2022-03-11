#ifndef _DATE_TIME_DATE_FACET__HPP___
#define _DATE_TIME_DATE_FACET__HPP___

/* Copyright (c) 2004-2005 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author:  Martin Andrian, Jeff Garland, Bart Garst
 * $Date$
 */

#include <locale>
#include <string>
#include <vector>
#include <iterator> // ostreambuf_iterator
#include <boost/throw_exception.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/date_time/compiler_config.hpp>
#include <boost/date_time/period.hpp>
#include <boost/date_time/special_defs.hpp>
#include <boost/date_time/special_values_formatter.hpp>
#include <boost/date_time/period_formatter.hpp>
#include <boost/date_time/period_parser.hpp>
#include <boost/date_time/date_generator_formatter.hpp>
#include <boost/date_time/date_generator_parser.hpp>
#include <boost/date_time/format_date_parser.hpp>

namespace boost { namespace date_time {


  /*! Class that provides format based I/O facet for date types.
   *
   * This class allows the formatting of dates by using format string.
   * Format strings are:
   *
   *  - %A => long_weekday_format - Full name Ex: Tuesday
   *  - %a => short_weekday_format - Three letter abbreviation Ex: Tue
   *  - %B => long_month_format - Full name Ex: October
   *  - %b => short_month_format - Three letter abbreviation Ex: Oct
   *  - %x => standard_format_specifier - defined by the locale
   *  - %Y-%b-%d => default_date_format - YYYY-Mon-dd
   *
   * Default month format == %b
   * Default weekday format == %a
   */
  template <class date_type,
            class CharT,
            class OutItrT = std::ostreambuf_iterator<CharT, std::char_traits<CharT> > >
  class BOOST_SYMBOL_VISIBLE date_facet : public std::locale::facet {
  public:
    typedef typename date_type::duration_type duration_type;
    // greg_weekday is gregorian_calendar::day_of_week_type
    typedef typename date_type::day_of_week_type day_of_week_type;
    typedef typename date_type::day_type day_type;
    typedef typename date_type::month_type month_type;
    typedef boost::date_time::period<date_type,duration_type> period_type;
    typedef std::basic_string<CharT> string_type;
    typedef CharT                    char_type;
    typedef boost::date_time::period_formatter<CharT>  period_formatter_type;
    typedef boost::date_time::special_values_formatter<CharT>  special_values_formatter_type;
    typedef std::vector<std::basic_string<CharT> > input_collection_type;
    // used for the output of the date_generators
    typedef date_generator_formatter<date_type, CharT> date_gen_formatter_type;
    typedef partial_date<date_type>          partial_date_type;
    typedef nth_kday_of_month<date_type>     nth_kday_type;
    typedef first_kday_of_month<date_type>   first_kday_type;
    typedef last_kday_of_month<date_type>    last_kday_type;
    typedef first_kday_after<date_type>      kday_after_type;
    typedef first_kday_before<date_type>     kday_before_type;
    static const char_type long_weekday_format[3];
    static const char_type short_weekday_format[3];
    static const char_type long_month_format[3];
    static const char_type short_month_format[3];
    static const char_type default_period_separator[4];
    static const char_type standard_format_specifier[3];
    static const char_type iso_format_specifier[7];
    static const char_type iso_format_extended_specifier[9];
    static const char_type default_date_format[9]; // YYYY-Mon-DD
    static std::locale::id id;

#if defined (__SUNPRO_CC) && defined (_RWSTD_VER)
      std::locale::id& __get_id (void) const { return id; }
#endif

    explicit date_facet(::size_t a_ref = 0)
      : std::locale::facet(a_ref),
        //m_format(standard_format_specifier)
        m_format(default_date_format),
        m_month_format(short_month_format),
        m_weekday_format(short_weekday_format)
    {}

    explicit date_facet(const char_type* format_str,
                        const input_collection_type& short_names,
                        ::size_t ref_count = 0)
      : std::locale::facet(ref_count),
        m_format(format_str),
        m_month_format(short_month_format),
        m_weekday_format(short_weekday_format),
        m_month_short_names(short_names)
    {}


    explicit date_facet(const char_type* format_str,
                        period_formatter_type per_formatter = period_formatter_type(),
                        special_values_formatter_type sv_formatter = special_values_formatter_type(),
                        date_gen_formatter_type dg_formatter = date_gen_formatter_type(),
                        ::size_t ref_count = 0)
      : std::locale::facet(ref_count),
        m_format(format_str),
        m_month_format(short_month_format),
        m_weekday_format(short_weekday_format),
        m_period_formatter(per_formatter),
        m_date_gen_formatter(dg_formatter),
        m_special_values_formatter(sv_formatter)
     {}
    void format(const char_type* const format_str) {
      m_format = format_str;
    }
    virtual void set_iso_format()
    {
      m_format = iso_format_specifier;
    }
    virtual void set_iso_extended_format()
    {
      m_format = iso_format_extended_specifier;
    }
    void month_format(const char_type* const format_str) {
      m_month_format = format_str;
    }
    void weekday_format(const char_type* const format_str) {
      m_weekday_format = format_str;
    }

    void period_formatter(period_formatter_type per_formatter) {
      m_period_formatter= per_formatter;
    }
    void special_values_formatter(const special_values_formatter_type& svf)
    {
      m_special_values_formatter = svf;
    }
    void short_weekday_names(const input_collection_type& short_names)
    {
      m_weekday_short_names = short_names;
    }
    void long_weekday_names(const input_collection_type& long_names)
    {
      m_weekday_long_names = long_names;
    }

    void short_month_names(const input_collection_type& short_names)
    {
      m_month_short_names = short_names;
    }

    void long_month_names(const input_collection_type& long_names)
    {
      m_month_long_names = long_names;
    }

    void date_gen_phrase_strings(const input_collection_type& new_strings,
                           typename date_gen_formatter_type::phrase_elements beg_pos=date_gen_formatter_type::first)
    {
      m_date_gen_formatter.elements(new_strings, beg_pos);
    }

    OutItrT put(OutItrT next,
                std::ios_base& a_ios,
                char_type fill_char,
                const date_type& d) const
    {
      if (d.is_special()) {
        return do_put_special(next, a_ios, fill_char, d.as_special());
      }
      //The following line of code required the date to support a to_tm function
      return do_put_tm(next, a_ios, fill_char, to_tm(d), m_format);
    }

    OutItrT put(OutItrT next,
                std::ios_base& a_ios,
                char_type fill_char,
                const duration_type& dd) const
    {
      if (dd.is_special()) {
        return do_put_special(next, a_ios, fill_char, dd.get_rep().as_special());
      }

      typedef std::num_put<CharT, OutItrT> num_put;
      if (std::has_facet<num_put>(a_ios.getloc())) {
        return std::use_facet<num_put>(a_ios.getloc()).put(next, a_ios, fill_char, dd.get_rep().as_number());
      }
      else {
        num_put* f = new num_put();
        std::locale l = std::locale(a_ios.getloc(), f);
        a_ios.imbue(l);
        return f->put(next, a_ios, fill_char, dd.get_rep().as_number());
      }

    }


    OutItrT put(OutItrT next,
                std::ios_base& a_ios,
                char_type fill_char,
                const month_type& m) const
    {
      //if (d.is_special()) {
      //  return do_put_special(next, a_ios, fill_char, d.as_special());
      //}
      //The following line of code required the date to support a to_tm function
      std::tm dtm;
      std::memset(&dtm, 0, sizeof(dtm));
      dtm.tm_mon = m - 1;
      return do_put_tm(next, a_ios, fill_char, dtm, m_month_format);
    }

    //! puts the day of month
    OutItrT put(OutItrT next,
                std::ios_base& a_ios,
                char_type fill_char,
                const day_type& day) const
    {
      std::tm dtm;
      std::memset(&dtm, 0, sizeof(dtm));
      dtm.tm_mday = day.as_number();
      char_type tmp[3] = {'%','d'};
      string_type temp_format(tmp);
      return do_put_tm(next, a_ios, fill_char, dtm, temp_format);
    }

    OutItrT put(OutItrT next,
                std::ios_base& a_ios,
                char_type fill_char,
                const day_of_week_type& dow) const
    {
      //if (d.is_special()) {
      //  return do_put_special(next, a_ios, fill_char, d.as_special());
      //}
      //The following line of code required the date to support a to_tm function
      std::tm dtm;
      std::memset(&dtm, 0, sizeof(dtm));
      dtm.tm_wday = dow;
      return do_put_tm(next, a_ios, fill_char, dtm, m_weekday_format);
    }


    OutItrT put(OutItrT next,
                std::ios_base& a_ios,
                char_type fill_char,
                const period_type& p) const
    {
      return m_period_formatter.put_period(next, a_ios, fill_char, p, *this);
    }

    OutItrT put(OutItrT next,
                std::ios_base& a_ios,
                char_type fill_char,
                const partial_date_type& pd) const
    {
      return m_date_gen_formatter.put_partial_date(next, a_ios, fill_char, pd, *this);
    }

    OutItrT put(OutItrT next,
                std::ios_base& a_ios,
                char_type fill_char,
                const nth_kday_type& nkd) const
    {
      return m_date_gen_formatter.put_nth_kday(next, a_ios, fill_char, nkd, *this);
    }

    OutItrT put(OutItrT next,
                std::ios_base& a_ios,
                char_type fill_char,
                const first_kday_type& fkd) const
    {
      return m_date_gen_formatter.put_first_kday(next, a_ios, fill_char, fkd, *this);
    }

    OutItrT put(OutItrT next,
                std::ios_base& a_ios,
                char_type fill_char,
                const last_kday_type& lkd) const
    {
      return m_date_gen_formatter.put_last_kday(next, a_ios, fill_char, lkd, *this);
    }

    OutItrT put(OutItrT next,
                std::ios_base& a_ios,
                char_type fill_char,
                const kday_before_type& fkb) const
    {
      return m_date_gen_formatter.put_kday_before(next, a_ios, fill_char, fkb, *this);
    }

    OutItrT put(OutItrT next,
                std::ios_base& a_ios,
                char_type fill_char,
                const kday_after_type& fka) const
    {
      return m_date_gen_formatter.put_kday_after(next, a_ios, fill_char, fka, *this);
    }

  protected:
    virtual OutItrT do_put_special(OutItrT next,
                                   std::ios_base& /*a_ios*/,
                                   char_type /*fill_char*/,
                                   const boost::date_time::special_values sv) const
    {
      m_special_values_formatter.put_special(next, sv);
      return next;
    }
    virtual OutItrT do_put_tm(OutItrT next,
                              std::ios_base& a_ios,
                              char_type fill_char,
                              const tm& tm_value,
                              string_type a_format) const
    {
      // update format string with custom names
      if (m_weekday_long_names.size()) {
        boost::algorithm::replace_all(a_format,
                                      long_weekday_format,
                                      m_weekday_long_names[tm_value.tm_wday]);
      }
      if (m_weekday_short_names.size()) {
        boost::algorithm::replace_all(a_format,
                                      short_weekday_format,
                                      m_weekday_short_names[tm_value.tm_wday]);

      }
      if (m_month_long_names.size()) {
        boost::algorithm::replace_all(a_format,
                                      long_month_format,
                                      m_month_long_names[tm_value.tm_mon]);
      }
      if (m_month_short_names.size()) {
        boost::algorithm::replace_all(a_format,
                                      short_month_format,
                                      m_month_short_names[tm_value.tm_mon]);
      }
      // use time_put facet to create final string
      const char_type* p_format = a_format.c_str();
      return std::use_facet<std::time_put<CharT> >(a_ios.getloc()).put(next, a_ios,
                                                                       fill_char,
                                                                       &tm_value,
                                                                       p_format,
                                                                       p_format + a_format.size());
    }
  protected:
    string_type                   m_format;
    string_type                   m_month_format;
    string_type                   m_weekday_format;
    period_formatter_type         m_period_formatter;
    date_gen_formatter_type       m_date_gen_formatter;
    special_values_formatter_type m_special_values_formatter;
    input_collection_type         m_month_short_names;
    input_collection_type         m_month_long_names;
    input_collection_type         m_weekday_short_names;
    input_collection_type         m_weekday_long_names;
  private:
  };

  template <class date_type, class CharT, class OutItrT>
  std::locale::id date_facet<date_type, CharT, OutItrT>::id;

  template <class date_type, class CharT, class OutItrT>
  const typename date_facet<date_type, CharT, OutItrT>::char_type
  date_facet<date_type, CharT, OutItrT>::long_weekday_format[3] = {'%','A'};

  template <class date_type, class CharT, class OutItrT>
  const typename date_facet<date_type, CharT, OutItrT>::char_type
  date_facet<date_type, CharT, OutItrT>::short_weekday_format[3] = {'%','a'};

  template <class date_type, class CharT, class OutItrT>
  const typename date_facet<date_type, CharT, OutItrT>::char_type
  date_facet<date_type, CharT, OutItrT>::long_month_format[3] = {'%','B'};

  template <class date_type, class CharT, class OutItrT>
  const typename date_facet<date_type, CharT, OutItrT>::char_type
  date_facet<date_type, CharT, OutItrT>::short_month_format[3] = {'%','b'};

  template <class date_type, class CharT, class OutItrT>
  const typename date_facet<date_type, CharT, OutItrT>::char_type
  date_facet<date_type, CharT, OutItrT>::default_period_separator[4] = { ' ', '/', ' '};

  template <class date_type, class CharT, class OutItrT>
  const typename date_facet<date_type, CharT, OutItrT>::char_type
  date_facet<date_type, CharT, OutItrT>::standard_format_specifier[3] =
    {'%', 'x' };

  template <class date_type, class CharT, class OutItrT>
  const typename date_facet<date_type, CharT, OutItrT>::char_type
  date_facet<date_type, CharT, OutItrT>::iso_format_specifier[7] =
    {'%', 'Y', '%', 'm', '%', 'd' };

  template <class date_type, class CharT, class OutItrT>
  const typename date_facet<date_type, CharT, OutItrT>::char_type
  date_facet<date_type, CharT, OutItrT>::iso_format_extended_specifier[9] =
    {'%', 'Y', '-', '%', 'm', '-', '%', 'd' };

  template <class date_type, class CharT, class OutItrT>
  const typename date_facet<date_type, CharT, OutItrT>::char_type
  date_facet<date_type, CharT, OutItrT>::default_date_format[9] =
    {'%','Y','-','%','b','-','%','d'};



  //! Input facet
  template <class date_type,
            class CharT,
            class InItrT = std::istreambuf_iterator<CharT, std::char_traits<CharT> > >
  class BOOST_SYMBOL_VISIBLE date_input_facet : public std::locale::facet {
  public:
    typedef typename date_type::duration_type duration_type;
    // greg_weekday is gregorian_calendar::day_of_week_type
    typedef typename date_type::day_of_week_type day_of_week_type;
    typedef typename date_type::day_type day_type;
    typedef typename date_type::month_type month_type;
    typedef typename date_type::year_type year_type;
    typedef boost::date_time::period<date_type,duration_type> period_type;
    typedef std::basic_string<CharT> string_type;
    typedef CharT                    char_type;
    typedef boost::date_time::period_parser<date_type, CharT>  period_parser_type;
    typedef boost::date_time::special_values_parser<date_type,CharT> special_values_parser_type;
    typedef std::vector<std::basic_string<CharT> > input_collection_type;
    typedef format_date_parser<date_type, CharT> format_date_parser_type;
    // date_generators stuff goes here
    typedef date_generator_parser<date_type, CharT> date_gen_parser_type;
    typedef partial_date<date_type>          partial_date_type;
    typedef nth_kday_of_month<date_type>     nth_kday_type;
    typedef first_kday_of_month<date_type>   first_kday_type;
    typedef last_kday_of_month<date_type>    last_kday_type;
    typedef first_kday_after<date_type>      kday_after_type;
    typedef first_kday_before<date_type>     kday_before_type;

    static const char_type long_weekday_format[3];
    static const char_type short_weekday_format[3];
    static const char_type long_month_format[3];
    static const char_type short_month_format[3];
    static const char_type four_digit_year_format[3];
    static const char_type two_digit_year_format[3];
    static const char_type default_period_separator[4];
    static const char_type standard_format_specifier[3];
    static const char_type iso_format_specifier[7];
    static const char_type iso_format_extended_specifier[9];
    static const char_type default_date_format[9]; // YYYY-Mon-DD
    static std::locale::id id;

    explicit date_input_facet(::size_t a_ref = 0)
      : std::locale::facet(a_ref),
        m_format(default_date_format),
        m_month_format(short_month_format),
        m_weekday_format(short_weekday_format),
        m_year_format(four_digit_year_format),
        m_parser(m_format, std::locale::classic())
        // default period_parser & special_values_parser used
    {}

    explicit date_input_facet(const string_type& format_str,
                              ::size_t a_ref = 0)
      : std::locale::facet(a_ref),
        m_format(format_str),
        m_month_format(short_month_format),
        m_weekday_format(short_weekday_format),
        m_year_format(four_digit_year_format),
        m_parser(m_format, std::locale::classic())
        // default period_parser & special_values_parser used
    {}

    explicit date_input_facet(const string_type& format_str,
                              const format_date_parser_type& date_parser,
                              const special_values_parser_type& sv_parser,
                              const period_parser_type& per_parser,
                              const date_gen_parser_type& date_gen_parser,
                              ::size_t ref_count = 0)
      : std::locale::facet(ref_count),
        m_format(format_str),
        m_month_format(short_month_format),
        m_weekday_format(short_weekday_format),
        m_year_format(four_digit_year_format),
        m_parser(date_parser),
        m_date_gen_parser(date_gen_parser),
        m_period_parser(per_parser),
        m_sv_parser(sv_parser)
    {}


    void format(const char_type* const format_str) {
      m_format = format_str;
    }
    virtual void set_iso_format()
    {
      m_format = iso_format_specifier;
    }
    virtual void set_iso_extended_format()
    {
      m_format = iso_format_extended_specifier;
    }
    void month_format(const char_type* const format_str) {
      m_month_format = format_str;
    }
    void weekday_format(const char_type* const format_str) {
      m_weekday_format = format_str;
    }
    void year_format(const char_type* const format_str) {
      m_year_format = format_str;
    }

    void period_parser(period_parser_type per_parser) {
      m_period_parser = per_parser;
    }
    void short_weekday_names(const input_collection_type& weekday_names)
    {
      m_parser.short_weekday_names(weekday_names);
    }
    void long_weekday_names(const input_collection_type& weekday_names)
    {
      m_parser.long_weekday_names(weekday_names);
    }

    void short_month_names(const input_collection_type& month_names)
    {
      m_parser.short_month_names(month_names);
    }

    void long_month_names(const input_collection_type& month_names)
    {
      m_parser.long_month_names(month_names);
    }

    void date_gen_element_strings(const input_collection_type& col)
    {
      m_date_gen_parser.element_strings(col);
    }
    void date_gen_element_strings(const string_type& first,
                                  const string_type& second,
                                  const string_type& third,
                                  const string_type& fourth,
                                  const string_type& fifth,
                                  const string_type& last,
                                  const string_type& before,
                                  const string_type& after,
                                  const string_type& of)

    {
      m_date_gen_parser.element_strings(first,second,third,fourth,fifth,last,before,after,of);
    }

    void special_values_parser(special_values_parser_type sv_parser)
    {
      m_sv_parser = sv_parser;
    }

    InItrT get(InItrT& from,
               InItrT& to,
               std::ios_base& /*a_ios*/,
               date_type& d) const
    {
      d = m_parser.parse_date(from, to, m_format, m_sv_parser);
      return from;
    }
    InItrT get(InItrT& from,
               InItrT& to,
               std::ios_base& /*a_ios*/,
               month_type& m) const
    {
      m = m_parser.parse_month(from, to, m_month_format);
      return from;
    }
    InItrT get(InItrT& from,
               InItrT& to,
               std::ios_base& /*a_ios*/,
               day_of_week_type& wd) const
    {
      wd = m_parser.parse_weekday(from, to, m_weekday_format);
      return from;
    }
    //! Expects 1 or 2 digit day range: 1-31
    InItrT get(InItrT& from,
               InItrT& to,
               std::ios_base& /*a_ios*/,
               day_type& d) const
    {
      d = m_parser.parse_var_day_of_month(from, to);
      return from;
    }
    InItrT get(InItrT& from,
               InItrT& to,
               std::ios_base& /*a_ios*/,
               year_type& y) const
    {
      y = m_parser.parse_year(from, to, m_year_format);
      return from;
    }
    InItrT get(InItrT& from,
               InItrT& to,
               std::ios_base& a_ios,
               duration_type& dd) const
    {
      // skip leading whitespace
      while(std::isspace(*from) && from != to) { ++from; }

      /* num_get.get() will always consume the first character if it
       * is a sign indicator (+/-). Special value strings may begin
       * with one of these signs so we'll need a copy of it
       * in case num_get.get() fails. */
      char_type c = '\0';
      // TODO Are these characters somewhere in the locale?
      if(*from == '-' || *from == '+') {
        c = *from;
      }
      typedef std::num_get<CharT, InItrT> num_get;
      typename duration_type::duration_rep_type val = 0;
      std::ios_base::iostate err = std::ios_base::goodbit;

      if (std::has_facet<num_get>(a_ios.getloc())) {
        from = std::use_facet<num_get>(a_ios.getloc()).get(from, to, a_ios, err, val);
      }
      else {
        num_get* ng = new num_get();
        std::locale l = std::locale(a_ios.getloc(), ng);
        a_ios.imbue(l);
        from = ng->get(from, to, a_ios, err, val);
      }
      if(err & std::ios_base::failbit){
        typedef typename special_values_parser_type::match_results match_results;
        match_results mr;
        if(c == '-' || c == '+') { // was the first character consumed?
          mr.cache += c;
        }
        m_sv_parser.match(from, to, mr);
        if(mr.current_match == match_results::PARSE_ERROR) {
          boost::throw_exception(std::ios_base::failure("Parse failed. No match found for '" + mr.cache + "'"));
          BOOST_DATE_TIME_UNREACHABLE_EXPRESSION(return from); // should never reach
        }
        dd = duration_type(static_cast<special_values>(mr.current_match));
      }
      else {
        dd = duration_type(val);
      }
      return from;
    }
    InItrT get(InItrT& from,
               InItrT& to,
               std::ios_base& a_ios,
               period_type& p) const
    {
      p = m_period_parser.get_period(from, to, a_ios, p, duration_type::unit(), *this);
      return from;
    }
    InItrT get(InItrT& from,
               InItrT& to,
               std::ios_base& a_ios,
               nth_kday_type& nkd) const
    {
      nkd = m_date_gen_parser.get_nth_kday_type(from, to, a_ios, *this);
      return from;
    }
    InItrT get(InItrT& from,
               InItrT& to,
               std::ios_base& a_ios,
               partial_date_type& pd) const
    {

      pd = m_date_gen_parser.get_partial_date_type(from, to, a_ios, *this);
      return from;
    }
    InItrT get(InItrT& from,
               InItrT& to,
               std::ios_base& a_ios,
               first_kday_type& fkd) const
    {
      fkd = m_date_gen_parser.get_first_kday_type(from, to, a_ios, *this);
      return from;
    }
    InItrT get(InItrT& from,
               InItrT& to,
               std::ios_base& a_ios,
               last_kday_type& lkd) const
    {
      lkd = m_date_gen_parser.get_last_kday_type(from, to, a_ios, *this);
      return from;
    }
    InItrT get(InItrT& from,
               InItrT& to,
               std::ios_base& a_ios,
               kday_before_type& fkb) const
    {
      fkb = m_date_gen_parser.get_kday_before_type(from, to, a_ios, *this);
      return from;
    }
    InItrT get(InItrT& from,
               InItrT& to,
               std::ios_base& a_ios,
               kday_after_type& fka) const
    {
      fka = m_date_gen_parser.get_kday_after_type(from, to, a_ios, *this);
      return from;
    }

  protected:
    string_type                   m_format;
    string_type                   m_month_format;
    string_type                   m_weekday_format;
    string_type                   m_year_format;
    format_date_parser_type       m_parser;
    date_gen_parser_type          m_date_gen_parser;
    period_parser_type            m_period_parser;
    special_values_parser_type    m_sv_parser;
  private:
  };


  template <class date_type, class CharT, class OutItrT>
  std::locale::id date_input_facet<date_type, CharT, OutItrT>::id;

  template <class date_type, class CharT, class OutItrT>
  const typename date_input_facet<date_type, CharT, OutItrT>::char_type
  date_input_facet<date_type, CharT, OutItrT>::long_weekday_format[3] = {'%','A'};

  template <class date_type, class CharT, class OutItrT>
  const typename date_input_facet<date_type, CharT, OutItrT>::char_type
  date_input_facet<date_type, CharT, OutItrT>::short_weekday_format[3] = {'%','a'};

  template <class date_type, class CharT, class OutItrT>
  const typename date_input_facet<date_type, CharT, OutItrT>::char_type
  date_input_facet<date_type, CharT, OutItrT>::long_month_format[3] = {'%','B'};

  template <class date_type, class CharT, class OutItrT>
  const typename date_input_facet<date_type, CharT, OutItrT>::char_type
  date_input_facet<date_type, CharT, OutItrT>::short_month_format[3] = {'%','b'};

  template <class date_type, class CharT, class OutItrT>
  const typename date_input_facet<date_type, CharT, OutItrT>::char_type
  date_input_facet<date_type, CharT, OutItrT>::four_digit_year_format[3] = {'%','Y'};

  template <class date_type, class CharT, class OutItrT>
  const typename date_input_facet<date_type, CharT, OutItrT>::char_type
  date_input_facet<date_type, CharT, OutItrT>::two_digit_year_format[3] = {'%','y'};

  template <class date_type, class CharT, class OutItrT>
  const typename date_input_facet<date_type, CharT, OutItrT>::char_type
  date_input_facet<date_type, CharT, OutItrT>::default_period_separator[4] = { ' ', '/', ' '};

  template <class date_type, class CharT, class OutItrT>
  const typename date_input_facet<date_type, CharT, OutItrT>::char_type
  date_input_facet<date_type, CharT, OutItrT>::standard_format_specifier[3] =
    {'%', 'x' };

  template <class date_type, class CharT, class OutItrT>
  const typename date_input_facet<date_type, CharT, OutItrT>::char_type
  date_input_facet<date_type, CharT, OutItrT>::iso_format_specifier[7] =
    {'%', 'Y', '%', 'm', '%', 'd' };

  template <class date_type, class CharT, class OutItrT>
  const typename date_input_facet<date_type, CharT, OutItrT>::char_type
  date_input_facet<date_type, CharT, OutItrT>::iso_format_extended_specifier[9] =
    {'%', 'Y', '-', '%', 'm', '-', '%', 'd' };

  template <class date_type, class CharT, class OutItrT>
  const typename date_input_facet<date_type, CharT, OutItrT>::char_type
  date_input_facet<date_type, CharT, OutItrT>::default_date_format[9] =
    {'%','Y','-','%','b','-','%','d'};

} } // namespaces


#endif

/* date_facet.hpp
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
*/