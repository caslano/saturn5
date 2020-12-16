
#ifndef BOOST_MPL_SET_AUX_SET0_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_SET0_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/long.hpp>
#include <boost/mpl/void.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/set/aux_/tag.hpp>
#include <boost/mpl/aux_/yes_no.hpp>
#include <boost/mpl/aux_/overload_names.hpp>
#include <boost/mpl/aux_/config/operators.hpp>

#include <boost/preprocessor/cat.hpp>

namespace boost { namespace mpl {

#if defined(BOOST_MPL_CFG_USE_OPERATORS_OVERLOADING)

#   define BOOST_MPL_AUX_SET0_OVERLOAD(R, f, X, T) \
    friend R BOOST_PP_CAT(BOOST_MPL_AUX_OVERLOAD_,f)(X const&, T) \
/**/

#   define BOOST_MPL_AUX_SET_OVERLOAD(R, f, X, T) \
    BOOST_MPL_AUX_SET0_OVERLOAD(R, f, X, T) \
/**/

#else

#   define BOOST_MPL_AUX_SET0_OVERLOAD(R, f, X, T) \
    static R BOOST_PP_CAT(BOOST_MPL_AUX_OVERLOAD_,f)(X const&, T) \
/**/

#   define BOOST_MPL_AUX_SET_OVERLOAD(R, f, X, T) \
    BOOST_MPL_AUX_SET0_OVERLOAD(R, f, X, T); \
    using Base::BOOST_PP_CAT(BOOST_MPL_AUX_OVERLOAD_,f) \
/**/

#endif

template< typename Dummy = na > struct set0
{
    typedef set0<>          item_;
    typedef item_           type;
    typedef aux::set_tag    tag;
    typedef void_           last_masked_;
    typedef void_           item_type_;
    typedef long_<0>        size;
    typedef long_<1>        order;

    BOOST_MPL_AUX_SET0_OVERLOAD( aux::no_tag, ORDER_BY_KEY, set0<>, void const volatile* );
    BOOST_MPL_AUX_SET0_OVERLOAD( aux::yes_tag, IS_MASKED, set0<>, void const volatile* );
};

}}

#endif // BOOST_MPL_SET_AUX_SET0_HPP_INCLUDED

/* set0.hpp
L1VIXlX07ABM+snD6CfvF/4iRu/6PEi90PSTtZpKGcudLPP/jOWnyf6/xgpk/lU1Y3EZF6hFe0u8/05H7mEZ/4OV8vE4HybzGRoay5FxqcawPT4PLjVWKOd+hrHsLjL/z1iG3DNcix2yTsKNxjKHef3aI3e3t60zbKbXuTv+k+8/ehvLaizjfzC5LvRHrszBuJty73q59xrL6+HZSHTpIuN/tHfQn1sPo588pzxuLPKwtyOHmH/l82WqsTSZf/U0MY95ubMpJ+8S5iJ3qS+3AN+/73VZTCzFtleJ2xFvx0p80MK39wb2zvDxfQsZsu7HRmzb73P8Pfx8v+z/S13R5WPqSrnPyDVZT6uAeIifd+MreQb7ARm3eBn/wLYVsv8v7W30Pv0dn8q6YEexQ9Z9S7nI9JOx9ZLG8rr5WJYzlnGPL3cSTOYfVDWWtVrW/6OcyKiNXHl/fqaxqOxDdJ6x/E+9D9KNFcY9a4QMeXa5xFhaVX++XYl+co/ZgvYWyvw/fCDxuAFdNvlcu4m6N/g+pxO23eb7xG7Gcm73/W4vdJb1gm6nvRyZ/2cs1lfm/xmLyPV3KP6T+Tn3oYvcm8VgostYY+kyB/cx2nvV+2qSsfhyL/dJY7ndZf9f/FyqhGPPorNcU56DLZb9f/F9ni+3iFhe5+PxirHMx2X/D3SWef+r0U/W5VxLPI7I/D/q5nsZm/HLBz6+cWIk4zTb0a+DzP8jX2S88yvqyt5s32KvrHW6F/2qefYzupzsbduP/2Qc8xD5IuN1f9JekmfJjUy/a+T7X2N5fWT8z1i6rCNX0VhWD1n/z1jmR95/NY1lN/W5kUY5eWY6w1hU5jaeiwz5Vr+BsZiMF19Ee9JvNMUOeYa9grqS482N5XyS5FgrYwW1Zf8PfNDan9PtYPLddkdjuSVl/M9YPNf3Lz2xV/YtvQ0m+t2JbXGZ/4dtC7z/7qGuzJsbgW1R394DsL6+3EPkgaytNA65j3mfTkRuHe+DKcYylnv9phO3yb7fnYVfpM/5G35uKPP/qCvvZ15CP5kL9jL2fiTz/5DxuM+/12lPxvXyjaXJGPJ6YrTVy32XfJH9Kz4g5nJ+bEO/J3y5nbQ31evyJbpM8jp/gy7TvH7fGyuUb81/oj2Zu/ULdeVdx0HK3edjeQSdG/q+OKmx+X6gfP8Lk3nXZYxFZA2IqLGY7HdX2VhGFR/zGsayZO3304ylyfNqXWO5mbL+H2ywz7X6xuJPyfw/5F7g2cXUlf7vcmw705/TV8EkRtfA5N77etgHPv/aGku/1fvgZuyV78q74j/Jvyxj+fKeuA91P5f9P4wVPuLPwYG0d9CXG4Jf5D3ncGOZGbL/h7G8HRHHHsSOj3zMH8Wnf3ofTECXbT5fnjAWTfcxfwoZU+T7X2PZf/P6zaGulHuecvmeLYSN9SwP2z72flmGT8fI/D9yTd6XrSE3rvRxW2csR+Znv4OMyrL/L76S984fEY/rZP4ftsk90hfGYk/K/h/I2CL7f+B7mfv2I/l3j/f9PmIua+f/hn4TfTz+QIY8O0eaMJ/Gx6OYsYi8cyhtLF2+P6pgLK+t16+Ssax1/jyvTrkNvtyptCfz0uoYy5b542fDZE5CPWNx6esuMJbTyPu+ibHc6V7ny2Bny/e/MNG5JXZM97pch4w7vR2Z2PGT93MH6kq/1gWfyjugHsYKZE3FW40Vrvasn7HM3lHHBqBLadn/F79IPIYR3w1ev1G0J3k1Bh/I2hiPoEsrWf8PO9K9bZOxQ97PTMMHQ2X/D9qTmOdSTubHzqOcnEcvwu6v7NgSY/ll/bmwlHicLvv/orOsR/Em/ltS3rG3kfGb99Um/LJUxv+MZWQ=
*/