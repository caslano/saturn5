/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/order.hpp
 * \author Andrey Semashev
 * \date   23.08.2009
 *
 * The header contains the \c order keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_ORDER_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_ORDER_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword allows to pass the ordering predicate to sink frontends
BOOST_PARAMETER_KEYWORD(tag, order)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_ORDER_HPP_INCLUDED_

/* order.hpp
MHAAd9Wa94rFkOGffOsoxVrcPErKp8vEFbylre0d1UTWOgiss1phHNo54DKbKM+eJXPIKGNYzK40ihOwF8agVNzo9+iv3662R/D/f8PFAlLyJeVWOBeZ2hth3+HV9SIpu7p6joaQjPK8Mv88Zfu/8F3xl/u2qLFusXWPz4yDURgMbSb1vjwgbGSsVhz05QYftOX36ZyZ/HURRhQERGsZlwJXpWBtYczAD6PUiMiblqRW9XYz49sk8D97Xe+fHh2ZtKEmKdXifPLqiUW1zcwi14x994I9178q7hDNpOEuuzWUgkQumS0Bu1mLPTl60uRV4FTJe5+lKz9dFuNom5kjvMLtQp77Ts3wfAFGCoT5J3YAbGWCukei8OqJK/4w3M6WQiY9SVWhc5/RuWI85bb2k496LzxzqWUVWeQ/JJpFWIYCj/IgIhb999dAsJSuwVW8KJV40WITs/X4SZmpbhtlE63vV0BhrDcNym3Ky9Ld0D1qdO5dFFaEOau0tGy2UPxsLaAZLSF7wzXYtJirjAb/cbn7bY46O5IHDRHJVxQU4pFcoGSwWh3QzfNzRMemvyh9Za2lZZxmtJQwmGU0sWheMsCjV64B2mOzbB4F66v6adofjmI3ucSizRg8DauKzBc2yGxHL5dWdGoXr0Pb
*/