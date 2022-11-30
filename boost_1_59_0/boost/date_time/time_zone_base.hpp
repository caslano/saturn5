#ifndef _DATE_TIME_TIME_ZONE_BASE__
#define _DATE_TIME_TIME_ZONE_BASE__

/* Copyright (c) 2003-2005 CrystalClear Software, Inc.
 * Subject to the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */


#include <string>
#include <sstream>
#include <boost/date_time/compiler_config.hpp>

namespace boost {
namespace date_time {



  //! Interface class for dynamic time zones.
  /*! This class represents the base interface for all timezone
   *  representations.  Subclasses may provide different systems
   *  for identifying a particular zone.  For example some may
   *  provide a geographical based zone construction while others
   *  may specify the offset from GMT.  Another possible implementation
   *  would be to convert from POSIX timezone strings.  Regardless of
   *  the construction technique, this is the interface that these
   *  time zone types must provide.
   *
   * Note that this class is intended to be used as a shared
   * resource (hence the derivation from boost::counted_base.
   */
  template<typename time_type, typename CharT>
  class BOOST_SYMBOL_VISIBLE time_zone_base  {
  public:
    typedef CharT char_type;
    typedef std::basic_string<CharT> string_type;
    typedef std::basic_ostringstream<CharT> stringstream_type;
    typedef typename time_type::date_type::year_type year_type;
    typedef typename time_type::time_duration_type time_duration_type;

    time_zone_base() {}
    virtual ~time_zone_base() {}
    //!String for the timezone when in daylight savings (eg: EDT)
    virtual string_type dst_zone_abbrev() const=0;
    //!String for the zone when not in daylight savings (eg: EST)
    virtual string_type std_zone_abbrev() const=0;
    //!String for the timezone when in daylight savings (eg: Eastern Daylight Time)
    virtual string_type dst_zone_name() const=0;
    //!String for the zone when not in daylight savings (eg: Eastern Standard Time)
    virtual string_type std_zone_name() const=0;
    //! True if zone uses daylight savings adjustments otherwise false
    virtual bool has_dst() const=0;
    //! Local time that DST starts -- undefined if has_dst is false
    virtual time_type dst_local_start_time(year_type y) const=0;
    //! Local time that DST ends -- undefined if has_dst is false
    virtual time_type dst_local_end_time(year_type y) const=0;
    //! Base offset from UTC for zone (eg: -07:30:00)
    virtual time_duration_type base_utc_offset() const=0;
    //! Adjustment forward or back made while DST is in effect
    virtual time_duration_type dst_offset() const=0;
    //! Returns a POSIX time_zone string for this object
    virtual string_type to_posix_string() const =0;

  private:

  };


  //! Structure which holds the time offsets associated with daylight savings time
  /*!
   *@tparam time_duration_type A type used to represent the offset
   */
  template<class time_duration_type>
  class dst_adjustment_offsets
  {
  public:
    dst_adjustment_offsets(const time_duration_type& dst_adjust,
                           const time_duration_type& dst_start_offset,
                           const time_duration_type& dst_end_offset) :
      dst_adjust_(dst_adjust),
      dst_start_offset_(dst_start_offset),
      dst_end_offset_(dst_end_offset)
    {}

    //! Amount DST adjusts the clock eg: plus one hour
    time_duration_type dst_adjust_;
    //! Time past midnight on start transition day that dst starts
    time_duration_type dst_start_offset_;
    //! Time past midnight on end transition day that dst ends
    time_duration_type dst_end_offset_;
  };


} } //namespace date_time



#endif

/* time_zone_base.hpp
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
*/