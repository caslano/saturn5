#ifndef _DATE_TIME_POSIX_TIME_ZONE__
#define _DATE_TIME_POSIX_TIME_ZONE__

/* Copyright (c) 2003-2005 CrystalClear Software, Inc.
 * Subject to the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include <string>
#include <sstream>
#include <stdexcept>
#include <boost/tokenizer.hpp>
#include <boost/throw_exception.hpp>
#include <boost/date_time/compiler_config.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/time_zone_names.hpp>
#include <boost/date_time/time_zone_base.hpp>
#include <boost/date_time/local_time/dst_transition_day_rules.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/string_convert.hpp>
#include <boost/date_time/time_parsing.hpp>

namespace boost{
namespace local_time{

  //! simple exception for UTC and Daylight savings start/end offsets
  struct BOOST_SYMBOL_VISIBLE bad_offset : public std::out_of_range
  {
    bad_offset(std::string const& msg = std::string()) :
      std::out_of_range(std::string("Offset out of range: " + msg)) {}
  };
  //! simple exception for UTC daylight savings adjustment
  struct BOOST_SYMBOL_VISIBLE bad_adjustment : public std::out_of_range
  {
    bad_adjustment(std::string const& msg = std::string()) :
      std::out_of_range(std::string("Adjustment out of range: " + msg)) {}
  };

  typedef boost::date_time::dst_adjustment_offsets<boost::posix_time::time_duration> dst_adjustment_offsets;

  //! A time zone class constructed from a POSIX time zone string
  /*! A POSIX time zone string takes the form of:<br>
   * "std offset dst [offset],start[/time],end[/time]" (w/no spaces)
   * 'std' specifies the abbrev of the time zone.<br>
   * 'offset' is the offset from UTC.<br>
   * 'dst' specifies the abbrev of the time zone during daylight savings time.<br>
   * The second offset is how many hours changed during DST. Default=1<br>
   * 'start' and'end' are the dates when DST goes into (and out of) effect.<br>
   * 'offset' takes the form of: [+|-]hh[:mm[:ss]] {h=0-23, m/s=0-59}<br>
   * 'time' and 'offset' take the same form. Time defaults=02:00:00<br>
   * 'start' and 'end' can be one of three forms:<br>
   * Mm.w.d {month=1-12, week=1-5 (5 is always last), day=0-6}<br>
   * Jn {n=1-365 Feb29 is never counted}<br>
   * n  {n=0-365 Feb29 is counted in leap years}<br>
   * Example "PST-5PDT01:00:00,M4.1.0/02:00:00,M10.1.0/02:00:00"
   * <br>
   * Exceptions will be thrown under these conditions:<br>
   * An invalid date spec (see date class)<br>
   * A boost::local_time::bad_offset exception will be thrown for:<br>
   * A DST start or end offset that is negative or more than 24 hours<br>
   * A UTC zone that is greater than +14 or less than -12 hours<br>
   * A boost::local_time::bad_adjustment exception will be thrown for:<br>
   * A DST adjustment that is 24 hours or more (positive or negative)<br>
   *
   * Note that UTC zone offsets can be greater than +12:
   * http://www.worldtimezone.com/utc/utc+1200.html
   */
  template<class CharT>
  class BOOST_SYMBOL_VISIBLE posix_time_zone_base : public date_time::time_zone_base<posix_time::ptime,CharT> {
  public:
    typedef boost::posix_time::time_duration time_duration_type;
    typedef date_time::time_zone_names_base<CharT> time_zone_names;
    typedef date_time::time_zone_base<posix_time::ptime,CharT> base_type;
    typedef typename base_type::string_type string_type;
    typedef CharT char_type;
    typedef typename base_type::stringstream_type stringstream_type;
    typedef boost::char_separator<char_type, std::char_traits<char_type> > char_separator_type;
    typedef boost::tokenizer<char_separator_type,
                             typename string_type::const_iterator,
                             string_type> tokenizer_type;
    typedef typename tokenizer_type::iterator tokenizer_iterator_type;

    //! Construct from a POSIX time zone string
    posix_time_zone_base(const string_type& s) :
      //zone_names_("std_name","std_abbrev","no-dst","no-dst"),
      zone_names_(),
      has_dst_(false),
      base_utc_offset_(posix_time::hours(0)),
      dst_offsets_(posix_time::hours(0),posix_time::hours(0),posix_time::hours(0)),
      dst_calc_rules_()
    {
#ifdef __HP_aCC
      // Work around bug in aC++ compiler: see QXCR1000880488 in the
      // HP bug tracking system
      const char_type sep_chars[2] = {',',0};
#else
      const char_type sep_chars[2] = {','};
#endif
      char_separator_type sep(sep_chars);
      tokenizer_type tokens(s, sep);
      tokenizer_iterator_type it = tokens.begin(), end = tokens.end();
      if (it == end)
        BOOST_THROW_EXCEPTION(std::invalid_argument("Could not parse time zone name"));
      calc_zone(*it++);
      if(has_dst_)
      {
        if (it == end)
          BOOST_THROW_EXCEPTION(std::invalid_argument("Could not parse DST begin time"));
        string_type dst_begin = *it++;

        if (it == end)
          BOOST_THROW_EXCEPTION(std::invalid_argument("Could not parse DST end time"));
        string_type dst_end = *it;
        calc_rules(dst_begin, dst_end);
      }
    }
    virtual ~posix_time_zone_base() {}
    //!String for the zone when not in daylight savings (eg: EST)
    virtual string_type std_zone_abbrev()const
    {
      return zone_names_.std_zone_abbrev();
    }
    //!String for the timezone when in daylight savings (eg: EDT)
    /*! For those time zones that have no DST, an empty string is used */
    virtual string_type dst_zone_abbrev() const
    {
      return zone_names_.dst_zone_abbrev();
    }
    //!String for the zone when not in daylight savings (eg: Eastern Standard Time)
    /*! The full STD name is not extracted from the posix time zone string.
     * Therefore, the STD abbreviation is used in it's place */
    virtual string_type std_zone_name()const
    {
      return zone_names_.std_zone_name();
    }
    //!String for the timezone when in daylight savings (eg: Eastern Daylight Time)
    /*! The full DST name is not extracted from the posix time zone string.
     * Therefore, the STD abbreviation is used in it's place. For time zones
     * that have no DST, an empty string is used */
    virtual string_type dst_zone_name()const
    {
      return zone_names_.dst_zone_name();
    }
    //! True if zone uses daylight savings adjustments otherwise false
    virtual bool has_dst()const
    {
      return has_dst_;
    }
    //! Local time that DST starts -- NADT if has_dst is false
    virtual posix_time::ptime dst_local_start_time(gregorian::greg_year y)const
    {
      gregorian::date d(gregorian::not_a_date_time);
      if(has_dst_)
      {
        d = dst_calc_rules_->start_day(y);
      }
      return posix_time::ptime(d, dst_offsets_.dst_start_offset_);
    }
    //! Local time that DST ends -- NADT if has_dst is false
    virtual posix_time::ptime dst_local_end_time(gregorian::greg_year y)const
    {
      gregorian::date d(gregorian::not_a_date_time);
      if(has_dst_)
      {
        d = dst_calc_rules_->end_day(y);
      }
      return posix_time::ptime(d, dst_offsets_.dst_end_offset_);
    }
    //! Base offset from UTC for zone (eg: -07:30:00)
    virtual time_duration_type base_utc_offset()const
    {
      return base_utc_offset_;
    }
    //! Adjustment forward or back made while DST is in effect
    virtual time_duration_type dst_offset()const
    {
      return dst_offsets_.dst_adjust_;
    }

    //! Returns a POSIX time_zone string for this object
    virtual string_type to_posix_string() const
    {
      // std offset dst [offset],start[/time],end[/time] - w/o spaces
      stringstream_type ss;
      ss.fill('0');
      boost::shared_ptr<dst_calc_rule> no_rules;
      // std
      ss << std_zone_abbrev();
      // offset
      if(base_utc_offset().is_negative()) {
        // inverting the sign guarantees we get two digits
        ss << '-' << std::setw(2) << base_utc_offset().invert_sign().hours();
      }
      else {
        ss << '+' << std::setw(2) << base_utc_offset().hours();
      }
      if(base_utc_offset().minutes() != 0 || base_utc_offset().seconds() != 0) {
        ss << ':' << std::setw(2) << base_utc_offset().minutes();
        if(base_utc_offset().seconds() != 0) {
          ss << ':' << std::setw(2) << base_utc_offset().seconds();
        }
      }
      if(dst_calc_rules_ != no_rules) {
        // dst
        ss << dst_zone_abbrev();
        // dst offset
        if(dst_offset().is_negative()) {
        // inverting the sign guarantees we get two digits
          ss << '-' << std::setw(2) << dst_offset().invert_sign().hours();
        }
        else {
          ss << '+' << std::setw(2) << dst_offset().hours();
        }
        if(dst_offset().minutes() != 0 || dst_offset().seconds() != 0) {
          ss << ':' << std::setw(2) << dst_offset().minutes();
          if(dst_offset().seconds() != 0) {
            ss << ':' << std::setw(2) << dst_offset().seconds();
          }
        }
        // start/time
        ss << ',' << date_time::convert_string_type<char, char_type>(dst_calc_rules_->start_rule_as_string()) << '/'
           << std::setw(2) << dst_offsets_.dst_start_offset_.hours() << ':'
           << std::setw(2) << dst_offsets_.dst_start_offset_.minutes();
        if(dst_offsets_.dst_start_offset_.seconds() != 0) {
          ss << ':' << std::setw(2) << dst_offsets_.dst_start_offset_.seconds();
        }
        // end/time
        ss << ',' << date_time::convert_string_type<char, char_type>(dst_calc_rules_->end_rule_as_string()) << '/'
           << std::setw(2) << dst_offsets_.dst_end_offset_.hours() << ':'
           << std::setw(2) << dst_offsets_.dst_end_offset_.minutes();
        if(dst_offsets_.dst_end_offset_.seconds() != 0) {
          ss << ':' << std::setw(2) << dst_offsets_.dst_end_offset_.seconds();
        }
      }

      return ss.str();
    }
  private:
    time_zone_names zone_names_;
    bool has_dst_;
    time_duration_type base_utc_offset_;
    dst_adjustment_offsets dst_offsets_;
    boost::shared_ptr<dst_calc_rule> dst_calc_rules_;

    /*! Extract time zone abbreviations for STD & DST as well
     * as the offsets for the time shift that occurs and how
     * much of a shift. At this time full time zone names are
     * NOT extracted so the abbreviations are used in their place */
    void calc_zone(const string_type& obj){
      const char_type empty_string[2] = {'\0'};
      stringstream_type ss(empty_string);
      typename string_type::const_pointer sit = obj.c_str(), obj_end = sit + obj.size();
      string_type l_std_zone_abbrev, l_dst_zone_abbrev;

      // get 'std' name/abbrev
      while(std::isalpha(*sit)){
        ss << *sit++;
      }
      l_std_zone_abbrev = ss.str();
      ss.str(empty_string);

      // get UTC offset
      if(sit != obj_end){
        // get duration
        while(sit != obj_end && !std::isalpha(*sit)){
          ss << *sit++;
        }
        base_utc_offset_ = date_time::str_from_delimited_time_duration<time_duration_type,char_type>(ss.str());
        ss.str(empty_string);

        // base offset must be within range of -12 hours to +14 hours
        if(base_utc_offset_ < time_duration_type(-12,0,0) ||
          base_utc_offset_ > time_duration_type(14,0,0))
        {
          boost::throw_exception(bad_offset(posix_time::to_simple_string(base_utc_offset_)));
        }
      }

      // get DST data if given
      if(sit != obj_end){
        has_dst_ = true;

        // get 'dst' name/abbrev
        while(sit != obj_end && std::isalpha(*sit)){
          ss << *sit++;
        }
        l_dst_zone_abbrev = ss.str();
        ss.str(empty_string);

        // get DST offset if given
        if(sit != obj_end){
          // get duration
          while(sit != obj_end && !std::isalpha(*sit)){
            ss << *sit++;
          }
          dst_offsets_.dst_adjust_ = date_time::str_from_delimited_time_duration<time_duration_type,char_type>(ss.str());
          ss.str(empty_string);
        }
        else{ // default DST offset
          dst_offsets_.dst_adjust_ = posix_time::hours(1);
        }

        // adjustment must be within +|- 1 day
        if(dst_offsets_.dst_adjust_ <= time_duration_type(-24,0,0) ||
            dst_offsets_.dst_adjust_ >= time_duration_type(24,0,0))
        {
          boost::throw_exception(bad_adjustment(posix_time::to_simple_string(dst_offsets_.dst_adjust_)));
        }
      }
      // full names not extracted so abbrevs used in their place
      zone_names_ = time_zone_names(l_std_zone_abbrev, l_std_zone_abbrev, l_dst_zone_abbrev, l_dst_zone_abbrev);
    }

    void calc_rules(const string_type& start, const string_type& end){
#ifdef __HP_aCC
      // Work around bug in aC++ compiler: see QXCR1000880488 in the
      // HP bug tracking system
      const char_type sep_chars[2] = {'/',0};
#else
      const char_type sep_chars[2] = {'/'};
#endif
      char_separator_type sep(sep_chars);
      tokenizer_type st_tok(start, sep);
      tokenizer_type et_tok(end, sep);
      tokenizer_iterator_type sit = st_tok.begin();
      tokenizer_iterator_type eit = et_tok.begin();

      // generate date spec
      char_type x = string_type(*sit).at(0);
      if(x == 'M'){
        M_func(*sit, *eit);
      }
      else if(x == 'J'){
        julian_no_leap(*sit, *eit);
      }
      else{
        julian_day(*sit, *eit);
      }

      ++sit;
      ++eit;
      // generate durations
      // starting offset
      if(sit != st_tok.end()){
        dst_offsets_.dst_start_offset_ =  date_time::str_from_delimited_time_duration<time_duration_type,char_type>(*sit);
      }
      else{
        // default
        dst_offsets_.dst_start_offset_ = posix_time::hours(2);
      }
      // start/end offsets must fall on given date
      if(dst_offsets_.dst_start_offset_ < time_duration_type(0,0,0) ||
          dst_offsets_.dst_start_offset_ >= time_duration_type(24,0,0))
      {
        boost::throw_exception(bad_offset(posix_time::to_simple_string(dst_offsets_.dst_start_offset_)));
      }

      // ending offset
      if(eit != et_tok.end()){
        dst_offsets_.dst_end_offset_ =  date_time::str_from_delimited_time_duration<time_duration_type,char_type>(*eit);
      }
      else{
        // default
        dst_offsets_.dst_end_offset_ = posix_time::hours(2);
      }
      // start/end offsets must fall on given date
      if(dst_offsets_.dst_end_offset_ < time_duration_type(0,0,0) ||
        dst_offsets_.dst_end_offset_ >= time_duration_type(24,0,0))
      {
        boost::throw_exception(bad_offset(posix_time::to_simple_string(dst_offsets_.dst_end_offset_)));
      }
    }

    /* Parses out a start/end date spec from a posix time zone string.
     * Date specs come in three possible formats, this function handles
     * the 'M' spec. Ex "M2.2.4" => 2nd month, 2nd week, 4th day .
     */
    void M_func(const string_type& s, const string_type& e){
      typedef gregorian::nth_kday_of_month nkday;
      unsigned short sm=0,sw=0,sd=0,em=0,ew=0,ed=0; // start/end month,week,day
#ifdef __HP_aCC
      // Work around bug in aC++ compiler: see QXCR1000880488 in the
      // HP bug tracking system
      const char_type sep_chars[3] = {'M','.',0};
#else
      const char_type sep_chars[3] = {'M','.'};
#endif
      char_separator_type sep(sep_chars);
      tokenizer_type stok(s, sep), etok(e, sep);

      tokenizer_iterator_type it = stok.begin();
      sm = lexical_cast<unsigned short>(*it++);
      sw = lexical_cast<unsigned short>(*it++);
      sd = lexical_cast<unsigned short>(*it);

      it = etok.begin();
      em = lexical_cast<unsigned short>(*it++);
      ew = lexical_cast<unsigned short>(*it++);
      ed = lexical_cast<unsigned short>(*it);

      dst_calc_rules_ = shared_ptr<dst_calc_rule>(
        new nth_kday_dst_rule(
          nth_last_dst_rule::start_rule(
            static_cast<nkday::week_num>(sw),sd,sm),
          nth_last_dst_rule::start_rule(
            static_cast<nkday::week_num>(ew),ed,em)
          )
      );
    }

    //! Julian day. Feb29 is never counted, even in leap years
    // expects range of 1-365
    void julian_no_leap(const string_type& s, const string_type& e){
      typedef gregorian::gregorian_calendar calendar;
      const unsigned short year = 2001; // Non-leap year
      unsigned short sm=1;
      int sd=0;
      sd = lexical_cast<int>(s.substr(1)); // skip 'J'
      while(sd >= calendar::end_of_month_day(year,sm)){
        sd -= calendar::end_of_month_day(year,sm++);
      }
      unsigned short em=1;
      int ed=0;
      ed = lexical_cast<int>(e.substr(1)); // skip 'J'
      while(ed > calendar::end_of_month_day(year,em)){
        ed -= calendar::end_of_month_day(year,em++);
      }

      dst_calc_rules_ = shared_ptr<dst_calc_rule>(
        new partial_date_dst_rule(
          partial_date_dst_rule::start_rule(
            static_cast<unsigned short>(sd), static_cast<date_time::months_of_year>(sm)),
          partial_date_dst_rule::end_rule(
            static_cast<unsigned short>(ed), static_cast<date_time::months_of_year>(em))
          )
      );
    }

    //! Julian day. Feb29 is always counted, but exception thrown in non-leap years
    // expects range of 0-365
    void julian_day(const string_type& s, const string_type& e){
      int sd=0, ed=0;
      sd = lexical_cast<int>(s);
      ed = lexical_cast<int>(e);
      dst_calc_rules_ = shared_ptr<dst_calc_rule>(
        new partial_date_dst_rule(
          partial_date_dst_rule::start_rule(++sd),// args are 0-365
          partial_date_dst_rule::end_rule(++ed) // pd expects 1-366
          )
      );
    }

    //! helper function used when throwing exceptions
    static std::string td_as_string(const time_duration_type& td)
    {
      std::string s;
#if defined(USE_DATE_TIME_PRE_1_33_FACET_IO)
      s = posix_time::to_simple_string(td);
#else
      std::stringstream ss;
      ss << td;
      s = ss.str();
#endif
      return s;
    }
  };

  typedef posix_time_zone_base<char> posix_time_zone;

} } // namespace boost::local_time


#endif // _DATE_TIME_POSIX_TIME_ZONE__

/* posix_time_zone.hpp
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
*/