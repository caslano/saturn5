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
U1dSSVRFRlVOQ1RJT04uM1VUBQABtkgkYK1W/W8jNRD9ff+KUZDoh7bJ8SEB5UDk2hyNSJMou6VUFEXOrtM1t7FXtrdt4PjfeWNv2h494JDYqtmN1/Nm/PzeOP3rHh3+b1fSZzj612sZ/pe4cN8Fza35VRb+/QHL5VuKfwi8xv0DUg3oMert8oA+KOot7YeoZZfrJT8vlx+Q7pqL5I8BB18v+REjMbKLPzHN1qqbytP+yQF98tVXX9IRffri0xcpnQqtZE2Zl3ol7U1KL8sw8l0l7u/7Tn6bkvQk6v47gHmlHDmz9nfCSsJzrQqpnSxJOCqlK6xa4YvS5CtJa1VLOpnNr8bT71O6q1RRdThb05KrTFuXVIlbSVYWUt1GmEZYT2YNBOCXynlgtl4Z3Ud6SV7ajetguAhRO0PiVqharJBOeKq8b9zxYFC0tsZKBqUp3KDYUdGv/OYvq7pCNRuxJdN48oZaJ1Pi+SltTKnWfAdFGGzaVa1clT6WhYS6HBhLTtZ1B4dQJV1cgqSsYyvlmdSgeuX55ox2nO2uMpt3JoLWDmjdWo10oAXzSgPiU2p1KW2YH4jYZelYDpT/y5Y91l6S0aiKesOMxlmPVsIpl9LlOD+bXeR0OVwshtP8imavaTi96vB+GE9PoQ2F
*/