/*
Copyright 2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_ALIGN_DOWN_HPP
#define BOOST_ALIGN_ALIGN_DOWN_HPP

#include <boost/align/detail/align_down.hpp>
#include <boost/align/detail/not_pointer.hpp>

namespace boost {
namespace alignment {

template<class T>
BOOST_CONSTEXPR inline typename detail::not_pointer<T, T>::type
align_down(T value, std::size_t alignment) BOOST_NOEXCEPT
{
    return T(value & ~T(alignment - 1));
}

} /* alignment */
} /* boost */

#endif

/* align_down.hpp
fAMzvzYMcAwLC45hgQjPI0SUtwg1yPpCyq1OnVAp07fbM4TI+rj8j3Kp8yoRdHYyduFSPnHBWqXJz1gLgwamBLWqwQ8dCnHVrvEJdYwnBjmbZF3JLA3NFxpjuhbj0eMa8Pt84y5GXIzNVHENH8bbIL2NSszSg2kRptqKRwC7ms27tZB+tz/Tvqd2PTtSJofyf35PMdsdY/GZyrFNM8mlgg8O45Y87EIScVkFxVOVNQ8MvXkx63zxmVGx6cZ1LcqrLLGqoOLUFfH0BBb0T+JOkhCBrxo0cl82UymYdPnQpgXwpr+tvSk1r/1zqZb1D9zgspNq5PbAwdW2TN85GGZTsV8W8kM4dK6em/wBHRfG8OlLurMbxlKvHPg+s/JDsqwhX7mAtOaDfYjFZJqSmklu9/6HXGqaa0DK9UF8J1q+0Bc78di/7GIcamSlAQl8gZxJJwrW2NdW0MkofB9g4HxPQ7u15sF4veaoy0nllGTQlUciRU7NPbdZME9uEm06S/PhGEfvh7uWJLueGIwqP3q52OQC1Ky4+aC3PwxBrHLiGXk/Z6zamct6Jw49StdNoi4YRqtgxjVaB2Mn0YMGaexzQXg0+tOZDN55ztgPgh9ohMtz0xkM06ewy4W/PwhYuEy763uAoc3ZXCLVotb82M2lXVOtxZzNdsHZf2GiMpm1hRuh59HCGaZgW1L95hK1ugLIq2kmPBFHVrlkW2/D
*/