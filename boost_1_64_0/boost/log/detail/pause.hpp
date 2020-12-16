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
HA9L4BR4PZwE74GT4WYx137fmgeHbT36/Rb6nNUShsNWMAm21vLbBjbT8zYQsfWRDlZ/09Rflz5Szb9lMBJeofm3XMvPSpgEr9L8vBp2hCWwM7wG9hB7Ws6sOV1Y16Octdd4dNB2Hr+0/7PmK3Hn0f9dp+3f9VrOVmv41mj7t1bHO/fAvmp+IbwBZql5tp4vhuvglXA9LIU3a3n6AXwY3gKfhLfC38Pb4B/hD+G78EfwI3gH/AxugF/rff4O74b0i2JeB2Ie7B/OUg+na37M0Ho4E66oEdDfOnJjpJG1MfKc35HaSYHrPQYdnYilt3XyNUHdrWUwl/NSZBcSMzaox/XQx/xeia5QxNLpeqIs3OjPuaXbdTJ06nfNXFlRx+sZGO3X38q1Lch+5DDmnTD7aiXXrg3ogE2GFfXAQswtXbDF/M6Cuzg/imzgfCdyEDmD9F6FPaRVOu6QJp+Ei97YwXA+56u4dvCmMOM4coffP8x2w+2Y52PHqVc2vAx9sDDuOtUxCzORA5j157wMFnN+G2Lpnk1Ej2wR3IbZOrgPVtBDi1mxrY+Wa2WE3e/2esLB+dPIHYRlDxJ9c5itqzaT6/1hMSxFMgfiN0zGznHc7ON3xKUBPbaJq0lDfg9GevN7MqK6bRn84D9i6bfdze8D3MvSc/sV58XY24AM5XwPPMX18rpvW50MN3qvIU7I9DLRhUtHhxvCk871fOQOzkvhTuSQ6sidzvUDmG/n9wl4BvPwtYSf83bQS3duOuZZMHE894edYDpife9rPr+3wNvWBvTpHoQnkN2YlYzHHIm7gTD4/YOn4LoywoV5pt8clsKv4G2Ez693N3nC2fXuHlXdu3twNxizuIlBHbzTYQmyEdnOfY7d4NbLe6icbt6UG4P6eUffGNDRO5L0LeH3FiRxEvahl87eo5hPxrwY+8VwA7ILqUyX7wnMItYRH+wf5rwdv7cTZ79+3wOYpXPeit9FcB0yWvX+7vCfw4PQqQN4I2ZDYeJ6wgFT4D7MxsNi5Bi/74BOHcE7ON8ID0FjCukI93CefBPh4XwoHAkzVYdwEecl/N6AHOV8u/98I7qlkd3IQeQEEn1fpNEJGY3kI3cgu5GjiLEp0khGBiPTkRXIBmQ3cgg5hcRsRgc2ko7kIquQjchu5PDmkH7i0BE6/teP71r/X3bh9OI5s+f4V9L6FQD+y/r/foBbS1/eidr67FeDsbMyrCvj6ePybnjosHEZem8Jja7Ttr+ZZa/5+tH7fvsPhq0w6oZZ+gQe+MBv9mfTWtOa/Z6s4TctHRuDP/KfJ9tr3f7yof+8j73mdaq4r+29ZuK4a52v/Y0a/9qyaPjZCa7zhFebmcVhxjZ7j+sKucdse21XmNg7ba/ZmCFhfDvc9N1rbmJzX/PwLUb58Mq6QTu8VxG+yd7rMY5XrjMvScJp2SmtUc88Y14V9onxYPg2xzoMtx/NOsuaBT64nrU4N9trLak7XZLEfs6S7DnBfdZdJX5PhDflLcBKX5rPWoM0U9K6u/gZ5/AzztvPRUsduhQ2yfU6ssYw0bZ/SdgXRl2f5U+ipz/k2dKgP8e4zlVZy9fEtv9DOyxqVm7NIyVT8z3Zuk4pbm6+wvuZdPv+yeXcRsm6tiIKcVB3k70HgfilatluALeKuy99W4yx6N6QvOTItcP9Ayn7EXZduP09sc/z6tP2WqsHtS4sMV6010TuEXt/MqN4ggzYo3RJeXwGLRCPYxYoI/eKvd+GnzHXytpJWd8v9kb5jnPfSB91yNYbUpxX0M2xFlPu29yoT2lK0vi8J2adWe3q49vHU5jveMbOu7fk2tW+QS4/SaeUoM6GhlLu23Ie8O8ZCV+GvS4=
*/