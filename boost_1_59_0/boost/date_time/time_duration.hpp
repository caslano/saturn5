#ifndef DATE_TIME_TIME_DURATION_HPP___
#define DATE_TIME_TIME_DURATION_HPP___

/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include <boost/core/enable_if.hpp>
#include <boost/cstdint.hpp>
#include <boost/date_time/compiler_config.hpp>
#include <boost/date_time/special_defs.hpp>
#include <boost/date_time/time_defs.hpp>
#include <boost/operators.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_integral.hpp>

namespace boost {
namespace date_time {


  //! Represents some amount of elapsed time measure to a given resolution
  /*! This class represents a standard set of capabilities for all
      counted time durations.  Time duration implementations should derive
      from this class passing their type as the first template parameter.
      This design allows the subclass duration types to provide custom
      construction policies or other custom features not provided here.

      @tparam T The subclass type
      @tparam rep_type The time resolution traits for this duration type.
  */
  template<class T, typename rep_type>
  class BOOST_SYMBOL_VISIBLE time_duration : private
      boost::less_than_comparable<T
    , boost::equality_comparable<T
    > >
  /* dividable, addable, and subtractable operator templates
   * won't work with this class (MSVC++ 6.0). return type
   * from '+=' is different than expected return type
   * from '+'. multipliable probably wont work
   * either (haven't tried) */
  {
  public:
    // A tag for type categorization. Can be used to detect Boost.DateTime duration types in generic code.
    typedef void _is_boost_date_time_duration;
    typedef T duration_type;  //the subclass
    typedef rep_type traits_type;
    typedef typename rep_type::day_type  day_type;
    typedef typename rep_type::hour_type hour_type;
    typedef typename rep_type::min_type  min_type;
    typedef typename rep_type::sec_type  sec_type;
    typedef typename rep_type::fractional_seconds_type fractional_seconds_type;
    typedef typename rep_type::tick_type tick_type;
    typedef typename rep_type::impl_type impl_type;

    BOOST_CXX14_CONSTEXPR time_duration() : ticks_(0) {}
    BOOST_CXX14_CONSTEXPR time_duration(hour_type hours_in,
                  min_type minutes_in,
                  sec_type seconds_in=0,
                  fractional_seconds_type frac_sec_in = 0) :
      ticks_(rep_type::to_tick_count(hours_in,minutes_in,seconds_in,frac_sec_in))
    {}
    //! Construct from special_values
    BOOST_CXX14_CONSTEXPR time_duration(special_values sv) : ticks_(impl_type::from_special(sv))
    {}
    //! Returns smallest representable duration
    static BOOST_CXX14_CONSTEXPR duration_type unit()
    {
      return duration_type(0,0,0,1);
    }
    //! Return the number of ticks in a second
    static BOOST_CXX14_CONSTEXPR tick_type ticks_per_second()
    {
      return rep_type::res_adjust();
    }
    //! Provide the resolution of this duration type
    static BOOST_CXX14_CONSTEXPR time_resolutions resolution()
    {
      return rep_type::resolution();
    }
    //! Returns number of hours in the duration
    BOOST_CXX14_CONSTEXPR hour_type hours()   const
    {
      return static_cast<hour_type>(ticks() / (3600*ticks_per_second()));
    }
    //! Returns normalized number of minutes
    BOOST_CXX14_CONSTEXPR min_type minutes() const
    {
      return static_cast<min_type>((ticks() / (60*ticks_per_second())) % 60);
    }
    //! Returns normalized number of seconds (0..60)
    BOOST_CXX14_CONSTEXPR sec_type seconds() const
    {
      return static_cast<sec_type>((ticks()/ticks_per_second()) % 60);
    }
    //! Returns total number of seconds truncating any fractional seconds
    BOOST_CXX14_CONSTEXPR sec_type total_seconds() const
    {
      return static_cast<sec_type>(ticks() / ticks_per_second());
    }
    //! Returns total number of milliseconds truncating any fractional seconds
    BOOST_CXX14_CONSTEXPR tick_type total_milliseconds() const
    {
      if (ticks_per_second() < 1000) {
        return ticks() * (static_cast<tick_type>(1000) / ticks_per_second());
      }
      return ticks() / (ticks_per_second() / static_cast<tick_type>(1000)) ;
    }
    //! Returns total number of nanoseconds truncating any sub millisecond values
    BOOST_CXX14_CONSTEXPR tick_type total_nanoseconds() const
    {
      if (ticks_per_second() < 1000000000) {
        return ticks() * (static_cast<tick_type>(1000000000) / ticks_per_second());
      }
      return ticks() / (ticks_per_second() / static_cast<tick_type>(1000000000)) ;
    }
    //! Returns total number of microseconds truncating any sub microsecond values
    BOOST_CXX14_CONSTEXPR tick_type total_microseconds() const
    {
      if (ticks_per_second() < 1000000) {
        return ticks() * (static_cast<tick_type>(1000000) / ticks_per_second());
      }
      return ticks() / (ticks_per_second() / static_cast<tick_type>(1000000)) ;
    }
    //! Returns count of fractional seconds at given resolution
    BOOST_CXX14_CONSTEXPR fractional_seconds_type fractional_seconds() const
    {
      return (ticks() % ticks_per_second());
    }
    //! Returns number of possible digits in fractional seconds
    static BOOST_CXX14_CONSTEXPR unsigned short num_fractional_digits()
    {
      return rep_type::num_fractional_digits();
    }
    BOOST_CXX14_CONSTEXPR duration_type invert_sign() const
    {
      return duration_type(ticks_ * (-1));
    }
    BOOST_CXX14_CONSTEXPR duration_type abs() const
    {
      if ( is_negative() )
      {
        return invert_sign();
      }
      return duration_type(ticks_);
    }
    BOOST_CONSTEXPR bool is_negative() const
    {
      return ticks_ < 0;
    }
    BOOST_CONSTEXPR bool is_zero() const
    {
      return ticks_ == 0;
    }
    BOOST_CONSTEXPR bool is_positive() const
    {
      return ticks_ > 0;
    }
    BOOST_CONSTEXPR bool operator<(const time_duration& rhs)  const
    {
      return ticks_ <  rhs.ticks_;
    }
    BOOST_CONSTEXPR bool operator==(const time_duration& rhs)  const
    {
      return ticks_ ==  rhs.ticks_;
    }
    //! unary- Allows for time_duration td = -td1
    BOOST_CONSTEXPR duration_type operator-()const
    {
      return duration_type(ticks_ * (-1));
    }
    BOOST_CONSTEXPR duration_type operator-(const duration_type& d) const
    {
      return duration_type(ticks_ - d.ticks_);
    }
    BOOST_CONSTEXPR duration_type operator+(const duration_type& d) const
    {
      return duration_type(ticks_ + d.ticks_);
    }
    BOOST_CONSTEXPR duration_type operator/(int divisor) const
    {
      return duration_type(ticks_ / divisor);
    }
    BOOST_CXX14_CONSTEXPR duration_type operator-=(const duration_type& d)
    {
      ticks_ = ticks_ - d.ticks_;
      return duration_type(ticks_);
    }
    BOOST_CXX14_CONSTEXPR duration_type operator+=(const duration_type& d)
    {
      ticks_ = ticks_ + d.ticks_;
      return duration_type(ticks_);
    }
    //! Division operations on a duration with an integer.
    BOOST_CXX14_CONSTEXPR duration_type operator/=(int divisor)
    {
      ticks_ = ticks_ / divisor;
      return duration_type(ticks_);
    }
    //! Multiplication operations an a duration with an integer
    BOOST_CXX14_CONSTEXPR duration_type operator*(int rhs) const
    {
      return duration_type(ticks_ * rhs);
    }
    BOOST_CXX14_CONSTEXPR duration_type operator*=(int divisor)
    {
      ticks_ = ticks_ * divisor;
      return duration_type(ticks_);
    }
    BOOST_CXX14_CONSTEXPR tick_type ticks() const
    {
      return traits_type::as_number(ticks_);
    }

    //! Is ticks_ a special value?
    BOOST_CXX14_CONSTEXPR bool is_special()const
    {
      if(traits_type::is_adapted())
      {
        return ticks_.is_special();
      }
      else{
        return false;
      }
    }
    //! Is duration pos-infinity
    BOOST_CXX14_CONSTEXPR bool is_pos_infinity()const
    {
      if(traits_type::is_adapted())
      {
        return ticks_.is_pos_infinity();
      }
      else{
        return false;
      }
    }
    //! Is duration neg-infinity
    BOOST_CXX14_CONSTEXPR bool is_neg_infinity()const
    {
      if(traits_type::is_adapted())
      {
        return ticks_.is_neg_infinity();
      }
      else{
        return false;
      }
    }
    //! Is duration not-a-date-time
    BOOST_CXX14_CONSTEXPR bool is_not_a_date_time()const
    {
      if(traits_type::is_adapted())
      {
        return ticks_.is_nan();
      }
      else{
        return false;
      }
    }

    //! Used for special_values output
    BOOST_CONSTEXPR impl_type get_rep()const
    {
      return ticks_;
    }

  protected:
    BOOST_CXX14_CONSTEXPR explicit time_duration(impl_type in) : ticks_(in) {}
    impl_type ticks_;
  };



  //! Template for instantiating derived adjusting durations
  /* These templates are designed to work with multiples of
   * 10 for frac_of_second and resolution adjustment
   */
  template<class base_duration, boost::int64_t frac_of_second>
  class BOOST_SYMBOL_VISIBLE subsecond_duration : public base_duration
  {
  public:
    typedef typename base_duration::impl_type impl_type;
    typedef typename base_duration::traits_type traits_type;

  private:
    // To avoid integer overflow we precompute the duration resolution conversion coefficient (ticket #3471)
    BOOST_STATIC_ASSERT_MSG((traits_type::ticks_per_second >= frac_of_second ? traits_type::ticks_per_second % frac_of_second : frac_of_second % traits_type::ticks_per_second) == 0,\
      "The base duration resolution must be a multiple of the subsecond duration resolution");
    BOOST_STATIC_CONSTANT(boost::int64_t, adjustment_ratio = (traits_type::ticks_per_second >= frac_of_second ? traits_type::ticks_per_second / frac_of_second : frac_of_second / traits_type::ticks_per_second));

  public:
    // The argument (ss) must be an integral type
    template <typename T>
    BOOST_CXX14_CONSTEXPR explicit subsecond_duration(T const& ss,
                                                      typename boost::enable_if<boost::is_integral<T>,
                                                        void>::type* = BOOST_DATE_TIME_NULLPTR) :
      base_duration(impl_type(traits_type::ticks_per_second >= frac_of_second ? ss * adjustment_ratio : ss / adjustment_ratio))
    {
    }
  };

} } //namespace date_time




#endif


/* time_duration.hpp
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
*/