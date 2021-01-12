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
zM3PZczNz2Wdm5+mc/PDdG5+WrwHLVq8/yxavPfMrBjaZSGXQ7ss4nJol8VcDu2yhMuhXaq4HNplKZdDuyzjcmiX5VwO7XI6l0O7rOBybJczaLFdVtJiu5xJi+2yihbb5SxabJezzZpDu5zD5dAO53I5xH0el0Ocq7kc4jqfyzGONbRY52parF8NrSjvPqDxb+ui8W/XRuN9HPXReK/Gumi8P6FBjHNniNXBNph1Vy6x8i6g
*/