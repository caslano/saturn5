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
Z9vvZNvvTrbf05L1b9U3J5C+I/n924SA+Wx+H7b9XpGkf7Ou3PpdaTMfk2z9Hm37/bbN33GYN8FF+Jdj+z3e9vss/TvQJx2Sb/XZ8vsFr9ofTf2+Bp3jcIDeD1L2okR8SJo5M1329e5lOzewRvTjRd9+7tsJr5ynBdvBD6Fpr1HsZbjY+yt6XtgM+8D3oBm+HacJX3cJX5qEbwuyR/Q3+gL6avxA9HfLuV5PwDz4FFwDX4A3wxfhNvhr+AtvQO81+DJ8Fx6CbXD3FdgVvgpHwz/A8fCPcBZ8E5bCfXA9fAZeDV+TcJ7U+1uRR4a7EqdjEs6r0OsAr4FJcD3sItdnwLWwr1xnwmthLvwanAqvhwVwIyyB34BXwpvgTfBmeDe8Ff4QboY/ht+Cu+Ed8Gl4Jzwk9o7Du+FHcCv8GH4bxhL+e2Ec/D7sAO+DXeAPYC+4HfaH94s7m/XeSIRF8tV+btdBKQ+vwDj4KvTD38L+8DAcBN+CQ+BrcBL8PVwAj8BSMV8J/wRXi/7l8A/wavhHeAN8HW6S+8dhublnD8xV4ZM9TCV8H0s5/5uU809gT3gK9oUxxLOfnOs1QK4HQg8cCaLgRDE3z1tpFP8GiH/281ZGcNtgNuwBR8FecAzsDUfD/upa9uvHoT3iXr6Ur75ItrSBOVK+xsOucBLsI9d94QQ4FE6Ew2EuzBK9s+AUOBvOkPI1BzbCuXADnAevh3nwG/A8+B2YD7fD8+EOeCF8BF4En4IXS7krgM/CQvgiLIK/F38+gufCU3A+/BROhV295BvsCSvgUHgJHA4r4Si4Ak6AVXA6rIazYQ3Mg5fCRbDW3t71D99uvS3l9B1pt45J+VmFbBF7S8SeH6kUe3G4r9pQ2Bb6oR+mSr60h71hAhwDO8FpMBnOg53hAtE/D3aBF8q1Pld1gHWOZxNiP8dzkU0vM0K93Aj18iLQm4EUil6aS3l/XtL1BajmVcPOcp2qruW8e6jPS7X8xXKwv5RVrbclQr0dEertiVDvQIR6RyLUa45QzzMwvF6RTS8hQr30CPUyI9TLjVAvL0K9wgj1aiw96lmw3kjRO+Dlh+hlyvPEGGSvtKO+qMB55FFQje/BVOiHI2F7OAYWwDNhAlT1Fl4Au8MyeAZcA3vCjbA3vBlmwDthX7gV9ofb4AC4Ey6AT4v7z8DB8FU4BL4Bh8JmOAweh6PhR3AsPAXPhD7iMg6mwrPgGXAy7AOnwPFwDpwCC+BUOA3Og9PheXAGLICz4KVivhLOg1fBi+G1Yv86OBveKO5uFvPb4LnwHjgf/gAugM/K/f1wEfwTzIcfwPPhKXgB7OgLmKfDi2E/WAAHwkQ4PHAt56TLmiD4oLQ/9nPS36adag//Is9bf4UT4PtwEjwBi+AH8DL4IbwCnpR+8GO4Dn4Cvwr/Lv3gp/CbsFn6wffgA2J+PNA/yroUlQcqXDNUvyfnmco5ciUwA66AU2EVXAqr4TJYC2tgHbwM1sOr4ErYBC+Dt8FV8F64Gm6Hl8Pn4ZXw16L/Olwr6bZOys96aPS318B0eB0cBK+Hw+BGOBreIOWnCU6G34Qz4Sa4EN4M8+EtsA7eClfB2+BG+C14L7wdboffho/D78Bn4HfhS/Bu+CrcCn8PvwffgPfAt+D3pbzcBz+GP4DJpOl22APeD7PhDngmfBBOhDvhDPgTOA/+FC6Bu+Al8GF4OXwENsJH4XXwCbgZ7oV3wV/Cn8In4aNy/2n4HPwdfB6+AV+AzfAp2Ib83weT4DMwRa67wqdhdzHvCX8F+8Ffw+HwIBwLX4IT4MuSf416Ljx5KOXefv78IHmuHQLPgENhLzgcjoSZcCzMgvPhGHgePBMugtk=
*/