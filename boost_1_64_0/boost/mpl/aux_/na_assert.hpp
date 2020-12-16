
#ifndef BOOST_MPL_AUX_NA_ASSERT_HPP_INCLUDED
#define BOOST_MPL_AUX_NA_ASSERT_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#if !BOOST_WORKAROUND(_MSC_FULL_VER, <= 140050601)    \
    && !BOOST_WORKAROUND(__EDG_VERSION__, <= 243)
#   include <boost/mpl/assert.hpp>
#   define BOOST_MPL_AUX_ASSERT_NOT_NA(x) \
    BOOST_MPL_ASSERT_NOT((boost::mpl::is_na<type>)) \
/**/
#else
#   include <boost/static_assert.hpp>
#   define BOOST_MPL_AUX_ASSERT_NOT_NA(x) \
    BOOST_STATIC_ASSERT(!boost::mpl::is_na<x>::value) \
/**/
#endif

#endif // BOOST_MPL_AUX_NA_ASSERT_HPP_INCLUDED

/* na_assert.hpp
DpK1DpWYXPWoYWSNQDUhKxBqH1lnUJ/JyohaR1ZkVDyyVqBek/UYNYesYljrZDVCtSCrIWoqWZVRw8iahrpBVnasdLIWYI2TNQ71haxIWO9kDUetJisVagO57lHhyKqDakHWbFRish5jxOzw0gsQJyU8XRuhgCf49hxEbjmelt8gVusxltcRq3LE5Sh+pXi8nGL4dQIwPifwdGcjMuN4aWtaIBnE6yR+/b0YrwcYh/34kb7gpRXHj1cKPbAQzX142s7hR/fES/Ic4ybEy7AUke/Cj3kTsXfG0zKGHzErAjKFEhgqkDle0rWISyVGkoOn9iWilg51UBErP7wEn6CWYxj/cIzde0SsGLr61XEIDjH8gKdoK0bAFLGIwjifxhgbI2I2iNIpjFAznqod0Ig34myFOE1h7FZCh4sxLoegKwdEnQK15CJGsnj6fwF1PHaFhKGLOxj1YYyUAeL4GsoIhUrUMEJ8jCkPetyG6FyAArsxGg8PQ+bQyVvoaw+UNBNjNSgJaSPWJhg1TWjgLFQRg9HNRKR3YixkMJKqiHQGlDwPGpbCOJVh1KQxnokYJTnEIAWq0EU0BjAygdBTH5TzFC+tEyJ6C3GTR6xmQS8bMEILoQ5zxG8LdHge6jFE/P2hrFUYofnQ6xWM2H1E/9cYaQvovxXjYwRtViCmNGj7NkZvHeI/DcVbIgKR0JjEz3/++5uCQJN60Ew74jEJ/V5CZIcw6u6pKD0Y7zjEJxoR2A5VFWIMPyIWc6HuJujQDFq5hpGcgbi/0ceSg7bmQMNHoP06KLw6CUsM2pqACu5BuY29KIaxKERQCBtquYuYrIG26NDlCigkH4oOK0AJg+6uemHhQkW10FUJVLUrBAUFuqiC+pWhyc+XUbyggY7ZWLKIbxt0YouYL4PKPKCig9DiNyj9OyIUBM3nQT8/lqDE/oTCBS06Qjs/g2ZEuChO0MQotMuE0i4Go/CuxvJGfA90ogBDaTpQths07Av93ICGkqF1e8Q0Dcp5hvif2YwijQgnLEJBEkXhgSbUobhfQqOK1ijBWiinGig6X1H4oKYF0K82NKGAaL9rQCGDOnqglFdQetELlNjdKKxQysgjlK5NKMDQbj3U0e+CYgjl+aSsPH5iz/47vMVvN104F3fmZxzb4RtXtvm8K/GbXqgR0zHyjfVaVtN01fPrOxednbr2ppr4//H/4//Hv3w8dJk0l5o+Uci5+yFq0159Poevo9XhTRxzeS2y3LOlsI1V+bCxpqF+534XkZfxh+4ffnEibO2D0CZFzZUD1/dNP9SN4a0yDLyfcvVWInP65fyQhA6XJuGiHZxetV9u3mna8ODkoxctRapz1lhnRNeGcmgLdfssrxhFKS0847Bvke59QcfJWy7dKzn220s5097E8wd1pj/xD+Y9vpY3t9Zt44JS2881w5dMLga2+3YNfRqPYWyiLLm/Kmmb2diH/QuvntXlBu67nMKJ9jq5on6+rOfKB6apr6/s17WqLVTkvZN7te98sPW0l8t19yl+nkWF2f0vvw5P/e5fcbuq81emPxVF1z48OV86/9pvXHR32vmsle5qfPXL9SeDfDiaP1uk6neseWG/Z92PyNlnd5dfqOpZTL/p3pweFpxDk+vc7ReQM8t+9QtbpzfVXxYahST/wqHmxMaf934/pbpa23VT58MJdraK+pdlrPX1Eanzz2TL7rcbFK25sbf15nbaki4jlsLcjKic9pOVOx4YZT9YdGa5cFcXNX6pq8Hx6pyW7bEqptXEGoX6l3GOl6+cSLT9+cLy4+4rtu2x5G9rU0k4de9koBnxcdabX/zYNZ9Szr/+JcRSlG+Xeqs5LPLRktaNLRuOPGw=
*/