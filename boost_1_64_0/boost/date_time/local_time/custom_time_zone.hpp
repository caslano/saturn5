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
dONUCZFWn6hCNc4xKpRyjn91W3999ydd188nuiYGXKs6J7mdrKqfIiP5QDGaS8Xv8WnPt00qY89Pnbz9H7bn33WJslV9h4fVBKsmZTLnbN3Wj6ZSnKssfhwt5gbX4n9oubX4n7UtJjMOFr84rbxZTkUVk63Pu0xeJ3usSnFNjDLs/PEwslaGxTGxXI/z0X25DIdKn3XTD6jDnqN2Tuk5NXg3p5S+pr671tWhvXITA2upNk4ump4Z+SZ15Y50f7dYt56HYq1HsX7OFusLu1FHekjQ/J43lnNk7C9m26DSbnqG94PIFJfID72IXGeI1HdPdYXpPE8UesmhRPtniKeIs/+wrR+CNQda3+52zE0HGZYyGEwgLsldTBJ2/wLuyFoCrQcC2OIcyAlYPqiy9DEptM5mRGWdAKNlLFrGoNUALQO0unURkCbcx8ajO2h9M0dJm33FjBkoZAYUrpMAOlvp5uTVicjaGzdOVPoU28/VxxOSXHud9bGdFJE1iW0Gdv13ZhSGptf7lhL9rKndWT9LrcC33EQyDEfiRhnV0c/2KPeKc109mrvMtvHPWz2aN8b0irsFOT2N6dz0GNMJ2ZypjjxUnEKU4UwttD3WNkuYVQda6xk53lEImV7rkIzMAjMytYYdbEpPy8MKwmR0P2MqnMYFy9AjLxwgEDSxX0KwyRqeRhge/sHZzVXzd9Q5vchdZX35VKkoozfyD3QidZIwKnMbKYqYKgqe6LwOds3vR9u/fd1eBPqBEQ3cEe84d2LAWfA0zwqGsH86fbObvutrJv0R/tIndPq84v/q732l3zpBpQ8EKf31SH+Xv/RrdPpFbvpTlyH//tJnB/EPufw7kX9/6ROD0odd/jnk/3e+0m/dR6ePuOV3PvI/ZPok5d9ND2VMdbSbUfB4+plLTe/vIXvcWT+9OIfiyGdg+sYHzYweTYARE3Xm9xkTKIQFJBMzZQMlzfU6x+IQkUBk+L45BdYBI13Sn8Kr/AZYXhm/HUqWTUT7PrNLIPCzEDrVm91+bO3XpR9b/05lAL0/yhSuqLHl04jyaduNfxpriAnoWRQkk5M7ZgbYnohKVJ32dG7oSbR/WKvfujbzwK/DZp4Km9lqbWYiQuOiyTKWe970fGy5Ev15YtNZn8j8k+MgN2u37U1Zq+8+zy2iS8zUfG0KkBef0uMOHs7lXLGzF9khw0lW7LPCrti27F+GJuqaOc6sev7DYruqWuHK62yBZYECQroYd0qxzakZUTawMdKsIfXJ1f+9tP6jfvlnUjeFvG0KH1VNASp+DGV3N5M7Y+jfjXK6yy2nzIW2ehfbcjomhOosJZrx3RB2ln/rniw/T/Srlnyb1Wxg4pYjfYwXd0cwbmSvoTBKynzX4pv64JgpT3NQcG9GMyUwltZAnbAZqhY3CjETh+9Fy4JQ9PpofXc8SAo0ZwXaGM8v50zhrDL6kVEzFOybbYZew87uTp+SkfRz420ZNINbc+7IiXWZmqqlHwrCAhzqSnfHBUa9V2BkHPyFq0BxKFA80AZne3dQlxpgNKnZXZS4hsLliuwAt7WuNXMhTGg6ClEzBK1aRwpJkAUvbesv3kKESUJTHiYHyxYFhdtmKs6A9qG1TZEcQZpM9aBQVIeixYM5mKrmqGUgN2T6XGoilqMgUWf9RI6qgWZSTA3J1nf5gF+uBg4CpoN/Y0CqmJj2iKRdiws5tr+Q22iawz4iVJSxrcpYAM0WkBq1Vj+QOpc3HuaakrXUlLeAqTdu4D7kfD6zOVWNSpVAVAUC9vfm1ET1uwa/7/Gn/zWk/3tY/Y+hdHqmPWILEge4EY9qNzC3Z46ZkuPlkwi+ydkVN6ocCbQe0jGjNtD2NnM=
*/