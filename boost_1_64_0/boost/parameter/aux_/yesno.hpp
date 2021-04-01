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
pEv5F8HN2X3LRFLY1HhmsCQ5U1+gKy8pxqFGUHvdjwpGsKKA2xBuMNno/hpFymaOJsbie6y0GwLbQ4ZgYLOgnlgvY1ZM3e0EeQuLDE2gQDhnFewZb9apN3zc/Hivg4LvHw/hgZfPBTdMHrAU6rLQPFojgGUd21ggW1T2B5kYKgpr799c6N6dX/bHM1Cxo+qAOSXD+xA49vLMJ7YxAtTH1KSpFWRole9Kq+mQ0sRHVbmwmnCpePmC2TNpa40tcKosUVGVihieoEJ5nVuzP1KuSYHh4k1a28XiAOqLCiqH7XcDBuZM73MWGXEvZOk9N0K55AF3ZWIjfbEJ2juVQaKZrxPHL5yv47aK765sFk4mA0B0kLevzkLdIXw/7giuBxsOp5Vx1bVYUUdLIdQAZpH4Ay7eLUnICGTjkVwGi4q9vM9Pa6cBQsQ7PID3JpS0d2Pkljve2+xNLTddH8RnfgQGAFf8CX6jx4pBMYcJVZO3rhRRrzqkZOlXqBquPle17P3Vve6TR4RAMGf0qjpJBjqYzblcfFH4i95GyYXkfE2J5xiHPveUx9D1X46VFQ==
*/