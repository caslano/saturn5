/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_INTERVAL_TRAITS_HPP_JOFA_100926
#define BOOST_ICL_INTERVAL_TRAITS_HPP_JOFA_100926

#include <boost/icl/type_traits/domain_type_of.hpp>
#include <boost/icl/type_traits/difference_type_of.hpp>
#include <boost/icl/type_traits/size_type_of.hpp>

namespace boost{ namespace icl
{

template<class Type> struct interval_traits;

template<class Type>
struct domain_type_of<interval_traits<Type> >
{
    typedef typename interval_traits<Type>::domain_type type;
};

//------------------------------------------------------------------------------
//- Adapter class
//------------------------------------------------------------------------------
template<class Type> struct interval_traits
{
    typedef interval_traits                     type;
    typedef typename domain_type_of<Type>::type domain_type;

    static Type construct(const domain_type& lo, const domain_type& up);

    static domain_type upper(const Type& inter_val);
    static domain_type lower(const Type& inter_val);
};

template<class Type>
struct difference_type_of<interval_traits<Type> >
{
    typedef typename interval_traits<Type>::domain_type domain_type;
    typedef typename difference_type_of<domain_type>::type type;
};

template<class Type>
struct size_type_of<interval_traits<Type> >
{
    typedef typename interval_traits<Type>::domain_type domain_type;
    typedef typename size_type_of<domain_type>::type type;
};

}} // namespace boost icl

#endif



/* interval_traits.hpp
8LvXBV2u/7Zzdliw7F1RJJh9txcV0IASYCCm/1aRAFfgBpYAL/A+8PmbPy/CVptF/q3bO30Ola0y5Jx6mzOUpsvO9+AhnYqcMw0lnYBCoSFgZgJWJuD+SsD/g0Hu3xwQf2f46/sLerP9TffpI6P/tvv6Ux8Bf2sbglOzbJuXIXscvp4ZysYnZhNk4q9k0t9pa3Py+HPreWcbZIJ0HTLLyy4nO21u3rLTZINsvcwtr2weqJl1TfyZ7UODCZn6QMs8enhq2vic6ZD2JmDB+F8o1+uZabLD2XHp9smUa3q53w6y60XIlO/PhYk35ZYt72+HV2/qQbb8vx3G59TL1PjLvzK/tPxz97tMXPa8+LeW9x8OkJnqo7fvfpzZrn/8LYGvJv/BgEbseSR7/Q7C4J9el7sDafIwlJ97LXGITqXBELxJW/XoT+f7EdIUYAjepB2E9VFhSJ17PfBXOlUVhqpz0rZBHhwYct6k/e8FFJxZsLCHSAgy1DUdoYJgIlgIHkKAMEAIEZYIEUKMgDc0IhYgPBHeCD/oMxqKCENEICIRsYhURDpiO2InIgeRiyhAFCGOIkoR5YgKRC2iDtGAaES0I3oQfYh7iIeIIcQTxDgCicQjyUgKkoFUQ2ogeUhzpDXSFilGeiC9kP7IFchAZBgyGpmI3IBMRWYgM5HZyDxkEfII8jiyDFmJrEbWIZuQLchWZDuyB3kfOYAcRo4iJ5AEFAnFRHFRRihzlC1KhJKgPFBeKF+UHyoAFYoKR0WgklBpqHTUVlQmai8qB1WIOoIqQZWjalANqFZUJ6ob1Ye6jxpCjaDGUEg0Fk1HM9ECtAHaEm2NFqHFaHe0D9oP7Y8OQEeiY9Hx6CT0TnQWOhddiC5Gl6LL0VXoRnQzug3die5B30M/QY+gx9ETaDyGgKFg1DAaGB6GjzHCOGJcMG6YBRhPjA9mBSYYE45JxaRhdmL2YgowRZhiTBmmBlOHacS0YFoxHZhezABmAjOJQWMJWBKWhmVgVbAaWD5WgBVivbC+2BXYUGwSNg2bhd2LzcHmYQ9gj2JLsKXYcmwttgnbjG3FtmE7sF3Y+9hh7DgWjyPjaDgVHAvHxRnghDgxToJzxy3ALcJ543xw/rhQXDIuFZeOy8AV4ApxRbhSXBWuGteAa8G1427genBPcKO4cdwEjoCn41l4Pt4a74b3wHvivfA+eF98ID4SH49Pxu/EZ+IL8AfwFfhqfD2+Cd+Cb8W347vwvfgB/CB+FI+Vo8gx5DhyXDm+nEDOXM5RTiLnJect5ye3Qi5ALlwuVi5dLl/ugNwRuVK5GrlauXq5ZrkuuW65XrmHckNyI3JjclgCnsAkcAk8ggFBSLAkuBAWEBYRPAk+BD9CACGCEEtIImQQthOyCPmEIkIxoZTQSLhB6CMMEIYII4RRwgSBTmQROURToi1RTFxA9CUGEoOJYcRoYiJxAzGVmEbMIO4k7iXmEvOIB4jFxBJiBbGGWEdsJd4g3iPeJw4SnxCHiWgSjcQgaZC4JAHJiORIcid5kXxJK0ihpGjSBtJ2UiZpLymPlE+qJFWR6knNpFZSN6mX9JA0Qhon4eVJ8jR5nrxQ3lReIu8vHyAfKB8pHy+fJJ8uv10+Wz5HvkC+XL5Cvkq+Wr5Rvk/+nvyA/BP5UflxeSQZTaaQ6WQWmUM2IBuRxWRHsifZhxxOTiankTPIW8k7yZnkInIJuZJcQ24kN5FbyO3kDnIX+R75PnmYPEGeJBMUVBSYChwFvoJQwVJBpOCh4Kvgp7BCIUIhViFRIUVhq0KWQo5CvkKZQqVClUK9QptCh0KXwqDCkMKYAp5CopApKhQeRUAxpbhQ3CmLKJ4Ub4ofxZ8=
*/