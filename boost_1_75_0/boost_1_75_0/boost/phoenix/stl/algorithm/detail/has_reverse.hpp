// Copyright 2005 Daniel Wallin.
// Copyright 2005 Joel de Guzman.
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Modeled after range_ex, Copyright 2004 Eric Niebler
///////////////////////////////////////////////////////////////////////////////
//
// has_reverse.hpp
//
/////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef BOOST_PHOENIX_HAS_REVERSE_EN_14_12_2004
#define BOOST_PHOENIX_HAS_REVERSE_EN_14_12_2004

#include "./is_std_list.hpp"

namespace boost
{
    // Specialize this for user-defined types
    template<typename T>
    struct has_reverse
        : is_std_list<T>
    {
    };
}

#endif

/* has_reverse.hpp
QU0YlHKhgOjW63GTcMb1U8AsHPkEalL6LxU5+Jfe3dIWNNxei0jZMFye0RU0PA27/qtCpEGb1we/IGJSNmMhgL7z2eZ/qVbIzt+Miq6zvxmgPPKCBoDEF6jJn/lxAVDebzjvtkWW4viGH/XZT79EPufTduLrCry67ZG/hjucxua/juez1n/4Cju/NeTbz3Vd9vy1ll+5vLaRCWJZPw48edNzN3ztleKa8ga0/Ihn6Tv3+m72ZfZWJ2uFkX3Xxt+QbwzIxeNZqudezxc49hkIMnka4m6iKVl6dTLK4u1ot0QZjzjJbuvUhVZm/iWBxsgxAvPWJjNQmN1SWjxiLZvK87EgOMx+ySAewSjPdb5MMT3OCRJbAJntDceK9beex3snFO2c2Vr422uGmSO7hy5ZUhBaAseft8JK/9auhf2S8gB6l/7saEzg+J+t5e+KBavU07xcIYE2DnetUmEagHBlaeDYpQAifMluSeigHUhgfi0DHGx1fr6+bLdEzPgv+sUj6gR4NKOfri/bLxkNAKVjb1cZp+s5QUD4NzDiq+v883WsxDYCK3AcMoBOpj9D/z0p3gCQ9W8a+bS1IQAxyhK5/nzaWh9Auv0NTNrfmvV8vfPzWdCD4m+6Shxs6WTqhI5Rvgp4xf/oKlexebycIXMjzCUMiApV+D4h5/LKI87firWNoo28jfI7oSQhO5GwNuU4WeJtJEgORsRiVZXa
*/