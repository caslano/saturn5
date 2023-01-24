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
Y5NTHu0PAL8NWpyH2gROIBS/hSQNO4exrcdBqx+16L+tqDkG8nH47QPNFKLH2CTEn1UG26SfgzanDqBv64T9Wtu4gqZnDLuXIHacs7cIdJbArxPKxaQDfm3QR0tQliG1RML+1Gb8Ecximmf42trSBhPuMH7v5lrSDna3gHQ/WqR9chhsUc398FSZAMwnoK+8918bSFLwZKD2U5ydcaTy+CgZI0dx0m/Dc9uD57aNYYfYuen9NDLjc9wFT0AJ7jDa+kHQGsAnldvY+Ay0lXroAd0UtGSMoa9E2wfp3SjdZrMpXtGprmeKrCXrQIee3wTUjsPISGFr++GuWAgjbgPe7dvIpXh/d8PTvgc0F5PlTFe7GwegX1ewXh3G1QDt23bw1wbeKLIXVwzrsY15xNIrMQHXbByodvgf7e8J4B4Bz22ApfdPO6DpQ3oEdCaAGsCzpk/0Y0BNYJ366YI20RZrZ7cPcHvhnLuAWgS/xdCOvWBpEVkG7e4AVAcc+0GHcgeB2wFW0vCj9F66D0Do27gh6NduaN84Xue9cGbHod1OfdsBv0XYp4S85064GtycuX0Gc+bf4N/ZnjPv8TBnnvy/OZOs/DucM6//O5gzF+B6wmyDNtoG8Vz6cY4aN8br/x/n18z/za9/V/Pr//1z+fcuCf8O5MHF/9sN+b9//xv/3rUaClkm6WtXv1EJt7z1/Lf+T1wKyqeuXT0KrIOy
*/