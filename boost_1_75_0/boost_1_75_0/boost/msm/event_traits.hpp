// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_EVENT_TRAITS_H
#define BOOST_MSM_EVENT_TRAITS_H

#include <boost/any.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace msm
{

template< typename Event > 
struct is_kleene_event
{
  // default: no event is a kleene event (kleene: matches any event in a transitions)
  typedef ::boost::mpl::false_ type;
};

// add this way in this namespace specializations for events which you want to use as kleene
// requirement: a copy-constructor matching the events which will be converted to this kleene
template<> 
struct is_kleene_event< boost::any >
{ 
  typedef ::boost::mpl::true_ type;
};

} } // boost::msm
#endif //BOOST_MSM_EVENT_TRAITS_H

/* event_traits.hpp
yQ20myAD96YKOFeJoRj8PQzzKavAtWm9iRFPgkQwjCFnq5yfq1TOT2WZJVpeYIEbG54DCtXKUS9v/6CX+/jlD1623mQPW09luklj7GMHGmQSlsXUUBo0j3iatWqzbuTd/mrRSYm8iJtnr2YCysRU/pdlJKm2r6XjRn58k19fzn9/zo8frvWzpq+y++p9pqgKNiGADb4Wb4vA9r06fs0onjJJ9sBdWu4BAafXSLAAd5HKeN7gX2VseIdURmNuIAikN+BNvZbWbLi+iP9VpS/+kvWFHAYnzinTeKyjWezLynAEKa0dPFHh/cRqyljcj9H2REZiu53XR+kCaRhZC03dCZI4Dj+9G7+ejKbrKNd+Rri+FaEUi27WncEtutJvJBn96Tfc/7WKHXn9929QXq9bRXe+XuWp66VcRKAAHizh05TS/qMopXRCouzHUhLef7pDveyTqCz73Cxh8RbAIgZMf4OzOxTN5pQ2hqI38ff7IMdh39XOdwmN4YgzSbwbZpwnys+ADdSxD/0iCbw/AX3Pwf4IdqtzOxmJZh8kZhASuXTEJ7yQaLYvq0BrvZ/RwpDIUOIcptcptvi27YCtG83Qwi7CFsOVTfomlbcd46qsI4Z4eycyHwrIfDBKqVk55mpXSpj7ayWiqZWMyl/oQkNCn44OtV8D9kq1kOLCf9wv4HHyxx4LIFK8nOz8OLpNjcEE8YJssi2UTLa3uYGc
*/