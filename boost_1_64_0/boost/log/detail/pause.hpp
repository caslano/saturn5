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
bjjzSeeRi/KKx7yYMJ1AQZTD9weyZnggRGORdDA+hVcW4M4fTbpudsFU2g3fsSuCoUmfacEE7SCqeCHO0WMAcIZyyG1muqimoofoq+l+OMW6wa84auqc876LeghuP6IjXsv9kenOMFNYyvmZndtjQvqJU7/Zuke4696gVyZ0V3aey2slnLvWSkxIPhlHjoovgmE7GX4eYGIB4r47KVOexaJerXfFN2XyoILW/EC17QL+s9DqNmLUn427+5eIXcFBtpG0swarSO4Zru3Lu7NfkKJNZYHTjlJehXP+Kajy3mNeXrQ7MDC0Je9VBgJKdX8EaP85eymw4xByYQCM3zg+JZalE0w3qWSlOVQ/CclIM50svwFcgP93+BbWrJjNXyx+EmiCShcuzR/LCBYOsQT7506bv41RQUOVsulvxxeV5FWE4UxGevCC8MZDs4g0saHbVHfoMKL7nF5U2TxL4cFLOiqRIvJ630niS4OpTNVp15j3yTAbWPhoJi2c2wDMRSVFgzbnJhiX//AekasPM/DR0UztWFtu2tsOasqeu7Ktxv7bcECfsGC6utwpYQ==
*/