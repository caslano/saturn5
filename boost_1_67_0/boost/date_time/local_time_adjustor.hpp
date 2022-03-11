#ifndef DATE_TIME_LOCAL_TIME_ADJUSTOR_HPP__
#define DATE_TIME_LOCAL_TIME_ADJUSTOR_HPP__

/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland 
 * $Date$
 */

/*! @file local_time_adjustor.hpp
  Time adjustment calculations for local times
*/

#include <stdexcept>
#include <boost/throw_exception.hpp>
#include <boost/date_time/compiler_config.hpp>
#include <boost/date_time/date_generators.hpp>
#include <boost/date_time/dst_rules.hpp>
#include <boost/date_time/time_defs.hpp> // boost::date_time::dst_flags
#include <boost/date_time/special_defs.hpp> // not_a_date_time

namespace boost {
  namespace date_time {


    //! Provides a base offset adjustment from utc
    template<class time_duration_type, 
             short hours, unsigned short minutes = 0>
    class utc_adjustment 
    {
    public:
      static time_duration_type local_to_utc_base_offset()
      {
        time_duration_type td(hours,minutes,0);
        return td.invert_sign();
      }
      static time_duration_type utc_to_local_base_offset()
      {
        return time_duration_type(hours,minutes,0);
      }
    };



    //! Allow sliding utc adjustment with fixed dst rules
    template<class time_type, class dst_rules>
    class dynamic_local_time_adjustor : public dst_rules
    {
    public:
      typedef typename time_type::time_duration_type time_duration_type;
      typedef typename time_type::date_type date_type;

      dynamic_local_time_adjustor(time_duration_type utc_offset) :
        utc_offset_(utc_offset)
      {}
      
      //! Presumes local time
      time_duration_type utc_offset(bool is_dst) 
      { 
        if (is_dst) {
          return utc_offset_ + this->dst_offset();
        }
        else {
          return utc_offset_;
        }

      }
    private:
      time_duration_type utc_offset_;

    };



    //! Embed the rules for local time adjustments at compile time
    template<class time_type, class dst_rules, class utc_offset_rules>
    class static_local_time_adjustor: public dst_rules, public utc_offset_rules
    {
    public:
      typedef typename time_type::time_duration_type time_duration_type;
      typedef typename time_type::date_type date_type;

      //! Calculates the offset from a utc time to local based on dst and utc offset
      /*! @param t UTC time to calculate offset to local time
       *  This adjustment depends on the following observations about the
       *  workings of the DST boundary offset.  Since UTC time labels are
       *  monotonically increasing we can determine if a given local time
       *  is in DST or not and therefore adjust the offset appropriately.
       * 
       *  The logic is as follows.  Starting with UTC time use the offset to
       *  create a label for an non-dst adjusted local time.  Then call
       *  dst_rules::local_is_dst with the non adjust local time.  The
       *  results of this function will either unabiguously decide that
       *  the initial local time is in dst or return an illegal or
       *  ambiguous result.  An illegal result only occurs at the end
       *  of dst (where labels are skipped) and indicates that dst has
       *  ended.  An ambiguous result means that we need to recheck by
       *  making a dst adjustment and then rechecking.  If the dst offset
       *  is added to the utc time and the recheck proves non-ambiguous
       *  then we are past the boundary.  If it is still ambiguous then
       *  we are ahead of the boundary and dst is still in effect.
       *
       *  TODO -- check if all dst offsets are positive.  If not then
       *  the algorithm needs to check for this and reverse the 
       *  illegal/ambiguous logic.
       */
      static time_duration_type utc_to_local_offset(const time_type& t)
      {
        //get initial local time guess by applying utc offset
        time_type initial = t + utc_offset_rules::utc_to_local_base_offset();
        time_is_dst_result dst_flag = 
          dst_rules::local_is_dst(initial.date(), initial.time_of_day());
        switch(dst_flag) {
        case is_in_dst:        return utc_offset_rules::utc_to_local_base_offset() + dst_rules::dst_offset();
        case is_not_in_dst:    return utc_offset_rules::utc_to_local_base_offset();
        case invalid_time_label:return utc_offset_rules::utc_to_local_base_offset() + dst_rules::dst_offset();
        case ambiguous: {
          time_type retry = initial + dst_rules::dst_offset();
          dst_flag = dst_rules::local_is_dst(retry.date(), retry.time_of_day());
          //if still ambibuous then the utc time still translates to a dst time
          if (dst_flag == ambiguous) {
            return utc_offset_rules::utc_to_local_base_offset() + dst_rules::dst_offset();
          }
          // we are past the dst boundary
          else {
            return utc_offset_rules::utc_to_local_base_offset();
          }
        }
        }//case
        //TODO  better exception type
        boost::throw_exception(std::out_of_range("Unreachable case"));
        BOOST_DATE_TIME_UNREACHABLE_EXPRESSION(return time_duration_type(not_a_date_time)); // should never reach
      }

      //! Get the offset to UTC given a local time
      static time_duration_type local_to_utc_offset(const time_type& t, 
                                                    date_time::dst_flags dst=date_time::calculate) 
      {
        switch (dst) {
        case is_dst:
          return utc_offset_rules::local_to_utc_base_offset() - dst_rules::dst_offset();
        case not_dst:
          return utc_offset_rules::local_to_utc_base_offset();
        case calculate:
          time_is_dst_result res = 
            dst_rules::local_is_dst(t.date(), t.time_of_day());
          switch(res) {
          case is_in_dst:      return utc_offset_rules::local_to_utc_base_offset() - dst_rules::dst_offset();
          case is_not_in_dst:      return utc_offset_rules::local_to_utc_base_offset();
          case ambiguous:          return utc_offset_rules::local_to_utc_base_offset();
          case invalid_time_label: break;
          }
        }
        boost::throw_exception(std::out_of_range("Time label invalid"));
        BOOST_DATE_TIME_UNREACHABLE_EXPRESSION(return time_duration_type(not_a_date_time)); // should never reach
      }


    private:

    };

    void dummy_to_prevent_msvc6_ice(); //why ask why?

    //! Template that simplifies the creation of local time calculator 
    /*! Use this template to create the timezone to utc convertors as required.
     * 
     *  This class will also work for other regions that don't use dst and
     *  have a utc offset which is an integral number of hours.
     *
     *  <b>Template Parameters</b>
     *  -time_type  -- Time class to use
     *  -utc_offset -- Number hours local time is adjust from utc
     *  -use_dst -- true (default) if region uses dst, false otherwise
     *  For example:
     *  @code
     *  //eastern timezone is utc-5
     typedef date_time::local_adjustor<ptime, -5, us_dst> us_eastern;
     typedef date_time::local_adjustor<ptime, -6, us_dst> us_central;
     typedef date_time::local_adjustor<ptime, -7, us_dst> us_mountain;
     typedef date_time::local_adjustor<ptime, -8, us_dst> us_pacific;
     typedef date_time::local_adjustor<ptime, -7, no_dst> us_arizona;
     @endcode
      
    */
    template<class time_type, short utc_offset, class dst_rule>
    class local_adjustor
    {
    public:
      typedef typename time_type::time_duration_type time_duration_type;
      typedef typename time_type::date_type date_type;
      typedef static_local_time_adjustor<time_type, 
                                         dst_rule,
                                         utc_adjustment<time_duration_type, 
                                                        utc_offset> > dst_adjustor;
      //! Convert a utc time to local time
      static time_type utc_to_local(const time_type& t)
      {
        time_duration_type td = dst_adjustor::utc_to_local_offset(t);
        return t + td;
      }
      //! Convert a local time to utc
      static time_type local_to_utc(const time_type& t, 
                                    date_time::dst_flags dst=date_time::calculate)
      {
        time_duration_type td = dst_adjustor::local_to_utc_offset(t, dst);
        return t + td;
      }
    };


  } } //namespace date_time



#endif

/* local_time_adjustor.hpp
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
*/