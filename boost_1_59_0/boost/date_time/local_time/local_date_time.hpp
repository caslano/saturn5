#ifndef LOCAL_TIME_LOCAL_DATE_TIME_HPP__
#define LOCAL_TIME_LOCAL_DATE_TIME_HPP__

/* Copyright (c) 2003-2005 CrystalClear Software, Inc.
 * Subject to the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include <string>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <boost/shared_ptr.hpp>
#include <boost/throw_exception.hpp>
#include <boost/date_time/time.hpp>
#include <boost/date_time/posix_time/posix_time.hpp> //todo remove?
#include <boost/date_time/compiler_config.hpp>
#include <boost/date_time/dst_rules.hpp>
#include <boost/date_time/time_zone_base.hpp>
#include <boost/date_time/special_defs.hpp>
#include <boost/date_time/time_resolution_traits.hpp> // absolute_value

namespace boost {
namespace local_time {

  //! simple exception for reporting when STD or DST cannot be determined
  struct BOOST_SYMBOL_VISIBLE ambiguous_result : public std::logic_error
  {
    ambiguous_result (std::string const& msg = std::string()) :
      std::logic_error(std::string("Daylight Savings Results are ambiguous: " + msg)) {}
  };
  //! simple exception for when time label given cannot exist
  struct BOOST_SYMBOL_VISIBLE time_label_invalid : public std::logic_error
  {
    time_label_invalid (std::string const& msg = std::string()) :
      std::logic_error(std::string("Time label given is invalid: " + msg)) {}
  };
  struct BOOST_SYMBOL_VISIBLE dst_not_valid: public std::logic_error
  {
    dst_not_valid(std::string const& msg = std::string()) :
      std::logic_error(std::string("is_dst flag does not match resulting dst for time label given: " + msg)) {}
  };

  //TODO: I think these should be in local_date_time_base and not
  // necessarily brought into the namespace
  using date_time::time_is_dst_result;
  using date_time::is_in_dst;
  using date_time::is_not_in_dst;
  using date_time::ambiguous;
  using date_time::invalid_time_label;

  //! Representation of "wall-clock" time in a particular time zone
  /*! Representation of "wall-clock" time in a particular time zone
   * Local_date_time_base holds a time value (date and time offset from 00:00)
   * along with a time zone. The time value is stored as UTC and conversions
   * to wall clock time are made as needed. This approach allows for
   * operations between wall-clock times in different time zones, and
   * daylight savings time considerations, to be made. Time zones are
   * required to be in the form of a boost::shared_ptr<time_zone_base>.
   */
  template<class utc_time_=posix_time::ptime,
           class tz_type=date_time::time_zone_base<utc_time_,char> >
  class BOOST_SYMBOL_VISIBLE local_date_time_base :  public date_time::base_time<utc_time_,
                                                            boost::posix_time::posix_time_system> {
  public:
    typedef utc_time_ utc_time_type;
    typedef typename utc_time_type::time_duration_type time_duration_type;
    typedef typename utc_time_type::date_type date_type;
    typedef typename date_type::duration_type date_duration_type;
    typedef typename utc_time_type::time_system_type time_system_type;
    /*! This constructor interprets the passed time as a UTC time.
     *  So, for example, if the passed timezone is UTC-5 then the
     *  time will be adjusted back 5 hours.  The time zone allows for
     *  automatic calculation of whether the particular time is adjusted for
     *  daylight savings, etc.
     *  If the time zone shared pointer is null then time stays unadjusted.
     *@param t A UTC time
     *@param tz Timezone for to adjust the UTC time to.
     */
    local_date_time_base(utc_time_type t,
                         boost::shared_ptr<tz_type> tz) :
      date_time::base_time<utc_time_type, time_system_type>(t),
      zone_(tz)
    {
      // param was already utc so nothing more to do
    }

    /*! This constructs a local time -- the passed time information
     * understood to be in the passed tz. The DST flag must be passed
     * to indicate whether the time is in daylight savings or not.
     *  @throws -- time_label_invalid if the time passed does not exist in
     *             the given locale. The non-existent case occurs typically
     *             during the shift-back from daylight savings time.  When
     *             the clock is shifted forward a range of times
     *             (2 am to 3 am in the US) is skipped and hence is invalid.
     *  @throws -- dst_not_valid if the DST flag is passed for a period
     *             where DST is not active.
     */
    local_date_time_base(date_type d,
                         time_duration_type td,
                         boost::shared_ptr<tz_type> tz,
                         bool dst_flag) : //necessary for constr_adj()
      date_time::base_time<utc_time_type,time_system_type>(construction_adjustment(utc_time_type(d, td), tz, dst_flag)),
      zone_(tz)
    {
      if(tz != boost::shared_ptr<tz_type>() && tz->has_dst()){

        // d & td are already local so we use them
        time_is_dst_result result = check_dst(d, td, tz);
        bool in_dst = (result == is_in_dst); // less processing than is_dst()

        // ambig occurs at end, invalid at start
        if(result == invalid_time_label){
          // Ex: 2:15am local on trans-in day in nyc, dst_flag irrelevant
          std::ostringstream ss;
          ss << "time given: " << d << ' ' << td;
          boost::throw_exception(time_label_invalid(ss.str()));
        }
        else if(result != ambiguous && in_dst != dst_flag){
          // is dst_flag accurate?
          // Ex: false flag in NYC in June
          std::ostringstream ss;
          ss.setf(std::ios_base::boolalpha);
          ss << "flag given: dst=" << dst_flag << ", dst calculated: dst=" << in_dst;
          boost::throw_exception(dst_not_valid(ss.str()));
        }

        // everything checks out and conversion to utc already done
      }
    }

    //TODO maybe not the right set...Ignore the last 2 for now...
    enum DST_CALC_OPTIONS { EXCEPTION_ON_ERROR, NOT_DATE_TIME_ON_ERROR };
                            //ASSUME_DST_ON_ERROR, ASSUME_NOT_DST_ON_ERROR };

    /*! This constructs a local time -- the passed time information
     * understood to be in the passed tz.  The DST flag is calculated
     * according to the specified rule.
     */
    local_date_time_base(date_type d,
                         time_duration_type td,
                         boost::shared_ptr<tz_type> tz,
                         DST_CALC_OPTIONS calc_option) :
      // dummy value - time_ is set in constructor code
      date_time::base_time<utc_time_type,time_system_type>(utc_time_type(d,td)),
      zone_(tz)
    {
      time_is_dst_result result = check_dst(d, td, tz);
      if(result == ambiguous) {
        if(calc_option == EXCEPTION_ON_ERROR){
          std::ostringstream ss;
          ss << "time given: " << d << ' ' << td;
          boost::throw_exception(ambiguous_result(ss.str()));
        }
        else{ // NADT on error
          this->time_ = posix_time::posix_time_system::get_time_rep(date_type(date_time::not_a_date_time), time_duration_type(date_time::not_a_date_time));
        }
      }
      else if(result == invalid_time_label){
        if(calc_option == EXCEPTION_ON_ERROR){
          std::ostringstream ss;
          ss << "time given: " << d << ' ' << td;
          boost::throw_exception(time_label_invalid(ss.str()));
        }
        else{ // NADT on error
          this->time_ = posix_time::posix_time_system::get_time_rep(date_type(date_time::not_a_date_time), time_duration_type(date_time::not_a_date_time));
        }
      }
      else if(result == is_in_dst){
        utc_time_type t =
          construction_adjustment(utc_time_type(d, td), tz, true);
        this->time_ = posix_time::posix_time_system::get_time_rep(t.date(),
                                                            t.time_of_day());
      }
      else{
        utc_time_type t =
          construction_adjustment(utc_time_type(d, td), tz, false);
        this->time_ = posix_time::posix_time_system::get_time_rep(t.date(),
                                                            t.time_of_day());
      }
    }


    //! Determines if given time label is in daylight savings for given zone
    /*! Determines if given time label is in daylight savings for given zone.
     * Takes a date and time_duration representing a local time, along
     * with time zone, and returns a time_is_dst_result object as result.
     */
    static time_is_dst_result check_dst(date_type d,
                                        time_duration_type td,
                                        boost::shared_ptr<tz_type> tz)
    {
      if(tz != boost::shared_ptr<tz_type>() && tz->has_dst()) {
        typedef typename date_time::dst_calculator<date_type, time_duration_type> dst_calculator;
        return dst_calculator::local_is_dst(
            d, td,
            tz->dst_local_start_time(d.year()).date(),
            tz->dst_local_start_time(d.year()).time_of_day(),
            tz->dst_local_end_time(d.year()).date(),
            tz->dst_local_end_time(d.year()).time_of_day(),
            tz->dst_offset()
        );
      }
      else{
        return is_not_in_dst;
      }
    }

    //! Simple destructor, releases time zone if last referrer
    ~local_date_time_base() {}

    //! Copy constructor
    local_date_time_base(const local_date_time_base& rhs) :
      date_time::base_time<utc_time_type, time_system_type>(rhs),
      zone_(rhs.zone_)
    {}

    //! Special values constructor
    explicit local_date_time_base(const boost::date_time::special_values sv,
                                  boost::shared_ptr<tz_type> tz = boost::shared_ptr<tz_type>()) :
      date_time::base_time<utc_time_type, time_system_type>(utc_time_type(sv)),
      zone_(tz)
    {}

    //! returns time zone associated with calling instance
    boost::shared_ptr<tz_type> zone() const
    {
      return zone_;
    }
    //! returns false is time_zone is NULL and if time value is a special_value
    bool is_dst() const
    {
      if(zone_ != boost::shared_ptr<tz_type>() && zone_->has_dst() && !this->is_special()) {
        // check_dst takes a local time, *this is utc
        utc_time_type lt(this->time_);
        lt += zone_->base_utc_offset();
        // dst_offset only needs to be considered with ambiguous time labels
        // make that adjustment there

        switch(check_dst(lt.date(), lt.time_of_day(), zone_)){
          case is_not_in_dst:
            return false;
          case is_in_dst:
            return true;
          case ambiguous:
            if(lt + zone_->dst_offset() < zone_->dst_local_end_time(lt.date().year())) {
              return true;
            }
            break;
          case invalid_time_label:
            if(lt >= zone_->dst_local_start_time(lt.date().year())) {
              return true;
            }
            break;
        }
      }
      return false;
    }
    //! Returns object's time value as a utc representation
    utc_time_type utc_time() const
    {
      return utc_time_type(this->time_);
    }
    //! Returns object's time value as a local representation
    utc_time_type local_time() const
    {
      if(zone_ != boost::shared_ptr<tz_type>()){
        utc_time_type lt = this->utc_time() + zone_->base_utc_offset();
        if (is_dst()) {
          lt += zone_->dst_offset();
        }
        return lt;
      }
      return utc_time_type(this->time_);
    }
    //! Returns string in the form "2003-Aug-20 05:00:00 EDT"
    /*! Returns string in the form "2003-Aug-20 05:00:00 EDT". If
     * time_zone is NULL the time zone abbreviation will be "UTC". The time
     * zone abbrev will not be included if calling object is a special_value*/
    std::string to_string() const
    {
      //TODO is this a temporary function ???
      std::ostringstream ss;
      if(this->is_special()){
        ss << utc_time();
        return ss.str();
      }
      if(zone_ == boost::shared_ptr<tz_type>()) {
        ss << utc_time() << " UTC";
        return ss.str();
      }
      bool is_dst_ = is_dst();
      utc_time_type lt = this->utc_time() + zone_->base_utc_offset();
      if (is_dst_) {
        lt += zone_->dst_offset();
      }
      ss << local_time() << " ";
      if (is_dst()) {
        ss << zone_->dst_zone_abbrev();
      }
      else {
        ss << zone_->std_zone_abbrev();
      }
      return ss.str();
    }
    /*! returns a local_date_time_base in the given time zone with the
     * optional time_duration added. */
    local_date_time_base local_time_in(boost::shared_ptr<tz_type> new_tz,
                                       time_duration_type td=time_duration_type(0,0,0)) const
    {
      return local_date_time_base(utc_time_type(this->time_) + td, new_tz);
    }

    //! Returns name of associated time zone or "Coordinated Universal Time".
    /*! Optional bool parameter will return time zone as an offset
     * (ie "+07:00" extended iso format). Empty string is returned for
     * classes that do not use a time_zone */
    std::string zone_name(bool as_offset=false) const
    {
      if(zone_ == boost::shared_ptr<tz_type>()) {
        if(as_offset) {
          return std::string("Z");
        }
        else {
          return std::string("Coordinated Universal Time");
        }
      }
      if (is_dst()) {
        if(as_offset) {
          time_duration_type td = zone_->base_utc_offset();
          td += zone_->dst_offset();
          return zone_as_offset(td, ":");
        }
        else {
          return zone_->dst_zone_name();
        }
      }
      else {
        if(as_offset) {
          time_duration_type td = zone_->base_utc_offset();
          return zone_as_offset(td, ":");
        }
        else {
          return zone_->std_zone_name();
        }
      }
    }
    //! Returns abbreviation of associated time zone or "UTC".
    /*! Optional bool parameter will return time zone as an offset
     * (ie "+0700" iso format). Empty string is returned for classes
     * that do not use a time_zone */
    std::string zone_abbrev(bool as_offset=false) const
    {
      if(zone_ == boost::shared_ptr<tz_type>()) {
        if(as_offset) {
          return std::string("Z");
        }
        else {
          return std::string("UTC");
        }
      }
      if (is_dst()) {
        if(as_offset) {
          time_duration_type td = zone_->base_utc_offset();
          td += zone_->dst_offset();
          return zone_as_offset(td, "");
        }
        else {
          return zone_->dst_zone_abbrev();
        }
      }
      else {
        if(as_offset) {
          time_duration_type td = zone_->base_utc_offset();
          return zone_as_offset(td, "");
        }
        else {
          return zone_->std_zone_abbrev();
        }
      }
    }

    //! returns a posix_time_zone string for the associated time_zone. If no time_zone, "UTC+00" is returned.
    std::string zone_as_posix_string() const
    {
      if(zone_ == shared_ptr<tz_type>()) {
        return std::string("UTC+00");
      }
      return zone_->to_posix_string();
    }

    //! Equality comparison operator
    /*bool operator==(const date_time::base_time<boost::posix_time::ptime,boost::posix_time::posix_time_system>& rhs) const
    { // fails due to rhs.time_ being protected
      return date_time::base_time<boost::posix_time::ptime,boost::posix_time::posix_time_system>::operator==(rhs);
      //return this->time_ == rhs.time_;
    }*/
    //! Equality comparison operator
    bool operator==(const local_date_time_base& rhs) const
    {
      return time_system_type::is_equal(this->time_, rhs.time_);
    }
    //! Non-Equality comparison operator
    bool operator!=(const local_date_time_base& rhs) const
    {
      return !(*this == rhs);
    }
    //! Less than comparison operator
    bool operator<(const local_date_time_base& rhs) const
    {
      return time_system_type::is_less(this->time_, rhs.time_);
    }
    //! Less than or equal to comparison operator
    bool operator<=(const local_date_time_base& rhs) const
    {
      return (*this < rhs || *this == rhs);
    }
    //! Greater than comparison operator
    bool operator>(const local_date_time_base& rhs) const
    {
      return !(*this <= rhs);
    }
    //! Greater than or equal to comparison operator
    bool operator>=(const local_date_time_base& rhs) const
    {
      return (*this > rhs || *this == rhs);
    }

    //! Local_date_time + date_duration
    local_date_time_base operator+(const date_duration_type& dd) const
    {
      return local_date_time_base(time_system_type::add_days(this->time_,dd), zone_);
    }
    //! Local_date_time += date_duration
    local_date_time_base operator+=(const date_duration_type& dd)
    {
      this->time_ = time_system_type::add_days(this->time_,dd);
      return *this;
    }
    //! Local_date_time - date_duration
    local_date_time_base operator-(const date_duration_type& dd) const
    {
      return local_date_time_base(time_system_type::subtract_days(this->time_,dd), zone_);
    }
    //! Local_date_time -= date_duration
    local_date_time_base operator-=(const date_duration_type& dd)
    {
      this->time_ = time_system_type::subtract_days(this->time_,dd);
      return *this;
    }
    //! Local_date_time + time_duration
    local_date_time_base operator+(const time_duration_type& td) const
    {
      return local_date_time_base(time_system_type::add_time_duration(this->time_,td), zone_);
    }
    //! Local_date_time += time_duration
    local_date_time_base operator+=(const time_duration_type& td)
    {
      this->time_ = time_system_type::add_time_duration(this->time_,td);
      return *this;
    }
    //! Local_date_time - time_duration
    local_date_time_base operator-(const time_duration_type& td) const
    {
      return local_date_time_base(time_system_type::subtract_time_duration(this->time_,td), zone_);
    }
    //! Local_date_time -= time_duration
    local_date_time_base operator-=(const time_duration_type& td)
    {
      this->time_ = time_system_type::subtract_time_duration(this->time_,td);
      return *this;
    }
    //! local_date_time -= local_date_time --> time_duration_type
    time_duration_type operator-(const local_date_time_base& rhs) const
    {
      return utc_time_type(this->time_) - utc_time_type(rhs.time_);
    }
  private:
    boost::shared_ptr<tz_type> zone_;
    //bool is_dst_;

    /*! Adjust the passed in time to UTC?
     */
    utc_time_type construction_adjustment(utc_time_type t,
                                          boost::shared_ptr<tz_type> z,
                                          bool dst_flag)
    {
      if(z != boost::shared_ptr<tz_type>()) {
        if(dst_flag && z->has_dst()) {
          t -= z->dst_offset();
        } // else no adjust
        t -= z->base_utc_offset();
      }
      return t;
    }

    /*! Simple formatting code -- todo remove this?
     */
    std::string zone_as_offset(const time_duration_type& td,
                               const std::string& separator) const
    {
      std::ostringstream ss;
      if(td.is_negative()) {
        // a negative duration is represented as "-[h]h:mm"
        // we require two digits for the hour. A positive duration
        // with the %H flag will always give two digits
        ss << "-";
      }
      else {
        ss << "+";
      }
      ss  << std::setw(2) << std::setfill('0')
          << date_time::absolute_value(td.hours())
          << separator
          << std::setw(2) << std::setfill('0')
          << date_time::absolute_value(td.minutes());
      return ss.str();
    }
  };

  //!Use the default parameters to define local_date_time
  typedef local_date_time_base<> local_date_time;

} }


#endif

/* local_date_time.hpp
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
*/