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
eosJS6ixEUvwIysfz+8vUEsDBAoAAAAIAC1nSlK2SQvS+AAAAIwBAAAeAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0OTMwVVQFAAG2SCRgVZFBa4QwEIXvA/sfhl0W2oOk0FOX4GURVuiiq7H0muqIUjWShC3++8ZoV3pJZuB7bx4z3JKxpTQUAm+HWrnvm6YfpSsTQn4VKWR5JOBc5CK5ZtGtiHIBnG0MZ4sMDnDAnPSddGDaioBrGrtpBtbCE+eupcGuROkbhxivC8H0dnSCvxb5IHtacuCcA5/+BXl2BFsQ5KXqezlUi8mJseMlyUWcno6zOk0ywd5eXzD4XIyC2M15SFy5RvEhP0i39YSVtBJlbUmjbQjnTWEjDX4RDbg3jbJ74HfPOotRK6tK1YUQXd4TdMN2fnc7uBWxeznbCM4eMrYd4BdQSwMECgAAAAgALWdKUvt7ld7bAAAARQEAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q5MzFVVAUAAbZIJGBNkMFqwzAQRO/7FQvBR6MUnxoWQTAxLdjYKO45GGtDRGu5SKIhf9913TS9SBrm7ewgShzTOETWQM6fZ7ne+Xadg40ajk3fQWnqKnc+fzM1kHqYpFYeNlh+OPYp
*/