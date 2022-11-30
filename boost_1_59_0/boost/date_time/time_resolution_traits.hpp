#ifndef DATE_TIME_TIME_RESOLUTION_TRAITS_HPP
#define DATE_TIME_TIME_RESOLUTION_TRAITS_HPP

/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include <ctime>
#include <boost/cstdint.hpp>
#include <boost/date_time/time_defs.hpp>
#include <boost/date_time/int_adapter.hpp>
#include <boost/date_time/compiler_config.hpp>

namespace boost {
namespace date_time {

  //! Simple function to calculate absolute value of a numeric type
  template <typename T>
  // JDG [7/6/02 made a template],
  // moved here from time_duration.hpp 2003-Sept-4.
  inline BOOST_CXX14_CONSTEXPR T absolute_value(T x)
  {
    return x < 0 ? -x : x;
  }

  //! traits struct for time_resolution_traits implementation type
  struct time_resolution_traits_bi32_impl {
    typedef boost::int32_t int_type;
    typedef boost::int32_t impl_type;
    static BOOST_CXX14_CONSTEXPR int_type as_number(impl_type i){ return i;}
    //! Used to determine if implemented type is int_adapter or int
    static BOOST_CXX14_CONSTEXPR bool is_adapted() { return false;}
  };
  //! traits struct for time_resolution_traits implementation type
  struct time_resolution_traits_adapted32_impl {
    typedef boost::int32_t int_type;
    typedef boost::date_time::int_adapter<boost::int32_t> impl_type;
    static BOOST_CXX14_CONSTEXPR int_type as_number(impl_type i){ return i.as_number();}
    //! Used to determine if implemented type is int_adapter or int
    static BOOST_CXX14_CONSTEXPR bool is_adapted() { return true;}
  };
  //! traits struct for time_resolution_traits implementation type
  struct time_resolution_traits_bi64_impl {
    typedef boost::int64_t int_type;
    typedef boost::int64_t impl_type;
    static BOOST_CXX14_CONSTEXPR int_type as_number(impl_type i){ return i;}
    //! Used to determine if implemented type is int_adapter or int
    static BOOST_CXX14_CONSTEXPR bool is_adapted() { return false;}
  };
  //! traits struct for time_resolution_traits implementation type
  struct time_resolution_traits_adapted64_impl {
    typedef boost::int64_t int_type;
    typedef boost::date_time::int_adapter<boost::int64_t> impl_type;
    static BOOST_CXX14_CONSTEXPR int_type as_number(impl_type i){ return i.as_number();}
    //! Used to determine if implemented type is int_adapter or int
    static BOOST_CXX14_CONSTEXPR bool is_adapted() { return true;}
  };

  //
  // Note about var_type, which is used to define the variable that
  // stores hours, minutes, and seconds values:
  //
  // In Boost 1.65.1 and earlier var_type was boost::int32_t which suffers
  // the year 2038 problem.  Binary serialization of posix_time uses
  // 32-bit values, and uses serialization version 0.
  //
  // In Boost 1.66.0 the var_type changed to std::time_t, however
  // binary serialization was not properly versioned, so on platforms
  // where std::time_t is 32-bits, it remains compatible, however on
  // platforms where std::time_t is 64-bits, binary serialization ingest
  // will be incompatible with previous versions.  Furthermore, binary
  // serialized output from 1.66.0 will not be compatible with future
  // versions.  Yes, it's a mess.  Static assertions were not present
  // in the serialization code to protect against this possibility.
  //
  // In Boost 1.67.0 the var_type was changed to boost::int64_t, 
  // ensuring the output size is 64 bits, and the serialization version
  // was bumped.  Static assertions were added as well, protecting
  // future changes in this area.
  //

  template<typename frac_sec_type,
           time_resolutions res,
#if (defined(BOOST_MSVC) && (_MSC_VER < 1300))
           boost::int64_t resolution_adjust,
#else
           typename frac_sec_type::int_type resolution_adjust,
#endif
           unsigned short frac_digits,
           typename var_type = boost::int64_t >     // see note above
  class time_resolution_traits {
  public:
    typedef typename frac_sec_type::int_type fractional_seconds_type;
    typedef typename frac_sec_type::int_type tick_type;
    typedef typename frac_sec_type::impl_type impl_type;
    typedef var_type  day_type;
    typedef var_type  hour_type;
    typedef var_type  min_type;
    typedef var_type  sec_type;

    // bring in function from frac_sec_type traits structs
    static BOOST_CXX14_CONSTEXPR fractional_seconds_type as_number(impl_type i)
    {
      return frac_sec_type::as_number(i);
    }
    static BOOST_CXX14_CONSTEXPR bool is_adapted()
    {
      return frac_sec_type::is_adapted();
    }

    //Would like this to be frac_sec_type, but some compilers complain
#if (defined(BOOST_MSVC) && (_MSC_VER < 1300))
    BOOST_STATIC_CONSTANT(boost::int64_t, ticks_per_second = resolution_adjust);
#else
    BOOST_STATIC_CONSTANT(fractional_seconds_type, ticks_per_second = resolution_adjust);
#endif

    static BOOST_CXX14_CONSTEXPR time_resolutions resolution()
    {
      return res;
    }
    static BOOST_CXX14_CONSTEXPR unsigned short num_fractional_digits()
    {
      return frac_digits;
    }
    static BOOST_CXX14_CONSTEXPR fractional_seconds_type res_adjust()
    {
      return resolution_adjust;
    }
    //! Any negative argument results in a negative tick_count
    static BOOST_CXX14_CONSTEXPR tick_type to_tick_count(hour_type hours,
                                                         min_type  minutes,
                                                         sec_type  seconds,
                                                         fractional_seconds_type  fs)
    {
      if(hours < 0 || minutes < 0 || seconds < 0 || fs < 0)
      {
        hours = absolute_value(hours);
        minutes = absolute_value(minutes);
        seconds = absolute_value(seconds);
        fs = absolute_value(fs);
        return static_cast<tick_type>(((((fractional_seconds_type(hours)*3600)
                                       + (fractional_seconds_type(minutes)*60)
                                       + seconds)*res_adjust()) + fs) * -1);
      }

      return static_cast<tick_type>((((fractional_seconds_type(hours)*3600)
                                    + (fractional_seconds_type(minutes)*60)
                                    + seconds)*res_adjust()) + fs);
    }

  };

  typedef time_resolution_traits<time_resolution_traits_adapted32_impl, milli, 1000, 3 > milli_res;
  typedef time_resolution_traits<time_resolution_traits_adapted64_impl, micro, 1000000, 6 > micro_res;
  typedef time_resolution_traits<time_resolution_traits_adapted64_impl, nano,  1000000000, 9 > nano_res;


} } //namespace date_time



#endif

/* time_resolution_traits.hpp
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
*/