
//          Copyright Oliver Kowalke 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if defined(BOOST_USE_UCONTEXT)
#include <boost/context/continuation_ucontext.hpp>
#elif defined(BOOST_USE_WINFIB)
#include <boost/context/continuation_winfib.hpp>
#else
#include <boost/context/continuation_fcontext.hpp>
#endif

/* continuation.hpp
LZGeM/rbrpXobCdcwNl2XYDvRz5d4XE9h6tvkdeZ4HRH1+k7iHwZZBPfQz2dwdgVIPFJvvCxJ0EWZwK+A/y+Arg1Z0BbUGD54Tga7IF/xSnCH89lUTfuj3vMlH1t/B1wCi8+9a3uImb65/IeS5FCEzgpi704Zak0NH+kcLEH5bHpku9yWceKy41DYXPDZwMbSJwHPSn59+AhwUfgfSamqf8C6JPH2fIYa/sjMU5hnzAxTQ0NE1/8A66TgW7bfwI=
*/