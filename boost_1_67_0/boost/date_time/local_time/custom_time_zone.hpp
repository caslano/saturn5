#ifndef LOCAL_TIME_CUSTOM_TIME_ZONE_HPP__
#define LOCAL_TIME_CUSTOM_TIME_ZONE_HPP__

/* Copyright (c) 2003-2005 CrystalClear Software, Inc.
 * Subject to the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include "boost/date_time/time_zone_base.hpp"
#include "boost/date_time/time_zone_names.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"
#include "boost/date_time/local_time/dst_transition_day_rules.hpp"
#include "boost/date_time/string_convert.hpp"
//#include "boost/date_time/special_defs.hpp"
#include "boost/shared_ptr.hpp"

namespace boost {
namespace local_time {

  //typedef boost::date_time::time_zone_names time_zone_names;
  typedef boost::date_time::dst_adjustment_offsets<boost::posix_time::time_duration> dst_adjustment_offsets;
  //typedef boost::date_time::time_zone_base<boost::posix_time::ptime> time_zone;
  typedef boost::shared_ptr<dst_calc_rule> dst_calc_rule_ptr;

  //! A real time zone
  template<class CharT>
  class custom_time_zone_base : public date_time::time_zone_base<posix_time::ptime,CharT> {
  public:
    typedef boost::posix_time::time_duration time_duration_type;
    typedef date_time::time_zone_base<posix_time::ptime,CharT> base_type;
    typedef typename base_type::string_type string_type;
    typedef typename base_type::stringstream_type stringstream_type;
    typedef date_time::time_zone_names_base<CharT> time_zone_names;
    typedef CharT char_type;

    custom_time_zone_base(const time_zone_names& zone_names,
                     const time_duration_type& utc_offset,
                     const dst_adjustment_offsets& dst_shift,
                     boost::shared_ptr<dst_calc_rule> calc_rule) :
      zone_names_(zone_names),
      base_utc_offset_(utc_offset),
      dst_offsets_(dst_shift),
      dst_calc_rules_(calc_rule)
    {}
    virtual ~custom_time_zone_base() {}
    virtual string_type dst_zone_abbrev() const
    {
      return zone_names_.dst_zone_abbrev();
    }
    virtual string_type std_zone_abbrev() const
    {
      return zone_names_.std_zone_abbrev();
    }
    virtual string_type dst_zone_name() const
    {
      return zone_names_.dst_zone_name();
    }
    virtual string_type std_zone_name() const
    {
      return zone_names_.std_zone_name();
    }
    //! True if zone uses daylight savings adjustments
    virtual bool has_dst() const
    {
      return (bool) dst_calc_rules_; //if calc_rule is set the tz has dst
    }
    //! Local time that DST starts -- NADT if has_dst is false
    virtual posix_time::ptime dst_local_start_time(gregorian::greg_year y) const
    {
      gregorian::date d(gregorian::not_a_date_time);
      if (dst_calc_rules_) {
        d = dst_calc_rules_->start_day(y);
      }
      return posix_time::ptime(d, dst_offsets_.dst_start_offset_);
    }
    //! Local time that DST ends -- NADT if has_dst is false
    virtual posix_time::ptime dst_local_end_time(gregorian::greg_year y) const
    {
      gregorian::date d(gregorian::not_a_date_time);
      if (dst_calc_rules_) {
        d = dst_calc_rules_->end_day(y);
      }
      return posix_time::ptime(d, dst_offsets_.dst_end_offset_);
    }
    //! Base offset from UTC for zone (eg: -07:30:00)
    virtual time_duration_type base_utc_offset() const
    {
      return base_utc_offset_;
    }
    //! Adjustment forward or back made while DST is in effect
    virtual time_duration_type dst_offset() const
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
    time_duration_type base_utc_offset_;
    dst_adjustment_offsets dst_offsets_;
    boost::shared_ptr<dst_calc_rule> dst_calc_rules_;
  };

  typedef custom_time_zone_base<char> custom_time_zone;

} }//namespace



#endif

/* custom_time_zone.hpp
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
*/