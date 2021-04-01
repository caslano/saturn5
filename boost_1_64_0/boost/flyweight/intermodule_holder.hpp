/* Copyright 2006-2011 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_INTERMODULE_HOLDER_HPP
#define BOOST_FLYWEIGHT_INTERMODULE_HOLDER_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/flyweight/holder_tag.hpp>
#include <boost/flyweight/intermodule_holder_fwd.hpp>
#include <boost/interprocess/detail/intermodule_singleton.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

/* intermodule_holder_class guarantees a unique instance across all dynamic
 * modules of a program.
 */

namespace boost{

namespace flyweights{

template<typename C>
struct intermodule_holder_class:
  interprocess::ipcdetail::intermodule_singleton<C,true>,
  holder_marker
{
  typedef intermodule_holder_class type;
  BOOST_MPL_AUX_LAMBDA_SUPPORT(1,intermodule_holder_class,(C))
};

/* intermodule_holder_class specifier */

struct intermodule_holder:holder_marker
{
  template<typename C>
  struct apply
  {
    typedef intermodule_holder_class<C> type;
  };
};

} /* namespace flyweights */

} /* namespace boost */

#endif

/* intermodule_holder.hpp
bSLc61ZsmglIg0agYFlatiGQI53BDVWBvGd43x3LZVlYevYswjQzMUqX8IFvJt2FTMLi82B3Ydslj3cBEgIL9b9AAcu2muHTpPd59/jg1474dbXUushobSL3OhsvSSUFGohkeVLGdX6dA8mEM1KmW2VfKq4pOFD8QBou8oUYCseJDkHyiTHgpeagifeG138ZKNvPAkXCbGi+Ug45LNAcvrH75vtnwUzYj+bUx6TEx68kQoTUKrHI3uHtYLNOQGR056r+ZJUH3hhjJrDAVRQUCDLMeAv+ONfIOSI0pWCrz+XS95ZdDcaPbLCNj2zJeh/FADchecLoyneBKCDBTdy4S48gP/QCkGkB9VPFxF/I+ltD0kEefcjY/b65yTpU6sncovoVYsu0DCN7k/04GqHDx8d81wh7EErAg/iM+p+3RR/C3d0/NS+bNOrGoBFoi2EtMo+a+/JBwsYaIpQOmzPD+cvPPLbySO7tlqChVhK7o/qfUhWU1oY0+hl6GGWFu8mdWjdOTxgBQ8mpo+pfPq3ymfUaWa3KcduoWgq8LALVcuXA26l6JpjFLPRfoA==
*/