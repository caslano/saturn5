/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2011 Helge Bahmann
 * Copyright (c) 2013 Tim Blechmann
 * Copyright (c) 2014, 2020 Andrey Semashev
 */
/*!
 * \file   atomic/detail/atomic_flag_impl.hpp
 *
 * This header contains implementation of \c atomic_flag.
 */

#ifndef BOOST_ATOMIC_DETAIL_ATOMIC_FLAG_IMPL_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_ATOMIC_FLAG_IMPL_HPP_INCLUDED_

#include <boost/assert.hpp>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/core_operations.hpp>
#include <boost/atomic/detail/wait_operations.hpp>
#include <boost/atomic/detail/aligned_variable.hpp>
#include <boost/atomic/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

/*
 * IMPLEMENTATION NOTE: All interface functions MUST be declared with BOOST_FORCEINLINE,
 *                      see comment for convert_memory_order_to_gcc in gcc_atomic_memory_order_utils.hpp.
 */

namespace boost {
namespace atomics {
namespace detail {

#if defined(BOOST_ATOMIC_DETAIL_NO_CXX11_CONSTEXPR_UNION_INIT) || defined(BOOST_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX)
#define BOOST_ATOMIC_NO_ATOMIC_FLAG_INIT
#else
#define BOOST_ATOMIC_FLAG_INIT {}
#endif

//! Atomic flag implementation
template< bool IsInterprocess >
struct atomic_flag_impl
{
    // Prefer 4-byte storage as most platforms support waiting/notifying operations without a lock pool for 32-bit integers
    typedef atomics::detail::core_operations< 4u, false, IsInterprocess > core_operations;
    typedef atomics::detail::wait_operations< core_operations > wait_operations;
    typedef typename core_operations::storage_type storage_type;

    static BOOST_CONSTEXPR_OR_CONST bool is_always_lock_free = core_operations::is_always_lock_free;
    static BOOST_CONSTEXPR_OR_CONST bool always_has_native_wait_notify = wait_operations::always_has_native_wait_notify;

    BOOST_ATOMIC_DETAIL_ALIGNED_VAR_TPL(core_operations::storage_alignment, storage_type, m_storage);

    BOOST_FORCEINLINE BOOST_ATOMIC_DETAIL_CONSTEXPR_UNION_INIT atomic_flag_impl() BOOST_NOEXCEPT : m_storage(0u)
    {
    }

    BOOST_FORCEINLINE bool is_lock_free() const volatile BOOST_NOEXCEPT
    {
        return is_always_lock_free;
    }

    BOOST_FORCEINLINE bool has_native_wait_notify() const volatile BOOST_NOEXCEPT
    {
        return wait_operations::has_native_wait_notify(m_storage);
    }

    BOOST_FORCEINLINE bool test(memory_order order = memory_order_seq_cst) const volatile BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_release);
        BOOST_ASSERT(order != memory_order_acq_rel);
        return !!core_operations::load(m_storage, order);
    }

    BOOST_FORCEINLINE bool test_and_set(memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return core_operations::test_and_set(m_storage, order);
    }

    BOOST_FORCEINLINE void clear(memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_consume);
        BOOST_ASSERT(order != memory_order_acquire);
        BOOST_ASSERT(order != memory_order_acq_rel);
        core_operations::clear(m_storage, order);
    }

    BOOST_FORCEINLINE bool wait(bool old_val, memory_order order = memory_order_seq_cst) const volatile BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_release);
        BOOST_ASSERT(order != memory_order_acq_rel);

        return !!wait_operations::wait(m_storage, static_cast< storage_type >(old_val), order);
    }

    BOOST_FORCEINLINE void notify_one() volatile BOOST_NOEXCEPT
    {
        wait_operations::notify_one(m_storage);
    }

    BOOST_FORCEINLINE void notify_all() volatile BOOST_NOEXCEPT
    {
        wait_operations::notify_all(m_storage);
    }

    BOOST_DELETED_FUNCTION(atomic_flag_impl(atomic_flag_impl const&))
    BOOST_DELETED_FUNCTION(atomic_flag_impl& operator= (atomic_flag_impl const&))
};

#if defined(BOOST_NO_CXX17_INLINE_VARIABLES)
template< bool IsInterprocess >
BOOST_CONSTEXPR_OR_CONST bool atomic_flag_impl< IsInterprocess >::is_always_lock_free;
template< bool IsInterprocess >
BOOST_CONSTEXPR_OR_CONST bool atomic_flag_impl< IsInterprocess >::always_has_native_wait_notify;
#endif

} // namespace detail
} // namespace atomics
} // namespace boost

#include <boost/atomic/detail/footer.hpp>

#endif // BOOST_ATOMIC_DETAIL_ATOMIC_FLAG_IMPL_HPP_INCLUDED_

/* atomic_flag_impl.hpp
cGdrKbX12oAR7TZ2Pj5VG/lZbJiFvJtPRg8uiA2/HRn5/OuKVv/m235SUwAgaKB4Teg0nDDm+c0X56QL0xGjZvbqfrlxTbHKz/NWfqxJtNkVvNMT+MCMcIW1sEDt/lMDQjY0zEJlsMUudb4Tj+WIyKS1AZzMqPAaFpMpa6yvmUnrWgg/0x+8XwrxxQXiNHMMww05n7A8fvtAfko3kTh8bhLttd4v/ENnFBzyek0flnTuExbbvunJq8u8+2xqEqvwlA1OhPeRWWfXevtxYbELmHrl7aelpMGspR/pCllwP6UOjlC3DJJWItdrqy1ZoiYM0t7i2jPDqYLt89zkGMZePByHbVgNUV9klJ7yKAATPl/WCUCgw8BA5RTyyJbosyMRt7pvhiGZhl4dNfTWfhhHhQ+OShSKHdX9EC4c/G8wYgkRCB0tqK3QJVGGNGptsKtDSwFsBgyHfoVdBOs5jmH9q2RowkTLa1hq1Aav+Bs7/V67dePAab7Po4EyjuNth6wMdDysACWi+oNjFuCTlGnx/cPzxzkfgzVVIIndvu67bzOxTbaOcwc91WoGKCHlNUiY1vrjSgMKzjiV52d6w0fe/qQdDFtRZsraXWC8vof2KjQiKGQmRj7ZZTgqzvTM1w/jJAU80NWXmUB2lbpkr7jfSN6no6EM5arwUudSRjhYlIeywHu/3grGpv/LRoQpnJPMnE71MtN7UmIF8qZ1qn3Ci9TX/VUH3eP4vurXl32PRCGnoLw2VSeh3p4Pw2Wjch5qpR3YBgKTP+HvYvDDuupejH0aVwNk2YnmJryL6CuBv4fx2L20QnFdNkhi90c/M2ORp+sZ83DLEKDniLDuQms9V2Vpv48mN8VLN39grnL3sy+hO6JNHjmxU91lBlOJQi2WlUeNjp+5S1Y8aROYUQOwVO/Pan/zPs8bHEFZRgLhZpVhP2QxBCsU+HLiGg5Msh3j1ZuxV9F5JHs65HIjEygAYxMtNhdOBrEx/Bm+izF/IPRIaMVoBhN8GrjZ1TZ2vDj3yhEZ+6R0qL9LfWzaxIRT74olQ0IAhk5cJcHa/K5FT59ASKUOnoHAL/FL1kcWtPsmJ70+HtD7HvB/cF1eXhQi4zutqqz00Y/psbQ9funHuAWNZdTaEo3ij7NfrfxZBX+/GXmPe4yYCfczyoo42AaNcNzNz8bYaRtg4SRpkXlSzMY3uzdTggXR5/ClAdpLj2DWavAL0wY+5Fr3JOedPNLrcvsOCAKc9Tmss6HbHyJ8m3AvQ4brD/ZbDUT2cfBtuCGLuzse/oWO1nfEFRDnrxCZO0VfdM5CUF2UvZ+qe0B635e5FEx13AKedjwdqdp9HQiGEVj3xj43Tdhm1C2egG7fbcWIFfM7MtfHuYbMADd62VCkAll+baegfpryQAbE2RPiqrbTOLp07NCloQYW3UdG8UZhZgNpAUNy4oisb15fDaDYefNE8+beHRp6+Q9AEBoNBBQRECzZiN42cIByDs2cjGgpOAQ++MabZu9yHZDmWGcwJWufJAN8AdPXpDrkYbBYSuIAJ8TAtebdrszng8v1U+l5xbkYbS0jEjjUFjiT6oQvgfysfUvN5bMeRy+t2v6QYEih/q7UVa9NCh0cj3HoQ1U8MHhLIkNXWgSk47NcUGiejm7dU488c4/SGGLlS9Ert292Gw2lOsZr6gQZrmnhaKdSWwACUsn4wT+CHRInv5juG3j6xYJtJm3iyKK9TjutMgKMTeAXJGxwHoEIVExvhjHHE3vc1H37ZlKXJa0N321CqZx655pam2hwoGkBGhMKDv/BLtgZIIDGmSMXvYuQ8CmAoExthW27NzRPYKjk6z/sggwHVELU/IPmyehTbwhUhDEg4JZgIEjGMcundBw3qNkRxkXbAqN6FQs1JftHog4xSsLtYMAquyk5LaTU74AEPKRRT18+uTK9x6F5ja6Mfa0k9bCr5nD5rY78dGohVyadF26C0/NEBav0S8gc3AwQfQaNL02imOa9CwgQoO8mVic3SSlRI1WKZgPJbbrtcMLvU9aolwmVcFQDJd1Py3vh4wSYqN+9FlEdikNKSevM9yhbf+UEy3EOFR4Sm+FEJZ2DNDPB3fiY3zkvQKB727g9bDBjZMx/rl0Al1HaRAoWYnOIiYjYSBgfiNwMzbggjpjKbeXudWaCzljMWYY80+ZCTvJaCeVxAMgoRfAeP/GhutSnvpgie36dnv4s81BQKZSAL45k/AwWaLBVQ3CnmRKyKCgOZxG/2404kATnaAFelcORclUVZ37LHP/pFSyZaM85/KJrOQzH8FNVpYl7axJcS2kKFuiO2bmTtiN3onLJsdN4m8HlL4IScnA4+AUoIKTf5Ti67Nq7XPeWtZmhGEmQuKHY7CIwnOF2IEWEeISHziGtuXfm3MKjfJ0MvXmzPaAmgeb0lcEg83ejMYZrUs0ehmDm+Sk5V5fD2uwSzF5oacWcRURsCK3jGgr4aIA4S7j8BZkz/ytG8jbRBIP/aI7ahDACyTAuGsWqPqtAORA0PBalZGWvm8cdkcSt6zTIt/LTEWmggHGR0BCTPqy7mrRQnu5IHzu+6Lm9/Xzy2IiBEluRFzUlMND7K2ThYKp+x/2FiOP/zRlJiEjbRNC7F1Cce6DPWi263DgCRoi/3kwwcgwBhh4FOiRmY7o8rY5D8gCf+CD4uDhV6M0XRajTgIvRfmOziptvkruBwUOE09ITCKnSr5ppVWGsMPSdZnUXwX/zbQ5Q/G5k1Zi9NbzthWC40M++SRfE8Cqx76vZTUL3epIAoGzIQE4Y8cn+89dL0mGFP7eVt5EYhoyUI8dm75cQKDvDo3s2c/7X9BWw4nXv99Whs+xXeGIORIiRk56BhhESEYOFAYKH7gwhDgkZz7fx3SoiFN6GHkUs42mNU7nT4tm1rGSvhkKuDg8gZoGfEf6wqj6+RJM8u4+Q+2+VMnZSjRK26KWo/QsCqxkQrbYhpOtyVuytg/tXnulw52vQAt+t7wFK4501M/YHMUBmbgvrqElGjcKsEVw0xyZl+sx1C98pjTcJMCjPOsEwFK54dOhH2q4prWzHihb94Pp0pWpbl0K1y7oyH6PX9I1BG4LRYhBqCA0+ExObMjNxEkSkGQym5jM/y6GTsuQNHA6KaooRpTauFVytkmaTyRW/Gift+AQqzVyAai/L5Ct9Sj6DROgeEvTZP3osT7D4wG4smeR6y/phdZcprSxhOn+mygUSXgXJw9pkMqXFtAg3YGIscMSGKjKfvWA/Bqcute0ZGCBg87sOrf/emxpFoVxumJMoVuHQOE3ICJ6GDWvTxB1q6YIEuWd9rcat572u+jqsCQA72/z4KCuuC22Sb5GNwV+P3z0j498XDct6xt2NAk5xZ8NbfGWGOl5bC31KL0mL18OOcIKpOoyAhwAFbz0ArRqFbgjV2pELW9vLJKIc/9uCBnsK/cwYgZHqg1GlpVHv71kYKScUfk1PyBO1JyOZOXK/VipiEDJEL3oD/R1CylRiMEF7aXnxYZME0uzm0d2zG75Y4qklDNohPwOfFBVkZK8AJBQyNPhv3U7hlZxJH0ocKIoje1v/xItYB3ZEez5Fo8wK6pjje5yGLG6Xt5FiOTbCA4ikZxoKAAw8jQy0Rsa2OCjNTbyPE8iO/s0Lsxfpy6S4Tef6BjJGG1SoT2DCD5xxx6vRFhNlyCZsfKTo2P2WC4f5G5Ao4CCABCys7nDYD84mawZNdF+Bdav9PJYjgN033qI2htSmy5BEfcbdnYPH7xuCnnPduL7TwBg3f6aTs7IciypU1QNQvvP4pLgST4rwD2iZamS3c2p8GKLMq3GhjX55IUCJgvXakC/VbigOXfo/sKYFAQClQR4twcGfRSXq7SRR9OT/PADY4K6UWTAPJZIhkGDdIuLKvWJPhEwaUSnI4A4qUG63y/z7D3SQP2qzPX7wtTpRwVvmkMllqYdvWGTc24Lj/QpSfAikti/pZm/jTw2JcSM1rlQA47NryMqGFFnSOQwLgFxKpCEyxFnGJLIjQgGkZAgUqJv9OM7iITP2DEEsfBFT03hpHVG+GZjAacCzCr8Qx6Ll3/xo9Kdl/BIQn2IKHGnUdAC/ALL6w/3660EU7pIOV7pvuNhsTkNHdPLw2laHEJlq5v51umUQJhZdq6yabThflg6RgzAAU1hEauzlhWdIlcAUFkkdLblpt4j19Pwa0ogLewZnCKEdUG+sUN4Wfm1rwbLbQTaLrlTgv7XPBU4d7BIRZQ9LJPZrI4ezQhSxxwivqKSERY8IUDgnKFPNshwbRHAwnpAfrQFDYOTUBwph4xZJeq/4w9TRfOIHA0/ph3nbCIa4Osz1C9tqn/WH0bZm06ZawQvvYoiBBLeH8zdOioWQ6xEHIDr/zP9b7YnnwQa9lV/v/7YfTrcQtwbG6mTzWRSms/wv1wLMxk5dukiwSIBIyqTeQmB4DlNk6dYMEzep31i6+gZJR1mFoV6C0zvPPGUsIU4d6SiloA9+L15z6LJwhSLGu0zE4Rdnb2s0RCCt24OhZy9aBrmPzmUWYCZc9zeTfpx8q1GRh95E35gw+B8IFgUshlIUbkQGAqUvQKRZgUEUoje/Y9vzC0+SBADGnGTbCtli3yc5DuLhv1MQ4L14hDJjXwrDjhnWAMzqEI859HMsWEht4NucAVkM77FKpocY0QxJHeI7DDANupMewbc9LINRaDiCzqx+l3/29XoVTKt6IJIcSFZirKMq6N1gcFl2VqFgRJgWc58UpI3IHjKOX/VcE1iNY+9TD7ci6GtkKdgmIHCC9p4dH6t6t+zpY+688VqXFfiVexuQNyYEW8aGEgCF/TvHiGVd0hRn1uEM5ZhC7ZL9xuOgp1diMqff8FpNdrcwu9fnNvu+mXkiRHFuBTaDbeLkhCvIu3bjYBRXnZLIFCXAaGGZuIvO6DxXtCYCEHQSxLHhjLtOMdIjcAR4idT17VExGwTAT+E0JQWFi0fUIAiuRKJcQDyq8aiQiXcSLLDKEqCZgU7uKffxYRocQdeYq1iTO7YIWpM707GwvlcDoAnB0cHeBongMLchpnm0XAgq5SGIt0/ox1h5badO48fxPPVpXnbTq5tgSzSiWPe1mmG2vkOwOewQ5MQmQAU0KDLlAr/0+W51eHIFaUcxDsF7/eeAVlhPnT3qBe8V43kExs7C9O4h0HKnGRgIDk9YFigSmT/emP8cyrLo3mXiOdL04IILxpGZrvzl6IjZVKh3ONzHIUBjoAwIouJQDxqFye7a9oI3lElpNcPLWcmA/tNxddznSRD8Xm+L4LqDNzQ3EdfwD93dALcnetrbwwpkuwjunC9G9E1zSU9ceH4IDLo2I3FIDys3DG418tUy6c0B8DwF0PyiHqXFqVQv0yJQiN2r/Pa1NoHxUD7hay78+NAR+1wnhiz1jyLf2fdINX2GRyQpHZVtmsZgOVkMXidsz+nXAe1C4+lP98kaE7orIRbsg9hjViZaIdEY/OXPb+t4CIYY/s6+4HNWmmeIBBEdlqnGtIyQiOHFGQ55X2dAbz71wDI+hb6d5+82jPB+zTsczo53OpCOi0UmlqQTjUKiiqCBce12auxJzH7/rOhz0vT0y8vsSqxS9W6z4lf+ditsfVgnrd5n/E8nM2jESGisHapboCwiZCx6pgfKRog9QO8+oYd/0vlzCXqlot9XD6n7bVq8dtvia7VvEPhEqlxxMe0rxiWv0uDfHBQfxA3wXogOoUL7XHTD7NxyYeAanHOwegFxCaPH0Hej3eD8+2iJDURTd6sbVfgxVV+xVdJZaVMbgWACtN9U/IeQxET0O0k7ByenpAUBGZnana0IBNZzf1MeTi6gVgGE7f73qfU2Sd65MHUz+t2At1mPX5Zc1XJKtInSS1gcJJGnvfnMeAy0DFlAbShiUF3Zf6Nottr3K/1cSxsrK2G6airq6uBwfIqisONJJ7Ua8Q0G6Qe+yuWVdXWzt4EMImZfPz9sL/cvfAGoP0DVh4O3zfVwhbA2AHrJ2BYItwQjTWtCDBwLQecYA8gB+WBGiJfCOY8AfM21nNJHQ1KCcwxjz8RRXkQMpcctR8OooFIX84zG4eD/afbumwHDsq5hfTgQrK2tlVMKGCQBX721ra6uIjbg4eEZC5DuRhX/IP8H30tOEJZjwyWQH0ANPFpIPdQWA/lJ8J/A4ku5whCK3JWkpKiWw2C7kLGV0PhcY2Nj7fy84jXGm5rOEpA+zVA/0WPb4DghnCb6kk8azOl7G8pnh+pYYjDtFbil3J1NQf/Cx8nJycvFhVVMkIzFk/I+MroUSIAEMP1dmSjMdw5JQmQ/EcMi66G4R3JJ/6diI2D21ieHJA+dTwW7/kTLycculkyhYEnRzIzcZw1cGZx0nGlRZ0k/d+H3jRonJX/c64TPZ3XYtsOjvolAvlLfYD0vxlH9sqenBqyKgaSnvb29p6MjIwikjQNSUYYB/J3ssN6u6ZhhzqwUBAaYVJ/ao1o/NUAEU1UCujEH/HiZeClIkwxValycHBwBXONyZQQsiFQomWjLtjmYsm19jycg9uwW57CY+Us4ZhfdyIVMT99kXaVABeHA2jOOTJO0uHhZdqL4f/14ihcHmXc0uwwARQOIh1rTRigJKjTAKI/qjDPCc1XGfPJ5NhJKkDKJyx0iDh4j41iYBCAuAVKAEJ0tCl6VvbujaLNF60oSecmLVHGECfa/GgPUh+k6caDQBgjyPfOXbu7OYpgajgAdZ+K9jAAKVBGlLyvhY0CJdF0AYqmERipQmJlcMgrjptQEGE1YkzSokLtpFWRYIIkJ0XVPwaFGXSU6zf1EpCos2br27l5d2dbW1oS1wVOIugytIP2o98t+fJn3AkT077UizgNx3AL6ChWFGzAWE8fO7IawxkIpqvQ00OBAFYLRhK015AdX6x8uYSOSU07qVI3pm4KEvfekhuuQhow7gAv5jh48tZVCNVTK0BffBVGWLF1+kZYeIUznTx7UqwMS4f21+OthUP+V0QX7uGXTvrbLPCJbFBQOECY/AKldrpho8K/EtDKsvUe3XAgNAv3SapoIVvnbunEh4uzqgrjNEATOcFCos+0pK/MOQ/BFfm0IwLsPQYAxPviRbGWdcaclqv5iD/KfaIGGlsWOrzlVy6sz/CJKkZJ4lC+YgoJWwaA9S8xrOEArbD05SXaCvZOUlJ32w791wgf4kGS8WwJRvn9boal/jnZc1wcc9P7yacuxsZwTKBwxY8Z2rD4dUYAwDpA+5GbRsiII0VDXOpERhuB+2VszUFTdN4L9OM8eqsROg5HcB73XRKTTv7fEUj6398clk/fu+3dy1Ic8a3IYBihqrkY3hBKAC1Qn9qBlT1vJLnmtOx7tEaIhHGaGHXTnyDhG9WAZrabMA8KJiylg488dz0zotFr52zvrzkFFi5qpZi2BZmOD1JYW867rfiwYZBPKCSlfO9Xwi0CR8d4SErOCQ5jasXXlPuu7/ccqn3mFv7qp8U+eJSATfJWRdqwGLGOPZ8W+vht9ELWMJoMxeoSmtt/fB/GimqA4ztB3UKKhcF0+JIbpeWus6nVrkp91wnDxzrglbRrehQSubioI1hDcW0PksZvDzEWTY+Q+Rz3ZFv7KVIEwKkworaHlncX6EZu4WIoKM2UR
*/