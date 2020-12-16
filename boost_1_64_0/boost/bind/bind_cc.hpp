//
//  bind/bind_cc.hpp - support for different calling conventions
//
//  Do not include this header directly.
//
//  Copyright (c) 2001 Peter Dimov and Multi Media Ltd.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
//  See http://www.boost.org/libs/bind/bind.html for documentation.
//

template<class R>
    _bi::bind_t<R, BOOST_BIND_ST R (BOOST_BIND_CC *) () BOOST_BIND_NOEXCEPT, _bi::list0>
    BOOST_BIND(BOOST_BIND_ST R (BOOST_BIND_CC *f) () BOOST_BIND_NOEXCEPT)
{
    typedef BOOST_BIND_ST R (BOOST_BIND_CC *F) () BOOST_BIND_NOEXCEPT;
    typedef _bi::list0 list_type;
    return _bi::bind_t<R, F, list_type> (f, list_type());
}

template<class R, class B1, class A1>
    _bi::bind_t<R, BOOST_BIND_ST R (BOOST_BIND_CC *) (B1) BOOST_BIND_NOEXCEPT, typename _bi::list_av_1<A1>::type>
    BOOST_BIND(BOOST_BIND_ST R (BOOST_BIND_CC *f) (B1) BOOST_BIND_NOEXCEPT, A1 a1)
{
    typedef BOOST_BIND_ST R (BOOST_BIND_CC *F) (B1) BOOST_BIND_NOEXCEPT;
    typedef typename _bi::list_av_1<A1>::type list_type;
    return _bi::bind_t<R, F, list_type> (f, list_type(a1));
}

template<class R, class B1, class B2, class A1, class A2>
    _bi::bind_t<R, BOOST_BIND_ST R (BOOST_BIND_CC *) (B1, B2) BOOST_BIND_NOEXCEPT, typename _bi::list_av_2<A1, A2>::type>
    BOOST_BIND(BOOST_BIND_ST R (BOOST_BIND_CC *f) (B1, B2) BOOST_BIND_NOEXCEPT, A1 a1, A2 a2)
{
    typedef BOOST_BIND_ST R (BOOST_BIND_CC *F) (B1, B2) BOOST_BIND_NOEXCEPT;
    typedef typename _bi::list_av_2<A1, A2>::type list_type;
    return _bi::bind_t<R, F, list_type> (f, list_type(a1, a2));
}

template<class R,
    class B1, class B2, class B3,
    class A1, class A2, class A3>
    _bi::bind_t<R, BOOST_BIND_ST R (BOOST_BIND_CC *) (B1, B2, B3) BOOST_BIND_NOEXCEPT, typename _bi::list_av_3<A1, A2, A3>::type>
    BOOST_BIND(BOOST_BIND_ST R (BOOST_BIND_CC *f) (B1, B2, B3) BOOST_BIND_NOEXCEPT, A1 a1, A2 a2, A3 a3)
{
    typedef BOOST_BIND_ST R (BOOST_BIND_CC *F) (B1, B2, B3) BOOST_BIND_NOEXCEPT;
    typedef typename _bi::list_av_3<A1, A2, A3>::type list_type;
    return _bi::bind_t<R, F, list_type>(f, list_type(a1, a2, a3));
}

template<class R,
    class B1, class B2, class B3, class B4,
    class A1, class A2, class A3, class A4>
    _bi::bind_t<R, BOOST_BIND_ST R (BOOST_BIND_CC *) (B1, B2, B3, B4) BOOST_BIND_NOEXCEPT, typename _bi::list_av_4<A1, A2, A3, A4>::type>
    BOOST_BIND(BOOST_BIND_ST R (BOOST_BIND_CC *f) (B1, B2, B3, B4) BOOST_BIND_NOEXCEPT, A1 a1, A2 a2, A3 a3, A4 a4)
{
    typedef BOOST_BIND_ST R (BOOST_BIND_CC *F) (B1, B2, B3, B4) BOOST_BIND_NOEXCEPT;
    typedef typename _bi::list_av_4<A1, A2, A3, A4>::type list_type;
    return _bi::bind_t<R, F, list_type>(f, list_type(a1, a2, a3, a4));
}

template<class R,
    class B1, class B2, class B3, class B4, class B5,
    class A1, class A2, class A3, class A4, class A5>
    _bi::bind_t<R, BOOST_BIND_ST R (BOOST_BIND_CC *) (B1, B2, B3, B4, B5) BOOST_BIND_NOEXCEPT, typename _bi::list_av_5<A1, A2, A3, A4, A5>::type>
    BOOST_BIND(BOOST_BIND_ST R (BOOST_BIND_CC *f) (B1, B2, B3, B4, B5) BOOST_BIND_NOEXCEPT, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
{
    typedef BOOST_BIND_ST R (BOOST_BIND_CC *F) (B1, B2, B3, B4, B5) BOOST_BIND_NOEXCEPT;
    typedef typename _bi::list_av_5<A1, A2, A3, A4, A5>::type list_type;
    return _bi::bind_t<R, F, list_type>(f, list_type(a1, a2, a3, a4, a5));
}

template<class R,
    class B1, class B2, class B3, class B4, class B5, class B6,
    class A1, class A2, class A3, class A4, class A5, class A6>
    _bi::bind_t<R, BOOST_BIND_ST R (BOOST_BIND_CC *) (B1, B2, B3, B4, B5, B6) BOOST_BIND_NOEXCEPT, typename _bi::list_av_6<A1, A2, A3, A4, A5, A6>::type>
    BOOST_BIND(BOOST_BIND_ST R (BOOST_BIND_CC *f) (B1, B2, B3, B4, B5, B6) BOOST_BIND_NOEXCEPT, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
{
    typedef BOOST_BIND_ST R (BOOST_BIND_CC *F) (B1, B2, B3, B4, B5, B6) BOOST_BIND_NOEXCEPT;
    typedef typename _bi::list_av_6<A1, A2, A3, A4, A5, A6>::type list_type;
    return _bi::bind_t<R, F, list_type>(f, list_type(a1, a2, a3, a4, a5, a6));
}

template<class R,
    class B1, class B2, class B3, class B4, class B5, class B6, class B7,
    class A1, class A2, class A3, class A4, class A5, class A6, class A7>
    _bi::bind_t<R, BOOST_BIND_ST R (BOOST_BIND_CC *) (B1, B2, B3, B4, B5, B6, B7) BOOST_BIND_NOEXCEPT, typename _bi::list_av_7<A1, A2, A3, A4, A5, A6, A7>::type>
    BOOST_BIND(BOOST_BIND_ST R (BOOST_BIND_CC *f) (B1, B2, B3, B4, B5, B6, B7) BOOST_BIND_NOEXCEPT, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)
{
    typedef BOOST_BIND_ST R (BOOST_BIND_CC *F) (B1, B2, B3, B4, B5, B6, B7) BOOST_BIND_NOEXCEPT;
    typedef typename _bi::list_av_7<A1, A2, A3, A4, A5, A6, A7>::type list_type;
    return _bi::bind_t<R, F, list_type>(f, list_type(a1, a2, a3, a4, a5, a6, a7));
}

template<class R,
    class B1, class B2, class B3, class B4, class B5, class B6, class B7, class B8,
    class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
    _bi::bind_t<R, BOOST_BIND_ST R (BOOST_BIND_CC *) (B1, B2, B3, B4, B5, B6, B7, B8) BOOST_BIND_NOEXCEPT, typename _bi::list_av_8<A1, A2, A3, A4, A5, A6, A7, A8>::type>
    BOOST_BIND(BOOST_BIND_ST R (BOOST_BIND_CC *f) (B1, B2, B3, B4, B5, B6, B7, B8) BOOST_BIND_NOEXCEPT, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
{
    typedef BOOST_BIND_ST R (BOOST_BIND_CC *F) (B1, B2, B3, B4, B5, B6, B7, B8) BOOST_BIND_NOEXCEPT;
    typedef typename _bi::list_av_8<A1, A2, A3, A4, A5, A6, A7, A8>::type list_type;
    return _bi::bind_t<R, F, list_type>(f, list_type(a1, a2, a3, a4, a5, a6, a7, a8));
}

template<class R,
    class B1, class B2, class B3, class B4, class B5, class B6, class B7, class B8, class B9,
    class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
    _bi::bind_t<R, BOOST_BIND_ST R (BOOST_BIND_CC *) (B1, B2, B3, B4, B5, B6, B7, B8, B9) BOOST_BIND_NOEXCEPT, typename _bi::list_av_9<A1, A2, A3, A4, A5, A6, A7, A8, A9>::type>
    BOOST_BIND(BOOST_BIND_ST R (BOOST_BIND_CC *f) (B1, B2, B3, B4, B5, B6, B7, B8, B9) BOOST_BIND_NOEXCEPT, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9)
{
    typedef BOOST_BIND_ST R (BOOST_BIND_CC *F) (B1, B2, B3, B4, B5, B6, B7, B8, B9) BOOST_BIND_NOEXCEPT;
    typedef typename _bi::list_av_9<A1, A2, A3, A4, A5, A6, A7, A8, A9>::type list_type;
    return _bi::bind_t<R, F, list_type>(f, list_type(a1, a2, a3, a4, a5, a6, a7, a8, a9));
}

/* bind_cc.hpp
T3ri1z2FdW6vziuuDNhTuJxDaXARnAMXQ7FDBa+Hl+l98+VwI7wSPqxyT8O18H24Dn4Ab4IRbsoD28KVsCO8BvaG18K+cA2cBm8072F0Hiic6Ap+L5Coey4nwTYwGQ6BrfT6TIHnwNPhWNueyqvMfEzuRTTd0+BS7/sG7a9egM3gbtgR1sAz4UvaD7wMZ8BX9DnjDZgP/wRnw1fhNfA1eK2G3wD/CNeqX98j6LxGGduD3iNkaj85Uvujc+BAOEr7n9FazjFwPBwLJ8NxcBocD3PgBDgLnqvtmgUXaLqVcDKsglPgBjgVboLnw7tgNrxP5X4DL4Q18CL4KszV56A8+BmcCb+C+fAoLFA9KIQN4CzYBM6G8bAIJsNc2AXOgT1gierHPKjjjc6XQ5dCjDfrdW/mW1SP79J6ulv76fvhuXATnKH+2XADrIBb4SXwPngZvN+MNzp/Db4eYrxpyyHL3w6eDtvDHjAN9oEd4HmwI5wCe8HpsIuerxtcAdP1OusOb4UZcKPKb1b/K5bf7HGs88tgglwX/nscD7PJlYYpV2WTWxXhL9feJlcdplyNn5zzHtEHw5SLjQtPLiNMuSybXLXbX26xvf7ClKsKU646TLmaMOUO2uT2BrTv+fb6a+4sl2evvzDlssKUKw1TrqoWuYoT2LObPZPNvt1HLPe5te9s3b7d4e7bPZwbluwrIv9r9u8+glt6RWSt+3hXXREZ1l7e99/9w+3nHe5e3tvI6/H2837hisj/yj29610Z+YPs683+/Kdsb+9t9/wb9vemXmx7fP9H7O+d+GnDk9rj+/BX7L99pKErE1eEW4fbgTuAS/wH58SV4Kpwj+P24ep9Tf+JG4crxVXhtuP24ep9Q95xBbgq3DbcXtxRXNpR+g1cAW4Vrhq3B+c6RhxcLq4K9zhuPy76W47jsnGLcZtwO3Ef4uK/IwyXhSvBrfqubo/wut//zu9ftP9f6aKyYmsHwO+9/1/HJJexv/O4fvNbpPPpynAPWfMW3zb2HCcVsmq/mEVf3q2T2B4sr7x80fwyXYsaIWstymz7W2l8Uu3ms/uL34rnkRlrZLJ4rmuux9yuTXKsE+VpwLHBMh+vocTDgIOmn2XiFrg6q13BLOI+KsdOE5tPRfrMv41j3vWez8h6QqsafbZrVkv4IFlHtc0l7+Rca2N5NzvaWr0c0TgKNGrAP1FNJI3OsTKf0G/+472SRoNQZbDZKJH8mz1VNohMivq9eW9oW9t3YutMI2T9SZl9nanaOvbUeYKuWaM+OWbq028dYJHudTYkkmdrmAYftuYNv223gZyRU+ZVCKMHjuvlNe4w+1zLCtRQ51p6wweJfy7y6e9Y/mMRcUZ+UVleqRhSF5mWHGsrMr9365o/TaOXhrNm98+Wf77Ll0bpzEJPEiJT7MuX2H7hHX6QjiIn+z+myLmaRNr3hSCu2ReC74dGT912PVX5jAD57Sr/otpnmkNVFtnW6XaR88VFePzespSa9PoHpLdD8x4TL3bQKhbb1srWSFrxxu7Ae+LvFvGGux0yHDPpt5NrJkFtou2XYz0l3YmyhrdwHu9VjA2kMySdv9FGatOM8Hwx0+6zKfSUyEyKCHXdjSP8k/1W+Cvq97WZ9if8kLbZ1+kh6X0r6W2NlfXKZMl/vwnaWo7TAuY6ay3niTXX2a3ijxb78da3cmsPvHWJso/Do4E2d2/A3w7/T7z7z6h9eHdz2qClx38JYefEefxpxIskLB73Hcf+QXgUf/fRNZY9lAfjSEfDrTj1abur9HgD5DslkbYt7hybHfrsWmz2ZNps9tCOPps9+KnjIBsvVTDQVsF6WCHpyLUqfccmc8xcj3J8izmu15g=
*/