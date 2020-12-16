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
zzvARXcJk0EAd9tIDWuAL5rilUimxsq7aay8+w3+IuF/m5ILYwFGgleDmaQbPj7LGJHWpehSE7kU8GGGOAwx5KtABwGJlIZdW6C/pDUuHrr3lWYhd1PR4fS7pjDNpRBX0YnoPe6QIswVl+jHqIPiX8HXgHmYvGatzqLxxxKLdiUTi7JrElSo9hpyaeVk5lIAuCSjAq34jDht+eCFrO+CRIWDTjPyb1PT18t8/8MvDYZ+/qNke/38P349IP18NRbUmQvi8Vz6EjC7aKlVDXngewN8R7rRKUu95QfFjc5rT7KS/pGLSUnf/WKhpJ+cU4cZqwYUL8crH8viiW1UanBpiqgCB76rqzf9IhDC6lg7KEKE58Lr4/WkqqqSMpDGWmN0VeUYKk9RVfJHwG/YVZCqMlNkqRh6+GSYWpn6b70KSp/oH1Svd7wGKsHf14lzTlV1wc5hWDtUQ7Qs8HE1l/u9Qo3YEaiy910sXg5yybyaoGnVXZ6A/zLKW4U6YsP2Btwaj5KZ9Kl59c+Wptj6U73SmCenvrv4kEjlVBHrGLaVlwYQwgLmfoIk120Kcp1U5M6AwT7UScDJY1RitEEcPj46S6uv9ugxGHJ5mn5edQU3mnKqcU+uR2USfkznD6Vu8lRrPu8TyPqMx/xLPEoNJ7yi1PBhGE7re4ri0eNPQbWPByuCxgqdjFmkI4xsS2KU5f/DQbdB1SiV6u8Cz5zlGLj3n7iqjYNLDiF6qGgzOK+J/Rcc8oYWVMenwVosHNZF8oKJuTCejU/H85kldD7z5lyjhUyPw06Lyyf8qfXikVaPwtzVEgtn6tIAjgtYbJG12MsnULEZUOzTF2GxnZRiQ6cCiYoEWoVCRe9SQ6vWDK/FNxlb4MHkPvIq6jbXdLZQ46sULKP9jAgKlukUvKYxCl5TUO01oRKulBT8YSCiMnCiQsGz3EzBBREUZAMqirKn4AKVgsXWYrMrJQWvpWI/mmChYLFKwUWCgsV2FFxkoeAdwhLs5jHZRUfCziIqCvpLO4z++q5BfzQmYzey7eQYz30wWzPbB/YWOYK8PrIiGjSeP5a9EssukWWXYJh+YVpfSp66DPk5GOox2F2ejP8yyi+ox+0Sex6Sa60UGheIkqeNz9WkCEF8PGYAEvS2SoWgF0XJq+YooeT6Zpw1uw/60/lcNTuffDuKB93FPn3U7GAeFvMjLM1wYl07bNbZf/Jql8OTeKFX6wjPifD0ged8eNL7e7VWA7zafHguHAi+VuG55yKvdh3E3QRPPTw/wfM5hL0BsF/1hzh4pmHaEvDHCk9LmFKvh/yX/Qnyh3ftUNeh8MPtHa/nUOsvvgUZiAkLsbbp7TLaHxrLr8Mhm/74/fFr3P/PHlpRwpk9Vvr3vAAUD73I/8+KSE18m9hc/ijllVJ56v5QL14ej/GgIMA+Z83acOlwZH6x8NbTPn6/vPUY6v1d31DxuDTHC4175YyYcAj+LT8B/nrKc+FvUvkR8PfK8qxQDqj8p+KI2RZeZuBLErx0OxJe3KEWVH7I3ZT7jA30L+Py+XbcFvgvXJEeTt86mk8aEXKzXoK1l3tf+xjm6zJacp5BbT2b0m36OJJxHfsikVEkKaTrSpmMuV82NMWdKtnfnGe/XzLr64aDtV9SRsd5uDyTH5IAykHFXD5vnGgTUvXXY7TU29DhPUJ4dIgRtCLARYBcDuRZF1StRtFyIBWmm0vPw+mmDlgUIg2XXAawaCrD1EWAHtedhe3BcXrV1GVqHcblB+/NytJwIQaHYHqNP6w60CdVy4XPOPjEHQecvEhqyw+lIRjk2ysXl1QcR+crx7dW5MBe2CwJliZChJUHLelS/iT9FQ4ZcUdDsJ4=
*/