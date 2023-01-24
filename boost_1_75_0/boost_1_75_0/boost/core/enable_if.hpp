// Boost enable_if library

// Copyright 2003 (c) The Trustees of Indiana University.

// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//    Authors: Jaakko Jarvi (jajarvi at osl.iu.edu)
//             Jeremiah Willcock (jewillco at osl.iu.edu)
//             Andrew Lumsdaine (lums at osl.iu.edu)


#ifndef BOOST_CORE_ENABLE_IF_HPP
#define BOOST_CORE_ENABLE_IF_HPP

#include "boost/config.hpp"

// Even the definition of enable_if causes problems on some compilers,
// so it's macroed out for all compilers that do not support SFINAE

#ifndef BOOST_NO_SFINAE

namespace boost
{
  template<typename T, typename R=void>
  struct enable_if_has_type
  {
    typedef R type;
  };
 
  template <bool B, class T = void>
  struct enable_if_c {
    typedef T type;
  };

  template <class T>
  struct enable_if_c<false, T> {};

  template <class Cond, class T = void> 
  struct enable_if : public enable_if_c<Cond::value, T> {};

  template <bool B, class T>
  struct lazy_enable_if_c {
    typedef typename T::type type;
  };

  template <class T>
  struct lazy_enable_if_c<false, T> {};

  template <class Cond, class T> 
  struct lazy_enable_if : public lazy_enable_if_c<Cond::value, T> {};


  template <bool B, class T = void>
  struct disable_if_c {
    typedef T type;
  };

  template <class T>
  struct disable_if_c<true, T> {};

  template <class Cond, class T = void> 
  struct disable_if : public disable_if_c<Cond::value, T> {};

  template <bool B, class T>
  struct lazy_disable_if_c {
    typedef typename T::type type;
  };

  template <class T>
  struct lazy_disable_if_c<true, T> {};

  template <class Cond, class T> 
  struct lazy_disable_if : public lazy_disable_if_c<Cond::value, T> {};

} // namespace boost

#else

namespace boost {

  namespace detail { typedef void enable_if_default_T; }

  template <typename T>
  struct enable_if_does_not_work_on_this_compiler;

  template<typename T, typename R=void>
  struct enable_if_has_type : enable_if_does_not_work_on_this_compiler<T>
  { };

  template <bool B, class T = detail::enable_if_default_T>
  struct enable_if_c : enable_if_does_not_work_on_this_compiler<T>
  { };

  template <bool B, class T = detail::enable_if_default_T> 
  struct disable_if_c : enable_if_does_not_work_on_this_compiler<T>
  { };

  template <bool B, class T = detail::enable_if_default_T> 
  struct lazy_enable_if_c : enable_if_does_not_work_on_this_compiler<T>
  { };

  template <bool B, class T = detail::enable_if_default_T> 
  struct lazy_disable_if_c : enable_if_does_not_work_on_this_compiler<T>
  { };

  template <class Cond, class T = detail::enable_if_default_T> 
  struct enable_if : enable_if_does_not_work_on_this_compiler<T>
  { };

  template <class Cond, class T = detail::enable_if_default_T> 
  struct disable_if : enable_if_does_not_work_on_this_compiler<T>
  { };

  template <class Cond, class T = detail::enable_if_default_T> 
  struct lazy_enable_if : enable_if_does_not_work_on_this_compiler<T>
  { };

  template <class Cond, class T = detail::enable_if_default_T> 
  struct lazy_disable_if : enable_if_does_not_work_on_this_compiler<T>
  { };

} // namespace boost

#endif // BOOST_NO_SFINAE

#endif

/* enable_if.hpp
YVBhoREWYY9jaVJEql6ljTfoylEWBPrOpOwYfqOQYduewL0zZPCodJVCmarVTBdou5LAfJmiUpWhw9hyuTB34SP1zIS6TDPo9CqDabrMZFApyhO1cjy3dQPHOml0en5+liwtPTUtLj1jkiwjPS4qWfjKmJQWJ2dxMS8PyWU5xJSlZeTLEpPTkgDFcDgv1VESa+RxQuJ8WVxMRmJqijyIn/9wkdLfEuMMBp0hSVcCaQW4M8mKi1IqGUYotxt5epzeWIN8s/4lwF1JpJ8+rrpIpU/UFuu4cqLP6UA8u2KdYJwbdmh37BtSVFQqlNsqj3ZkxSYuazPKjOtASsL0TRJGFZkqUAAQf8keZanfWH2lUW/Um8zpXEjpy/pKhQEkpQKyE/GrPK4XFVpoFxei3iKbqtZn6OK0SrlIb5HGfEEOuMay5OVMJgQJDSjMKflKL/7QrH1TK0yIX4++LOmXKzeoTQJP1Ux+nPoIrCIM9497EL+txpoktVYVoysvZ6IpxzzwHIsHia5mechqoozRICF8XivbYF1czjXWcKXG+P72aLdVZ0arStRaM1ecxsI06Cc6Er8Rxpqm9X7iB73eVknkojoenqFXVsXodFPVKp6/xW3RLoreALXYhJq43jq+JyQT6q0t2X0xXlNhLBXVvTvZ/JDrQxxxC93ue0TsmOO3JS+0jdHojMgLztnh/KmX9Ls3UHdFV6g1ymSFFkYu
*/