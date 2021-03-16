/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    holder.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_HOLDER_H
#define BOOST_HOF_GUARD_HOLDER_H

namespace boost { namespace hof { namespace detail {

template<class... Ts>
struct holder
{
    typedef void type;
};

template<template<class...> class T>
struct template_holder
{
    typedef void type;
};

}}} // namespace boost::hof

#endif

/* holder.hpp
0vPSsnta04y0zCB3Z9j6snUiOfkgmpOmnnLCOPWuT/nnabwTVzWDbdV4aE55oyi/Vd1J/f2p5eY7lVVpjyZ7OtvJdNU4iaenswGlbLbGMluf96nld1/SNRJ5iuu5RWPTL5PNc/eNJDwxM2F+o6G1fLM8QnbflemSlN5fRedxTGdqyTNtIKpnPM3+VndTc5XdYJfTfj/OI3WzshGQW9zZV9zZ99xZBu1sFarMs2eP8ezZWs/e2+7O3u/JtCyo7/g=
*/