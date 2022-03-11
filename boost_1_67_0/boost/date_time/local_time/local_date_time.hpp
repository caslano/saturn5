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