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
8rTdliUDptMKDR9ViEkjKttvshrnizGCE3yohXtE1cuI+HvExdiu/+cFKS4romjTAgWXK1L2O6hjnWwoF8iG7yAdfmu9u7yDza904WJnG6Xr+TM0O8gC2urFpUP2CykjWpzls0pSpyr0d8E2aJhEXgh21uz+vhYFDHoUjs65AtiGzxp1104RHoGBbkLzSTjp8UWYWOzUTtIVJDwpJ8EuhxhRZsTpVakmZzQI1a+VEZhfuk0ugBaI0fA/8dDmgOCpLWD4GBY8qHnRCgkQbrZBmXQmJUMjb127Igxpy+TtXZMovtZ+9ZdVXpt1tq7n3bh5pJmj239j7RTRvT2RFPoRKKg02Shvd0ayJ3tDuMxPGANGNQXsT5BTkytc2Eg061M/TAbQVm36hR7iVRFv9iluFhrfQqMCe4ytrsJJqQv4RJMOkIojpNwHTk1xEoBrSM43lPp8uIQ4Ei1nLpQDbeRvhxUCVppX0/a70PC4bbwzQcvMGrfCg8nFyXHxJ2gQpGmjRTnfuRpYUClYUnXCkFV7LWxqMCe/XvnUVuVB1eyUsxPBLtbxUTvQ6vgBDg==
*/