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
NuRBL4HwX35tJTy2KK057G1HzI38YPQ2sbmZIaAWRWlxEJjUB1pQdMiN4colamMYtAeASioAqbCQrKB3NGgy/B/lMW8ywZ5sW+VMtpbccsOemLbX3ClNgg5AQyzdvPsH5fp/4xHyfVKj7ofOF/PfFmw1SiWLEPLO4V7PnZsXSgGlneF0JG/4iaNmif2Tlmly/JPDxkexmHXhC3au0HraOlzyj5N7enIPUIfUMSZ//4hHtYpYE4DIYq3W4wHBgdM1QnkqHHCjE8VqfNFB+BlY3xvSVoDkoz5TtDY/EPUoKEgUC+WqQmRH8yhgHF2heofpvlcqsSJ9P4vFlK5JrzoXOLh/WWmBCrWc4bCQMZuw7s97gibyXdGxaZsLWOprQrS9USG2Nvz0Rs0KPUW5GDB0e2WrN76C/uMkqL1tJKIGT0loU5RdQS5ZECZ3TrogSGilVKJBuvWuPsXSeqZQuVAvrH0WvJW41zHaN0YxWqphZlRiub2Tl+sCqvtqp+T78STdL/vnLOvJfemDJD/ePPkj0quNoyCrL5UOD8Ynt39OVt6h6FX+ChRFO8wb9Hou1sv4YpSYgwPjmjtVNh67etlcTaUxCmJP6A1a3Cecuf+Q96jvPUVvoy/Ve9SvThbme5PFUmxhVkDKS1UrAi6s4S1B1bQ5zS7XdVDNikCW9PoLXm7Y5hDkpc3nfXGtDi+IhtSotcie80eKuuVJG3BntH9gq/t9CqUHrB92M53zIte6Ulj/mAq35nNVGQ/ONv1zY0XKGq3xS1BIcJRUDHSbR5+RJ9IsGrWFPeEDh6KmIOo6FyTzssZceS71xHylY6A82tN2r1DnHFSE3VdvGGERFMrbnL8+OyfuUBIaicZRjI+VYkUSlrLlSWNtp9uC8+RdNlkggHzPFg5JQj3D7u5UPrDPx9BoJlCKeLy7QDHlXahciU08qptGV7WRL45mGZq8GrofWz/CGAJXoh3kefd4izpeWFl7lBPw/8TIBnoSeM8Kd29CcFN7+49LZkqNrZtb3HFSPrdzrNfQv4/CnHmSMnh2i3BMtfJqsc3anrmhyQ1zFWaybbFeb386Su8NFvL+KTJcj8XsEi5o7YmyoMjvbhwshGB0+NjrUL1S9EodHbZEfyPudaToi3X0HEu0kYchk6Jn6+jjrcCRG8TvLrraSRNb/0ObcUn1I71nSCMG9x/Rl4SyeH0OxcTvyn/qo4RAKZXzDuz/e3r8+ZmHilM8P7NEZUWuUb4O7+cXmSYmlDftVJkzJXy7JuTPPLq9/HHZt58tspu5fzdf5u6QXsqPG/KReNKF/hnDmze1TZ/qs62u1bO1ixqng8/4VSoXNWPr2sbBZIIeDI4G5g/PpYE5hMu4zyS2jNBMSMOZ+yUKpchnESn6WA+HXPpO99m2KUivgr6lUcoUn1LF/Bx3sdCkfENwWOTzEchsTkCA/BgSybH/dCovcgqhAMf+ZY0vcP6xlJ9npSra9qAsyxDOxZ+E8qBVIBy6rPBYvo510Qxs/fasCNjis2ju1cjzxJuHe+sLRCK6cCBGj3z3WN6z0VfF+z7vsB3wC5iFOaVD/hatPLzaNOoQbWa6fpMUx5R6A6qGmqRmT1MHyC+epeb7pul6vq/mGzFW8vQTcaGxTUmKD8IXsiT10fGQpO6DJPWmlqTCE0XrYhtXnaYOZWo3BYMwn+E1vBpxkt0/C+oL3WeKzkGWmqMXjhWvS+tyboCK9WDMiMgJCJx1tc1UIHKGnwyQhnSY7L7RVCMIchA+1szZ53uslv5ee6ZqOlTJlRvqzvUtPJ4w7RftoyL6hLI4os8xFAFXgej7He7HxdsfO1Rx7l3TdHvWqtMNfNa61aXtTUoQc5c=
*/