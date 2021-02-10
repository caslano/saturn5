// Copyright Daniel Wallin, David Abrahams 2005.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_YESNO_HPP
#define BOOST_PARAMETER_AUX_YESNO_HPP

namespace boost { namespace parameter { namespace aux {

    // types used with the "sizeof trick" to capture the results of
    // overload resolution at compile-time.
    typedef char yes_tag;
    typedef char (&no_tag)[2];
}}} // namespace boost::parameter::aux

#include <boost/mpl/bool.hpp>

namespace boost { namespace parameter { namespace aux {

    // mpl::true_ and mpl::false_ are not distinguishable by sizeof(),
    // so we pass them through these functions to get a type that is.
    ::boost::parameter::aux::yes_tag to_yesno(::boost::mpl::true_);
    ::boost::parameter::aux::no_tag to_yesno(::boost::mpl::false_);
}}} // namespace boost::parameter::aux

#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/integral.hpp>

namespace boost { namespace parameter { namespace aux {

    // mp11::mp_true and mp11::mp_false are not distinguishable by sizeof(),
    // so we pass them through these functions to get a type that is.
    ::boost::parameter::aux::yes_tag to_yesno(::boost::mp11::mp_true);
    ::boost::parameter::aux::no_tag to_yesno(::boost::mp11::mp_false);
}}} // namespace boost::parameter::aux

#endif  // BOOST_PARAMETER_CAN_USE_MP11
#endif  // include guard


/* yesno.hpp
CAAtZ0pSR9jNGyYEAABLCgAAJQAJAGN1cmwtbWFzdGVyL3Rlc3RzL21lbS1pbmNsdWRlLXNjYW4ucGxVVAUAAbZIJGCtVu9P40YQ/Z6/YnCiwwETc3w84ASCckWV4AS0J9S0lmNP8BZn19pdA+mF/u19u3ESkssVVN0i/GM8897sm9mB9kZcGx0PhIxZPlDFumy1t37carXp1ZX43wQLdxfwWau/OLPrnZNkQtMfBPVxf4UipkXEJOnSqxETCn1E0nAcuOckeYWm7xJzl9gF9hP3CEurjbgTVY21uCsshSdd2tt9v0s7uO3tRnSaSsElXVuWA9Z3ER3k3nJUpE9PPcMfI2JLadnzQDeFMGTU0D6mmgnPpchYGs4pNZSzybQY4EVIsgXTUJRMJ5efb88vPkX0WIisAMZY1WQKVZc5FekDk+aMxcMUokq1JTVENLBzYSzwaiuU7IGaybIeGUA48rQ0itKHVJTpADSppcLaynyI46zWJTKPc5WZOJttvVfYUbOLW2QwSsekKktWUW04IucX0UjlYujukALGqh6UwhTRIhUQyTxWmgyXaFQXJthMU2a6bpSJnJfr5ZGw7maUNI7psVCjJUdICJBhrSVoIAF8cgWBI6plztr7+k3PGBo1vbTfKcki15yURCYU
*/