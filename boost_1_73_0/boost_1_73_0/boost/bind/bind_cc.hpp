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
5Bu0rIhfoBzRd99/CuiabKOPLkle+/QVV1CMJPsyWytxExto9dvw6u3bP+F32N/b3/PgmKWCJzA1PJ1zdePBUWhX/orZ7W1H8/cecAMs6RSqZrHQoGVkVkxxwO+JCHiqeQhMQ8h1oMQcf4gUTMwhEgmH/vnkajj+4MEqFkFMStYyBx3LPAkhZksOigdcLJ2OjCkDMkJxVB4KbVBhboRMO4jNwXC10KSD4FmiJbAlEwmbIxAzEBuT6YNuN8hVgtZ3QxnoblC634nNYuPJFRqxYGuQmQEjIdfcA9rpwUKGIqI7BgQXs3yeCB17W2sQKg27UoHmSUK6UE5w7czmMC3C49E2yNBiYeimZaoJahXLRW0jxpG0RLlKEQjjgJtCiWH2IE9Druxm63kJUcTUBvi7qdnaG4JM0Rho9qYwnDZhzrTQHnwazk7PL2fwqXdx0RvPruD8BHrjK1J2NhwfY+oFgingt5niGsEViEWWCB4WmL/u6ja6u3B0PJj23xP8NJYrDaez2WSKmWE3HFZoCgSInRoIuDLaBheTh9RgCWidAE9vRMopk2QeHHVLdd3GC5EGSR5yONImFLITv29U1ogtjjK0joZouSBW/psLxReIqCGSylGS8ifVl4MGVt2rDn5orI+sjxadENnx8Yb4
*/