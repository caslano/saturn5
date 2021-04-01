/* Copyright 2003-2015 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_VALUE_COMPARE_HPP
#define BOOST_MULTI_INDEX_DETAIL_VALUE_COMPARE_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/call_traits.hpp>

namespace boost{

namespace multi_index{

namespace detail{

template<typename Value,typename KeyFromValue,typename Compare>
struct value_comparison
{
  typedef Value first_argument_type;
  typedef Value second_argument_type;
  typedef bool  result_type;

  value_comparison(
    const KeyFromValue& key_=KeyFromValue(),const Compare& comp_=Compare()):
    key(key_),comp(comp_)
  {
  }

  bool operator()(
    typename call_traits<Value>::param_type x,
    typename call_traits<Value>::param_type y)const
  {
    return comp(key(x),key(y));
  }

private:
  KeyFromValue key;
  Compare      comp;
};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* value_compare.hpp
bgiJ5yQW6a7qJJSEX5z5hkBp1q3D2avJIel8O9N77sxnFzunXVY7rxr7jdhAlEb0mIQypH3u7blhtdHJKAPr3NpXVq7suH0ki8ui0v9MM4++cLEtg3Y8+Mpk996MSP+lCxb1zdxf48dg29oNQ6IvSIOrx8CZlJ0sKzYFSB7hqC/c0L1hfVZq3sLYLUZ0s5EV9AEixfSMRCLJmUT8PSIDIGEllR6k5jQOca78uLA8bbnfgVU/xuYpDUpGNmnSA933ef0aQ+p7+uzWK/zGAnm6oEtIJyDrTflbcRxKN/iHRw15W0J48RN7FfZ/kzsj38qiL7SKq/pBAbaB8QMbni07L/eNL8xDOI3A55/uUYWk9isAVf4+drbjW+emoTRNKLKNcmDAnH6LJo3H3JlaFMiO7xpx1oXkQIDUfTDalMr7WBM/Sahq05BG1t9KiKL3el2ej2JMQhhlyBslsxRvOgAx5Bwb5SEGcBS8ebIKNGfEaXAjenEc3FVAsHsVwqUN9u+pIlLebxc1lxPhaw3b+dPNESFgn69ZemD8giXc4WFplfJCbZUSB+rkupgz6A==
*/