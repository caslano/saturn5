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
emul1P1KmjapmigESq00304LLZ5GPcDFAoF5NyoDUwV2yGiioPq/ZAX1Jfu/wYOZjw1MnUJxnEtI3Tu3yo3OVygffRfvOaTAcMSmwpBZAAW6ghM76/sRe+cl0TsI/cIZRJC9lyHxlcTie7B0hdUYPEMIc92feOuyJKfkZZYLw35UQ0peXWfQ/tIA6R5jibgyOBOvhwoTcKyHqjV8v5R9JCoD+DqvF7akBc9F/D9yWeR6/Ey30R3GxlD2BC1B+V2B+AORT3ZGMzEq245EVvW2jAbepQJ/k98RCsNLSMtg1aqJ9nCz0BsCd5sii5iQFM2vEwVui1OIUKQP3A4AwS9cf+FKcYnb9+VC6aQGA8vykAROc+A9571yGQZssuyhV9LD2Z3CMFega90nZ9atxOCpt6bPkvdbowS4/NCtAoLzt0I6up49Hhy4lp/FuCoPISfeLpZU7b13o4WHXzJqFhA184oQDOJ0NlZKJ6n8/7l0btysom2yKCYC1eLB0iaZu8JkSrgVA3uB2ilsjJZcF0/yQEx8O9iAHwBWQIomB1HdRdMgpHfwGLKMJE49+QDMfwzyhL6bpXRXyVpgAWGPl1GTSXiUQvp0+ipqaGOrSVBFeUiewthHH+MZSU5VtHqUM68gTDRuqnTlafqT/RpK+z3N5hletsv4d6eNsxrEx8adjQ3ww5TxjYFVxddzbwyok9urs1upexLEGUfBLnT0WFbTFbcmMVaMXQt7mAFvPUgPvvaAKs8St6iY4ij1Ep7sgyJ5buhnX1vq/MPYlpV8S5QPnlBumtFvb82mcjadfTrlA2xcc/zwWh/PrUTsQmKmi0Yjk2A+//06A/CuPfLPRHpCunGFxeMCiBGbOMSXHiA5cmPqkwA28VWmGIOBE9dRRyl81wqjQ/gHs9iqNWPJYq2iL84PRX3HwJ85qH2m4c9XlhsBeNMlau1RPtQA//zN9b6um4FhFaihcGck/WQMG6LMaeR2Fcms1ZcECzpVz/tEwmm/ttFhE7SlsKSjoFqrFAdOfERBS5fB+ru6kBstq0W+rARXDg/wwT+mANfbKSwHh3NHnzx2sXuYk3Mo2bIS2Z17jHxGSlZ1OfNdi5dbY+vaiAJBk9YovH3X1EIvn01MLxq8ZuTYmSSH13w9Lio9Reyn9AfR2GLJdZMdJwvcA47k+89iP0rxUK8x380fvUQlbXXnm0/3BZHARNk6o7RBjukQfVMSCrt4RewcROo6TSqNXy8D1M9gaeBNAWwG+CwWg2z3UQMZDz7pPcLoWWaFlg7AFcaWd9GNyhP0oHeBYz/Yt7oRaSy1xmbxPkMbvJXde+fNNRpsGhWmGX2LNmO3qXSKJinOu7++3Ck9Gp3XSd6o093kpxLnTI9vrh7GxjRDlKLO9Wk56wyjaTahddJDF54KD5YzwB42BU9iyOWzGQwQuBuRXqw0OKyjvnoymzkyHF+FBQo5aU6gORqht2sK6d/aci2BgTOAsAXvC8I+t6uNNhnD5QX7r1CYB1KwI7gfw0BBg4oVfjb8OjLheEJcVsC7GKG805bOk7UBKSOWMC1nMKB7oE1qPNpWBIHbqjfVpua7KZs5bn9H5rBtf96mg2iaoihO29ZWGmbRc/DDjStybOsz1W0zdyAfzqAZMKyKNqzOv+BBhn4kLzO5+k7lseU6xoqN4sM3iXlTgqgUS0QtK91DGsamCjfCPWHGRu3dqVhBzq7TaRIbP5KJGFK4DzN4mgEZiOkjpXkVKdyVKtoolfQ2TG4anVsq0A3evnJszxEAedg6qlXr0Qigtt90db/s8YDwUXupyyOrdVo1/qdYbDKD2BXSG0okbIvqhMx3u2Y+aS06lfBC8bUQ2CBj8fJfdPNmbzUygFXbAorFMEyg7WUraksqVA9f0x8MGU7sVlCEE5Wt5zmOsVpz62e6GI6PoGCah33vU8NIj0zKhGTiWI1wtnIVpVRdGGh2NU9A6ZiYIsSZIJSsvXPyy6FUrn9XEIdp57BhIysFmI2MLVbONVAdCyiLxOYF91U318P+UOkrJ9t5Ey+p2aFtoVQ133wrb29q2U1hUghpfWFM9JlH4TXeMtfIBSKhjqZpvn65kVUYVxHL5OfgR2zj0i2HnLB6nWx6gxYfokBVC/ZUU15kRmhG3rgUePdlsaW3VhRjP1M+FDJjWv4nIGTK64BZVPiQrKc1ymbv+OQGM1jQQWgUiEbe4HyAf4FgRTzYM3xpWQGr63lUud+FiyXVMrg4dnaqExQhEnClBR7qdIN4ssj2GUIwGejTLAYedoRRkizUinEWhnxc+SITF/8oN/JeYnhbtcmefkExSo1xtwoA66/3R6DFoqqcB2U7qax0OadlXsFBdGm4qIOpKqWiiMovAKwRG+8VmF3rXucoWgeGfSRndIYGjeQv4+gVTd1Fw66KKCRqzZC7AY3ZkZJSBbv2PpVFG+VjgefVNUt9AyEje1bmQWHBSQnKcaYVGtjDHMlptCdXZuI2D4KYgzo0GkfQm8PKzPJH2yb1AXw50ggD8A8x7g/kJrkFTWLl/I4GsJDHo4Syr3ktz6QChDxIO/BOEQ+3KdRQWBW8ToHZtEV1gITenagwjMFi3H3hszURN53CSrBNx/eXLB8iJBdGd7bNLFEhoO1OGI+2x9diqBhPLtXHFVYXdTg45dHSDV/RuDe5MJ+fhiCWHqQiMflMff1FTN4fZKZsqaG9stFxgkJbfezGfveZbGY2NsNsbmloRV9uo9P5AztuKo2/QS+eLEyUyu3mA/Z4XG+5R0fLlZjPfZnE3x+IQIQXvOndezebfGIrzQNcxb6fywAILPfTJjornVmcMVSfjIilZ4qN3R0Vss+ANQQu/pfrEK39rQizR1jjboWVCyC/DQER2xFXfUC/31ENpDACn70Btlzb+fqhBqE1RL8oToPjuSF4PxqHp0LX6wLIsuqOXISMonLDnm4jigHJV46Adc3M2ETaPfQbxCdiws5YUBhcigtSLyGHuFUe02np+tYw+V4CaUKFg4ekQDLzm0862Cr2TphhedeeJaXRQjRu45DFJvORAralVGUEe7TJWuV+iSM6qRtQ6Ydf3IvUYzmWoxGfuANgzNQ742HwE9kxb5RM+8wDafAvYaWB4DA18728H7lGu6fU6ojmC09WrS2PcHOAMe97ylEQc+yQg/iIGMPjDLt6W5lx8crLURyyUcDQS+PrSsbP4hpGNvZpV6brXbpwJuIgTc6P7sXRqc+igxsiIfqWJNXxfb2Q3Se4u0PBR69l4OKN/5t6MnDOt1sgJZM7awt2luw6qBg1YLXfoGIU/EmH6aqi1gzNSvPLIhqZqBQi/lH09VniDHvcqfMChYBzL5wv4DtMlDN2RHUBlYhcqw2vBnojsnEOI/b/bxz35PVO3+WEOJY59RBmljwWSFiCfYEoVSisYwbIi+M1n8uh4tv1TAvsragH4jljwUgKgEbt+Fa5/1J+zlWOproLCBO3UCmGzk1M04aaneoL5q7qfINL6oSiJ04FzugF5ayF2yVVFMJcABOkVM1kmkFj/buLKeGxenK50gYHCxIfiD76dBJkOXpfJ1ZAB49yvvWMbOknuUpBL+avzXXgI3TxWVdTnJ3Q7MXnXq05/lVfwtAy5fqSnYAjwCQb6w+ss0RPy0XXKW+SoaU+Tm60HbfAl0RWAlXVQOzoUvqbqpgaGUVkfZN+MN8KTQl7v01FvnDeKu9M/XL56e68bDXfANk95Nw/85BpgrXZEXbCoVY11GVlTpODtey5PbvCUg+Kq4t0mOZNTpBWHhoWghOufCcAsP3i8Cs9timIOTbWxCNR8tHxA3lyba3pvs1U7wT26fn0zTpR2NrQmQnNroX0qu+rURa7S9IsSTw6HBBehCLkMZ811ipl/BrjOiIo4DLXnfsGhB1+6bi+zJd3dbq4Lz5q9lm447BqTzlC/rWgcHGQAqSxSS9mblQgZrclJ4OYXA0dScKcNh021c28BFRbbyJEvEuGJ2p+RMHvsf2SNiESOdT+c2Q6VQ3JPzrX7ZlBzzElM/BJ7oE7KuVwGCtAzv6UB+Hl3hAB+h+2aRWYfRc+mWfUCxSbZ3MyRWympv/hq1kRWL2ftksfNfdWN+oH9dko2tN7GFTBDnVNFaXEXbGAiM72BUzJQ6MWl375qxHztIlPhAejBBpVSstn/HtzZwkT9EqmsbHhLjsRoBPviJalqJ/0M3hiA9p5mQ7R6UuFpFQyRblV0oprP7bLiYBAMHWM3NYzUy4Ght60AX3Ry/E5/c/5sqqZfGmRl2FjZYmgXtJvRL3M+ysnAiKAQLSzWCLQxkITU/6IGQE0XsZvw03ZiQAw06EOa0Jh+2oqF4LW74q3qp0kwAthy0NQWHN4a04mUu8loKyrItxK3g29ItdOWYezVxzs3TQAgRc09U1wGYb1fOaaudNYmS4wUPR3ohKvRiHhrtQu4j1bb6kGB29IlIaDAqBuZ3/Jml0quktYin4sUMw/NDcD6FPp5oPUAnIIf5lpdMY4fafWholvk/0Q+Gr6aAMHquc3Fs7/1B7IgV3owRXdns7kXuNpYjDLq1KN0Og44pLh9U9JFh/+kgitaps8c09XcxX2W6I2UJ1xufpbo0g4LYcuTahjecXfXUAHu3+xbAIGqIv90mRw+3r0FXklApp3mUZ4QMs6BHXTR+U9LelCdY6C464/Y/lcvn6D0KEilgeXpX/A4knsXXaFMVlc71yAFoEtrnx3cvuHhuaanc96u2FD6M8Avv82NDUdjyBEuQUMvfHdjQL+JRIqiWC1JPvKjwsUZ5h6wsA9aWyUqevjGEAnWjBeO9PWR0GOVMgVcY55Ra1M81sqW8hRdrfhKMwckpm0c8zIUse7lAa7C6Cn30cqUH/405VT0n+GBsW1M5XDL6GdBHBMUuhh9Yk4BpQVrk5m3V9fyx2+wKQ4XhkVOd86MsZEJ9kzGLwq31WRxdUHbzGiaf7OWgCFuI+2ux5QXVH844Be7MbC30mlZNSETFbCv8SM6y/zh0G2uvCwLzALYfH0RD1whbekgsuNT3tgxbrfY4x59RbhkHIkT3m6/BCqiiuO/4yLu0s/fOUa4k1sdV52j2/Q0YnYQwe5mqBUeZjKd5wfSOev3q4Y6jnFKvVY0deKPED0g86xincDROodf1hDlAKG6s07ntxD65EaC7A3zCOGdTtDbfLkH09Bq/iIKn3EtMvbr8E22E/e4Dc9b0R7o67AuSpTmcM0kMI2XMDjUqppoH9fOkPv2o3lmUHkIpdeI6MBXL+qHTlJgyq6/P6l23vIBPRP6H5B7HM+f+Zh4nwRxslOsDZAKiIZ8D8xFKSR0kgPcdEqr631DIMN7chqepOiuaihkx9jG2kfh5LBE6T1AMKjxrf4Mcnc913iDA7khjPgcU9CpKKSjnGwP3vtfPxh6vlSk++sWBjSXOSppirHEHhyqjMPzro/uI7+8PSFRDKY2D8UTxCf7N5hSFRi241/c4l3di2o20UTMq9kdNL9W2lBz4PX0OWH6u1HXB0a5hsvUefXhR4hO4KZFog747pMXjOfzj0PpM9X7LijlbeCn8SgpOS2TM1NqkuebNihVElCSPV81OCPgDt9JWAyjb1CX2t7DESFGfKm01LJqK+UWstofzTBZ70THPpVcmxcepcM6whBr/P4FYvkfoSi964cwDu1qF5HXMNheLcuoBsJ0mAif10fD+Ik9XSrJQHxwcbzg+tjeG1KrLZUEJ32VpMlo9/QCrwzlkilrd553mONjXsd8L41OUq0JJQuDjkO0bKGD7volbn8RUz9GO3iaM6A9r36XHasXZSqj/DcqrzVwhSYhF2RPPo1zr0Q7t7lIIKiRWPfsltcVyOWpLdcui+/U7lpuVT4dCuMfOcavWDFUjlNgefRpIbkBRLyFRAxvQdmX6TozJBUYmui/Cu0fJ1Ry2S41NxvuE2KmJo/hnYj38VekCr4e/waXXJihSxkXxhsIoMNxTTqrCn7/uLqxThOOYowU8frmR0osmTkn7Hveag6DqMdHgwnzjS1XNjyVmTgMpoQzsQZ+ddWRJIfDqIeKH01KzBDFWQOtIbZBXcFdknw8F9nI7Na8bKEgWAj/B0GIO/QYzZSVTLgCzUS5alDfM9rBZI+d+eE/Y3lY0FR2OJ7fd9cKRCkOYpUR8bER5DuxSw1YvO2JQr/pfpzG0gT2vdWF5N94A3661JZFm+38lOOChkDVFAC0wZ8sS5oAQ6S3G8yqDYjSRwGzLRka5OpupyPm4p54msfnV5ogpOMKYaTIIc9ZuU+XSUIMdNsCAEA2+Ez1SfKjIDn65htgwWgjiZ2kB55CENcOI8Rac/WoTqcYlHabsRT9AjARRoNtFllaT69BldiUPN2Y65wWo5RBrUrYzqykIOcHTTgRjxti9WT3Pj6ZBcQP9W6l6Kq3OsK3J0cdka4YSWMEDFytHGgQCyrHFsz5G6gDv+GNvxEIpXQYxZVvWBVD6+C+zXmQNJerTGScPx22a1qTPx2MN1PXBEY3lny4jyuYjfXCUezDoPBcayztpr2uP4OIX9A9MBaHkr37smCt7ItqoZbaLpIcw7ZIQbbPAwwBqELJmo4Lsx1XM9jsOINcMkwviIvxYnv+6S51jzRL/lBRWeRFB+j50waw5ma2uBu1RefLtQXMt16g7PsblacsfHDCVAi2ao1rIxqCqeorWPffv4xCVhqHCSW/+BkRwq5i7RleJCwQhnAQiBWEqKb3BCH4T33tEUkeBtg7mQcxxXyzQdoI/K/WcVfOck5Vq8BtyuJXuBXVhLP9OMwedvj6JERaAlkG4samwnRYM6FLtLWyl2DxZF+zfuOtwM01ob+aplPY71xekL4/R+pw+lkRG8fpD3Z4SKsYAdSOm4uy+uvixeR3wOHMMeOttGsU1fGqMG8NWtg6LGMFijLRFVuXLJn16pWAwifLT7gVW0ClMvnOf/+Wcgqfi49/pZvcUViisw6E90RRIxPNOko+tbcEFAWmNEGbUI/HO2YAgKyHS0FmJVbPsT/JdRuFA4xH8uZY2W8Srx83mHPUH76jegG4lxo0HivBTzkSPRHkjM6k0UgvEIqq1jtEoiyiyPbTdm2ckFwKzranQq+LYeF3lgtRYRoQW4bhZBP5CivPl87Pr9DGO3HcNSW2sqaM9DKnE88Dfa+Gr4AUF7yUTwz4zKjGVubAzGsQfCiIgAwRgRdhQ2E0z1ukY+ppz8dyAMZg4t4/DYb1/P095h87IOlb54prB3qsuqeApIQpwwX82UL96ylk+lluJRTPvw31LYCXqj8rCYiUuqx/Td69JzvZ55se624Ok79DwItt3GYkc5Sxdq3GxokMoY1iPJLf9rqLZTTYp2CRm1XFuSSRwICT7iiU33rHWvsg2c9UGP+7EkwnggsOolyZyOgo65dWUErdWLSm0oYS8JL8mI9WYFyl9xUEPw3BILIjND5CTq4UUOpcgWrcsorbp/G4GbnWjNUqi7yxO8BbRo6AoWNFVm4r4lx6FyVGZmcQhK9ixXvdMLkqY8tQNmTXojsjIIRlKmKuLyxLMOS0Ykqkxsm6RTxVVkoPiYLUnF/jjJRyvJMfd99+gsDlUpCP2zATE7yHNK/hiS/piVoote7ly5/swtyXlMy8XyjRyJ3gelMEeAjqa3vViPIm2nmR/pO55/7MbUZg9C7BZjl+Wks46nxdUSbp1Q7wilnvuBxr0p/XVpmX63KU7ZiJr/HLH5EApF3W5lRfZAJBEoH2DO8OvvOXbazG3bFv4irXr6eiU0iHgogFixSsrTvALpnVAc9NGEETqm370d3pDCtOh57eTN8ye7sVjgxqkp1gYifxv01e5RSS5PBAo4t8sUFBHPul+1BgmRQ17V5Joy+gD5XauU976H9cP+1bg7/grZhHMrm7ejZziO9Nw9rmfVeKSFaF7fk1dGKsTbY2X40CjA9KqL30pTeJ12T7bcIy/6AYNSAyz76K2MRB8QGLqd5iMfbawLvsSzfmLYjcl1Tn2akIRNkjOVe400AlKxr7CmQIkfAO/kfljvcprAV/tHfNvgokXdNRJSN9kcMEuuU2Rf+UAy/bHffCGfauN1oVzizbJkOn73T+FwGpSvxzGj7p5IDLbZDfRrrqySrPMyr0G6sWi3bbdDKrifVS6Qiw64+bNQa5ojHPh3fGxJfzvmLTIyK6HvjU4r/sXiNLnopcnJ5Kp1ZN52QXhWKDyjIxasOh17XcdH7RTZzVVmkd+rzIpHYkODIbHrRPMv4KX8/tqIhSuzr+Jdaxy3VdjiQLHKOPfgIC1InPkhIHL92YvR/iaFEP+PElINgIpri40kqPqMhJU80pQFH4L9REiFlIcQiW6PGCnWpws5I7eDBeE179z7oMjbUm/zf2vE+1B6F5NfujmiveR/CZ5iy0TqpS0bCTPXO9Df/uaTlYmfS51RFsST41ya0EMIRWVdQe9YsxYlEBjcHM0peYZ+HyJZcbxRqrxt0ZQddI85Lba5QRJNAUXeDpUelCo2TDTCBcO9blpPmu4L3hqykmeoAHknqtS80lXhvj+U2Ns86FlVgZMrC5Z2YTJAB5Ud5vlfjcjNQIV1Jx/TxBnJ7F+knZS39dqsZKe1j0bRQjDhRpVZ4Em64Ezzjkj6FyyTKvuoFVRgkiqvsX0zAxGqOMshbRrM7NXEz5EJ03wv786RRNH+Kuk2DQQgxNwwQryivlE8d8srLd/XztxuvJnK1t3Wz0ri6DEn94uczPJ1WBU4FGFczW8P4XaBYdn7N97CJIhQeSoPyt5BMy1X0+ywcOJ8u7SrYnjMqWqg9ri2uAGL3pw4xjTsZfarmxIDgovlWjpBR+dsjeCH97Xua0JtWHw9WLDhyPPxkWqf//toODMMNvAEAQ7LVwD/Fyj7EibVnObSATAXCBjJcjDKC4APUSYLihITQouMAlNLzjpH/PNgGLAtLi4JZ3/L9/8GBqfeAdwnBSlcCyVTazSOH6UvqMBkx2DUOsMJuFkiRvfKSpnRL7aPFv9MchuKMdglAQ8xXgs6ySOXPgt7MaVnNJvzBtt3+rxkvuCLw/pEDJb3yriwSGcn6VpBi/gHCCyHGlKQhC2eATUFO8jKxqFQBNcHoJCtngffKdfdd/w24FD6b9skSbOcHEE0JWpGR9NmlB7LbWr7opr1IRMW8ch8Vh6BdPIC5qnnihIHgoVPR9jI=
*/