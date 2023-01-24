// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_TAG_KEYWORD_ARG_HPP
#define BOOST_PARAMETER_AUX_PACK_TAG_KEYWORD_ARG_HPP

#include <boost/parameter/aux_/tag.hpp>
#include <boost/parameter/config.hpp>

namespace boost { namespace parameter { namespace aux {

    struct tag_keyword_arg
    {
        template <typename K, typename T>
        struct apply
        {
            typedef typename ::boost::parameter::aux::tag<K,T>::type type;
        };

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        template <typename K, typename T>
        using fn = typename ::boost::parameter::aux::tag<K,T>::type;
#endif
    };
}}} // namespace boost::parameter::aux

#endif  // include guard


/* tag_keyword_arg.hpp
7JmT7T4lzjsFQaXpbXwaeektwQv3+F5uvnlyik814+aoDRPo2nt3vI9a8Kys503yGJ0EClucPoy5hvL9g7jtlumg5oqBoB6vHBDS2d3rrsva67NlSXtR+o4hsrR037G7DcDIldQ4xjUpkLpopxsWjhjy7dGpwejtujIWmGP3+M2ScyJT+iMM8fNWwiu0Q7wDTxKnjNnyjgj3Tj+eQeADya9i/pJuk/sj8yfxQ4yOMtGUs0Pe6tJSuiUbp5PvienVC56gra5GQA3UfFIJt+S1xVN5YrdvkkQ5927NnhlvMyj0tFVT35sdmopN2hirZsmZk/SanqRgK8LEdOxQMKXIW43HMI/1YEc67znMzXKwTrkUAwf/ti65WY3zZk3/xQlzxang8XG80qy3PZiDxiM7wvSPzLeMYR+q689Ltnkb+hlHn7RaAzr6ipq8wY9DDXN6PMhQ5DT9ktwsHPyDwOhdVMp6l2ixkTIYUIZMCBLuxtK7uJC8eXBThFBsYjyD2EqwSzuEE1vpQ2vspAGP66CboCLvdXwciijyrFkuDj/bCTGbwcaddptD0NDXPJP+WJTnwMVgd7SU9b4MtMV3Hp9cX7v/yrTUGvu5nPzJT4k4lZwbRzj1bO64xGzWaXIGrfDKcepVaKtN8cCAcDIbsYyoqbbrX667jTlkjKm1Gste+0VgWxyiiR4cer22C1m3ylZR2EEXwO54C6uin9IT
*/