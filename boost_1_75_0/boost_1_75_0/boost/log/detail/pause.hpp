/*
 *             Copyright Andrey Semashev 2016.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   pause.hpp
 * \author Andrey Semashev
 * \date   06.01.2016
 *
 * \brief  This header is the Boost.Log library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 */

#ifndef BOOST_LOG_DETAIL_PAUSE_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_PAUSE_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(__INTEL_COMPILER) || defined(_MSC_VER)
#    if defined(_M_IX86)
#        define BOOST_LOG_AUX_PAUSE __asm { pause }
#    elif defined(_M_AMD64)
extern "C" void _mm_pause(void);
#        if defined(BOOST_MSVC)
#            pragma intrinsic(_mm_pause)
#        endif
#        define BOOST_LOG_AUX_PAUSE _mm_pause()
#    endif
#elif defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__))
#    define BOOST_LOG_AUX_PAUSE __asm__ __volatile__("pause;")
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

BOOST_FORCEINLINE void pause() BOOST_NOEXCEPT
{
#if defined(BOOST_LOG_AUX_PAUSE)
    BOOST_LOG_AUX_PAUSE;
#endif
}

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_PAUSE_HPP_INCLUDED_

/* pause.hpp
9Cb08Za/tZsECjjeWWn/iOfVt1R/xtLNbbMV1eqyGgf9rR2QCS80sP3MEdtaRmT0y8jzicX6HBtxsq9gHfLFv9nBm74Y8dqbptzr3IV8Hz/H/m3yOX/81XN5fmqWryvvf5fxeAMmtRH7UiW/b68P8QbMBMZ5S1unjYdgQtiNboyXX2stHBvY/RLxAy6xjf0M9fGdBcHd2gXcJ/4cdNhuBu7iK3y2sQh0Gte4FbhzH2J+/f154K6/DtzjXcxPcJdew5j8kZ8Fnbaa4XQeZxv6r+o7qBo/nEH9feoo30ug/g/c9MfBd30HcKgE4FpfRz84XsPx+/fJTShFX/9h1FvXFoTt2qPGOfD519lO9x+Ql/a+XA76AvCD7cBPvKXu5Rr8pV3I44a/B702D+B6zrCt1GN818DCt+0Cn/0vgF4vzIEf7QB+9y+A3safYZ1kdRN8v6ibtuZu1bkM+uzUZOAabgZv+tTvwh3XX/yLLexYVvkYukj4VqrrRS0f+fuBPQfh4HRjOr2D8T3dWLO89w9QffA79TH8/tF38vvU7yT1p6qq3NuHoIKQBkNJHsN+OcIaSWYtrfq7Wg5L7ddBzHf6E6jn/211voDDUnUYD/zADtgM33p6314ox8bQuPZJCutGHtf0Sx7htpvx3djfbDq7OQ3M7s3bdm5V9L2YS5tWnVX4HZs3bd+RAr4R56tNP/d/KvzW7amdHZuBv9mO
*/