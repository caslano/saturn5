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
    // copy constructor required for dividable<>
    //! Construct from another time_duration (Copy constructor)
    BOOST_CXX14_CONSTEXPR time_duration(const time_duration<T, rep_type>& other)
      : ticks_(other.ticks_)
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