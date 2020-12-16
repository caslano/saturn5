
#ifndef BOOST_MPL_SET_SET40_C_HPP_INCLUDED
#define BOOST_MPL_SET_SET40_C_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
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

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/set/set30_c.hpp>
#   include <boost/mpl/set/set40.hpp>
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER set40_c.hpp
#   include <boost/mpl/set/aux_/include_preprocessed.hpp>

#else

#   include <boost/preprocessor/iterate.hpp>

namespace boost { namespace mpl {

#   define BOOST_PP_ITERATION_PARAMS_1 \
    (3,(31, 40, <boost/mpl/set/aux_/numbered_c.hpp>))
#   include BOOST_PP_ITERATE()

}}

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS

#endif // BOOST_MPL_SET_SET40_C_HPP_INCLUDED

/* set40_c.hpp
3w5aI/QxrQX6lNb+FNG+n59on89hsDNYTP83j4BB4FH6zY1jYCT4M91b8zgYB/5C99A8AarBX8FU8CSoB0+BBvB30ASeBSeA58CJYAk4BTwPTgP/AGeCl8Cnwcvg8+AVcAVY301kvwY2APPBhuCHoBLcDTYGi0FP8DzYDCwFm4PoW/gK+2cXnkPzXgfRQcjyVsjzfhfYALwbxPPwuvRZBBTS89og3Gme33eT53kz2BT8APQGD4Ctwe9AWx/fg/eDB0Ff8BAYAP4ABoM/guFgETgI/Al8BDwMJoDFoAo8AiaDR8EU8BiYDp4AjeCvoBU8CWaCp8DHwdNgNvgbOAM8C84Fz4OLBITrXQ64gevAOuBboDu4A2wI7gKVNC8D3egzkT4r54MdEcE0L6E0L31pXsJoXhJpXkbSvIyieVHRvIymeVHTvCTRvGhoXrQ0Lzqal2SalxSal1SaFz3NSzrNSwbNi4HmxUjzMo7mxUTzYqV5yaR5mQ4uB58E14FP0b+/WeBmcC64DXwa/AKcD+4DF4DHwWdBBeZkEdgMXAx6gS+CbcGloA9YpjaAmsGynkqxFVGEQB3BUUNwD1CKvTjP2EkpYvyUN1w/uA+vU1ENYT5e16e70lFLUPbDY4jJ5WoKMXj+epyrDEMfOD8IHIhIQOzEcSOOpeEcqnNUWnvIxnnl6w+z8LyNiL0IEagU9wXyekMWi3VryR0xytX+32w1OhIAQtQoB1AVb77YyZuvou8Gh2yPIQ7Q+vuir23fI9xUDlOl0mfoLfJKBbufbCoqFL6zyl62BP7mYKgQ5iwzBqqTjp3EsS87CGHUmZI1FhOOyT7IKhyeV/Lh7XfT9+h75HYQtV9uKrcjyrXjqf0DXtvuozzcqu8rKvNRAa/bjh/b0qBk7SJj4PRdhRd2t2qfWX2fVl1/4ip/Zft+uFPQ+0rv90BEc8RmIStayL9BGEP+ZCT5EDX99l8S3fM/DYwCjeAQcByYAFpALWgFjeAT5CumgdNBRPY8cDb5iBfAXPrtvjXgMnAd+DKYB+aCn4CrwF3gavAAuAYsENday1H9NRzuA+rWbB0Hovz3qoi+dct8t1oyteK1HZP5uxSLxWKxWCwWi/WvlOvr/1KhVpOc0hVHat/7r/QSjpp2BHn/pgL9IRojPghFvlzyiGGqFKvapFVJ41PpNeq0NPL97qIi+Uj3r3f28/FqU4rOIvvzF8l3fhgq/tV1zmTJ5y+K3XE57J5L+/aszb/S4p3NX7nOh1c3H+HKOqevoPeW3vPy9bYQupdBX6ffJNgLFgQqnb217LtBW72jJPDG6x0V1zquX+egGodc36DaBrx3lfdSNA1iv81isVgsFovFYrGur1qo/0suG0sAXLIHoCo5gPVO9X/72sCGAv3ZgnIAPnuk+v8/cwCqDIPxOnmA7hXmAWhNd7l1B/fSnLZHhGJRra9zv9Sj1LtZpctINpg0Ou11+66N+v9iuf5/xdKgR/GxTgVLX+k1J+f0pernL6rr212Vd5DWJwt6X+n9HohQIFoKWWHk/yOFfX0uvR/0Pg0sly8YR/ceNIPtqf5P91iocT2+JrX46uQC5gUh34Ao4pwAi8VisVgsFovFqvX6f5pBraXy/01Y+//OLXz/v4PkTY/0Qv24t1L4IxIR2YhViIrWkW/F8YHkKY/j78o+rq135/V1zf0Bg/qwf2WxWCwWi8VisVgsV8r19X9tVobKkmaW9tffnD0AW5EDGEB1eF+qwzeg2q4H4rhtD0Chff8/rkCF8r3KeZwqW10+Sa0ZW6X7yrm6Fv+FVIt/aVXOiHqPbXo178LlSOu5iLr/nTwE1dZpjjH3FdTWm9A9x5qCHmAzMI8=
*/