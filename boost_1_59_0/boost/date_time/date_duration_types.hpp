#ifndef DATE_DURATION_TYPES_HPP___
#define DATE_DURATION_TYPES_HPP___

/* Copyright (c) 2004 CrystalClear Software, Inc.
 * Subject to the Boost Software License, Version 1.0. 
 * (See accompanying file LICENSE_1_0.txt or 
 * http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include <boost/date_time/compiler_config.hpp>
#include <boost/date_time/int_adapter.hpp>
#include <boost/date_time/special_defs.hpp>
#include <boost/date_time/date_duration.hpp>

namespace boost {
namespace date_time {


  //! Additional duration type that represents a number of n*7 days
  template <class duration_config>
  class BOOST_SYMBOL_VISIBLE weeks_duration : public date_duration<duration_config> {
  public:
    BOOST_CXX14_CONSTEXPR weeks_duration(typename duration_config::impl_type w) 
      : date_duration<duration_config>(w * 7) {}
    BOOST_CXX14_CONSTEXPR weeks_duration(special_values sv) 
      : date_duration<duration_config>(sv) {}
  };

  // predeclare
  template<class t>
  class BOOST_SYMBOL_VISIBLE years_duration;

  //! additional duration type that represents a logical month
  /*! A logical month enables things like: "date(2002,Mar,2) + months(2) -> 
   * 2002-May2". If the date is a last day-of-the-month, the result will 
   * also be a last-day-of-the-month.
   */
  template<class base_config>
  class BOOST_SYMBOL_VISIBLE months_duration
  {
    private:
      typedef typename base_config::int_rep int_rep;
      typedef typename int_rep::int_type int_type;
      typedef typename base_config::date_type date_type;
      typedef typename date_type::duration_type duration_type;
      typedef typename base_config::month_adjustor_type month_adjustor_type;
      typedef months_duration<base_config> months_type;
      typedef years_duration<base_config> years_type;
    public:
      BOOST_CXX14_CONSTEXPR months_duration(int_rep num) : _m(num) {}
      BOOST_CXX14_CONSTEXPR months_duration(special_values sv) : _m(sv) 
      {
        _m = int_rep::from_special(sv);
      }
      int_rep number_of_months() const { return _m; }
      //! returns a negative duration
      BOOST_CXX14_CONSTEXPR duration_type get_neg_offset(const date_type& d) const
      {
        month_adjustor_type m_adj(_m.as_number());
        return duration_type(m_adj.get_neg_offset(d));
      }
      BOOST_CXX14_CONSTEXPR duration_type get_offset(const date_type& d) const
      {
        month_adjustor_type m_adj(_m.as_number());
        return duration_type(m_adj.get_offset(d));
      }
      BOOST_CONSTEXPR bool operator==(const months_type& rhs) const
      {
        return(_m == rhs._m);
      }
      BOOST_CONSTEXPR bool operator!=(const months_type& rhs) const
      {
        return(_m != rhs._m);
      }
      BOOST_CXX14_CONSTEXPR months_type operator+(const months_type& rhs)const
      {
        return months_type(_m + rhs._m);
      }
      BOOST_CXX14_CONSTEXPR months_type& operator+=(const months_type& rhs)
      {
        _m = _m + rhs._m;
        return *this;
      }
      BOOST_CXX14_CONSTEXPR months_type operator-(const months_type& rhs)const
      {
        return months_type(_m - rhs._m);
      }
      BOOST_CXX14_CONSTEXPR months_type& operator-=(const months_type& rhs)
      {
        _m = _m - rhs._m;
        return *this;
      }
      BOOST_CXX14_CONSTEXPR months_type operator*(const int_type rhs)const
      {
        return months_type(_m * rhs);
      }
      BOOST_CXX14_CONSTEXPR months_type& operator*=(const int_type rhs)
      {
        _m = _m * rhs;
        return *this;
      }
      BOOST_CXX14_CONSTEXPR months_type operator/(const int_type rhs)const
      {
        return months_type(_m / rhs);
      }
      BOOST_CXX14_CONSTEXPR months_type& operator/=(const int_type rhs)
      {
        _m = _m / rhs;
        return *this;
      }
      BOOST_CXX14_CONSTEXPR months_type operator+(const years_type& y)const
      {
        return months_type(y.number_of_years() * 12 + _m);
      }
      BOOST_CXX14_CONSTEXPR months_type& operator+=(const years_type& y)
      {
        _m = y.number_of_years() * 12 + _m;
        return *this;
      }
      BOOST_CXX14_CONSTEXPR months_type operator-(const years_type& y) const
      {
        return months_type(_m - y.number_of_years() * 12);
      }
      BOOST_CXX14_CONSTEXPR months_type& operator-=(const years_type& y)
      {
        _m = _m - y.number_of_years() * 12;
        return *this;
      }
      //
      BOOST_CXX14_CONSTEXPR friend date_type operator+(const date_type& d, const months_type& m)
      {
        return d + m.get_offset(d);
      }
      BOOST_CXX14_CONSTEXPR friend date_type operator+=(date_type& d, const months_type& m)
      {
        return d += m.get_offset(d);
      }
      BOOST_CXX14_CONSTEXPR friend date_type operator-(const date_type& d, const months_type& m)
      {
        // get_neg_offset returns a negative duration, so we add
        return d + m.get_neg_offset(d);
      }
      BOOST_CXX14_CONSTEXPR friend date_type operator-=(date_type& d, const months_type& m)
      {
        // get_neg_offset returns a negative duration, so we add
        return d += m.get_neg_offset(d);
      }
    private:
      int_rep _m;
  };

  //! additional duration type that represents a logical year
  /*! A logical year enables things like: "date(2002,Mar,2) + years(2) -> 
   * 2004-Mar-2". If the date is a last day-of-the-month, the result will 
   * also be a last-day-of-the-month (ie date(2001-Feb-28) + years(3) ->
   * 2004-Feb-29).
   */
  template<class base_config>
  class BOOST_SYMBOL_VISIBLE years_duration
  {
    private:
      typedef typename base_config::int_rep int_rep;
      typedef typename int_rep::int_type int_type;
      typedef typename base_config::date_type date_type;
      typedef typename date_type::duration_type duration_type;
      typedef typename base_config::month_adjustor_type month_adjustor_type;
      typedef years_duration<base_config> years_type;
      typedef months_duration<base_config> months_type;
    public:
      BOOST_CXX14_CONSTEXPR years_duration(int_rep num) : _y(num) {}
      BOOST_CXX14_CONSTEXPR years_duration(special_values sv) : _y(sv) 
      {
        _y = int_rep::from_special(sv);
      }
      BOOST_CXX14_CONSTEXPR int_rep number_of_years() const { return _y; }
      //! returns a negative duration
      BOOST_CXX14_CONSTEXPR duration_type get_neg_offset(const date_type& d) const
      {
        month_adjustor_type m_adj(_y.as_number() * 12);
        return duration_type(m_adj.get_neg_offset(d));
      }
      BOOST_CXX14_CONSTEXPR duration_type get_offset(const date_type& d) const
      {
        month_adjustor_type m_adj(_y.as_number() * 12);
        return duration_type(m_adj.get_offset(d));
      }
      BOOST_CXX14_CONSTEXPR bool operator==(const years_type& rhs) const
      {
        return(_y == rhs._y);
      }
      bool operator!=(const years_type& rhs) const
      {
        return(_y != rhs._y);
      }
      BOOST_CXX14_CONSTEXPR years_type operator+(const years_type& rhs)const
      {
        return years_type(_y + rhs._y);
      }
      BOOST_CXX14_CONSTEXPR years_type& operator+=(const years_type& rhs)
      {
        _y = _y + rhs._y;
        return *this;
      }
      BOOST_CXX14_CONSTEXPR years_type operator-(const years_type& rhs)const
      {
        return years_type(_y - rhs._y);
      }
      BOOST_CXX14_CONSTEXPR years_type& operator-=(const years_type& rhs)
      {
        _y = _y - rhs._y;
        return *this;
      }
      BOOST_CXX14_CONSTEXPR years_type operator*(const int_type rhs)const
      {
        return years_type(_y * rhs);
      }
      BOOST_CXX14_CONSTEXPR years_type& operator*=(const int_type rhs)
      {
        _y = _y * rhs;
        return *this;
      }
      BOOST_CXX14_CONSTEXPR years_type operator/(const int_type rhs)const
      {
        return years_type(_y / rhs);
      }
      BOOST_CXX14_CONSTEXPR years_type& operator/=(const int_type rhs)
      {
        _y = _y / rhs;
        return *this;
      }
      BOOST_CXX14_CONSTEXPR months_type operator+(const months_type& m) const
      {
        return(months_type(_y * 12 + m.number_of_months()));
      }
      BOOST_CXX14_CONSTEXPR months_type operator-(const months_type& m) const
      {
        return(months_type(_y * 12 - m.number_of_months()));
      }
      //
      BOOST_CXX14_CONSTEXPR friend date_type operator+(const date_type& d, const years_type& y)
      {
        return d + y.get_offset(d);
      }
      BOOST_CXX14_CONSTEXPR friend date_type operator+=(date_type& d, const years_type& y)
      {
        return d += y.get_offset(d);
      }
      BOOST_CXX14_CONSTEXPR friend date_type operator-(const date_type& d, const years_type& y)
      {
        // get_neg_offset returns a negative duration, so we add
        return d + y.get_neg_offset(d);
      }
      BOOST_CXX14_CONSTEXPR friend date_type operator-=(date_type& d, const years_type& y)
      {
        // get_neg_offset returns a negative duration, so we add
        return d += y.get_neg_offset(d);
      }
    private:
      int_rep _y;
  };
}} // namespace boost::date_time

#endif // DATE_DURATION_TYPES_HPP___

/* date_duration_types.hpp
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
*/