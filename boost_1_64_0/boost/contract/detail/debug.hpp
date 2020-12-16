
#ifndef BOOST_CONTRACT_DETAIL_DEBUG_HPP_
#define BOOST_CONTRACT_DETAIL_DEBUG_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

// Usually, never #defined (so "debug" assertions always in code).
#ifdef BOOST_CONTRACT_DETAIL_NDEBUG
    #define BOOST_CONTRACT_DETAIL_DEBUG(cond) /* nothing */
#else
    #include <boost/assert.hpp>
    // Extra parenthesis around BOOST_ASSERT to be safe because its is a macro.
    #define BOOST_CONTRACT_DETAIL_DEBUG(cond) (BOOST_ASSERT(cond))
#endif

#endif // #include guard


/* debug.hpp
bBpFHqeCPGjcjiqP9ygfjBssj9OXoQ0bzGuIcGTPgOOZ+Q4TDGPxnFkI+zxKXyTpN0oULvXJXlbP6mB9fTA/ESdl4g/0L9N9st7B1rTQAbjuk7Udd5o9xCD0B/JNc5jT82cLT/w9cuRzSZtAVu77HtqYSYLZ77FW1mm/PPmY4c7VMnPnyvC6TceswFw+6pz3Qb3IO8pqO9Bw/urHjG3/QYVLn1xsYrN8SNst5bHd5wi/VE51Hqed7xvTcQMfMOk+kz4d0qhz7RuTn5D6Y6Z8xKQTJp0y6XWY1rGBvjGWjblzJXWTTPbHLcyVy8XLQC6Ci+36remTL0CfONgDBv5FsxbFjV/tMgMfMPCvGHifgV9u4Kcb+NdgnGo/IL821tKVy3B9DT4/fJWp055RvdrUYeHXmPIxw/O1Bh4x8OsNPGHg3zHwlIF/z8jkSoO/zvo+AV/P3ih+B/hgXpa5fguugcUEZzsJdTTd3QGdbceZy7PfBm5TmgB/tNDEUGKaE4pTcvb1MI17I3zUGBvsp7iuwxnfoPfl7jK4skYF4t5tcMsKRsb9JeEij4+WGB+nthvgVl/fa2hY2d1n4NZndr/WAT41W8eDBidojX5I+pTqkP6ANN5X8LK+OOTrdsP3H03bg/r8MdM262f7s/inZsj6pbhPUNriPkl5OAZrDfxpgCcD4H8x5WsMfJeB25gYu6G9lBe4Nv9V2vOCtofG+1sKs28b1I3hG3N3Z09X9rO1yZf91ktCH95U5N+UQh3PVi/mey9D+/Y4Ps18e1XGA+Vz/y8r4nWI61I74x+mn14XW0LKMZ29sM6vlDpcfRwzx/BwrbER3qA8vFd9U2GW1utGz3lVmlZcoa12sem/CVVwf1tovSh8TSSYa1+P+XY6ifJVtjpeCIftuMkEQzydcxbvEIIpXy7P8nWYgVuf6VurgJ6NiVySO2enVskYZViwPV8k9Aiu9JS+xhvkcTtFzvRPo64KPBvM54PwhA+kZZyWVMlbd6OPe1cwNZAMkVOJ4ufj2LcwoTtT6Ab7OXOLIHeYqzzOElqfUZ9nFdOgdvg+siOq+M4oFUsGxuU4kuAl3iCRDss5L47J4RDkfBDfkR10l4LUV7aAYnbg2aNF3rCm2R4pl+/pS+SNmqOq8J7s6GeyaWxwm3TOllZlff+z6W+cv3Oq/B+Ot7kyF+YJrtLA/cV8KUNt5zFzjJQpEzz1H5cyzXQyTM5YSRM0GR0g72FcfJClXOsgO0X1DBS+QTWX/UO9mTNSD/t+9eGNMXpTQPyMx4J8Sg+q/7k93Ic4jxZIe94p7amT9rx6DIGp76Kbh7O8UpoIZtpXQGm6drzf2bQlcufreOC15ABzCPw8/NM1Nu3hHnqit1jnPeDaeb+0CsqgTSdl7HpXSfgIt+t/lYHb9XY58IRnUJCnFcJTXHTPxwpzabp8pPkuQzPI5qgFPb/Z7LXqq8CulT27ygTTvzVwtyfGtKOL6bhJD5h0n0mfDmnch55/POxDAR4x6YRJp0x6nUk/YOIgPzc9u8bjGrp7OvowRo5hfIr2veBtMXuSUw3cyRPh7zHwucYOON3AnzTlQzhfWW7ovwjeF643NOeYvWWvji2AFymO+p2AhmtTkaHRb+qw+90zDdzu5QaUB4h7V4RxsImHIbA7KI/bavC4j4ahrocD4hMl/HlSMBPWipTR82ljY22GuqVfAsfHVrOmhKBdjg+1n3HP+T6cm1Tm86VSBsaILfOBAB1j7wzsQJ75zoK9tyDxfwhP9a1tm90XftiMlSB9e67gAP/8Q5zztI9E1pQP6yrFBTI61p6xOV/hIk/r//mUtkngehc6HXDH8kKQk8VFOX3G4OWNgHc=
*/