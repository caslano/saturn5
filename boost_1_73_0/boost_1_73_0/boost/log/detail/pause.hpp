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
vv1RVuxjNFvenF+t2G9fveka+zMgNF2KidWCvR70OmB4y7q2jXGFdV3AUllRxyBqK0JpW1dVZzh13ULVX4B5u1eX9g+qBxRVNPpQ7AGVyqqY57G+s1hqVBy/e7Wms7JUU6C/YbKgVNbzvclf65H3e69+lxUncZj63roBvbq6HPUVpf4Ct3I9zN/tkdIxHVgfeGVmPUlBCb5VjNq3LftquGbkUIqSfAw1ZH2UtcdrlwCVGjVPNtY8yfnv3iZlndQsFuC/X8cYdeqObAO0balXAtSBtgtu6gWm5ZvzVqh/cd0f9YyJG26c4KGuJ68UX0O6dn9kv1W6Fi+UWD9vWAoVDcF1G3pTTBMK0rG6c+Og5v0ih3soxQpvNvFQHoK6OPBAxj17kV/Q7n1s4v3v7OlT7xBlOPNmB2Zhfu07+zZHQGISf6gzs4N99g/r6KeE/SP5gO8RKUEvPsC75Q9fUHtQAHipPhsiFP2ikxXuU83CLJg2WY/ubmrgNWkxT7M4SNgR3mkvCYJDm/OcGmN5ucOBqQ4eQBbjVSt1hEFaj/Ek2J+Z4x9UKjdyAlUp9I/kuSLP+obykUEiVpnvQk2NUNUWVIKxSALrJ0cvisTGPTtjcmnndMG9mKlXz6C9klOaWM8gNbQ5wGdfSFSTf46S
*/