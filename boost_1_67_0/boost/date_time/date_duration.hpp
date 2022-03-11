#ifndef DATE_TIME_DATE_DURATION__
#define DATE_TIME_DATE_DURATION__

/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */


#include <boost/operators.hpp>
#include <boost/date_time/special_defs.hpp>
#include <boost/date_time/compiler_config.hpp>
#include <boost/date_time/int_adapter.hpp>

namespace boost {
namespace date_time {


  //! Duration type with date level resolution
  template<class duration_rep_traits>
  class BOOST_SYMBOL_VISIBLE date_duration : private
              boost::less_than_comparable1< date_duration< duration_rep_traits >
            , boost::equality_comparable1< date_duration< duration_rep_traits >
            , boost::addable1< date_duration< duration_rep_traits >
            , boost::subtractable1< date_duration< duration_rep_traits >
            , boost::dividable2< date_duration< duration_rep_traits >, int
            > > > > >
  {
  public:
    typedef typename duration_rep_traits::int_type duration_rep_type;
    typedef typename duration_rep_traits::impl_type duration_rep;

    //! Construct from a day count
    BOOST_CXX14_CONSTEXPR explicit date_duration(duration_rep day_count) : days_(day_count) {}

    /*! construct from special_values - only works when
     * instantiated with duration_traits_adapted */
    BOOST_CXX14_CONSTEXPR date_duration(special_values sv) :
            days_(duration_rep::from_special(sv))
    {}

    // copy constructor required for addable<> & subtractable<>
    //! Construct from another date_duration (Copy Constructor)
    BOOST_CXX14_CONSTEXPR date_duration(const date_duration<duration_rep_traits>& other) :
            days_(other.days_)
    {}

    //! returns days_ as it's instantiated type - used for streaming
    BOOST_CXX14_CONSTEXPR duration_rep get_rep()const
    {
        return days_;
    }
    BOOST_CXX14_CONSTEXPR special_values as_special() const
    {
        return days_.as_special();
    }
    BOOST_CXX14_CONSTEXPR bool is_special()const
    {
        return days_.is_special();
    }
    //! returns days as value, not object.
    BOOST_CXX14_CONSTEXPR duration_rep_type days() const
    {
        return duration_rep_traits::as_number(days_);
    }
    //! Returns the smallest duration -- used by to calculate 'end'
    static BOOST_CXX14_CONSTEXPR date_duration unit()
    {
        return date_duration<duration_rep_traits>(1);
    }
    //! Equality
    BOOST_CXX14_CONSTEXPR bool operator==(const date_duration& rhs) const
    {
        return days_ == rhs.days_;
    }
    //! Less
    BOOST_CXX14_CONSTEXPR bool operator<(const date_duration& rhs) const
    {
        return days_ < rhs.days_;
    }

    /* For shortcut operators (+=, -=, etc) simply using
     * "days_ += days_" may not work. If instantiated with
     * an int_adapter, shortcut operators are not present,
     * so this will not compile */

    //! Subtract another duration -- result is signed
    BOOST_CXX14_CONSTEXPR date_duration& operator-=(const date_duration& rhs)
    {
        //days_ -= rhs.days_;
        days_ = days_ - rhs.days_;
        return *this;
    }
    //! Add a duration -- result is signed
    BOOST_CXX14_CONSTEXPR date_duration& operator+=(const date_duration& rhs)
    {
        days_ = days_ + rhs.days_;
        return *this;
    }

    //! unary- Allows for dd = -date_duration(2); -> dd == -2
    BOOST_CXX14_CONSTEXPR date_duration operator-() const
    {
        return date_duration<duration_rep_traits>(get_rep() * (-1));
    }
    //! Division operations on a duration with an integer.
    BOOST_CXX14_CONSTEXPR date_duration& operator/=(int divisor)
    {
        days_ = days_ / divisor;
        return *this;
    }

    //! return sign information
    BOOST_CXX14_CONSTEXPR bool is_negative() const
    {
        return days_ < 0;
    }

  private:
    duration_rep days_;
  };


  /*! Struct for instantiating date_duration with <b>NO</b> special values
   * functionality. Allows for transparent implementation of either
   * date_duration<long> or date_duration<int_adapter<long> > */
  struct BOOST_SYMBOL_VISIBLE duration_traits_long
  {
    typedef long int_type;
    typedef long impl_type;
    static BOOST_CXX14_CONSTEXPR int_type as_number(impl_type i) { return i; }
  };

  /*! Struct for instantiating date_duration <b>WITH</b> special values
   * functionality. Allows for transparent implementation of either
   * date_duration<long> or date_duration<int_adapter<long> > */
  struct BOOST_SYMBOL_VISIBLE duration_traits_adapted
  {
    typedef long int_type;
    typedef boost::date_time::int_adapter<long> impl_type;
    static BOOST_CXX14_CONSTEXPR int_type as_number(impl_type i) { return i.as_number(); }
  };


} } //namspace date_time


#endif


/* date_duration.hpp
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
*/