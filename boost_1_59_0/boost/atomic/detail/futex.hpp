/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2020 Andrey Semashev
 */
/*!
 * \file   atomic/detail/futex.hpp
 *
 * This header defines wrappers around futex syscall.
 *
 * http://man7.org/linux/man-pages/man2/futex.2.html
 * https://man.openbsd.org/futex
 */

#ifndef BOOST_ATOMIC_DETAIL_FUTEX_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_FUTEX_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(__linux__) || defined(__OpenBSD__) || defined(__NETBSD__) || defined(__NetBSD__)

#include <sys/syscall.h>

#if defined(SYS_futex)
#define BOOST_ATOMIC_DETAIL_SYS_FUTEX SYS_futex
#elif defined(SYS_futex_time64)
// On some 32-bit targets (e.g. riscv32) SYS_futex is not defined and instead SYS_futex_time64 is implemented,
// which is equivalent to SYS_futex but uses 64-bit time_t.
#define BOOST_ATOMIC_DETAIL_SYS_FUTEX SYS_futex_time64
#elif defined(__NR_futex)
// Some Android NDKs (Google NDK and older Crystax.NET NDK versions) don't define SYS_futex.
#define BOOST_ATOMIC_DETAIL_SYS_FUTEX __NR_futex
#elif defined(SYS___futex)
// NetBSD defines SYS___futex, which has slightly different parameters. Basically, it has decoupled timeout and val2 parameters:
// int __futex(int *addr1, int op, int val1, const struct timespec *timeout, int *addr2, int val2, int val3);
// https://ftp.netbsd.org/pub/NetBSD/NetBSD-current/src/sys/sys/syscall.h
// http://bxr.su/NetBSD/sys/kern/sys_futex.c
#define BOOST_ATOMIC_DETAIL_SYS_FUTEX SYS___futex
#define BOOST_ATOMIC_DETAIL_NETBSD_FUTEX
#endif

#if defined(BOOST_ATOMIC_DETAIL_SYS_FUTEX)

#include <cstddef>
#if defined(__linux__)
#include <linux/futex.h>
#else
#include <sys/futex.h>
#endif
#include <boost/atomic/detail/intptr.hpp>
#include <boost/atomic/detail/header.hpp>

#define BOOST_ATOMIC_DETAIL_HAS_FUTEX

#if defined(FUTEX_PRIVATE_FLAG)
#define BOOST_ATOMIC_DETAIL_FUTEX_PRIVATE_FLAG FUTEX_PRIVATE_FLAG
#elif defined(__ANDROID__)
// On Android, futex.h is lacking many definitions, but the actual Linux kernel supports the API in full.
#define BOOST_ATOMIC_DETAIL_FUTEX_PRIVATE_FLAG 128
#else
#define BOOST_ATOMIC_DETAIL_FUTEX_PRIVATE_FLAG 0
#endif

namespace boost {
namespace atomics {
namespace detail {

//! Invokes an operation on the futex
BOOST_FORCEINLINE int futex_invoke(void* addr1, int op, unsigned int val1, const void* timeout = NULL, void* addr2 = NULL, unsigned int val3 = 0) BOOST_NOEXCEPT
{
#if !defined(BOOST_ATOMIC_DETAIL_NETBSD_FUTEX)
    return ::syscall(BOOST_ATOMIC_DETAIL_SYS_FUTEX, addr1, op, val1, timeout, addr2, val3);
#else
    // Pass 0 in val2.
    return ::syscall(BOOST_ATOMIC_DETAIL_SYS_FUTEX, addr1, op, val1, timeout, addr2, 0u, val3);
#endif
}

//! Invokes an operation on the futex
BOOST_FORCEINLINE int futex_invoke(void* addr1, int op, unsigned int val1, unsigned int val2, void* addr2 = NULL, unsigned int val3 = 0) BOOST_NOEXCEPT
{
#if !defined(BOOST_ATOMIC_DETAIL_NETBSD_FUTEX)
    return ::syscall(BOOST_ATOMIC_DETAIL_SYS_FUTEX, addr1, op, val1, static_cast< atomics::detail::uintptr_t >(val2), addr2, val3);
#else
    // Pass NULL in timeout.
    return ::syscall(BOOST_ATOMIC_DETAIL_SYS_FUTEX, addr1, op, val1, static_cast< void* >(NULL), addr2, val2, val3);
#endif
}

//! Checks that the value \c pval is \c expected and blocks
BOOST_FORCEINLINE int futex_wait(void* pval, unsigned int expected) BOOST_NOEXCEPT
{
    return futex_invoke(pval, FUTEX_WAIT, expected);
}

//! Checks that the value \c pval is \c expected and blocks
BOOST_FORCEINLINE int futex_wait_private(void* pval, unsigned int expected) BOOST_NOEXCEPT
{
    return futex_invoke(pval, FUTEX_WAIT | BOOST_ATOMIC_DETAIL_FUTEX_PRIVATE_FLAG, expected);
}

//! Wakes the specified number of threads waiting on the futex
BOOST_FORCEINLINE int futex_signal(void* pval, unsigned int count = 1u) BOOST_NOEXCEPT
{
    return futex_invoke(pval, FUTEX_WAKE, count);
}

//! Wakes the specified number of threads waiting on the futex
BOOST_FORCEINLINE int futex_signal_private(void* pval, unsigned int count = 1u) BOOST_NOEXCEPT
{
    return futex_invoke(pval, FUTEX_WAKE | BOOST_ATOMIC_DETAIL_FUTEX_PRIVATE_FLAG, count);
}

//! Wakes all threads waiting on the futex
BOOST_FORCEINLINE int futex_broadcast(void* pval) BOOST_NOEXCEPT
{
    return futex_signal(pval, (~static_cast< unsigned int >(0u)) >> 1);
}

//! Wakes all threads waiting on the futex
BOOST_FORCEINLINE int futex_broadcast_private(void* pval) BOOST_NOEXCEPT
{
    return futex_signal_private(pval, (~static_cast< unsigned int >(0u)) >> 1);
}

//! Wakes the wake_count threads waiting on the futex pval1 and requeues up to requeue_count of the blocked threads onto another futex pval2
BOOST_FORCEINLINE int futex_requeue(void* pval1, void* pval2, unsigned int wake_count = 1u, unsigned int requeue_count = (~static_cast< unsigned int >(0u)) >> 1) BOOST_NOEXCEPT
{
    return futex_invoke(pval1, FUTEX_REQUEUE, wake_count, requeue_count, pval2);
}

//! Wakes the wake_count threads waiting on the futex pval1 and requeues up to requeue_count of the blocked threads onto another futex pval2
BOOST_FORCEINLINE int futex_requeue_private(void* pval1, void* pval2, unsigned int wake_count = 1u, unsigned int requeue_count = (~static_cast< unsigned int >(0u)) >> 1) BOOST_NOEXCEPT
{
    return futex_invoke(pval1, FUTEX_REQUEUE | BOOST_ATOMIC_DETAIL_FUTEX_PRIVATE_FLAG, wake_count, requeue_count, pval2);
}

} // namespace detail
} // namespace atomics
} // namespace boost

#include <boost/atomic/detail/footer.hpp>

#endif // defined(BOOST_ATOMIC_DETAIL_SYS_FUTEX)

#endif // defined(__linux__) || defined(__OpenBSD__) || defined(__NETBSD__) || defined(__NetBSD__)

#endif // BOOST_ATOMIC_DETAIL_FUTEX_HPP_INCLUDED_

/* futex.hpp
y3vhWfV9y0raLLXf4QcTJVmOuZgXHk+8MJ6kLfeOTnwOckoL0LJuqB5MCo87V1MvBzPPZg5qd69bpQIz4bY4YRkhJ3wm5L7HBiC9NJKXylE+ZliVXCp64PRCcEEuTK779NH9PYLt0fP3bOzazZNYDU9PX+8WtS/b2DFqr2gWsPeeVppy+Pg7GWQXTw4rwI7e7chmP5RgsN/7efnRehEd5lxGPh5bD3Rnfb7WvvVbUR7ibz+xM+N6ZMtq3Du1uzPJrWiKzQz2MIns4G5EmI4F6IBdXiDikSdIcZ1MNXS7onC8sZ7vxXWmOohiUuSRWyI8UveyaEWb6SbWJbIAbypjJMiQP/70HT/TvZwgo/5BaW36BjGfzXd+kqBbGjvhxrY3eubtoMjy3BL75zSWo/rV93IQXsqWy5iXqLB1DxZ4Is1cr621t/so4PKiQxBdzefQbKRIpjSQ13bKWX+8LUvFz5gltqnnDLhlX7qE311v6LT8pF1yjOVFaRO0IEeVGKAP6Kq9ssy8ODc64Nr70jm+cq6+JMfdNBkjDH7sHZugJ8DW8Cn3gWC0+0Z6X3stNYRo7IvfGdxJ2t2PtO7UT51476TTOZ1O4QpDCTLs53WDIbPqp/Q5vyaT2K9fCiLe3KS5t8/IT4ofdPqkdzK8v3I66hqrPJhxqA/67v7jnJXzrIH+E/ADcMZgjWDjBwBv7+hqttD3g+vS10S13BKsdqvuUS2G+jnibWwLitagCTB9qgn+xO3Rq1iPuWa3hTdfcXxXZs+e+HJHYnoVOV+Kb1DhhxTYo//fEhhzL58WRHxJIQbHREiituN8L2vSpZyKXEU4c3IuzeSR78RbjgXOMmndHomoViUXWckQJOinMzMlxgW1Apnb4zEL+W5eWKSx5tJMv1yUySCrSuC9fTGNqznA3OFtzaa9+yigfEMazEohlGT2WE+dHyZVyHVAeRiXkjtKIAE3rbAS2QC/w0FaFYfWh1moOq1kG9kgFrEDDyTKosoBZ1MOhwAqLx5ONgU7JiERaLmedjuYiycM2yFWLTXQ8DSYjijYxLAOKugGPqO3INSJaBGXd4s3TSwcTYzAPLtEBkKez6jrNa5xqZl7APyFKmLV8vE5gpP5R9sMuwThDLlH61DbL5OfEbOMmsfcioU5wNpq7VqFOVyGK533TeX4KgjaWhO7F/O0uSb4v0/aZDJ/53TmKRk1Q8z6OinA6WxWcu8b+s1iBsE59NvWJL2NlsvSem6FME8Hrga7TfEZNHfDGQPC23iv8BwNcqTHtwHpr3cTmHvIJDHKIEspSuJC5ORQCssDmmoo4vS/Je3DuW0Wgj/eDnGCMt+J+QRcStUXLfBSwEAr6qQoCF3ECTXOq9047lwpYmCGup+8pJ/a4iPj6RG3VVx3zrbwmAc5QMWttCxzNLBd1b47YvQtrpf74W0J5V3vXc4RNQdq4RcbwdYzfgpA43h7qhAfXObcaChvxsQTA0f7nFTJwLkTGokqIrW2ki8zYSkqZfKuDmzrQybuvdyqUxbHycd2tQBjmizXZJ6iu8cJ+huvVliGZHspBtclbujpgg1dMx7mpu+XDp4lEaN9bjg7K2lwXK76n+PW4jgGNlSOV6jdjDkJq13G8Yq8PiLxIZMp7gdRjy9fEyxmg7eMT+U0RE37MC5bWFUlqkPNK1H65X38jq6u5DtY5rqkEslc7mycJpfKyUbv3AK0N86Ov5UpiZGJVfnipdZWJSEQbyHeWHIkJL4nlddfj09o4UHnumQjvT34PU5u2cQMrJlbnLRoPGw4JfhBJETYJfSUD7CMy4m27LPdRvsEXHtQOC6yXVfnuU0+GIm6xD9A6GjzcW+POTmPf3h14Fbmcm1yPl0t8FBdFFe/4HFGYzb7QClLxVU5P2JfaByLpV3eqFA97jFte0yqnjFzsUBBm9vnN53XdXVb1dHx3q93hflpsHy4fEkZM+UmsrwcS001dTZFXfXy4hMtzf3W8N5oVdVJLG0FdYWeitoSh56unhJTtbWcrqiky27Zo1wxkdOdPE1FdcDew43PGfjjN7IRM1X1zypj1ccbSadrR1ZZR9vRmXHVuR0D+ps1VQzU9NoKSnzr+mx3RMu7wJrz+d7O8OSdRpOix5NGikaTH/YmFt3lln4YK2WXE+XlFZVVDMCKgzv55BYPtCPp/DZjB48d/Kf9xfoRs+Sbu+tPqmOQDAXDZmNV5VRlB8dEyuCfx2iAJ7HAsgq6kPkf0IaKVlKqWX6CQ9SPbenM5igdH47Kh7X8bJK7GzpMDaBW/MVusNRShXfpWpRftBQOdL+v9BT0qFo9TyvhBCqB8dIe03x5qyvemNj+vq28wVat6qEpck9ImBcfkKo+Xl5KG8J/YoarqKrpENHt5YHktxiYptBc4rzjt/0NHdi43tVWOeArrc0bil1YFO1CsNWheOX4RUm7qSfFxIXLnr5KS0dTUVXJswVZaroGcXXjUlpV97i3TcvPYpFUe1TB1Fazv/cjxSyWtX0yS5N0piJEQfrta6u9gDXfY42b0c5zeKNYEa++5FO8a9xHznXw9+F2u1dEFy9jPKHEOwML9D4o1nzpvnqJWN8Zuo8qbhbj/H3r47Dqaz69iqOFHb/SevDhzE1Z6eMif1YdXDoCuPkFA3yavDW/chN0HSwuJZnYi9aG7LXh8JnmpqoKMR6lUyJLTuaxH1gq7YvdIRdXAl3ee/ON2JUiFBr1I+/51Q3oq9GC3vWJ48a9JQ9lJY2WRJtOYiUbk4SbTmggrZLEm05pIDuWZBjshjiQ4I4fL4Q7kGoL2D0n5pMEvgf65AJvudhXSAVRwSMJX6G8p2B6RxlDAjFYa0yMI/LyCwLch1sKCSbJhA/GMDhSb+M3jCEXuhTfzAzE1b75NBC0mgHj1OdgzBzVXbbtzhyd+VqOfGYI3n0iLReiqWvU1bTF8Z3Z3sd2oH1ha1zmtkadVtwG6eRCYt4nOYqS+JkhnG0ZR0xNofFXe3FOQx7b3o5grXF0FFjxJtuGdZk6QgwUqfEjQxjbUo4Yrek6wmoKctVk84l4pSK2pByJySpxqttqjnitWSuC38jd4tvL4J0uLcvjoAeDtkmU5OfiGo0JNOUJX+ENkhmTLYqwJ4oPGalQyMfRb0ueonuk8wpnU0zE7w3BbYueonqkdQjpUdTEV227nL7wSOyQXSNZHmzf5jvlv/H3lmhKJNgmq0s8Im0XrOcnyUmYGNzbhjuluHnZEWk3SHhKfxPjLX+ZQDQYu015ynITci/lS9adKDCYo1LAvSiPGBdELgrLVirp0wBmI+FkTrb0jj1P1oJlKbMpl96Cdim9Kc/Ggmcpe1dJ4Pg1z7RcA8uxUPu0bQPPsaDXtF4Dx7Hw3bQva+yLUtEgVpEzi3di5kkD5n6e8ASvY4sgDoi1Xm81xGFOQdIXS3K/Q8wTPmDkzozJJTug4k6PyTM64OTOlstFOyD3xM+SKZksO3fnjs5+LV84cwCvJWQ2rdmQlDK16IyYJT1ywMudozYJ1ZCgNhVyTq4la2VOX1UQuW/oycwXki0lX1Ayw7Kfdk7XFpwtO5G3N322f3MO7kmiKwXMH9nvd+bqDNaTAhakzvz8XaknW+fb6tz56a/7F+cvPMk6w9dk1Ke192k8aTuj1+S+57pNt++vnhN6AnVlvxdczUDvB52TYNf+fDekugRpBuEcpS3eNj/joOCc6ZbTJ9A2T366ZH/mHOeWzieGX14/Fziduj9yjnFL4xNtW1Qzw7GfcU5/y+4Talvwffpq/+4c4pZkVc5tMnZfri3yWzHRjPx+yTnLLddDoK9kd77+jN0+4S39Q4yv/NU00X7sOeUty0PIo5RfQfeMwH7OObAt9lsJ9L5geqCgHI5RpqQMY9rKR/Ri5uiD0TevzmpfVJKMGERrGM0Fs5mMaTjNBa70atWpVbJZfVyqc63kGzHxnQtwMc7SMJsLcaGY/8cP7v/m1/UaSf0afq7weD0xJhCLxGo9m5VxGLWQtKaS7O8QDIQXGdkzo9+QLVKxp0cbGC1ysmfLvkFbJHfFzxgtfl925M4endUjZzyzCK/Wa1qnWZmUXLtojZgxMrzIy56j+h6qMkG1NuSIXG3MUoO+wihywdCVmScka1jOqKSeZSHtiK4pOGts3GCv7mzh5gjclUR7mMFwZKHfmqs9WHeYwSi1nnYh+YjGla01Xvej2nurRZcjT1eI9vjVPltT2kV6a4z25NUBWzO39zyLuke2rkjtqVWmV7V3ixBHgpfIFWZWC1pNMVVmSPUIRyhN8TaGGYsFR0yXnF6BNgbydSULM0c4l3ReMXwTem+AdakLI0cYlzRe0TYmNfUcCxlH9JfsXqE2Rt/rrhbujiAuSZbHXd/HLsg1RR6bEtXLL5QcsVxy3QX6DHUZ6tfbLRBe0t/F+Exc1hEtxB5RXrLchTwM+xp11wss5BwBm2KPzaAXBFM2g5XHOfdQsXR2X6q3DrjY2ifeuUOsxe39EOtgsuvNODXt4LL7oH2q1sFm93H51LWDb2LHdy3AbTvL3WwtxG1n1d1tLehqu9Pdbi30aufBnRDJPhLaI2zvjDH2B1XsyeM9Nr8/0Qj0qWCH/ycPEuAmrN5oojcjUW/oqYE3J9EH8VNFb1aij59OHbx5c3ooTyXvOfnT5DeUb068cQUCcgZLznA6gie2692pgWSxZ4veiDkjIze8/DnqP6A6EtRPQu7J9cas3OlrtiKvDX2ZBUJyhuW3Ss5YrtPu6bqCc8YmNvZOz65v7sF9SfSHgZsj1/3eXN3BIHYr9Yz2Ovmexpet+23Nl/nTr9cX7xna49f77HZpb+i9MbqT1wfs9tx+8Nzo3tv6InWn1uxendzdQNwLPiLXhLKtaHXF1OwhnSHco3RNAA8s8NNpjvANEwWprqK9b/JKEOjP2Z34YXbjdO/xCO4X392nv1vzQ/3GypvWL6v7w/q23UnzDY83nl9q96f1PaIfSDeuXUF+fW6nut4cT+/8egV2ck4mbrDupR8xntL9Pl79sLtxu/fqSn3q8dsWOMm5Ad6rP+I9ZT19eNr2O/HxFhDoQTpNEiGnYQqXTiAn11QiV50m12UmVz6VRCh8qxQzK2FJxxafLjVWuKsEV1Y0K2VJ3xi/JHXc0z2UfK8EXVYwK3lI5xLfJrVa+E0JqaxkVvqQ/iL+VuqhkPdHAB01VUihNzWdaGEpeuKt9CcJiB5aXCqEhJeFLSpUGJKwZRpSgTWsIrg0CBB+FsGsSrgU0SkDEkZFDtPuFoGsiunkBJSyKcUSykVbRRbTsNPh084Wb1VIx5JMJYuU0li108nGkoeLPKa9y4S0iFWlVKeFDsjLtMrjLYu4LeIbNLg1uUW5VblluXW5hbmVuaW1SLPos8iyaLMos4C6xLpU9MkMCSmSWNIjRdKF0kUjhSNFtIW0RRWFFUVWhRjTjdMu0xfTCNPR07LTY9NSB5gWyc4VzhnO7c6hziXOqc7NzrHONQ1abfJt+p6vPRU8JcpT5ySsilymPQ8MLILOwxoUl8htUgiTCRMJU7PjmiTkpeQl5aUnJCakJiQnpIESQCmgJFC6RqJGqkZSu2i+iKOQo6i5sLnIrdBmun3aa/puGno6dNrVIvQ8vkF5ieI4hT+FP54/mT+RP7UrriupK6ErpSv+UmJdal1yXdqriKiQqCinMKdIv1C/aL1wvUigUKCou9DnX7zmFkztnR9gTuUoQjalwYoiK8oypdOATC9KO6XVgGIjyjOlt/2ye5+YO0Iuv36ftC3CNr99n8QzQi+/eZ/sNsKXVB4ymCKQlPxUVENERKVPxM8hCps4BgOin1iReDNfAT08mApTkkkDHkW4n5FJJwqZrJ+KSSsKxaifk+n5HYZ+cofMd3TFYWWb7kyymcRy6DP98IqkphGa+SpJ4YuGMe9oh/t5mfRVwqDylVTCQzbJFektRapK0SL7DB3qOEUzaeTQSiJZ+tI26WpFMunHUfYizvpuNsEd8jRoGFBH+voNW1tEdGgY0FIjafuSN2kcGlvEKpHnI772XWy+cChokVyhU4vQ7qNxqGiRXWH4huwW0d63uknoUKNB/w3tKhK6L2iTRBE4F9ZomKUBJMTE6yMzLFggZ48U7zfadDgJXiDNRpcPL+ln2dQ8yXTX6yDWQweGp/bTbqqepC/Q6GHZhXH0a2/anMQsvFrD+B5+1Q+9KVyre4RMFJ5lmLpAz4+ZEybfb7bpdBJyreRN0YW5Hsa3qX2Sda13hCEQRtQvv2l2Enmtev/KF8svTKBf3zBnAYgYFkRKgZY2LLNbRw6nmYKhmcymmYqwmOTjCNGal0nGkYA3Irtd7MjS2roiZEvdnKA9YrPd5MjT2plJe7eD6Cjemrii+Y3ULbl9aHWH0FG+NXVF+xvZVfLdkIfj66btXPyEs533+PEFjjLfgERkSHGxydDDQdvgXAxYw6KOQgwpiadvPMJ4VQhfIaWKD5LtKJ6ae0TxqhFSxqZSDqLtSJ46nBp7RPCq8utlv8ohzqGSTzUbpDiV8UjRoUkdqt/hOtVp1cmmnEil3YZyLNKhACbJJ1Ts4LaqVSdiDUXuJO4obyvvzGzP7LBss+zUb1OcLp5ynbaeepzenEKdhpwq3ZB6pHnXduh0iXSpdMl06XQJdSl1SXVpdYnpkejT6lPqA9eJ/+XboyNXg1fDFTt323c70NvQO6Hbnh7RHWp6lDWpRCkcg7GDeDuyp6Y3ijdMNw43sB6R94X3SfcN91H3lfeZ9x33gff59wn3dfcR9+X36R2qvrq+wr7KvtK+2r7ia6+6abspu4F+xH5Udqlug0RDPDu6p7Y3RjdoN8o3LDdON3A30je0N1Y3eB6x91X3WfedHeqPgo+Kj5KPmo+ij6qPso+6j8KPyo/Sa5TfU5EGoXeShNDLGUNoE0jRNRXRVafQdZnQlU+oEZLeSsVMS1hUgrZDmrGkXSm4oqJpKYsq0PZCc5x0KVW9qc5NRZAsJ2VWFDmtelDsrO5JxZesJ2VXFDutflCyTQ3WrxQoJTGk3islEk7DVNTtGMX8mksNpxRe6WVSi1IpOjVskYYkTVAyybCCyTtmHZy8KBUx6oJkpmENk0xmvbRcGZVX1J+oE5Oph1V23E3SHQMd85l10/KSqFiSNaXKlIpH1XapnJIdTbKZ9csUMKmSpZLrFLgky9Qsk7SK5DQL6dTk1OQU5VTllOXUxxXGVcaVUqjMaPeo9mj2qPdosaiwaKSTI5NMhvuHHXdQd5R2mHccd17uSO3Q7Fju4JqEOFY5Zjl2OgY5FjgmOtbXKbWKahatlK8Ur1Sv5K2UrRStVK0UrFRUqn1T/qZOqECoQqh0mMw2rGWSVafnobGYy5tvrcJOnZEsnvwp6VMyZRL9cOKw8vDMMMtw/bDT8Nkw3HDksPTwyDDtcMWw1bDajssOwo7sDv2OzQ6BScZp9Wn2addpwGlene5innfhkYordXtybLJ8knzyRNJEMjAJmFyTVJNsl8Q33DzsNnw1rLcDvSO+Q7ljtoO1o77DseO2g7QjvwM0yanT58rFV1GiUSwbVqmWKlcwUVVUVVV2+awg+7mEXQGvnMuSrLF2ScSmnF05o4J+NsWStrFxScymokl5uaK1XP8411WFpyzrM4Ol
*/