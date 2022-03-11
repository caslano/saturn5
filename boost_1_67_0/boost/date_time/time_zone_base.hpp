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