//          Copyright Oliver Kowalke 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTEXT_DETAIL_PREFETCH_H
#define BOOST_CONTEXT_DETAIL_PREFETCH_H

#include <cstddef>
#include <cstdint>

#include <boost/config.hpp>
#include <boost/predef.h>

#include <boost/context/detail/config.hpp>

#if BOOST_COMP_INTEL || BOOST_COMP_INTEL_EMULATED
#include <immintrin.h>
#endif

#if BOOST_COMP_MSVC && !defined(_M_ARM) && !defined(_M_ARM64)
#include <mmintrin.h>
#endif

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace context {
namespace detail {

#if BOOST_COMP_GNUC || BOOST_COMP_CLANG
#define BOOST_HAS_PREFETCH 1
BOOST_FORCEINLINE
void prefetch( void * addr) {
    // L1 cache : hint == 1
    __builtin_prefetch( addr, 1, 1);
}
#elif BOOST_COMP_INTEL || BOOST_COMP_INTEL_EMULATED
#define BOOST_HAS_PREFETCH 1
BOOST_FORCEINLINE
void prefetch( void * addr) {
    // L1 cache : hint == _MM_HINT_T0
    _mm_prefetch( (const char *)addr, _MM_HINT_T0);
}
#elif BOOST_COMP_MSVC && !defined(_M_ARM) && !defined(_M_ARM64)
#define BOOST_HAS_PREFETCH 1
BOOST_FORCEINLINE
void prefetch( void * addr) {
    // L1 cache : hint == _MM_HINT_T0
    _mm_prefetch( (const char *)addr, _MM_HINT_T0);
}
#endif

inline
void prefetch_range( void * addr, std::size_t len) {
#if defined(BOOST_HAS_PREFETCH)
    void * vp = addr;
    void * end = reinterpret_cast< void * >(
        reinterpret_cast< uintptr_t >( addr) + static_cast< uintptr_t >( len) );
    while ( vp < end) {
        prefetch( vp);
        vp = reinterpret_cast< void * >(
            reinterpret_cast< uintptr_t >( vp) + static_cast< uintptr_t >( prefetch_stride) );
    }
#endif
}

#undef BOOST_HAS_PREFETCH

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_CONTEXT_DETAIL_PREFETCH_H

/* prefetch.hpp
2hXfiwl6XGHm37ZHcr1/uXnm1Dk02kv0xvG5BQOVeZX+04ek5XTqT7bCPDTJzr8+40/eg3yG49DbR1p/BAfn+PvQ51L9+XcE1w0MTfAR/zF8U5YW8f3YlEGYbJ9COWo8jgHySrwMfTzB/b/c+hhaAjwBH3nuVAL+BOa9VSfo34chvRxtzM4lmTobAnxRZ7uWoM7Af4HOdgdaVFe0vBCPae0BeVB/qPi2TEcorvgExLe4I0v8/t+7ERgDQd0dXZJb92NKcPzOZYftDaVlGtyfQb3sZcoDefWZ8hhXAvcnyZ2ETt53RF6Hu3dJdv+aYI4e573M8I+UiA0Knr3fudTEl5u+2MQS8SMSj36qAuK0f0P0OS4quEMBN/tuL907g95Gw7AnuSTTX04xcuwr5bqf4ClfjJsqcVwWQkPf09a/WBZVkm66pOsOn99lfQ73aCpYwl8g/EK6g7Uj5YenUbjYW0+AZPr+6RmOd3rPkCcw3ue8uYcuasR7p2eW4N4O1k1XPNWeaFV1Aajf9zkHmNbleX/J81GS59ksg8Pz5P1RPJcR6+iGd0l3C+CJvlSAXyh5c9gKG6UwwsQ3Sotlb5fe4zUHdBDp3164DElebLs5P9r2fjGwJbYrhc8zNvZlsbEvOVoErwab07Dizpa4KYK7kP5aO9M+uR1H1wAdxwvr0BLDcwn42NNo7vrG0f4P/fVSqM9jBQfr+zKIr4R4+svx9WL315s3fhpK7NwfzWGVQFqhjfEXj8r0AWeNkbwKb4xbDXpoML5jjZG50MzbH6zxknYfc6/g1yD+ptHCG+IPlTzHxAZEx4x3WAng67yUloPw2yZzi4jTYmS275fGjcw2vs3o9t09kZ6fD4w/3NArKMwsi05sn8dwO8A/fEeouyRzTufm0bIXTvSCOrzJ2FWv6DBpcDdSOCV0SW7G7QNZ17i5UZGD5Ob4IyD+NJEV87oFbGWssaMjhZeDqw/APFUWmncghvh35E0S/JvGZfJ2usFy+UYJ6EzCqJfzjO0dK3r5dohtHVdi8emtD4Lhewq76z3EIM/PRolc0M6fVAJrv3LHMIar+c56vJe6uafHNVuyRpdHwn4H/CydB6BthjHXkMWS8VSKnnBOqsfNjhHfC/Zpx7mnmzK1dfBM0eskKDekd9YIcycj2HOlseci0eU50EdDmy8yuvu+qatKZ6zY6w+gzJUu8kaaLsz7wAzOeSE4FyoO5NHiXGTagNPHwJgiRC+XYhsBNLGNuExs8oixmW3eFcbvXilhB9cywftVTxzr07kK67zQsf3Mqwm2eAdnl1bUL44tX7Fo1bIaNrOwiHQf5Vqf54Bo1lmiNkb6mb8QmpNDabYm03tU6RP7SzdIOn0j+cYSwad4rW/YR3xjz8w+4gNjsvuI3F/w6PH0DUndO079w75kb8zvG2n/8Jemf9i93j2Q09cZV1kzQRlvC/+F/WkPRXpGTg3zmwO8CUD7bMXy/qbKFEGZ5FzPzSBT1JepwwgFMHM3tNU59081HYQpDfr1f0l7xHmCMMkoYZg7Gp3d3v6qJDPepcP4u8CX3Cj2TeVIZYd8871fl2TyfRr4OhxL97d+W8a2p33Re01f9PfGB9wH7d/1ps7eL2GXBw3bdr/UjPH/lO0nLR7n7SGghThI6xHJz7WQn8dMfh43+fkz5OdGE/cklMt19E1w1Tfr7y8Qf5HMSWO/5xmIfzwk/XPA+zqjyxckfB34P5TlL6YP9FIJ0Ja+huqVYKoz1jHq9VVJd30IHwd73/B5Hfhov83p+VbRc5adQr4JxjzfBL0IHsffMs7n8Rb0J/Dtmj545yn8vZfag+rqG5vmx2JcY9Mh8bHvioxV4WkZuX4=
*/