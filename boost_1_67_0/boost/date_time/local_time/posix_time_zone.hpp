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