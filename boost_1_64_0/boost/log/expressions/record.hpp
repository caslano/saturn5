/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   record.hpp
 * \author Andrey Semashev
 * \date   25.07.2012
 *
 * The header contains implementation of a log record placeholder in template expressions.
 */

#ifndef BOOST_LOG_EXPRESSIONS_RECORD_HPP_INCLUDED_
#define BOOST_LOG_EXPRESSIONS_RECORD_HPP_INCLUDED_

#include <boost/phoenix/core/argument.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace expressions {

/*!
 * Log record placeholder type in formatter template expressions.
 */
typedef phoenix::expression::argument< 1 >::type record_type;

/*!
 * Log record placeholder in formatter template expressions.
 */
const record_type record = {};

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_EXPRESSIONS_RECORD_HPP_INCLUDED_

/* record.hpp
YyCB8Q8z3hE01qHjHDLGse2p2LhE7IgdsSN2xI7YETtiR+z49x5fyvf/0pEFR+P73/6GH5RjmbVurPGWowVJUb2Jzra+dl5gHZlZL2OWo7iumTH2+98Xv7+y+pAzU5EbkQfc98nR53jMWhaPc92Lu94rftzWo7mvq1G3QXb1zXoBXYdlyTMD6wWWDrP9LJCdeWYjEdZMGXv7f5dnLLayecpkxGXdlFnrMFnCrrOmo0FRifj3sPLvcTJY93KwZXV6QO9/CNdXpYfvoeaNcp1OlnMtW9jaIud6HV1vqbr+ur+JhHso4tqr4DXnKz3EC1bATOJh5UtdwnB6eE2SvBJVq9VltXWyTsitnhBGaD0hYRWlGo5bPQn2UyZ612VV9bUXFtdfWFPmvibW+JF49ZV40YbK2DZppa/epDrcpzrcZ5l4lV1QT8MmJXUaOfGX6fCX6erPbI0RlKYeDn89guOndbK0bJmur83S+ni9uLlG1roczy5kJeRAyP4mpq53EbcLPP2oi+ciru3E1Geepc/pBtPF7yJPIi38Vkqp2Zpq9h0sl3tZpn5Ps86QvEvS+j1UuVn2MQnU+1z9+zhlsq59OR5+kK31v5X1nb5nW0FrX7KRLqaOhbSH4Lpk1jBTZ7gXXGcIT9LRV8IL1I1eXM804YXVAbnfw9wPK+uw9pYW1N7I95C1Bxma8G069vYDpKvdbw/XdV8acjFeq0vLtK80+6KYNU/Pifs7yR+PdRXi2kcPj37vT3Xr6ANxu7Sh3LneuJOMHZ5H3xqv9VjdST0O2HxILAjsqZXG+RA5n0+9zgrsPUV68Gb8LBE3cWZN1QsSnxSzL9km8uCj9Mh2C7wu9WlaQdh6VS1H8tJtX7Io91twH2ONPBbsPvYdeaz5GhnjPufD7aOf7/9ax7Mbb7r1kmueGB9prLzt+yccrfUE7mPukcem3cfQj95+C+5j7pHmEiKPxYsNaf87iL5jXRBiQ/oK1Qm+CubAa2Au3ACnwK/B6XArPAk2wbmqc78cXg/P1fvV8AZYD2+EV8Cb4CZ4M7wFfhP+BG6CD6i/h+C34VPwFvhb+B34EtwC96u7N+Ht8ICcq+6vR3+T9Hf/Au0b+9kXVEfXCyfCznAS7A4n65zANE33dDgSXgTHwjXwRDgXngLnwXJ4IayDX4Fr1H2jul8HF6qu7anwmzrX8AOda9gBT4e/gmdrus6Br8NiTd8S+BZcCt+DZdBLWsphKlwO0+AKmAHPg5mwEg6HVbAIroLzYB0sg6thBVyj+bbb9JX04VovuiK7QmyLZ2l+9YLHwt6aX9mwPxwLB8C+Wm/6wYmwP5wKB8A5cCCcB4fAs+FQWAJz4Wo4Gl4Jx8ANGu7X4DCtP/lwCxwB74Qj4Q/U3eZ4K2Z/O2Z/O2Z/+z/I/nb208nWFGTF07H5stgRO2JH7IgdsSN2xI7YETtiR+yIHbHjaBwJSPm/cP7fRmXFUnv6/4jn/oc5bP/P07n/XJ33GIr8kYHDpiG+uf/5p89bOLcYM3LLmOBS+1X7+/vmkIpLXOdp1a8n2O1S17ki3LrusW/mbr4l91Pc5mmN3w46f8wIqviLt8e+5d4AuddT7C4uNfbGt8i9RD3HjriGE3BbYuaSNsq9NLWNyCyZnGfgu0Ordmb980R2HnTR/NJ5osC1pRH3yDdz6tu1jDyOZ+3lyXt8ZTR33tQ5CxbMLl5W08AEZl1ZfUNNdOsp8jX8AjUmOMQKcGUWcZTw1/vDL60osxx2I5n1rCtZLjbNCJIg1P1gU0Z6zc1OvPhJcvGj10Lsn1VWVKkfr4sfvRZkB21cFGtK7Hm95KFiQ77f7DnDQ84LQmwmmvS62WXXMlT7aSY=
*/