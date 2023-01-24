/* Copyright 2006-2009 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_STATIC_HOLDER_HPP
#define BOOST_FLYWEIGHT_STATIC_HOLDER_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/flyweight/static_holder_fwd.hpp>
#include <boost/flyweight/holder_tag.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

/* Simplest holder storing the T object as a local static variable.
 */

namespace boost{

namespace flyweights{

template<typename C>
struct static_holder_class:holder_marker
{
  static C& get()
  {
    static C c;
    return c;
  }

  typedef static_holder_class type;
  BOOST_MPL_AUX_LAMBDA_SUPPORT(1,static_holder_class,(C))
};

/* static_holder_class specifier */

struct static_holder:holder_marker
{
  template<typename C>
  struct apply
  {
    typedef static_holder_class<C> type;
  };
};

} /* namespace flyweights */

} /* namespace boost */

#endif

/* static_holder.hpp
AHbr9M4ajjqgt2+pt+/IcjxXTucQWTZ9KZtKiY745Uv688go8xiB04jAKr6IssA3nvFVJvU8o2I9+SM+A6+EEOcZ5YE2nu5rSmczCbohXb6WLpene53SgaihKrNnj9Ez2P2jlmHPPPQsG55l8Wd30rMstVGhjFStjCQuyWDXhs/0wn4ewmb35+iIfu7pP4ZYh7lGS/KgVOPJmdSgkzNbfohmZ2fIq+FMdx4lLcx5mWtHh/Br32cSlpjRP+hpzsF4N4NTpd5/uuPyGlruoZ1Z2K8bkUUI1TDv2oToT6SjzODPQmMxF2H2YCxWoHy7KfR0oULG7zhgkHo5QZoT1vumV0LajhedSQuNd+IYFZFPEw+E4hOghWQp1lEHMg1HVHodiIYzy18Ox5nm02m6+LcBc87SkYbg9WBCwmlGs1R/ul9vBt7CzcBHXADtjh3/IolNgT02W5anFoZCRXYn5jU0NzK+FfvmZANG2HOoXqKXRTbqTlv8l7FJ0e75QmEr3lvhuHVCUV4DWDjzV36I+vdmpQ7ss6QrPA2iumB213z39RwrfYu/iGUAnwHsWNBnrBfcxRV2Jmn37GPiHkRQSy8N/2MfF8akvn20T2y7hYnyjUa8opcMZ14NM6H7VBrMhFNOhekfF98SsX8M2Beuf+Qo1mv3GfuHdV80/eOxZeH6x4aTEfrH3JsDAoMep/6hrZ+f2au3pG4hS6oIC9q+
*/