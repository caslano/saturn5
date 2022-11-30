#ifndef DATE_TIME_DATE_NAMES_PUT_HPP___
#define DATE_TIME_DATE_NAMES_PUT_HPP___

/* Copyright (c) 2002-2005 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */


#include <boost/date_time/locale_config.hpp> // set BOOST_DATE_TIME_NO_LOCALE

#ifndef BOOST_DATE_TIME_NO_LOCALE

#include <boost/date_time/compiler_config.hpp>
#include <boost/date_time/special_defs.hpp>
#include <boost/date_time/date_defs.hpp>
#include <boost/date_time/parse_format_base.hpp>
#include <boost/lexical_cast.hpp>
#include <locale>


namespace boost {
namespace date_time {

    //! Output facet base class for gregorian dates.
    /*! This class is a base class for date facets used to localize the
     *  names of months and the names of days in the week.
     *
     * Requirements of Config
     *  - define an enumeration month_enum that enumerates the months.
     *    The enumeration should be '1' based eg: Jan==1
     *  - define as_short_string and as_long_string
     *
     * (see langer & kreft p334).
     *
     */
    template<class Config,
             class charT = char,
             class OutputIterator = std::ostreambuf_iterator<charT> >
    class BOOST_SYMBOL_VISIBLE date_names_put : public std::locale::facet
    {
    public:
      date_names_put() {}
      typedef OutputIterator iter_type;
      typedef typename Config::month_type month_type;
      typedef typename Config::month_enum month_enum;
      typedef typename Config::weekday_enum weekday_enum;
      typedef typename Config::special_value_enum special_value_enum;
      //typedef typename Config::format_type format_type;
      typedef std::basic_string<charT> string_type;
      typedef charT char_type;
      static const char_type default_special_value_names[3][17];
      static const char_type separator[2];

      static std::locale::id id;

#if defined (__SUNPRO_CC) && defined (_RWSTD_VER)
      std::locale::id& __get_id (void) const { return id; }
#endif

      void put_special_value(iter_type& oitr, special_value_enum sv) const
      {
        do_put_special_value(oitr, sv);
      }
      void put_month_short(iter_type& oitr, month_enum moy) const
      {
        do_put_month_short(oitr, moy);
      }
      void put_month_long(iter_type& oitr, month_enum moy) const
      {
        do_put_month_long(oitr, moy);
      }
      void put_weekday_short(iter_type& oitr, weekday_enum wd) const
      {
        do_put_weekday_short(oitr, wd);
      }
      void put_weekday_long(iter_type& oitr, weekday_enum wd) const
      {
        do_put_weekday_long(oitr, wd);
      }
      bool has_date_sep_chars() const
      {
        return do_has_date_sep_chars();
      }
      void year_sep_char(iter_type& oitr) const
      {
        do_year_sep_char(oitr);
      }
      //! char between year-month
      void month_sep_char(iter_type& oitr) const
      {
        do_month_sep_char(oitr);
      }
      //! Char to separate month-day
      void day_sep_char(iter_type& oitr) const
      {
        do_day_sep_char(oitr);
      }
      //! Determines the order to put the date elements
      ymd_order_spec date_order() const
      {
        return do_date_order();
      }
      //! Determines if month is displayed as integer, short or long string
      month_format_spec month_format() const
      {
        return do_month_format();
      }

    protected:
      //! Default facet implementation uses month_type defaults
      virtual void do_put_month_short(iter_type& oitr, month_enum moy) const
      {
        month_type gm(moy);
        charT c = '\0';
        put_string(oitr, gm.as_short_string(c));
      }
      //! Default facet implementation uses month_type defaults
      virtual void do_put_month_long(iter_type& oitr,
                                     month_enum moy) const
      {
        month_type gm(moy);
        charT c = '\0';
        put_string(oitr, gm.as_long_string(c));
      }
      //! Default facet implementation for special value types
      virtual void do_put_special_value(iter_type& oitr, special_value_enum sv) const
      {
        if(sv <= 2) { // only output not_a_date_time, neg_infin, or pos_infin
          string_type s(default_special_value_names[sv]);
          put_string(oitr, s);
        }
      }
      virtual void do_put_weekday_short(iter_type&, weekday_enum) const
      {
      }
      virtual void do_put_weekday_long(iter_type&, weekday_enum) const
      {
      }
      virtual bool do_has_date_sep_chars() const
      {
        return true;
      }
      virtual void do_year_sep_char(iter_type& oitr) const
      {
        string_type s(separator);
        put_string(oitr, s);
      }
      //! char between year-month
      virtual void do_month_sep_char(iter_type& oitr) const
      {
        string_type s(separator);
        put_string(oitr, s);
      }
      //! Char to separate month-day
      virtual void do_day_sep_char(iter_type& oitr) const
      {
        string_type s(separator); //put in '-'
        put_string(oitr, s);
      }
      //! Default for date order
      virtual ymd_order_spec do_date_order() const
      {
        return ymd_order_iso;
      }
      //! Default month format
      virtual month_format_spec do_month_format() const
      {
        return month_as_short_string;
      }
      void put_string(iter_type& oi, const charT* const s) const
      {
        string_type s1(boost::lexical_cast<string_type>(s));
        typename string_type::iterator si,end;
        for (si=s1.begin(), end=s1.end(); si!=end; si++, oi++) {
          *oi = *si;
        }
      }
      void put_string(iter_type& oi, const string_type& s1) const
      {
        typename string_type::const_iterator si,end;
        for (si=s1.begin(), end=s1.end(); si!=end; si++, oi++) {
          *oi = *si;
        }
      }
    };

    template<class Config, class charT, class OutputIterator>
    const typename date_names_put<Config, charT, OutputIterator>::char_type
    date_names_put<Config, charT, OutputIterator>::default_special_value_names[3][17] = {
      {'n','o','t','-','a','-','d','a','t','e','-','t','i','m','e'},
      {'-','i','n','f','i','n','i','t','y'},
      {'+','i','n','f','i','n','i','t','y'} };

    template<class Config, class charT, class OutputIterator>
    const typename date_names_put<Config, charT, OutputIterator>::char_type
    date_names_put<Config, charT, OutputIterator>::separator[2] =
      {'-', '\0'} ;


    //! Generate storage location for a std::locale::id
    template<class Config, class charT, class OutputIterator>
    std::locale::id date_names_put<Config, charT, OutputIterator>::id;

    //! A date name output facet that takes an array of char* to define strings
    template<class Config,
             class charT = char,
             class OutputIterator = std::ostreambuf_iterator<charT> >
    class BOOST_SYMBOL_VISIBLE all_date_names_put : public date_names_put<Config, charT, OutputIterator>
    {
    public:
      all_date_names_put(const charT* const month_short_names[],
                         const charT* const month_long_names[],
                         const charT* const special_value_names[],
                         const charT* const weekday_short_names[],
                         const charT* const weekday_long_names[],
                         charT separator_char = '-',
                         ymd_order_spec order_spec = ymd_order_iso,
                         month_format_spec month_format = month_as_short_string) :
        month_short_names_(month_short_names),
        month_long_names_(month_long_names),
        special_value_names_(special_value_names),
        weekday_short_names_(weekday_short_names),
        weekday_long_names_(weekday_long_names),
        order_spec_(order_spec),
        month_format_spec_(month_format)
      {
        separator_char_[0] = separator_char;
        separator_char_[1] = '\0';

      }
      typedef OutputIterator iter_type;
      typedef typename Config::month_enum month_enum;
      typedef typename Config::weekday_enum weekday_enum;
      typedef typename Config::special_value_enum special_value_enum;

      const charT* const* get_short_month_names() const
      {
        return month_short_names_;
      }
      const charT* const* get_long_month_names() const
      {
        return month_long_names_;
      }
      const charT* const* get_special_value_names() const
      {
        return special_value_names_;
      }
      const charT* const* get_short_weekday_names()const
      {
        return weekday_short_names_;
      }
      const charT* const* get_long_weekday_names()const
      {
        return weekday_long_names_;
      }

    protected:
      //! Generic facet that takes array of chars
      virtual void do_put_month_short(iter_type& oitr, month_enum moy) const
      {
        this->put_string(oitr, month_short_names_[moy-1]);
      }
      //! Long month names
      virtual void do_put_month_long(iter_type& oitr, month_enum moy) const
      {
        this->put_string(oitr, month_long_names_[moy-1]);
      }
      //! Special values names
      virtual void do_put_special_value(iter_type& oitr, special_value_enum sv) const
      {
        this->put_string(oitr, special_value_names_[sv]);
      }
      virtual void do_put_weekday_short(iter_type& oitr, weekday_enum wd) const
      {
        this->put_string(oitr, weekday_short_names_[wd]);
      }
      virtual void do_put_weekday_long(iter_type& oitr, weekday_enum wd) const
      {
        this->put_string(oitr, weekday_long_names_[wd]);
      }
      //! char between year-month
      virtual void do_month_sep_char(iter_type& oitr) const
      {
        this->put_string(oitr, separator_char_);
      }
      //! Char to separate month-day
      virtual void do_day_sep_char(iter_type& oitr) const
      {
        this->put_string(oitr, separator_char_);
      }
      //! Set the date ordering
      virtual ymd_order_spec do_date_order() const
      {
        return order_spec_;
      }
      //! Set the date ordering
      virtual month_format_spec do_month_format() const
      {
        return month_format_spec_;
      }

    private:
      const charT* const* month_short_names_;
      const charT* const* month_long_names_;
      const charT* const* special_value_names_;
      const charT* const* weekday_short_names_;
      const charT* const* weekday_long_names_;
      charT separator_char_[2];
      ymd_order_spec order_spec_;
      month_format_spec month_format_spec_;
    };

} } //namespace boost::date_time

#endif //BOOST_NO_STD_LOCALE

#endif

/* date_names_put.hpp
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
*/